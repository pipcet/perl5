/* -*- buffer-read-only: t -*-
 *
 *    reentr.h
 *
 *    Copyright (C) 2002, 2003, 2005, 2006 by Larry Wall and others
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 *  !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
 *  This file is built by reentr.pl from data in reentr.pl.
 */

#ifndef REENTR_H
#define REENTR_H

/* If compiling for a threaded perl, we will macro-wrap the system/library
 * interfaces (e.g. getpwent()) which have threaded versions
 * (e.g. getpwent_r()), which will handle things correctly for
 * the Perl interpreter, but otherwise (for XS) the wrapping does
 * not take place.  See L<perlxs/Thread-aware system interfaces>.
 */

#ifndef PERL_REENTR_API
# if defined(PERL_CORE) || defined(PERL_EXT)
#  define PERL_REENTR_API 1
# else
#  define PERL_REENTR_API 0
# endif
#endif

#ifdef USE_REENTRANT_API

#ifdef PERL_CORE
#   define PL_REENTRANT_RETINT PL_reentrant_retint
#endif

/* Deprecations: some platforms have the said reentrant interfaces
 * but they are declared obsolete and are not to be used.  Often this
 * means that the platform has threadsafed the interfaces (hopefully).
 * All this is OS version dependent, so we are of course fooling ourselves.
 * If you know of more deprecations on some platforms, please add your own
 * (by editing reentr.pl, mind!) */

#ifdef __hpux
#   undef HAS_CRYPT_R
#   undef HAS_DRAND48_R
#   undef HAS_ENDGRENT_R
#   undef HAS_ENDPWENT_R
#   undef HAS_GETGRENT_R
#   undef HAS_GETPWENT_R
#   undef HAS_SETLOCALE_R
#   undef HAS_SRAND48_R
#   undef HAS_STRERROR_R
#   define NETDB_R_OBSOLETE
#endif

#if defined(__osf__) && defined(__alpha) /* Tru64 aka Digital UNIX */
#   undef HAS_CRYPT_R
#   undef HAS_STRERROR_R
#   define NETDB_R_OBSOLETE
#endif

#ifdef NETDB_R_OBSOLETE
#   undef HAS_ENDHOSTENT_R
#   undef HAS_ENDNETENT_R
#   undef HAS_ENDPROTOENT_R
#   undef HAS_ENDSERVENT_R
#   undef HAS_GETHOSTBYADDR_R
#   undef HAS_GETHOSTBYNAME_R
#   undef HAS_GETHOSTENT_R
#   undef HAS_GETNETBYADDR_R
#   undef HAS_GETNETBYNAME_R
#   undef HAS_GETNETENT_R
#   undef HAS_GETPROTOBYNAME_R
#   undef HAS_GETPROTOBYNUMBER_R
#   undef HAS_GETPROTOENT_R
#   undef HAS_GETSERVBYNAME_R
#   undef HAS_GETSERVBYPORT_R
#   undef HAS_GETSERVENT_R
#   undef HAS_SETHOSTENT_R
#   undef HAS_SETNETENT_R
#   undef HAS_SETPROTOENT_R
#   undef HAS_SETSERVENT_R
#endif

#ifdef I_PWD
#   include <pwd.h>
#endif
#ifdef I_GRP
#   include <grp.h>
#endif
#ifdef I_NETDB
#   include <netdb.h>
#endif
#ifdef I_STDLIB
#   include <stdlib.h>	/* drand48_data */
#endif
#ifdef I_CRYPT
#   ifdef I_CRYPT
#       include <crypt.h>
#   endif
#endif
#ifdef HAS_GETSPNAM_R
#   ifdef I_SHADOW
#       include <shadow.h>
#   endif
#endif

