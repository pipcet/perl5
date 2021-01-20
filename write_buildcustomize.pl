#!./miniperl -w

use strict;

my $osname = $^O;
my $file = 'lib/buildcustomize.pl';

if ( @ARGV % 2 ) {
    my $dir = shift;
    chdir $dir or die "Can't chdir '$dir': $!";
    unshift @INC, 'lib';
}

if ( @ARGV ) {
    # Used during cross-compilation.
    $osname = $ARGV[1];
}

# To clarify, this isn't the entire suite of modules considered "toolchain"
# It's not even all modules needed to build ext/
# It's just the source paths of the (minimum complete set of) modules in ext/
# needed to build the nonxs modules
# After which, all nonxs modules are in lib, which was always sufficient to
# allow miniperl to build everything else.
# Getopt::Long is here because it's used by podlators, which is one of the
# nonxs modules.
# Term::ReadLine is not here for building but for allowing the debugger to
# run under miniperl when nothing but miniperl will build :-(.
# Text::ParseWords is required in ExtUtils::Liblist::Kid

my @toolchain = qw(cpan/AutoLoader/lib
		   dist/Carp/lib
		   dist/PathTools dist/PathTools/lib
		   cpan/ExtUtils-Install/lib
		   cpan/ExtUtils-MakeMaker/lib
		   cpan/ExtUtils-Manifest/lib
		   cpan/File-Path/lib
		   ext/re
		   dist/Term-ReadLine/lib
                   dist/Exporter/lib
                   ext/File-Find/lib
                   cpan/Text-Tabs/lib
		   dist/constant/lib
		   cpan/version/lib
		   cpan/Getopt-Long/lib
		   cpan/Text-ParseWords/lib
                   cpan/ExtUtils-PL2Bat/lib
		   );

# These are for XS building on Win32, since nonxs and xs build simultaneously
# on Win32 if parallel building
push @toolchain, qw(
	dist/ExtUtils-ParseXS/lib
	cpan/parent/lib
	cpan/ExtUtils-Constant/lib
) if $^O eq 'MSWin32';
push @toolchain, 'ext/VMS-Filespec/lib' if $^O eq 'VMS';

unshift @INC, @toolchain;
require File::Spec::Functions;
require Cwd;

my $cwd  = Cwd::getcwd();

defined $cwd
  or die "$0: Can't determine current working directory\n";

# lib must be last, as the toolchain modules write themselves into it
# as they build, and it's important that @INC order ensures that the partially
# written files are always masked by the complete versions.

my $inc = join ",\n        ",
    map { "q\0$_\0" }
    (map {File::Spec::Functions::rel2abs($_, $cwd)} (
# faster build on the non-parallel Win32 build process
        $^O eq 'MSWin32' ? ('lib', @toolchain ) : (@toolchain, 'lib')
    ));

open my $fh, '>', $file
    or die "Can't open $file: $!";

my $error;

# If any of the system's build tools are written in Perl, then this module
# may well be loaded by a much older version than we are building. So keep it
# as backwards compatible as is easy.
print $fh <<"EOT" or $error = "Can't print to $file: $!";
#!perl

#   !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
#   This file is generated by write_buildcustomize.pl.
#   Any changes made here will be lost!

# We are miniperl, building extensions
# Replace the first entry of \@INC ("lib") with the list of
# directories we need.
splice(\@INC, 0, 1, $inc);
\$^O = '$osname';
1;
__END__
EOT

if ($error) {
    close $fh
        or warn "Can't unlink $file after error: $!";
} else {
    if (close $fh) {
        do $file and exit;
        $error = "Can't load generated $file: $@";
    } else {
        $error = "Can't close $file: $!";
    }
}

# It's going very wrong, so try to remove the botched file.

unlink $file
    or warn "Can't unlink $file after error: $!";
die $error;

# ex: set ts=8 sts=4 sw=4 et:
