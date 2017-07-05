/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         pcap_parse
#define yylex           pcap_lex
#define yyerror         pcap_error
#define yylval          pcap_lval
#define yychar          pcap_char
#define yydebug         pcap_debug
#define yynerrs         pcap_nerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "grammar.y"

/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32
#include <pcap-stdinc.h>
#else /* WIN32 */
#include <sys/types.h>
#include <sys/socket.h>
#endif /* WIN32 */

#include <stdlib.h>

#ifndef WIN32
#if __STDC__
struct mbuf;
struct rtentry;
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
#endif /* WIN32 */

#include <stdio.h>

#include "pcap-int.h"

#include "gencode.h"
#ifdef HAVE_NET_PFVAR_H
#include <net/if.h>
#include <net/pfvar.h>
#include <net/if_pflog.h>
#endif
#include "llc.h"
#include "ieee80211.h"
#include <pcap/namedb.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#define QSET(q, p, d, a) (q).proto = (p),\
			 (q).dir = (d),\
			 (q).addr = (a)

struct tok {
	int v;			/* value */
	const char *s;		/* string */
};

static const struct tok ieee80211_types[] = {
	{ IEEE80211_FC0_TYPE_DATA, "data" },
	{ IEEE80211_FC0_TYPE_MGT, "mgt" },
	{ IEEE80211_FC0_TYPE_MGT, "management" },
	{ IEEE80211_FC0_TYPE_CTL, "ctl" },
	{ IEEE80211_FC0_TYPE_CTL, "control" },
	{ 0, NULL }
};
static const struct tok ieee80211_mgt_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assocreq" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assoc-req" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assocresp" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassocreq" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassoc-req" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassocresp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probereq" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probe-req" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "proberesp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "probe-resp" },
	{ IEEE80211_FC0_SUBTYPE_BEACON, "beacon" },
	{ IEEE80211_FC0_SUBTYPE_ATIM, "atim" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassoc" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassociation" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "auth" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "authentication" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauth" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauthentication" },
	{ 0, NULL }
};
static const struct tok ieee80211_ctl_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_PS_POLL, "ps-poll" },
	{ IEEE80211_FC0_SUBTYPE_RTS, "rts" },
	{ IEEE80211_FC0_SUBTYPE_CTS, "cts" },
	{ IEEE80211_FC0_SUBTYPE_ACK, "ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_END, "cf-end" },
	{ IEEE80211_FC0_SUBTYPE_CF_END_ACK, "cf-end-ack" },
	{ 0, NULL }
};
static const struct tok ieee80211_data_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_DATA, "data" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACK, "data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_POLL, "data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACPL, "data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_NODATA, "null" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACK, "cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "cf-poll"  },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_DATA, "qos-data" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACK, "qos-data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_POLL, "qos-data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACPL, "qos-data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA, "qos" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "qos-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "qos-cf-ack-poll" },
	{ 0, NULL }
};
static const struct tok llc_s_subtypes[] = {
	{ LLC_RR, "rr" },
	{ LLC_RNR, "rnr" },
	{ LLC_REJ, "rej" },
	{ 0, NULL }
};
static const struct tok llc_u_subtypes[] = {
	{ LLC_UI, "ui" },
	{ LLC_UA, "ua" },
	{ LLC_DISC, "disc" },
	{ LLC_DM, "dm" },
	{ LLC_SABME, "sabme" },
	{ LLC_TEST, "test" },
	{ LLC_XID, "xid" },
	{ LLC_FRMR, "frmr" },
	{ 0, NULL }
};
struct type2tok {
	int type;
	const struct tok *tok;
};
static const struct type2tok ieee80211_type_subtypes[] = {
	{ IEEE80211_FC0_TYPE_MGT, ieee80211_mgt_subtypes },
	{ IEEE80211_FC0_TYPE_CTL, ieee80211_ctl_subtypes },
	{ IEEE80211_FC0_TYPE_DATA, ieee80211_data_subtypes },
	{ 0, NULL }
};

static int
str2tok(const char *str, const struct tok *toks)
{
	int i;

	for (i = 0; toks[i].s != NULL; i++) {
		if (pcap_strcasecmp(toks[i].s, str) == 0)
			return (toks[i].v);
	}
	return (-1);
}

int n_errors = 0;

static struct qual qerr = { Q_UNDEF, Q_UNDEF, Q_UNDEF, Q_UNDEF };

static void
yyerror(const char *msg)
{
	++n_errors;
	bpf_error("%s", msg);
	/* NOTREACHED */
}

#ifdef NEED_YYPARSE_WRAPPER
int yyparse(void);

int
pcap_parse()
{
	return (yyparse());
}
#endif

#ifdef HAVE_NET_PFVAR_H
static int
pfreason_to_num(const char *reason)
{
	const char *reasons[] = PFRES_NAMES;
	int i;

	for (i = 0; reasons[i]; i++) {
		if (pcap_strcasecmp(reason, reasons[i]) == 0)
			return (i);
	}
	bpf_error("unknown PF reason");
	/*NOTREACHED*/
}

static int
pfaction_to_num(const char *action)
{
	if (pcap_strcasecmp(action, "pass") == 0 ||
	    pcap_strcasecmp(action, "accept") == 0)
		return (PF_PASS);
	else if (pcap_strcasecmp(action, "drop") == 0 ||
		pcap_strcasecmp(action, "block") == 0)
		return (PF_DROP);
#if HAVE_PF_NAT_THROUGH_PF_NORDR
	else if (pcap_strcasecmp(action, "rdr") == 0)
		return (PF_RDR);
	else if (pcap_strcasecmp(action, "nat") == 0)
		return (PF_NAT);
	else if (pcap_strcasecmp(action, "binat") == 0)
		return (PF_BINAT);
	else if (pcap_strcasecmp(action, "nordr") == 0)
		return (PF_NORDR);
#endif
	else {
		bpf_error("unknown PF action");
		/*NOTREACHED*/
	}
}
#else /* !HAVE_NET_PFVAR_H */
static int
pfreason_to_num(const char *reason)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}

static int
pfaction_to_num(const char *action)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}
#endif /* HAVE_NET_PFVAR_H */


/* Line 268 of yacc.c  */
#line 335 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DST = 258,
     SRC = 259,
     HOST = 260,
     GATEWAY = 261,
     NET = 262,
     NETMASK = 263,
     PORT = 264,
     PORTRANGE = 265,
     LESS = 266,
     GREATER = 267,
     PROTO = 268,
     PROTOCHAIN = 269,
     CBYTE = 270,
     ARP = 271,
     RARP = 272,
     IP = 273,
     SCTP = 274,
     TCP = 275,
     UDP = 276,
     ICMP = 277,
     IGMP = 278,
     IGRP = 279,
     PIM = 280,
     VRRP = 281,
     CARP = 282,
     ATALK = 283,
     AARP = 284,
     DECNET = 285,
     LAT = 286,
     SCA = 287,
     MOPRC = 288,
     MOPDL = 289,
     TK_BROADCAST = 290,
     TK_MULTICAST = 291,
     NUM = 292,
     INBOUND = 293,
     OUTBOUND = 294,
     PF_IFNAME = 295,
     PF_RSET = 296,
     PF_RNR = 297,
     PF_SRNR = 298,
     PF_REASON = 299,
     PF_ACTION = 300,
     TYPE = 301,
     SUBTYPE = 302,
     DIR = 303,
     ADDR1 = 304,
     ADDR2 = 305,
     ADDR3 = 306,
     ADDR4 = 307,
     RA = 308,
     TA = 309,
     LINK = 310,
     GEQ = 311,
     LEQ = 312,
     NEQ = 313,
     ID = 314,
     EID = 315,
     HID = 316,
     HID6 = 317,
     AID = 318,
     LSH = 319,
     RSH = 320,
     LEN = 321,
     IPV6 = 322,
     ICMPV6 = 323,
     AH = 324,
     ESP = 325,
     VLAN = 326,
     MPLS = 327,
     PPPOED = 328,
     PPPOES = 329,
     ISO = 330,
     ESIS = 331,
     CLNP = 332,
     ISIS = 333,
     L1 = 334,
     L2 = 335,
     IIH = 336,
     LSP = 337,
     SNP = 338,
     CSNP = 339,
     PSNP = 340,
     STP = 341,
     IPX = 342,
     NETBEUI = 343,
     LANE = 344,
     LLC = 345,
     METAC = 346,
     BCC = 347,
     SC = 348,
     ILMIC = 349,
     OAMF4EC = 350,
     OAMF4SC = 351,
     OAM = 352,
     OAMF4 = 353,
     CONNECTMSG = 354,
     METACONNECT = 355,
     VPI = 356,
     VCI = 357,
     RADIO = 358,
     FISU = 359,
     LSSU = 360,
     MSU = 361,
     HFISU = 362,
     HLSSU = 363,
     HMSU = 364,
     SIO = 365,
     OPC = 366,
     DPC = 367,
     SLS = 368,
     HSIO = 369,
     HOPC = 370,
     HDPC = 371,
     HSLS = 372,
     AND = 373,
     OR = 374,
     UMINUS = 375
   };