#define REENTRANT_PROTO_B_B	1
#define REENTRANT_PROTO_B_BI	2
#define REENTRANT_PROTO_B_BW	3
#define REENTRANT_PROTO_B_CCD	4
#define REENTRANT_PROTO_B_CCS	5
#define REENTRANT_PROTO_B_IBI	6
#define REENTRANT_PROTO_B_IBW	7
#define REENTRANT_PROTO_B_SB	8
#define REENTRANT_PROTO_B_SBI	9
#define REENTRANT_PROTO_I_BI	10
#define REENTRANT_PROTO_I_BW	11
#define REENTRANT_PROTO_I_CCSBWR	12
#define REENTRANT_PROTO_I_CCSD	13
#define REENTRANT_PROTO_I_CII	14
#define REENTRANT_PROTO_I_CIISD	15
#define REENTRANT_PROTO_I_CSBI	16
#define REENTRANT_PROTO_I_CSBIR	17
#define REENTRANT_PROTO_I_CSBWR	18
#define REENTRANT_PROTO_I_CSBWRE	19
#define REENTRANT_PROTO_I_CSD	20
#define REENTRANT_PROTO_I_CWISBWRE	21
#define REENTRANT_PROTO_I_CWISD	22
#define REENTRANT_PROTO_I_D	23
#define REENTRANT_PROTO_I_H	24
#define REENTRANT_PROTO_I_IBI	25
#define REENTRANT_PROTO_I_IBW	26
#define REENTRANT_PROTO_I_ICBI	27
#define REENTRANT_PROTO_I_ICSBWR	28
#define REENTRANT_PROTO_I_ICSD	29
#define REENTRANT_PROTO_I_ID	30
#define REENTRANT_PROTO_I_IISD	31
#define REENTRANT_PROTO_I_ISBWR	32
#define REENTRANT_PROTO_I_ISD	33
#define REENTRANT_PROTO_I_LISBI	34
#define REENTRANT_PROTO_I_LISD	35
#define REENTRANT_PROTO_I_LS	36
#define REENTRANT_PROTO_I_SB	37
#define REENTRANT_PROTO_I_SBI	38
#define REENTRANT_PROTO_I_SBIE	39
#define REENTRANT_PROTO_I_SBIH	40
#define REENTRANT_PROTO_I_SBIR	41
#define REENTRANT_PROTO_I_SBWR	42
#define REENTRANT_PROTO_I_SBWRE	43
#define REENTRANT_PROTO_I_SD	44
#define REENTRANT_PROTO_I_ST	45
#define REENTRANT_PROTO_I_St	46
#define REENTRANT_PROTO_I_TISD	47
#define REENTRANT_PROTO_I_TS	48
#define REENTRANT_PROTO_I_TSBI	49
#define REENTRANT_PROTO_I_TSBIR	50
#define REENTRANT_PROTO_I_TSBWR	51
#define REENTRANT_PROTO_I_TSR	52
#define REENTRANT_PROTO_I_TsISBWRE	53
#define REENTRANT_PROTO_I_UISBWRE	54
#define REENTRANT_PROTO_I_iS	55
#define REENTRANT_PROTO_I_lS	56
#define REENTRANT_PROTO_I_uISBWRE	57
#define REENTRANT_PROTO_S_CBI	58
#define REENTRANT_PROTO_S_CCSBI	59
#define REENTRANT_PROTO_S_CIISBIE	60
#define REENTRANT_PROTO_S_CSBI	61
#define REENTRANT_PROTO_S_CSBIE	62
#define REENTRANT_PROTO_S_CWISBIE	63
#define REENTRANT_PROTO_S_CWISBWIE	64
#define REENTRANT_PROTO_S_ICSBI	65
#define REENTRANT_PROTO_S_ISBI	66
#define REENTRANT_PROTO_S_LISBI	67
#define REENTRANT_PROTO_S_SBI	68
#define REENTRANT_PROTO_S_SBIE	69
#define REENTRANT_PROTO_S_SBW	70
#define REENTRANT_PROTO_S_TISBI	71
#define REENTRANT_PROTO_S_TS	72
#define REENTRANT_PROTO_S_TSBI	73
#define REENTRANT_PROTO_S_TSBIE	74
#define REENTRANT_PROTO_S_TWISBIE	75
#define REENTRANT_PROTO_V_D	76
#define REENTRANT_PROTO_V_H	77
#define REENTRANT_PROTO_V_ID	78

/* Defines for indicating which special features are supported. */

/* The getgrent getgrgid getgrnam using buffer? */

#if defined(HAS_GETGRENT_R) && (GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBWR || GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBIR || GETGRENT_R_PROTO == REENTRANT_PROTO_S_SBW || GETGRENT_R_PROTO == REENTRANT_PROTO_S_SBI || GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBI || GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBIH)
#   define GETGRENT_R_HAS_BUFFER
#else
#   undef  GETGRENT_R_HAS_BUFFER
#endif
#if defined(HAS_GETGRGID_R) && (GETGRGID_R_PROTO == REENTRANT_PROTO_I_TSBWR || GETGRGID_R_PROTO == REENTRANT_PROTO_I_TSBIR || GETGRGID_R_PROTO == REENTRANT_PROTO_I_TSBI || GETGRGID_R_PROTO == REENTRANT_PROTO_S_TSBI)
#   define GETGRGID_R_HAS_BUFFER
#else
#   undef  GETGRGID_R_HAS_BUFFER
#endif
#if defined(HAS_GETGRNAM_R) && (GETGRNAM_R_PROTO == REENTRANT_PROTO_I_CSBWR || GETGRNAM_R_PROTO == REENTRANT_PROTO_I_CSBIR || GETGRNAM_R_PROTO == REENTRANT_PROTO_S_CBI || GETGRNAM_R_PROTO == REENTRANT_PROTO_I_CSBI || GETGRNAM_R_PROTO == REENTRANT_PROTO_S_CSBI)
#   define GETGRNAM_R_HAS_BUFFER
#else
#   undef  GETGRNAM_R_HAS_BUFFER
#endif

/* Any of the getgrent getgrgid getgrnam using buffer? */

#if (defined(GETGRENT_R_HAS_BUFFER) || defined(GETGRGID_R_HAS_BUFFER) || defined(GETGRNAM_R_HAS_BUFFER))
#   define USE_GRENT_BUFFER
#else
#   undef  USE_GRENT_BUFFER
#endif

/* The getgrent getgrgid getgrnam using ptr? */

#if defined(HAS_GETGRENT_R) && (GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBWR || GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBIR)
#   define GETGRENT_R_HAS_PTR
#else
#   undef  GETGRENT_R_HAS_PTR
#endif
#if defined(HAS_GETGRGID_R) && (GETGRGID_R_PROTO == REENTRANT_PROTO_I_TSBWR || GETGRGID_R_PROTO == REENTRANT_PROTO_I_TSBIR)
#   define GETGRGID_R_HAS_PTR
#else
#   undef  GETGRGID_R_HAS_PTR
#endif
#if defined(HAS_GETGRNAM_R) && (GETGRNAM_R_PROTO == REENTRANT_PROTO_I_CSBWR || GETGRNAM_R_PROTO == REENTRANT_PROTO_I_CSBIR)
#   define GETGRNAM_R_HAS_PTR
#else
#   undef  GETGRNAM_R_HAS_PTR
#endif

/* Any of the getgrent getgrgid getgrnam using ptr? */

#if (defined(GETGRENT_R_HAS_PTR) || defined(GETGRGID_R_HAS_PTR) || defined(GETGRNAM_R_HAS_PTR))
#   define USE_GRENT_PTR
#else
#   undef  USE_GRENT_PTR
#endif

/* The getpwent getpwnam getpwuid using ptr? */

#if defined(HAS_GETPWENT_R) && (GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBWR || GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBIR)
#   define GETPWENT_R_HAS_PTR
#else
#   undef  GETPWENT_R_HAS_PTR
#endif
#if defined(HAS_GETPWNAM_R) && (GETPWNAM_R_PROTO == REENTRANT_PROTO_I_CSBWR || GETPWNAM_R_PROTO == REENTRANT_PROTO_I_CSBIR)
#   define GETPWNAM_R_HAS_PTR
#else
#   undef  GETPWNAM_R_HAS_PTR
#endif
#if defined(HAS_GETPWUID_R) && (GETPWUID_R_PROTO == REENTRANT_PROTO_I_TSBWR || GETPWUID_R_PROTO == REENTRANT_PROTO_I_TSBIR)
#   define GETPWUID_R_HAS_PTR
#else
#   undef  GETPWUID_R_HAS_PTR
#endif

/* Any of the getpwent getpwnam getpwuid using ptr? */

#if (defined(GETPWENT_R_HAS_PTR) || defined(GETPWNAM_R_HAS_PTR) || defined(GETPWUID_R_HAS_PTR))
#   define USE_PWENT_PTR
#else
#   undef  USE_PWENT_PTR
#endif

/* The getspent getspnam using ptr? */

#if defined(HAS_GETSPNAM_R) && (GETSPNAM_R_PROTO == REENTRANT_PROTO_I_CSBWR)
#   define GETSPNAM_R_HAS_PTR
#else
#   undef  GETSPNAM_R_HAS_PTR
#endif

/* Any of the getspent getspnam using ptr? */

#if (defined(GETSPENT_R_HAS_PTR) || defined(GETSPNAM_R_HAS_PTR))
#   define USE_SPENT_PTR
#else
#   undef  USE_SPENT_PTR
#endif

/* The getgrent getgrgid getgrnam setgrent endgrent using fptr? */

#if defined(HAS_GETGRENT_R) && (GETGRENT_R_PROTO == REENTRANT_PROTO_I_SBIH)
#   define GETGRENT_R_HAS_FPTR
#else
#   undef  GETGRENT_R_HAS_FPTR
#endif
#if defined(HAS_SETGRENT_R) && (SETGRENT_R_PROTO == REENTRANT_PROTO_I_H || SETGRENT_R_PROTO == REENTRANT_PROTO_V_H)
#   define SETGRENT_R_HAS_FPTR
#else
#   undef  SETGRENT_R_HAS_FPTR
#endif
#if defined(HAS_ENDGRENT_R) && (ENDGRENT_R_PROTO == REENTRANT_PROTO_I_H || ENDGRENT_R_PROTO == REENTRANT_PROTO_V_H)
#   define ENDGRENT_R_HAS_FPTR
#else
#   undef  ENDGRENT_R_HAS_FPTR
#endif

/* Any of the getgrent getgrgid getgrnam setgrent endgrent using fptr? */

#if (defined(GETGRENT_R_HAS_FPTR) || defined(GETGRGID_R_HAS_FPTR) || defined(GETGRNAM_R_HAS_FPTR) || defined(SETGRENT_R_HAS_FPTR) || defined(ENDGRENT_R_HAS_FPTR))
#   define USE_GRENT_FPTR
#else
#   undef  USE_GRENT_FPTR
#endif