#endif
/* Tokens.  */
#define DST 258
#define SRC 259
#define HOST 260
#define GATEWAY 261
#define NET 262
#define NETMASK 263
#define PORT 264
#define PORTRANGE 265
#define LESS 266
#define GREATER 267
#define PROTO 268
#define PROTOCHAIN 269
#define CBYTE 270
#define ARP 271
#define RARP 272
#define IP 273
#define SCTP 274
#define TCP 275
#define UDP 276
#define ICMP 277
#define IGMP 278
#define IGRP 279
#define PIM 280
#define VRRP 281
#define CARP 282
#define ATALK 283
#define AARP 284
#define DECNET 285
#define LAT 286
#define SCA 287
#define MOPRC 288
#define MOPDL 289
#define TK_BROADCAST 290
#define TK_MULTICAST 291
#define NUM 292
#define INBOUND 293
#define OUTBOUND 294
#define PF_IFNAME 295
#define PF_RSET 296
#define PF_RNR 297
#define PF_SRNR 298
#define PF_REASON 299
#define PF_ACTION 300
#define TYPE 301
#define SUBTYPE 302
#define DIR 303
#define ADDR1 304
#define ADDR2 305
#define ADDR3 306
#define ADDR4 307
#define RA 308
#define TA 309
#define LINK 310
#define GEQ 311
#define LEQ 312
#define NEQ 313
#define ID 314
#define EID 315
#define HID 316
#define HID6 317
#define AID 318
#define LSH 319
#define RSH 320
#define LEN 321
#define IPV6 322
#define ICMPV6 323
#define AH 324
#define ESP 325
#define VLAN 326
#define MPLS 327
#define PPPOED 328
#define PPPOES 329
#define ISO 330
#define ESIS 331
#define CLNP 332
#define ISIS 333
#define L1 334
#define L2 335
#define IIH 336
#define LSP 337
#define SNP 338
#define CSNP 339
#define PSNP 340
#define STP 341
#define IPX 342
#define NETBEUI 343
#define LANE 344
#define LLC 345
#define METAC 346
#define BCC 347
#define SC 348
#define ILMIC 349
#define OAMF4EC 350
#define OAMF4SC 351
#define OAM 352
#define OAMF4 353
#define CONNECTMSG 354
#define METACONNECT 355
#define VPI 356
#define VCI 357
#define RADIO 358
#define FISU 359
#define LSSU 360
#define MSU 361
#define HFISU 362
#define HLSSU 363
#define HMSU 364
#define SIO 365
#define OPC 366
#define DPC 367
#define SLS 368
#define HSIO 369
#define HOPC 370
#define HDPC 371
#define HSLS 372
#define AND 373
#define OR 374
#define UMINUS 375




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 256 "grammar.y"

	int i;
	bpf_u_int32 h;
	u_char *e;
	char *s;
	struct stmt *stmt;
	struct arth *a;
	struct {
		struct qual q;
		int atmfieldtype;
		int mtp3fieldtype;
		struct block *b;
	} blk;
	struct block *rblk;