/* The getpwent getpwnam getpwuid setpwent endpwent using fptr? */

#if defined(HAS_GETPWENT_R) && (GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBIH)
#   define GETPWENT_R_HAS_FPTR
#else
#   undef  GETPWENT_R_HAS_FPTR
#endif
#if defined(HAS_SETPWENT_R) && (SETPWENT_R_PROTO == REENTRANT_PROTO_I_H || SETPWENT_R_PROTO == REENTRANT_PROTO_V_H)
#   define SETPWENT_R_HAS_FPTR
#else
#   undef  SETPWENT_R_HAS_FPTR
#endif
#if defined(HAS_ENDPWENT_R) && (ENDPWENT_R_PROTO == REENTRANT_PROTO_I_H || ENDPWENT_R_PROTO == REENTRANT_PROTO_V_H)
#   define ENDPWENT_R_HAS_FPTR
#else
#   undef  ENDPWENT_R_HAS_FPTR
#endif

/* Any of the getpwent getpwnam getpwuid setpwent endpwent using fptr? */

#if (defined(GETPWENT_R_HAS_FPTR) || defined(GETPWNAM_R_HAS_FPTR) || defined(GETPWUID_R_HAS_FPTR) || defined(SETPWENT_R_HAS_FPTR) || defined(ENDPWENT_R_HAS_FPTR))
#   define USE_PWENT_FPTR
#else
#   undef  USE_PWENT_FPTR
#endif

/* The getpwent getpwgid getpwnam using buffer? */

#if defined(HAS_GETPWENT_R) && (GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBWR || GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBIR || GETPWENT_R_PROTO == REENTRANT_PROTO_S_SBW || GETPWENT_R_PROTO == REENTRANT_PROTO_S_SBI || GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBI || GETPWENT_R_PROTO == REENTRANT_PROTO_I_SBIH)
#   define GETPWENT_R_HAS_BUFFER
#else
#   undef  GETPWENT_R_HAS_BUFFER
#endif
#if defined(HAS_GETPWNAM_R) && (GETPWNAM_R_PROTO == REENTRANT_PROTO_I_CSBWR || GETPWNAM_R_PROTO == REENTRANT_PROTO_I_CSBIR || GETPWNAM_R_PROTO == REENTRANT_PROTO_S_CSBI || GETPWNAM_R_PROTO == REENTRANT_PROTO_I_CSBI)
#   define GETPWNAM_R_HAS_BUFFER
#else
#   undef  GETPWNAM_R_HAS_BUFFER
#endif

/* Any of the getpwent getpwgid getpwnam using buffer? */

#if (defined(GETPWENT_R_HAS_BUFFER) || defined(GETPWGID_R_HAS_BUFFER) || defined(GETPWNAM_R_HAS_BUFFER))
#   define USE_PWENT_BUFFER
#else
#   undef  USE_PWENT_BUFFER
#endif

/* The gethostent gethostbyaddr gethostbyname using ptr? */

#if defined(HAS_GETHOSTENT_R) && (GETHOSTENT_R_PROTO == REENTRANT_PROTO_I_SBWRE)
#   define GETHOSTENT_R_HAS_PTR
#else
#   undef  GETHOSTENT_R_HAS_PTR
#endif
#if defined(HAS_GETHOSTBYADDR_R) && (GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_I_CWISBWRE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_I_TsISBWRE)
#   define GETHOSTBYADDR_R_HAS_PTR
#else
#   undef  GETHOSTBYADDR_R_HAS_PTR
#endif
#if defined(HAS_GETHOSTBYNAME_R) && (GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWRE)
#   define GETHOSTBYNAME_R_HAS_PTR
#else
#   undef  GETHOSTBYNAME_R_HAS_PTR
#endif

/* Any of the gethostent gethostbyaddr gethostbyname using ptr? */

#if (defined(GETHOSTENT_R_HAS_PTR) || defined(GETHOSTBYADDR_R_HAS_PTR) || defined(GETHOSTBYNAME_R_HAS_PTR))
#   define USE_HOSTENT_PTR
#else
#   undef  USE_HOSTENT_PTR
#endif

/* The getnetent getnetbyaddr getnetbyname using ptr? */

#if defined(HAS_GETNETENT_R) && (GETNETENT_R_PROTO == REENTRANT_PROTO_I_SBWRE)
#   define GETNETENT_R_HAS_PTR
#else
#   undef  GETNETENT_R_HAS_PTR
#endif
#if defined(HAS_GETNETBYADDR_R) && (GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_UISBWRE || GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_uISBWRE)
#   define GETNETBYADDR_R_HAS_PTR
#else
#   undef  GETNETBYADDR_R_HAS_PTR
#endif
#if defined(HAS_GETNETBYNAME_R) && (GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWRE)
#   define GETNETBYNAME_R_HAS_PTR
#else
#   undef  GETNETBYNAME_R_HAS_PTR
#endif

/* Any of the getnetent getnetbyaddr getnetbyname using ptr? */

#if (defined(GETNETENT_R_HAS_PTR) || defined(GETNETBYADDR_R_HAS_PTR) || defined(GETNETBYNAME_R_HAS_PTR))
#   define USE_NETENT_PTR
#else
#   undef  USE_NETENT_PTR
#endif

/* The getprotoent getprotobyname getprotobynumber using ptr? */

#if defined(HAS_GETPROTOENT_R) && (GETPROTOENT_R_PROTO == REENTRANT_PROTO_I_SBWR)
#   define GETPROTOENT_R_HAS_PTR
#else
#   undef  GETPROTOENT_R_HAS_PTR
#endif
#if defined(HAS_GETPROTOBYNAME_R) && (GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWR)
#   define GETPROTOBYNAME_R_HAS_PTR
#else
#   undef  GETPROTOBYNAME_R_HAS_PTR
#endif
#if defined(HAS_GETPROTOBYNUMBER_R) && (GETPROTOBYNUMBER_R_PROTO == REENTRANT_PROTO_I_ISBWR)
#   define GETPROTOBYNUMBER_R_HAS_PTR
#else
#   undef  GETPROTOBYNUMBER_R_HAS_PTR
#endif

/* Any of the getprotoent getprotobyname getprotobynumber using ptr? */

#if (defined(GETPROTOENT_R_HAS_PTR) || defined(GETPROTOBYNAME_R_HAS_PTR) || defined(GETPROTOBYNUMBER_R_HAS_PTR))
#   define USE_PROTOENT_PTR
#else
#   undef  USE_PROTOENT_PTR
#endif

/* The getservent getservbyname getservbyport using ptr? */

#if defined(HAS_GETSERVENT_R) && (GETSERVENT_R_PROTO == REENTRANT_PROTO_I_SBWR)
#   define GETSERVENT_R_HAS_PTR
#else
#   undef  GETSERVENT_R_HAS_PTR
#endif
#if defined(HAS_GETSERVBYNAME_R) && (GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_I_CCSBWR)
#   define GETSERVBYNAME_R_HAS_PTR
#else
#   undef  GETSERVBYNAME_R_HAS_PTR
#endif
#if defined(HAS_GETSERVBYPORT_R) && (GETSERVBYPORT_R_PROTO == REENTRANT_PROTO_I_ICSBWR)
#   define GETSERVBYPORT_R_HAS_PTR
#else
#   undef  GETSERVBYPORT_R_HAS_PTR
#endif

/* Any of the getservent getservbyname getservbyport using ptr? */

#if (defined(GETSERVENT_R_HAS_PTR) || defined(GETSERVBYNAME_R_HAS_PTR) || defined(GETSERVBYPORT_R_HAS_PTR))
#   define USE_SERVENT_PTR
#else
#   undef  USE_SERVENT_PTR
#endif

/* The gethostent gethostbyaddr gethostbyname using buffer? */

#if defined(HAS_GETHOSTENT_R) && (GETHOSTENT_R_PROTO == REENTRANT_PROTO_I_SBWRE || GETHOSTENT_R_PROTO == REENTRANT_PROTO_I_SBIE || GETHOSTENT_R_PROTO == REENTRANT_PROTO_S_SBIE || GETHOSTENT_R_PROTO == REENTRANT_PROTO_S_SBI || GETHOSTENT_R_PROTO == REENTRANT_PROTO_I_SBI)
#   define GETHOSTENT_R_HAS_BUFFER
#else
#   undef  GETHOSTENT_R_HAS_BUFFER
#endif
#if defined(HAS_GETHOSTBYADDR_R) && (GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_I_CWISBWRE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CWISBWIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CWISBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_TWISBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CIISBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CSBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_TSBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_I_TsISBWRE)
#   define GETHOSTBYADDR_R_HAS_BUFFER
#else
#   undef  GETHOSTBYADDR_R_HAS_BUFFER
#endif
#if defined(HAS_GETHOSTBYNAME_R) && (GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWRE || GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_S_CSBIE)
#   define GETHOSTBYNAME_R_HAS_BUFFER
#else
#   undef  GETHOSTBYNAME_R_HAS_BUFFER
#endif

/* Any of the gethostent gethostbyaddr gethostbyname using buffer? */

#if (defined(GETHOSTENT_R_HAS_BUFFER) || defined(GETHOSTBYADDR_R_HAS_BUFFER) || defined(GETHOSTBYNAME_R_HAS_BUFFER))
#   define USE_HOSTENT_BUFFER
#else
#   undef  USE_HOSTENT_BUFFER
#endif

/* The getnetent getnetbyaddr getnetbyname using buffer? */