/* Line 293 of yacc.c  */
#line 629 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 641 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   758

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  218
/* YYNRULES -- Number of states.  */
#define YYNSTATES  292

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   375

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   120,     2,     2,     2,   136,   122,     2,
     129,   128,   125,   123,     2,   124,     2,   126,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   135,     2,
     132,   131,   130,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   133,     2,   134,   137,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   121,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   127
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    11,    15,    19,    23,
      27,    29,    31,    33,    35,    39,    41,    45,    49,    51,
      55,    57,    59,    61,    64,    66,    68,    70,    74,    78,
      80,    82,    84,    87,    91,    94,    97,   100,   103,   106,
     109,   113,   115,   119,   123,   125,   127,   129,   132,   134,
     137,   139,   140,   142,   144,   148,   152,   156,   160,   162,
     164,   166,   168,   170,   172,   174,   176,   178,   180,   182,
     184,   186,   188,   190,   192,   194,   196,   198,   200,   202,
     204,   206,   208,   210,   212,   214,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   234,   236,   238,   240,   242,
     244,   246,   248,   250,   252,   254,   256,   258,   260,   263,
     266,   269,   272,   277,   279,   281,   284,   286,   289,   291,
     293,   296,   298,   300,   303,   305,   308,   311,   314,   317,
     320,   323,   328,   331,   334,   337,   339,   341,   343,   345,
     347,   349,   352,   355,   357,   359,   361,   363,   365,   367,
     369,   371,   373,   375,   377,   379,   381,   386,   393,   397,
     401,   405,   409,   413,   417,   421,   425,   429,   433,   436,
     440,   442,   444,   446,   448,   450,   452,   454,   458,   460,
     462,   464,   466,   468,   470,   472,   474,   476,   478,   480,
     482,   484,   486,   489,   492,   496,   498,   500,   504,   506,
     508,   510,   512,   514,   516,   518,   520,   522,   524,   526,
     528,   530,   532,   534,   537,   540,   544,   546,   548
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     139,     0,    -1,   140,   141,    -1,   140,    -1,    -1,   150,
      -1,   141,   142,   150,    -1,   141,   142,   144,    -1,   141,
     143,   150,    -1,   141,   143,   144,    -1,   118,    -1,   119,
      -1,   145,    -1,   173,    -1,   147,   148,   128,    -1,    59,
      -1,    61,   126,    37,    -1,    61,     8,    61,    -1,    61,
      -1,    62,   126,    37,    -1,    62,    -1,    60,    -1,    63,
      -1,   146,   144,    -1,   120,    -1,   129,    -1,   145,    -1,
     149,   142,   144,    -1,   149,   143,   144,    -1,   173,    -1,
     148,    -1,   152,    -1,   146,   150,    -1,   153,   154,   155,
      -1,   153,   154,    -1,   153,   155,    -1,   153,    13,    -1,
     153,    14,    -1,   153,   156,    -1,   151,   144,    -1,   147,
     141,   128,    -1,   157,    -1,   170,   168,   170,    -1,   170,
     169,   170,    -1,   158,    -1,   174,    -1,   175,    -1,   176,
     177,    -1,   180,    -1,   181,   182,    -1,   157,    -1,    -1,
       4,    -1,     3,    -1,     4,   119,     3,    -1,     3,   119,
       4,    -1,     4,   118,     3,    -1,     3,   118,     4,    -1,
      49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,
      54,    -1,     5,    -1,     7,    -1,     9,    -1,    10,    -1,
       6,    -1,    55,    -1,    18,    -1,    16,    -1,    17,    -1,
      19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    34,    -1,
      33,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
      75,    -1,    76,    -1,    78,    -1,    79,    -1,    80,    -1,
      81,    -1,    82,    -1,    83,    -1,    85,    -1,    84,    -1,
      77,    -1,    86,    -1,    87,    -1,    88,    -1,   103,    -1,
     153,    35,    -1,   153,    36,    -1,    11,    37,    -1,    12,
      37,    -1,    15,    37,   172,    37,    -1,    38,    -1,    39,
      -1,    71,   173,    -1,    71,    -1,    72,   173,    -1,    72,
      -1,    73,    -1,    74,   173,    -1,    74,    -1,   159,    -1,
     153,   160,    -1,   164,    -1,    40,    59,    -1,    41,    59,
      -1,    42,    37,    -1,    43,    37,    -1,    44,   166,    -1,
      45,   167,    -1,    46,   161,    47,   162,    -1,    46,   161,
      -1,    47,   163,    -1,    48,   165,    -1,    37,    -1,    59,
      -1,    37,    -1,    59,    -1,    59,    -1,    90,    -1,    90,
      59,    -1,    90,    42,    -1,    37,    -1,    59,    -1,    37,
      -1,    59,    -1,    59,    -1,   130,    -1,    56,    -1,   131,
      -1,    57,    -1,   132,    -1,    58,    -1,   173,    -1,   171,
      -1,   157,   133,   170,   134,    -1,   157,   133,   170,   135,
      37,   134,    -1,   170,   123,   170,    -1,   170,   124,   170,
      -1,   170,   125,   170,    -1,   170,   126,   170,    -1,   170,
     136,   170,    -1,   170,   122,   170,    -1,   170,   121,   170,
      -1,   170,   137,   170,    -1,   170,    64,   170,    -1,   170,
      65,   170,    -1,   124,   170,    -1,   147,   171,   128,    -1,
      66,    -1,   122,    -1,   121,    -1,   132,    -1,   130,    -1,
     131,    -1,    37,    -1,   147,   173,   128,    -1,    89,    -1,
      91,    -1,    92,    -1,    95,    -1,    96,    -1,    93,    -1,
      94,    -1,    97,    -1,    98,    -1,    99,    -1,   100,    -1,
     101,    -1,   102,    -1,   178,    -1,   168,    37,    -1,   169,
      37,    -1,   147,   179,   128,    -1,    37,    -1,   178,    -1,
     179,   143,   178,    -1,   104,    -1,   105,    -1,   106,    -1,
     107,    -1,   108,    -1,   109,    -1,   110,    -1,   111,    -1,
     112,    -1,   113,    -1,   114,    -1,   115,    -1,   116,    -1,
     117,    -1,   183,    -1,   168,    37,    -1,   169,    37,    -1,
     147,   184,   128,    -1,    37,    -1,   183,    -1,   184,   143,
     183,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   330,   330,   334,   336,   338,   339,   340,   341,   342,
     344,   346,   348,   349,   351,   353,   354,   356,   358,   371,
     380,   389,   398,   407,   409,   411,   413,   414,   415,   417,
     419,   421,   422,   424,   425,   426,   427,   428,   429,   431,
     432,   433,   434,   436,   438,   439,   440,   441,   442,   443,
     446,   447,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   464,   465,   466,   467,   470,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   531,   532,   533,   534,   535,
     536,   539,   544,   547,   551,   554,   555,   561,   562,   582,
     598,   599,   620,   623,   624,   637,   638,   641,   644,   645,
     646,   648,   649,   650,   652,   653,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   668,
     669,   671,   672,   673,   674,   675,   677,   678,   680,   681,
     682,   683,   684,   685,   686,   688,   689,   690,   691,   694,
     695,   697,   698,   699,   700,   702,   709,   710,   713,   714,
     715,   716,   717,   718,   721,   722,   723,   724,   725,   726,
     727,   728,   730,   731,   732,   733,   735,   748,   749
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DST", "SRC", "HOST", "GATEWAY", "NET",
  "NETMASK", "PORT", "PORTRANGE", "LESS", "GREATER", "PROTO", "PROTOCHAIN",
  "CBYTE", "ARP", "RARP", "IP", "SCTP", "TCP", "UDP", "ICMP", "IGMP",
  "IGRP", "PIM", "VRRP", "CARP", "ATALK", "AARP", "DECNET", "LAT", "SCA",
  "MOPRC", "MOPDL", "TK_BROADCAST", "TK_MULTICAST", "NUM", "INBOUND",
  "OUTBOUND", "PF_IFNAME", "PF_RSET", "PF_RNR", "PF_SRNR", "PF_REASON",
  "PF_ACTION", "TYPE", "SUBTYPE", "DIR", "ADDR1", "ADDR2", "ADDR3",
  "ADDR4", "RA", "TA", "LINK", "GEQ", "LEQ", "NEQ", "ID", "EID", "HID",
  "HID6", "AID", "LSH", "RSH", "LEN", "IPV6", "ICMPV6", "AH", "ESP",
  "VLAN", "MPLS", "PPPOED", "PPPOES", "ISO", "ESIS", "CLNP", "ISIS", "L1",
  "L2", "IIH", "LSP", "SNP", "CSNP", "PSNP", "STP", "IPX", "NETBEUI",
  "LANE", "LLC", "METAC", "BCC", "SC", "ILMIC", "OAMF4EC", "OAMF4SC",
  "OAM", "OAMF4", "CONNECTMSG", "METACONNECT", "VPI", "VCI", "RADIO",
  "FISU", "LSSU", "MSU", "HFISU", "HLSSU", "HMSU", "SIO", "OPC", "DPC",
  "SLS", "HSIO", "HOPC", "HDPC", "HSLS", "AND", "OR", "'!'", "'|'", "'&'",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "')'", "'('", "'>'", "'='", "'<'",
  "'['", "']'", "':'", "'%'", "'^'", "$accept", "prog", "null", "expr",
  "and", "or", "id", "nid", "not", "paren", "pid", "qid", "term", "head",
  "rterm", "pqual", "dqual", "aqual", "ndaqual", "pname", "other", "pfvar",
  "p80211", "type", "subtype", "type_subtype", "pllc", "dir", "reason",
  "action", "relop", "irelop", "arth", "narth", "byteop", "pnum",
  "atmtype", "atmmultitype", "atmfield", "atmvalue", "atmfieldvalue",
  "atmlistvalue", "mtp2type", "mtp3field", "mtp3value", "mtp3fieldvalue",
  "mtp3listvalue", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
      33,   124,    38,    43,    45,    42,    47,   375,    41,    40,
      62,    61,    60,    91,    93,    58,    37,    94
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   138,   139,   139,   140,   141,   141,   141,   141,   141,
     142,   143,   144,   144,   144,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   146,   147,   148,   148,   148,   149,
     149,   150,   150,   151,   151,   151,   151,   151,   151,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     153,   153,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   155,   155,   155,   155,   156,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   159,   159,   159,   159,   159,
     159,   160,   160,   160,   160,   161,   161,   162,   162,   163,
     164,   164,   164,   165,   165,   166,   166,   167,   168,   168,
     168,   169,   169,   169,   170,   170,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   172,   172,   172,   172,   172,   173,   173,   174,   174,
     174,   174,   174,   174,   174,   175,   175,   175,   175,   176,
     176,   177,   177,   177,   177,   178,   179,   179,   180,   180,
     180,   180,   180,   180,   181,   181,   181,   181,   181,   181,
     181,   181,   182,   182,   182,   182,   183,   184,   184
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     3,     3,     1,     3,
       1,     1,     1,     2,     1,     1,     1,     3,     3,     1,
       1,     1,     2,     3,     2,     2,     2,     2,     2,     2,
       3,     1,     3,     3,     1,     1,     1,     2,     1,     2,
       1,     0,     1,     1,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     4,     1,     1,     2,     1,     2,     1,     1,
       2,     1,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     4,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     6,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    51,     1,     0,     0,     0,    71,    72,    70,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    88,    87,   176,   113,   114,     0,
       0,     0,     0,     0,     0,    69,   170,    89,    90,    91,
      92,   116,   118,   119,   121,    93,    94,   103,    95,    96,
      97,    98,    99,   100,   102,   101,   104,   105,   106,   178,
     140,   179,   180,   183,   184,   181,   182,   185,   186,   187,
     188,   189,   190,   107,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,    24,     0,
      25,     2,    51,    51,     5,     0,    31,     0,    50,    44,
     122,   124,     0,   155,   154,    45,    46,     0,    48,     0,
     110,   111,     0,   125,   126,   127,   128,   145,   146,   129,
     147,   130,     0,   115,   117,   120,   142,   141,     0,     0,
     168,    10,    11,    51,    51,    32,     0,   155,   154,    15,
      21,    18,    20,    22,    39,    12,     0,     0,    13,    53,
      52,    64,    68,    65,    66,    67,    36,    37,   108,   109,
       0,     0,     0,    58,    59,    60,    61,    62,    63,    34,
      35,    38,   123,     0,   149,   151,   153,     0,     0,     0,
       0,     0,     0,     0,     0,   148,   150,   152,     0,     0,
       0,     0,   195,     0,     0,     0,    47,   191,   216,     0,
       0,     0,    49,   212,   172,   171,   174,   175,   173,     0,
       0,     0,     7,    51,    51,     6,   154,     9,     8,    40,
     169,   177,     0,     0,     0,    23,    26,    30,     0,    29,
       0,     0,     0,     0,   135,   136,   132,   139,   133,   143,
     144,   134,    33,     0,   166,   167,   164,   163,   158,   159,
     160,   161,   162,   165,    42,    43,   196,     0,   192,   193,
     217,     0,   213,   214,   112,   154,    17,    16,    19,    14,
       0,     0,    57,    55,    56,    54,     0,   156,     0,   194,
       0,   215,     0,    27,    28,   137,   138,   131,     0,   197,
     218,   157
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   136,   133,   134,   225,   145,   146,   128,
     227,   228,    94,    95,    96,    97,   169,   170,   171,   129,
      99,   100,   172,   236,   287,   238,   101,   241,   119,   121,
     190,   191,   102,   103,   209,   104,   105,   106,   107,   196,
     197,   257,   108,   109,   202,   203,   261
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -204
static const yytype_int16 yypact[] =
{
    -204,    24,   233,  -204,    -8,    27,    44,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,    45,
      47,    46,    75,   -21,    60,  -204,  -204,  -204,  -204,  -204,
    -204,   -26,   -26,  -204,   -26,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
     -25,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,   577,
    -204,   -31,   463,   463,  -204,   -11,  -204,   704,    10,  -204,
    -204,  -204,   161,  -204,  -204,  -204,  -204,    19,  -204,    59,
    -204,  -204,    71,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,  -204,   -26,  -204,  -204,  -204,  -204,  -204,   577,   -86,
     -12,  -204,  -204,   348,   348,  -204,   -98,   -67,     9,  -204,
    -204,    -5,    13,  -204,  -204,  -204,   -11,   -11,  -204,     8,
      15,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
      -6,    83,    -4,  -204,  -204,  -204,  -204,  -204,  -204,   189,
    -204,  -204,  -204,   577,  -204,  -204,  -204,   577,   577,   577,
     577,   577,   577,   577,   577,  -204,  -204,  -204,   577,   577,
     577,   577,  -204,    93,   115,   130,  -204,  -204,  -204,   139,
     142,   143,  -204,  -204,  -204,  -204,  -204,  -204,  -204,   144,
       9,   566,  -204,   348,   348,  -204,    28,  -204,  -204,  -204,
    -204,  -204,   123,   150,   158,  -204,  -204,    69,   -31,     9,
     196,   200,   202,   203,  -204,  -204,   160,  -204,  -204,  -204,
    -204,  -204,  -204,   548,   -58,   -58,   -52,    49,    29,    29,
     -12,   -12,   566,   566,   566,   566,  -204,  -101,  -204,  -204,
    -204,   -39,  -204,  -204,  -204,   -96,  -204,  -204,  -204,  -204,
     -11,   -11,  -204,  -204,  -204,  -204,     4,  -204,   171,  -204,
      93,  -204,   139,  -204,  -204,  -204,  -204,  -204,    76,  -204,
    -204,  -204
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -204,  -204,  -204,   207,   -15,  -203,   -88,  -132,     2,    -2,
    -204,  -204,   -90,  -204,  -204,  -204,  -204,    53,  -204,     7,
    -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,  -204,
     -72,   -47,   -20,   -92,  -204,   -36,  -204,  -204,  -204,  -204,
    -179,  -204,  -204,  -204,  -204,  -180,  -204
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -42
static const yytype_int16 yytable[] =
{
      93,   137,   135,   222,    92,   123,   124,   144,   125,    98,
     -41,    26,   177,   178,   256,   226,   117,   126,   132,   260,
     131,   132,   -29,   -29,     3,   271,    26,   279,   -13,   110,
     219,   234,   221,   239,   127,   194,   137,   200,   118,   122,
     122,   285,   122,   215,   218,   212,   217,   173,   139,   140,
     141,   142,   143,   235,   280,   240,   192,   138,   282,   148,
     195,   220,   201,   286,   111,   181,   182,   183,   184,   130,
     180,   181,   182,   183,   184,   174,   175,   176,   188,   189,
     132,   112,   226,   115,   188,   189,   210,   131,   132,   281,
      93,    93,   138,   147,    92,    92,   198,   216,   216,    98,
      98,   289,   290,    90,   113,   193,   114,   199,   211,    88,
     148,   229,   116,   177,   178,   174,   175,   176,    90,   120,
     122,   223,   137,   135,   188,   189,   230,   231,   -41,   -41,
     192,   214,   214,   232,   233,   213,   213,   221,   -41,   224,
      98,    98,   237,   173,   147,   122,   -13,   -13,    90,   185,
     186,   187,   258,   243,   183,   184,   -13,   244,   245,   246,
     247,   248,   249,   250,   251,   188,   189,   259,   252,   253,
     254,   255,   181,   182,   183,   184,   198,   216,   265,   262,
     263,   264,   283,   284,   266,   188,   189,   267,    90,   185,
     186,   187,   204,   205,   151,   268,   153,   269,   154,   155,
     272,   206,   207,   208,   273,   274,   275,   276,   288,    91,
     291,   214,    93,   270,     0,   213,   213,   174,   175,   176,
      98,    98,   242,     0,     0,   177,   178,     0,     0,     0,
       0,     0,     0,    -3,   148,   148,     0,     0,     0,     0,
       0,     0,     0,     0,     4,     5,     0,     0,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   147,   147,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
       0,     0,   179,   180,   181,   182,   183,   184,    35,     0,
       0,   185,   186,   187,     0,     0,     0,   188,   189,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,     0,    88,     0,     0,     0,    89,     0,     4,
       5,     0,    90,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,    88,     0,
       0,     0,    89,     0,     4,     5,     0,    90,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,     0,    88,     0,     0,     0,    89,     0,     0,
       0,     0,    90,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,   177,   178,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     177,   178,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,    37,    38,    39,    40,     0,     0,
       0,     0,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,     0,     0,     0,   179,
     180,   181,   182,   183,   184,     0,     0,     0,     0,     0,
      73,     0,   277,   278,   188,   189,     0,   179,   180,   181,
     182,   183,   184,     0,     0,     0,     0,     0,     0,     0,
       0,    89,   188,   189,     0,     0,    90,   149,   150,   151,
     152,   153,     0,   154,   155,     0,     0,   156,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
     159,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     160,   161,   162,   163,   164,   165,   166,   167,   168
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-204))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    93,    92,     8,     2,    41,    42,    95,    44,     2,
       0,    37,    64,    65,   193,   147,    37,    42,   119,   199,
     118,   119,   118,   119,     0,   228,    37,   128,     0,    37,
     128,    37,   128,    37,    59,   107,   128,   109,    59,    41,
      42,    37,    44,   133,   134,   133,   134,   133,    59,    60,
      61,    62,    63,    59,   257,    59,    37,    93,   261,    95,
     107,   128,   109,    59,    37,   123,   124,   125,   126,    89,
     122,   123,   124,   125,   126,    56,    57,    58,   136,   137,
     119,    37,   214,    37,   136,   137,   122,   118,   119,   128,
      92,    93,   128,    95,    92,    93,    37,   133,   134,    92,
      93,   280,   282,   129,    59,   107,    59,   109,   128,   120,
     146,   147,    37,    64,    65,    56,    57,    58,   129,    59,
     122,   126,   214,   213,   136,   137,   118,   119,   118,   119,
      37,   133,   134,   118,   119,   133,   134,   128,   128,   126,
     133,   134,    59,   133,   146,   147,   118,   119,   129,   130,
     131,   132,    37,   173,   125,   126,   128,   177,   178,   179,
     180,   181,   182,   183,   184,   136,   137,    37,   188,   189,
     190,   191,   123,   124,   125,   126,    37,   213,   214,    37,
      37,    37,   270,   271,    61,   136,   137,    37,   129,   130,
     131,   132,   121,   122,     5,    37,     7,   128,     9,    10,
       4,   130,   131,   132,     4,     3,     3,    47,    37,     2,
     134,   213,   214,   228,    -1,   213,   214,    56,    57,    58,
     213,   214,   169,    -1,    -1,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,     0,   270,   271,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    12,    -1,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,   270,   271,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,   121,   122,   123,   124,   125,   126,    55,    -1,
      -1,   130,   131,   132,    -1,    -1,    -1,   136,   137,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,    -1,    11,
      12,    -1,   129,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,    -1,    -1,   120,    -1,
      -1,    -1,   124,    -1,    11,    12,    -1,   129,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,   129,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    64,    65,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    -1,    -1,    -1,   121,
     122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,
     103,    -1,   134,   135,   136,   137,    -1,   121,   122,   123,
     124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,   136,   137,    -1,    -1,   129,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   139,   140,     0,    11,    12,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    55,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   120,   124,
     129,   141,   146,   147,   150,   151,   152,   153,   157,   158,
     159,   164,   170,   171,   173,   174,   175,   176,   180,   181,
      37,    37,    37,    59,    59,    37,    37,    37,    59,   166,
      59,   167,   147,   173,   173,   173,    42,    59,   147,   157,
     170,   118,   119,   142,   143,   150,   141,   171,   173,    59,
      60,    61,    62,    63,   144,   145,   146,   147,   173,     3,
       4,     5,     6,     7,     9,    10,    13,    14,    35,    36,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   154,
     155,   156,   160,   133,    56,    57,    58,    64,    65,   121,
     122,   123,   124,   125,   126,   130,   131,   132,   136,   137,
     168,   169,    37,   147,   168,   169,   177,   178,    37,   147,
     168,   169,   182,   183,   121,   122,   130,   131,   132,   172,
     173,   170,   144,   146,   147,   150,   173,   144,   150,   128,
     128,   128,     8,   126,   126,   144,   145,   148,   149,   173,
     118,   119,   118,   119,    37,    59,   161,    59,   163,    37,
      59,   165,   155,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   178,   179,    37,    37,
     183,   184,    37,    37,    37,   173,    61,    37,    37,   128,
     142,   143,     4,     4,     3,     3,    47,   134,   135,   128,
     143,   128,   143,   144,   144,    37,    59,   162,    37,   178,
     183,   134
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 331 "grammar.y"
    {
	finish_parse((yyvsp[(2) - (2)].blk).b);
}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 336 "grammar.y"
    { (yyval.blk).q = qerr; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 339 "grammar.y"
    { gen_and((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 340 "grammar.y"
    { gen_and((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 341 "grammar.y"
    { gen_or((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 342 "grammar.y"
    { gen_or((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 344 "grammar.y"
    { (yyval.blk) = (yyvsp[(0) - (1)].blk); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 346 "grammar.y"
    { (yyval.blk) = (yyvsp[(0) - (1)].blk); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 349 "grammar.y"
    { (yyval.blk).b = gen_ncode(NULL, (bpf_u_int32)(yyvsp[(1) - (1)].i),
						   (yyval.blk).q = (yyvsp[(0) - (1)].blk).q); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 351 "grammar.y"
    { (yyval.blk) = (yyvsp[(2) - (3)].blk); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 353 "grammar.y"
    { (yyval.blk).b = gen_scode((yyvsp[(1) - (1)].s), (yyval.blk).q = (yyvsp[(0) - (1)].blk).q); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 354 "grammar.y"
    { (yyval.blk).b = gen_mcode((yyvsp[(1) - (3)].s), NULL, (yyvsp[(3) - (3)].i),
				    (yyval.blk).q = (yyvsp[(0) - (3)].blk).q); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 356 "grammar.y"
    { (yyval.blk).b = gen_mcode((yyvsp[(1) - (3)].s), (yyvsp[(3) - (3)].s), 0,
				    (yyval.blk).q = (yyvsp[(0) - (3)].blk).q); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 358 "grammar.y"
    {
				  /* Decide how to parse HID based on proto */
				  (yyval.blk).q = (yyvsp[(0) - (1)].blk).q;
				  if ((yyval.blk).q.addr == Q_PORT)
				  	bpf_error("'port' modifier applied to ip host");
				  else if ((yyval.blk).q.addr == Q_PORTRANGE)
				  	bpf_error("'portrange' modifier applied to ip host");
				  else if ((yyval.blk).q.addr == Q_PROTO)
				  	bpf_error("'proto' modifier applied to ip host");
				  else if ((yyval.blk).q.addr == Q_PROTOCHAIN)
				  	bpf_error("'protochain' modifier applied to ip host");
				  (yyval.blk).b = gen_ncode((yyvsp[(1) - (1)].s), 0, (yyval.blk).q);
				}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 371 "grammar.y"
    {
#ifdef INET6
				  (yyval.blk).b = gen_mcode6((yyvsp[(1) - (3)].s), NULL, (yyvsp[(3) - (3)].i),
				    (yyval.blk).q = (yyvsp[(0) - (3)].blk).q);
#else
				  bpf_error("'ip6addr/prefixlen' not supported "
					"in this configuration");
#endif /*INET6*/
				}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 380 "grammar.y"
    {
#ifdef INET6
				  (yyval.blk).b = gen_mcode6((yyvsp[(1) - (1)].s), 0, 128,
				    (yyval.blk).q = (yyvsp[(0) - (1)].blk).q);
#else
				  bpf_error("'ip6addr' not supported "
					"in this configuration");
#endif /*INET6*/
				}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 389 "grammar.y"
    { 
				  (yyval.blk).b = gen_ecode((yyvsp[(1) - (1)].e), (yyval.blk).q = (yyvsp[(0) - (1)].blk).q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free((yyvsp[(1) - (1)].e));
				}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 398 "grammar.y"
    {
				  (yyval.blk).b = gen_acode((yyvsp[(1) - (1)].e), (yyval.blk).q = (yyvsp[(0) - (1)].blk).q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free((yyvsp[(1) - (1)].e));
				}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 407 "grammar.y"
    { gen_not((yyvsp[(2) - (2)].blk).b); (yyval.blk) = (yyvsp[(2) - (2)].blk); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 409 "grammar.y"
    { (yyval.blk) = (yyvsp[(0) - (1)].blk); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 411 "grammar.y"
    { (yyval.blk) = (yyvsp[(0) - (1)].blk); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 414 "grammar.y"
    { gen_and((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 415 "grammar.y"
    { gen_or((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 417 "grammar.y"
    { (yyval.blk).b = gen_ncode(NULL, (bpf_u_int32)(yyvsp[(1) - (1)].i),
						   (yyval.blk).q = (yyvsp[(0) - (1)].blk).q); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 422 "grammar.y"
    { gen_not((yyvsp[(2) - (2)].blk).b); (yyval.blk) = (yyvsp[(2) - (2)].blk); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 424 "grammar.y"
    { QSET((yyval.blk).q, (yyvsp[(1) - (3)].i), (yyvsp[(2) - (3)].i), (yyvsp[(3) - (3)].i)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 425 "grammar.y"
    { QSET((yyval.blk).q, (yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].i), Q_DEFAULT); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 426 "grammar.y"
    { QSET((yyval.blk).q, (yyvsp[(1) - (2)].i), Q_DEFAULT, (yyvsp[(2) - (2)].i)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 427 "grammar.y"
    { QSET((yyval.blk).q, (yyvsp[(1) - (2)].i), Q_DEFAULT, Q_PROTO); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 428 "grammar.y"
    { QSET((yyval.blk).q, (yyvsp[(1) - (2)].i), Q_DEFAULT, Q_PROTOCHAIN); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 429 "grammar.y"
    { QSET((yyval.blk).q, (yyvsp[(1) - (2)].i), Q_DEFAULT, (yyvsp[(2) - (2)].i)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 431 "grammar.y"
    { (yyval.blk) = (yyvsp[(2) - (2)].blk); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 432 "grammar.y"
    { (yyval.blk).b = (yyvsp[(2) - (3)].blk).b; (yyval.blk).q = (yyvsp[(1) - (3)].blk).q; }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 433 "grammar.y"
    { (yyval.blk).b = gen_proto_abbrev((yyvsp[(1) - (1)].i)); (yyval.blk).q = qerr; }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 434 "grammar.y"
    { (yyval.blk).b = gen_relation((yyvsp[(2) - (3)].i), (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a), 0);
				  (yyval.blk).q = qerr; }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 436 "grammar.y"
    { (yyval.blk).b = gen_relation((yyvsp[(2) - (3)].i), (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a), 1);
				  (yyval.blk).q = qerr; }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 438 "grammar.y"
    { (yyval.blk).b = (yyvsp[(1) - (1)].rblk); (yyval.blk).q = qerr; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 439 "grammar.y"
    { (yyval.blk).b = gen_atmtype_abbrev((yyvsp[(1) - (1)].i)); (yyval.blk).q = qerr; }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 440 "grammar.y"
    { (yyval.blk).b = gen_atmmulti_abbrev((yyvsp[(1) - (1)].i)); (yyval.blk).q = qerr; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 441 "grammar.y"
    { (yyval.blk).b = (yyvsp[(2) - (2)].blk).b; (yyval.blk).q = qerr; }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 442 "grammar.y"
    { (yyval.blk).b = gen_mtp2type_abbrev((yyvsp[(1) - (1)].i)); (yyval.blk).q = qerr; }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 443 "grammar.y"
    { (yyval.blk).b = (yyvsp[(2) - (2)].blk).b; (yyval.blk).q = qerr; }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 447 "grammar.y"
    { (yyval.i) = Q_DEFAULT; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 450 "grammar.y"
    { (yyval.i) = Q_SRC; }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 451 "grammar.y"
    { (yyval.i) = Q_DST; }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 452 "grammar.y"
    { (yyval.i) = Q_OR; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 453 "grammar.y"
    { (yyval.i) = Q_OR; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 454 "grammar.y"
    { (yyval.i) = Q_AND; }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 455 "grammar.y"
    { (yyval.i) = Q_AND; }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 456 "grammar.y"
    { (yyval.i) = Q_ADDR1; }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 457 "grammar.y"
    { (yyval.i) = Q_ADDR2; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 458 "grammar.y"
    { (yyval.i) = Q_ADDR3; }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 459 "grammar.y"
    { (yyval.i) = Q_ADDR4; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 460 "grammar.y"
    { (yyval.i) = Q_RA; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 461 "grammar.y"
    { (yyval.i) = Q_TA; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 464 "grammar.y"
    { (yyval.i) = Q_HOST; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 465 "grammar.y"
    { (yyval.i) = Q_NET; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 466 "grammar.y"
    { (yyval.i) = Q_PORT; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 467 "grammar.y"
    { (yyval.i) = Q_PORTRANGE; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 470 "grammar.y"
    { (yyval.i) = Q_GATEWAY; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 472 "grammar.y"
    { (yyval.i) = Q_LINK; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 473 "grammar.y"
    { (yyval.i) = Q_IP; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 474 "grammar.y"
    { (yyval.i) = Q_ARP; }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 475 "grammar.y"
    { (yyval.i) = Q_RARP; }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 476 "grammar.y"
    { (yyval.i) = Q_SCTP; }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 477 "grammar.y"
    { (yyval.i) = Q_TCP; }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 478 "grammar.y"
    { (yyval.i) = Q_UDP; }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 479 "grammar.y"
    { (yyval.i) = Q_ICMP; }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 480 "grammar.y"
    { (yyval.i) = Q_IGMP; }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 481 "grammar.y"
    { (yyval.i) = Q_IGRP; }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 482 "grammar.y"
    { (yyval.i) = Q_PIM; }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 483 "grammar.y"
    { (yyval.i) = Q_VRRP; }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 484 "grammar.y"
    { (yyval.i) = Q_CARP; }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 485 "grammar.y"
    { (yyval.i) = Q_ATALK; }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 486 "grammar.y"
    { (yyval.i) = Q_AARP; }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 487 "grammar.y"
    { (yyval.i) = Q_DECNET; }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 488 "grammar.y"
    { (yyval.i) = Q_LAT; }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 489 "grammar.y"
    { (yyval.i) = Q_SCA; }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 490 "grammar.y"
    { (yyval.i) = Q_MOPDL; }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 491 "grammar.y"
    { (yyval.i) = Q_MOPRC; }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 492 "grammar.y"
    { (yyval.i) = Q_IPV6; }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 493 "grammar.y"
    { (yyval.i) = Q_ICMPV6; }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 494 "grammar.y"
    { (yyval.i) = Q_AH; }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 495 "grammar.y"
    { (yyval.i) = Q_ESP; }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 496 "grammar.y"
    { (yyval.i) = Q_ISO; }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 497 "grammar.y"
    { (yyval.i) = Q_ESIS; }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 498 "grammar.y"
    { (yyval.i) = Q_ISIS; }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 499 "grammar.y"
    { (yyval.i) = Q_ISIS_L1; }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 500 "grammar.y"
    { (yyval.i) = Q_ISIS_L2; }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 501 "grammar.y"
    { (yyval.i) = Q_ISIS_IIH; }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 502 "grammar.y"
    { (yyval.i) = Q_ISIS_LSP; }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 503 "grammar.y"
    { (yyval.i) = Q_ISIS_SNP; }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 504 "grammar.y"
    { (yyval.i) = Q_ISIS_PSNP; }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 505 "grammar.y"
    { (yyval.i) = Q_ISIS_CSNP; }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 506 "grammar.y"
    { (yyval.i) = Q_CLNP; }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 507 "grammar.y"
    { (yyval.i) = Q_STP; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 508 "grammar.y"
    { (yyval.i) = Q_IPX; }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 509 "grammar.y"
    { (yyval.i) = Q_NETBEUI; }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 510 "grammar.y"
    { (yyval.i) = Q_RADIO; }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 512 "grammar.y"
    { (yyval.rblk) = gen_broadcast((yyvsp[(1) - (2)].i)); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 513 "grammar.y"
    { (yyval.rblk) = gen_multicast((yyvsp[(1) - (2)].i)); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 514 "grammar.y"
    { (yyval.rblk) = gen_less((yyvsp[(2) - (2)].i)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 515 "grammar.y"
    { (yyval.rblk) = gen_greater((yyvsp[(2) - (2)].i)); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 516 "grammar.y"
    { (yyval.rblk) = gen_byteop((yyvsp[(3) - (4)].i), (yyvsp[(2) - (4)].i), (yyvsp[(4) - (4)].i)); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 517 "grammar.y"
    { (yyval.rblk) = gen_inbound(0); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 518 "grammar.y"
    { (yyval.rblk) = gen_inbound(1); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 519 "grammar.y"
    { (yyval.rblk) = gen_vlan((yyvsp[(2) - (2)].i)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 520 "grammar.y"
    { (yyval.rblk) = gen_vlan(-1); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 521 "grammar.y"
    { (yyval.rblk) = gen_mpls((yyvsp[(2) - (2)].i)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 522 "grammar.y"
    { (yyval.rblk) = gen_mpls(-1); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 523 "grammar.y"
    { (yyval.rblk) = gen_pppoed(); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 524 "grammar.y"
    { (yyval.rblk) = gen_pppoes((yyvsp[(2) - (2)].i)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 525 "grammar.y"
    { (yyval.rblk) = gen_pppoes(-1); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 526 "grammar.y"
    { (yyval.rblk) = (yyvsp[(1) - (1)].rblk); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 527 "grammar.y"
    { (yyval.rblk) = (yyvsp[(2) - (2)].rblk); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 528 "grammar.y"
    { (yyval.rblk) = (yyvsp[(1) - (1)].rblk); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 531 "grammar.y"
    { (yyval.rblk) = gen_pf_ifname((yyvsp[(2) - (2)].s)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 532 "grammar.y"
    { (yyval.rblk) = gen_pf_ruleset((yyvsp[(2) - (2)].s)); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 533 "grammar.y"
    { (yyval.rblk) = gen_pf_rnr((yyvsp[(2) - (2)].i)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 534 "grammar.y"
    { (yyval.rblk) = gen_pf_srnr((yyvsp[(2) - (2)].i)); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 535 "grammar.y"
    { (yyval.rblk) = gen_pf_reason((yyvsp[(2) - (2)].i)); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 536 "grammar.y"
    { (yyval.rblk) = gen_pf_action((yyvsp[(2) - (2)].i)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 540 "grammar.y"
    { (yyval.rblk) = gen_p80211_type((yyvsp[(2) - (4)].i) | (yyvsp[(4) - (4)].i),
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 544 "grammar.y"
    { (yyval.rblk) = gen_p80211_type((yyvsp[(2) - (2)].i),
					IEEE80211_FC0_TYPE_MASK);
				}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 547 "grammar.y"
    { (yyval.rblk) = gen_p80211_type((yyvsp[(2) - (2)].i),
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 551 "grammar.y"
    { (yyval.rblk) = gen_p80211_fcdir((yyvsp[(2) - (2)].i)); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 555 "grammar.y"
    { (yyval.i) = str2tok((yyvsp[(1) - (1)].s), ieee80211_types);
				  if ((yyval.i) == -1)
				  	bpf_error("unknown 802.11 type name");
				}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 562 "grammar.y"
    { const struct tok *types = NULL;
				  int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type");
						break;
					}
					if ((yyvsp[(-1) - (1)].i) == ieee80211_type_subtypes[i].type) {
						types = ieee80211_type_subtypes[i].tok;
						break;
					}
				  }

				  (yyval.i) = str2tok((yyvsp[(1) - (1)].s), types);
				  if ((yyval.i) == -1)
					bpf_error("unknown 802.11 subtype name");
				}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 582 "grammar.y"
    { int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type name");
						break;
					}
					(yyval.i) = str2tok((yyvsp[(1) - (1)].s), ieee80211_type_subtypes[i].tok);
					if ((yyval.i) != -1) {
						(yyval.i) |= ieee80211_type_subtypes[i].type;
						break;
					}
				  }
				}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 598 "grammar.y"
    { (yyval.rblk) = gen_llc(); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 599 "grammar.y"
    { if (pcap_strcasecmp((yyvsp[(2) - (2)].s), "i") == 0)
					(yyval.rblk) = gen_llc_i();
				  else if (pcap_strcasecmp((yyvsp[(2) - (2)].s), "s") == 0)
					(yyval.rblk) = gen_llc_s();
				  else if (pcap_strcasecmp((yyvsp[(2) - (2)].s), "u") == 0)
					(yyval.rblk) = gen_llc_u();
				  else {
				  	u_int subtype;

					subtype = str2tok((yyvsp[(2) - (2)].s), llc_s_subtypes);
					if (subtype != -1)
						(yyval.rblk) = gen_llc_s_subtype(subtype);
					else {
						subtype = str2tok((yyvsp[(2) - (2)].s), llc_u_subtypes);
						if (subtype == -1)
					  		bpf_error("unknown LLC type name \"%s\"", (yyvsp[(2) - (2)].s));
						(yyval.rblk) = gen_llc_u_subtype(subtype);
					}
				  }
				}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 620 "grammar.y"
    { (yyval.rblk) = gen_llc_s_subtype(LLC_RNR); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 624 "grammar.y"
    { if (pcap_strcasecmp((yyvsp[(1) - (1)].s), "nods") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_NODS;
				  else if (pcap_strcasecmp((yyvsp[(1) - (1)].s), "tods") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_TODS;
				  else if (pcap_strcasecmp((yyvsp[(1) - (1)].s), "fromds") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_FROMDS;
				  else if (pcap_strcasecmp((yyvsp[(1) - (1)].s), "dstods") == 0)
					(yyval.i) = IEEE80211_FC1_DIR_DSTODS;
				  else
					bpf_error("unknown 802.11 direction");
				}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 637 "grammar.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 638 "grammar.y"
    { (yyval.i) = pfreason_to_num((yyvsp[(1) - (1)].s)); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 641 "grammar.y"
    { (yyval.i) = pfaction_to_num((yyvsp[(1) - (1)].s)); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 644 "grammar.y"
    { (yyval.i) = BPF_JGT; }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 645 "grammar.y"
    { (yyval.i) = BPF_JGE; }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 646 "grammar.y"
    { (yyval.i) = BPF_JEQ; }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 648 "grammar.y"
    { (yyval.i) = BPF_JGT; }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 649 "grammar.y"
    { (yyval.i) = BPF_JGE; }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 650 "grammar.y"
    { (yyval.i) = BPF_JEQ; }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 652 "grammar.y"
    { (yyval.a) = gen_loadi((yyvsp[(1) - (1)].i)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 655 "grammar.y"
    { (yyval.a) = gen_load((yyvsp[(1) - (4)].i), (yyvsp[(3) - (4)].a), 1); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 656 "grammar.y"
    { (yyval.a) = gen_load((yyvsp[(1) - (6)].i), (yyvsp[(3) - (6)].a), (yyvsp[(5) - (6)].i)); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 657 "grammar.y"
    { (yyval.a) = gen_arth(BPF_ADD, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 658 "grammar.y"
    { (yyval.a) = gen_arth(BPF_SUB, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 659 "grammar.y"
    { (yyval.a) = gen_arth(BPF_MUL, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 660 "grammar.y"
    { (yyval.a) = gen_arth(BPF_DIV, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 661 "grammar.y"
    { (yyval.a) = gen_arth(BPF_MOD, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 662 "grammar.y"
    { (yyval.a) = gen_arth(BPF_AND, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 663 "grammar.y"
    { (yyval.a) = gen_arth(BPF_OR, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 664 "grammar.y"
    { (yyval.a) = gen_arth(BPF_XOR, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 665 "grammar.y"
    { (yyval.a) = gen_arth(BPF_LSH, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 666 "grammar.y"
    { (yyval.a) = gen_arth(BPF_RSH, (yyvsp[(1) - (3)].a), (yyvsp[(3) - (3)].a)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 667 "grammar.y"
    { (yyval.a) = gen_neg((yyvsp[(2) - (2)].a)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 668 "grammar.y"
    { (yyval.a) = (yyvsp[(2) - (3)].a); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 669 "grammar.y"
    { (yyval.a) = gen_loadlen(); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 671 "grammar.y"
    { (yyval.i) = '&'; }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 672 "grammar.y"
    { (yyval.i) = '|'; }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 673 "grammar.y"
    { (yyval.i) = '<'; }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 674 "grammar.y"
    { (yyval.i) = '>'; }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 675 "grammar.y"
    { (yyval.i) = '='; }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 678 "grammar.y"
    { (yyval.i) = (yyvsp[(2) - (3)].i); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 680 "grammar.y"
    { (yyval.i) = A_LANE; }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 681 "grammar.y"
    { (yyval.i) = A_METAC;	}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 682 "grammar.y"
    { (yyval.i) = A_BCC; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 683 "grammar.y"
    { (yyval.i) = A_OAMF4EC; }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 684 "grammar.y"
    { (yyval.i) = A_OAMF4SC; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 685 "grammar.y"
    { (yyval.i) = A_SC; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 686 "grammar.y"
    { (yyval.i) = A_ILMIC; }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 688 "grammar.y"
    { (yyval.i) = A_OAM; }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 689 "grammar.y"
    { (yyval.i) = A_OAMF4; }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 690 "grammar.y"
    { (yyval.i) = A_CONNECTMSG; }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 691 "grammar.y"
    { (yyval.i) = A_METACONNECT; }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 694 "grammar.y"
    { (yyval.blk).atmfieldtype = A_VPI; }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 695 "grammar.y"
    { (yyval.blk).atmfieldtype = A_VCI; }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 698 "grammar.y"
    { (yyval.blk).b = gen_atmfield_code((yyvsp[(0) - (2)].blk).atmfieldtype, (bpf_int32)(yyvsp[(2) - (2)].i), (bpf_u_int32)(yyvsp[(1) - (2)].i), 0); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 699 "grammar.y"
    { (yyval.blk).b = gen_atmfield_code((yyvsp[(0) - (2)].blk).atmfieldtype, (bpf_int32)(yyvsp[(2) - (2)].i), (bpf_u_int32)(yyvsp[(1) - (2)].i), 1); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 700 "grammar.y"
    { (yyval.blk).b = (yyvsp[(2) - (3)].blk).b; (yyval.blk).q = qerr; }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 702 "grammar.y"
    {
	(yyval.blk).atmfieldtype = (yyvsp[(0) - (1)].blk).atmfieldtype;
	if ((yyval.blk).atmfieldtype == A_VPI ||
	    (yyval.blk).atmfieldtype == A_VCI)
		(yyval.blk).b = gen_atmfield_code((yyval.blk).atmfieldtype, (bpf_int32) (yyvsp[(1) - (1)].i), BPF_JEQ, 0);
	}
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 710 "grammar.y"
    { gen_or((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 713 "grammar.y"
    { (yyval.i) = M_FISU; }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 714 "grammar.y"
    { (yyval.i) = M_LSSU; }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 715 "grammar.y"
    { (yyval.i) = M_MSU; }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 716 "grammar.y"
    { (yyval.i) = MH_FISU; }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 717 "grammar.y"
    { (yyval.i) = MH_LSSU; }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 718 "grammar.y"
    { (yyval.i) = MH_MSU; }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 721 "grammar.y"
    { (yyval.blk).mtp3fieldtype = M_SIO; }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 722 "grammar.y"
    { (yyval.blk).mtp3fieldtype = M_OPC; }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 723 "grammar.y"
    { (yyval.blk).mtp3fieldtype = M_DPC; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 724 "grammar.y"
    { (yyval.blk).mtp3fieldtype = M_SLS; }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 725 "grammar.y"
    { (yyval.blk).mtp3fieldtype = MH_SIO; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 726 "grammar.y"
    { (yyval.blk).mtp3fieldtype = MH_OPC; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 727 "grammar.y"
    { (yyval.blk).mtp3fieldtype = MH_DPC; }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 728 "grammar.y"
    { (yyval.blk).mtp3fieldtype = MH_SLS; }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 731 "grammar.y"
    { (yyval.blk).b = gen_mtp3field_code((yyvsp[(0) - (2)].blk).mtp3fieldtype, (u_int)(yyvsp[(2) - (2)].i), (u_int)(yyvsp[(1) - (2)].i), 0); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 732 "grammar.y"
    { (yyval.blk).b = gen_mtp3field_code((yyvsp[(0) - (2)].blk).mtp3fieldtype, (u_int)(yyvsp[(2) - (2)].i), (u_int)(yyvsp[(1) - (2)].i), 1); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 733 "grammar.y"
    { (yyval.blk).b = (yyvsp[(2) - (3)].blk).b; (yyval.blk).q = qerr; }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 735 "grammar.y"
    {
	(yyval.blk).mtp3fieldtype = (yyvsp[(0) - (1)].blk).mtp3fieldtype;
	if ((yyval.blk).mtp3fieldtype == M_SIO ||
	    (yyval.blk).mtp3fieldtype == M_OPC ||
	    (yyval.blk).mtp3fieldtype == M_DPC ||
	    (yyval.blk).mtp3fieldtype == M_SLS ||
	    (yyval.blk).mtp3fieldtype == MH_SIO ||
	    (yyval.blk).mtp3fieldtype == MH_OPC ||
	    (yyval.blk).mtp3fieldtype == MH_DPC ||
	    (yyval.blk).mtp3fieldtype == MH_SLS)
		(yyval.blk).b = gen_mtp3field_code((yyval.blk).mtp3fieldtype, (u_int) (yyvsp[(1) - (1)].i), BPF_JEQ, 0);
	}
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 749 "grammar.y"
    { gen_or((yyvsp[(1) - (3)].blk).b, (yyvsp[(3) - (3)].blk).b); (yyval.blk) = (yyvsp[(3) - (3)].blk); }
    break;



/* Line 1806 of yacc.c  */
#line 3826 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 751 "grammar.y"