#if defined(HAS_GETNETENT_R) && (GETNETENT_R_PROTO == REENTRANT_PROTO_I_SBWRE || GETNETENT_R_PROTO == REENTRANT_PROTO_I_SBIE || GETNETENT_R_PROTO == REENTRANT_PROTO_S_SBIE || GETNETENT_R_PROTO == REENTRANT_PROTO_S_SBI || GETNETENT_R_PROTO == REENTRANT_PROTO_I_SBI)
#   define GETNETENT_R_HAS_BUFFER
#else
#   undef  GETNETENT_R_HAS_BUFFER
#endif
#if defined(HAS_GETNETBYADDR_R) && (GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_UISBWRE || GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_LISBI || GETNETBYADDR_R_PROTO == REENTRANT_PROTO_S_TISBI || GETNETBYADDR_R_PROTO == REENTRANT_PROTO_S_LISBI || GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_uISBWRE)
#   define GETNETBYADDR_R_HAS_BUFFER
#else
#   undef  GETNETBYADDR_R_HAS_BUFFER
#endif
#if defined(HAS_GETNETBYNAME_R) && (GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWRE || GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBI || GETNETBYNAME_R_PROTO == REENTRANT_PROTO_S_CSBI)
#   define GETNETBYNAME_R_HAS_BUFFER
#else
#   undef  GETNETBYNAME_R_HAS_BUFFER
#endif

/* Any of the getnetent getnetbyaddr getnetbyname using buffer? */

#if (defined(GETNETENT_R_HAS_BUFFER) || defined(GETNETBYADDR_R_HAS_BUFFER) || defined(GETNETBYNAME_R_HAS_BUFFER))
#   define USE_NETENT_BUFFER
#else
#   undef  USE_NETENT_BUFFER
#endif

/* The getprotoent getprotobyname getprotobynumber using buffer? */

#if defined(HAS_GETPROTOENT_R) && (GETPROTOENT_R_PROTO == REENTRANT_PROTO_I_SBWR || GETPROTOENT_R_PROTO == REENTRANT_PROTO_I_SBI || GETPROTOENT_R_PROTO == REENTRANT_PROTO_S_SBI)
#   define GETPROTOENT_R_HAS_BUFFER
#else
#   undef  GETPROTOENT_R_HAS_BUFFER
#endif
#if defined(HAS_GETPROTOBYNAME_R) && (GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWR || GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_S_CSBI)
#   define GETPROTOBYNAME_R_HAS_BUFFER
#else
#   undef  GETPROTOBYNAME_R_HAS_BUFFER
#endif
#if defined(HAS_GETPROTOBYNUMBER_R) && (GETPROTOBYNUMBER_R_PROTO == REENTRANT_PROTO_I_ISBWR || GETPROTOBYNUMBER_R_PROTO == REENTRANT_PROTO_S_ISBI)
#   define GETPROTOBYNUMBER_R_HAS_BUFFER
#else
#   undef  GETPROTOBYNUMBER_R_HAS_BUFFER
#endif

/* Any of the getprotoent getprotobyname getprotobynumber using buffer? */

#if (defined(GETPROTOENT_R_HAS_BUFFER) || defined(GETPROTOBYNAME_R_HAS_BUFFER) || defined(GETPROTOBYNUMBER_R_HAS_BUFFER))
#   define USE_PROTOENT_BUFFER
#else
#   undef  USE_PROTOENT_BUFFER
#endif

/* The getservent getservbyname getservbyport using buffer? */

#if defined(HAS_GETSERVENT_R) && (GETSERVENT_R_PROTO == REENTRANT_PROTO_I_SBWR || GETSERVENT_R_PROTO == REENTRANT_PROTO_I_SBI || GETSERVENT_R_PROTO == REENTRANT_PROTO_S_SBI)
#   define GETSERVENT_R_HAS_BUFFER
#else
#   undef  GETSERVENT_R_HAS_BUFFER
#endif
#if defined(HAS_GETSERVBYNAME_R) && (GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_I_CCSBWR || GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_S_CCSBI)
#   define GETSERVBYNAME_R_HAS_BUFFER
#else
#   undef  GETSERVBYNAME_R_HAS_BUFFER
#endif
#if defined(HAS_GETSERVBYPORT_R) && (GETSERVBYPORT_R_PROTO == REENTRANT_PROTO_I_ICSBWR || GETSERVBYPORT_R_PROTO == REENTRANT_PROTO_S_ICSBI)
#   define GETSERVBYPORT_R_HAS_BUFFER
#else
#   undef  GETSERVBYPORT_R_HAS_BUFFER
#endif

/* Any of the getservent getservbyname getservbyport using buffer? */

#if (defined(GETSERVENT_R_HAS_BUFFER) || defined(GETSERVBYNAME_R_HAS_BUFFER) || defined(GETSERVBYPORT_R_HAS_BUFFER))
#   define USE_SERVENT_BUFFER
#else
#   undef  USE_SERVENT_BUFFER
#endif

/* The gethostent gethostbyaddr gethostbyname using errno? */

#if defined(HAS_GETHOSTENT_R) && (GETHOSTENT_R_PROTO == REENTRANT_PROTO_I_SBWRE || GETHOSTENT_R_PROTO == REENTRANT_PROTO_I_SBIE || GETHOSTENT_R_PROTO == REENTRANT_PROTO_S_SBIE)
#   define GETHOSTENT_R_HAS_ERRNO
#else
#   undef  GETHOSTENT_R_HAS_ERRNO
#endif
#if defined(HAS_GETHOSTBYADDR_R) && (GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_I_CWISBWRE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CWISBWIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CWISBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_TWISBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CIISBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_CSBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_S_TSBIE || GETHOSTBYADDR_R_PROTO == REENTRANT_PROTO_I_TsISBWRE)
#   define GETHOSTBYADDR_R_HAS_ERRNO
#else
#   undef  GETHOSTBYADDR_R_HAS_ERRNO
#endif
#if defined(HAS_GETHOSTBYNAME_R) && (GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWRE || GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_S_CSBIE)
#   define GETHOSTBYNAME_R_HAS_ERRNO
#else
#   undef  GETHOSTBYNAME_R_HAS_ERRNO
#endif

/* Any of the gethostent gethostbyaddr gethostbyname using errno? */

#if (defined(GETHOSTENT_R_HAS_ERRNO) || defined(GETHOSTBYADDR_R_HAS_ERRNO) || defined(GETHOSTBYNAME_R_HAS_ERRNO))
#   define USE_HOSTENT_ERRNO
#else
#   undef  USE_HOSTENT_ERRNO
#endif

/* The getnetent getnetbyaddr getnetbyname using errno? */

#if defined(HAS_GETNETENT_R) && (GETNETENT_R_PROTO == REENTRANT_PROTO_I_SBWRE || GETNETENT_R_PROTO == REENTRANT_PROTO_I_SBIE || GETNETENT_R_PROTO == REENTRANT_PROTO_S_SBIE)
#   define GETNETENT_R_HAS_ERRNO
#else
#   undef  GETNETENT_R_HAS_ERRNO
#endif
#if defined(HAS_GETNETBYADDR_R) && (GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_UISBWRE || GETNETBYADDR_R_PROTO == REENTRANT_PROTO_I_uISBWRE)
#   define GETNETBYADDR_R_HAS_ERRNO
#else
#   undef  GETNETBYADDR_R_HAS_ERRNO
#endif
#if defined(HAS_GETNETBYNAME_R) && (GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSBWRE)
#   define GETNETBYNAME_R_HAS_ERRNO
#else
#   undef  GETNETBYNAME_R_HAS_ERRNO
#endif

/* Any of the getnetent getnetbyaddr getnetbyname using errno? */

#if (defined(GETNETENT_R_HAS_ERRNO) || defined(GETNETBYADDR_R_HAS_ERRNO) || defined(GETNETBYNAME_R_HAS_ERRNO))
#   define USE_NETENT_ERRNO
#else
#   undef  USE_NETENT_ERRNO
#endif


typedef struct {
#ifdef HAS_ASCTIME_R
	char*	_asctime_buffer;
	size_t	_asctime_size;
#endif /* HAS_ASCTIME_R */
#ifdef HAS_CRYPT_R
#if CRYPT_R_PROTO == REENTRANT_PROTO_B_CCD
	CRYPTD* _crypt_data;
#else
	struct crypt_data _crypt_struct;
#endif
#endif /* HAS_CRYPT_R */
#ifdef HAS_CTIME_R
	char*	_ctime_buffer;
	size_t	_ctime_size;
#endif /* HAS_CTIME_R */
#ifdef HAS_DRAND48_R
	struct drand48_data _drand48_struct;
	double	_drand48_double;
#endif /* HAS_DRAND48_R */
#ifdef HAS_GETGRNAM_R
	struct group	_grent_struct;
	char*	_grent_buffer;
	size_t	_grent_size;
#   ifdef USE_GRENT_PTR
	struct group*	_grent_ptr;
#   endif
#   ifdef USE_GRENT_FPTR
	FILE*	_grent_fptr;
#   endif
#endif /* HAS_GETGRNAM_R */
#ifdef HAS_GETHOSTBYNAME_R
	struct hostent	_hostent_struct;
#   if GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD
	struct hostent_data	_hostent_data;
#   else
	char*	_hostent_buffer;
	size_t	_hostent_size;
#   endif
#   ifdef USE_HOSTENT_PTR
	struct hostent*	_hostent_ptr;
#   endif
#   ifdef USE_HOSTENT_ERRNO
	int	_hostent_errno;
#   endif 
#endif /* HAS_GETHOSTBYNAME_R */
#ifdef HAS_GETLOGIN_R
	char*	_getlogin_buffer;
	size_t	_getlogin_size;
#endif /* HAS_GETLOGIN_R */
#ifdef HAS_GETNETBYNAME_R
	struct netent	_netent_struct;
#   if GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD
	struct netent_data	_netent_data;
#   else
	char*	_netent_buffer;
	size_t	_netent_size;
#   endif
#   ifdef USE_NETENT_PTR
	struct netent*	_netent_ptr;
#   endif
#   ifdef USE_NETENT_ERRNO
	int	_netent_errno;
#   endif 
#endif /* HAS_GETNETBYNAME_R */
#ifdef HAS_GETPROTOBYNAME_R
	struct protoent	_protoent_struct;
#   if GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD
	struct protoent_data	_protoent_data;
#   else
	char*	_protoent_buffer;
	size_t	_protoent_size;
#   endif
#   ifdef USE_PROTOENT_PTR
	struct protoent*	_protoent_ptr;
#   endif
#   ifdef USE_PROTOENT_ERRNO
	int	_protoent_errno;
#   endif 
#endif /* HAS_GETPROTOBYNAME_R */
#ifdef HAS_GETPWNAM_R
	struct passwd	_pwent_struct;
	char*	_pwent_buffer;
	size_t	_pwent_size;
#   ifdef USE_PWENT_PTR
	struct passwd*	_pwent_ptr;
#   endif
#   ifdef USE_PWENT_FPTR
	FILE*	_pwent_fptr;
#   endif
#endif /* HAS_GETPWNAM_R */
#ifdef HAS_GETSERVBYNAME_R
	struct servent	_servent_struct;
#   if GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_I_CCSD
	struct servent_data	_servent_data;
#   else
	char*	_servent_buffer;
	size_t	_servent_size;
#   endif
#   ifdef USE_SERVENT_PTR
	struct servent*	_servent_ptr;
#   endif
#   ifdef USE_SERVENT_ERRNO
	int	_servent_errno;
#   endif 
#endif /* HAS_GETSERVBYNAME_R */
#ifdef HAS_GETSPNAM_R
	struct spwd	_spent_struct;
	char*	_spent_buffer;
	size_t	_spent_size;
#   ifdef USE_SPENT_PTR
	struct spwd*	_spent_ptr;
#   endif
#   ifdef USE_SPENT_FPTR
	FILE*	_spent_fptr;
#   endif
#endif /* HAS_GETSPNAM_R */
#ifdef HAS_GMTIME_R
	struct tm _gmtime_struct;
#endif /* HAS_GMTIME_R */
#ifdef HAS_LOCALTIME_R
	struct tm _localtime_struct;
#endif /* HAS_LOCALTIME_R */
#ifdef HAS_RANDOM_R
#   if RANDOM_R_PROTO != REENTRANT_PROTO_I_St
	struct random_data _random_struct;
#   endif
#endif /* HAS_RANDOM_R */
#ifdef HAS_READDIR_R
	struct dirent*	_readdir_struct;
	size_t	_readdir_size;
#   if READDIR_R_PROTO == REENTRANT_PROTO_I_TSR
	struct dirent*	_readdir_ptr;
#   endif
#endif /* HAS_READDIR_R */
#ifdef HAS_READDIR64_R
	struct dirent64*	_readdir64_struct;
	size_t	_readdir64_size;
#   if READDIR64_R_PROTO == REENTRANT_PROTO_I_TSR
	struct dirent64*	_readdir64_ptr;
#   endif
#endif /* HAS_READDIR64_R */
#ifdef HAS_SETLOCALE_R
	char*	_setlocale_buffer;
	size_t	_setlocale_size;
#endif /* HAS_SETLOCALE_R */
#ifdef HAS_STRERROR_R
	char*	_strerror_buffer;
	size_t	_strerror_size;
#endif /* HAS_STRERROR_R */
#ifdef HAS_TTYNAME_R
	char*	_ttyname_buffer;
	size_t	_ttyname_size;
#endif /* HAS_TTYNAME_R */
#ifdef HAS_CRYPT_R
#if CRYPT_R_PROTO == REENTRANT_PROTO_B_CCD
#else
	struct crypt_data *_crypt_struct_buffer;
#endif
#endif /* HAS_CRYPT_R */
#ifdef HAS_RANDOM_R
#   if RANDOM_R_PROTO == REENTRANT_PROTO_I_iS
	int	_random_retval;
#   endif
#   if RANDOM_R_PROTO == REENTRANT_PROTO_I_lS
	long	_random_retval;
#   endif
#   if RANDOM_R_PROTO == REENTRANT_PROTO_I_St
	struct random_data _random_struct;
	int32_t	_random_retval;
#   endif
#endif /* HAS_RANDOM_R */
#ifdef HAS_SRANDOM_R
	struct random_data _srandom_struct;
#endif /* HAS_SRANDOM_R */

    int dummy; /* cannot have empty structs */
} REENTR;

#endif /* USE_REENTRANT_API */

#endif
