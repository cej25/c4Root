/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 32 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:337  */

#define YYERROR_VERBOSE

#define YYTYPE_INT16 int

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "mc_def.hh"
#include "str_set.hh"

#include "signal_id_map.hh"
#include "../common/prefix_unit.hh"

//#include "parse_error.hh"

//#include "file_line.hh"

int yylex(void);

int yyparse(void);

void yyerror(const char *s);

extern int yylineno;

void print_lineno(FILE* fid,int internal);
/*
struct md_ident_fl
{
 public:
  md_ident_fl(const char *id,const file_line &loc)
  {
    _id   = id;
    _loc = loc;
  }

 public:
  const char *_id;
  file_line   _loc;
};
*/

#define CURR_FILE_LINE file_line(yylineno)


#line 118 "mc_gen_NovTest/y.tab.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_MC_GEN_NOVTEST_Y_TAB_H_INCLUDED
# define YY_YY_MC_GEN_NOVTEST_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    DOUBLE = 259,
    STRING = 260,
    IDENTIFIER = 261,
    SIGNAL_MAPPING = 262,
    STICKY_MAPPING = 263,
    CALIB_PARAM = 264,
    CALIB_PARAM_C = 265,
    TOGGLE = 266,
    UINT32 = 267,
    UINT16 = 268,
    UINT8 = 269,
    UMINUS = 270
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define DOUBLE 259
#define STRING 260
#define IDENTIFIER 261
#define SIGNAL_MAPPING 262
#define STICKY_MAPPING 263
#define CALIB_PARAM 264
#define CALIB_PARAM_C 265
#define TOGGLE 266
#define UINT32 267
#define UINT16 268
#define UINT8 269
#define UMINUS 270

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 80 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:352  */

  // What we get from the lexer:

  double  fValue;              /* double value */
  int     iValue;              /* integer value */
  const char *strValue;        /* string */

  // We generate internally:

  def_node       *node;
  def_node_list  *nodes;

  map_info       *map;
  calib_param    *calib;
  user_calib_param    *user_calib;

  sig_part            *var_part;
  sig_part_ptr_vector *var_vect;
  signal_id           *var;

  double_unit          du;

  vect_double_unit    *v_double_unit;

#line 216 "mc_gen_NovTest/y.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MC_GEN_NOVTEST_Y_TAB_H_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

#define YYUNDEFTOK  2
#define YYMAXUTOK   270

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      21,    23,    17,    15,    22,    16,    28,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,    20,
       2,    24,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
      19
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   172,   172,   173,   177,   178,   183,   184,   185,   186,
     194,   208,   231,   242,   253,   263,   273,   283,   296,   304,
     311,   318,   336,   343,   347,   348,   352,   362,   366,   370,
     371,   375,   388,   389,   393,   394,   398,   410,   411,   415,
     419,   420,   425,   426,   427,   428,   429,   430,   431,   432,
     438,   443,   444,   445,   449,   450,   451,   455,   456,   460,
     461,   463,   465,   467
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "DOUBLE", "STRING",
  "IDENTIFIER", "SIGNAL_MAPPING", "STICKY_MAPPING", "CALIB_PARAM",
  "CALIB_PARAM_C", "TOGGLE", "UINT32", "UINT16", "UINT8", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "';'", "'('", "','", "')'", "'='", "'{'", "'}'",
  "':'", "'.'", "'['", "']'", "'^'", "$accept", "program", "stmt_list",
  "stmt", "signal_mapping", "calib_param", "user_calib_param",
  "calib_type", "data_type", "toggle_null", "toggle", "var_or_name",
  "data_name", "var_ident_rec", "var_ident", "array_spec_list_null",
  "array_spec_list", "array_spec", "value_vector_np",
  "value_vector_np_single", "value_unit", "value", "unit", "unit_part",
  "unit_part_many", "unit_part_block", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    43,    45,    42,    47,   270,
      59,    40,    44,    41,    61,   123,   125,    58,    46,    91,
      93,    94
};
# endif

#define YYPACT_NINF -69

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-69)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      88,   -21,    35,    44,    47,    48,    51,   -69,    32,    88,
     -69,   -69,   -69,   -69,    68,    65,    56,   -69,   114,   -69,
     -21,   -69,   112,   112,    13,    33,    92,   -69,   -69,    96,
       6,    68,    94,   -69,   -69,    99,   100,   101,   119,    68,
     104,   -69,   122,   -69,   -69,   -69,    67,    67,    67,    67,
     109,   111,   -69,    85,   -69,   -69,   126,   126,    46,   113,
     115,    46,   117,   -69,   -69,    62,    29,   -69,    67,   -69,
     -69,     2,    67,    67,    67,    60,   -69,   -69,    20,   -69,
     -69,   118,   120,   121,    23,   122,   122,   123,    37,    67,
      67,   -69,    67,   116,    64,   -69,   130,    14,    11,    11,
     -69,   -69,   -69,   128,   128,   -69,    68,    68,    67,   124,
     125,   127,    67,   131,    82,   -69,   -69,   132,   -69,   -69,
     136,   -69,   -69,   133,   134,    84,   -69,    67,    67,    87,
     -69,   137,   -69,   -69,   135,   135,   138,    91,    93,   139,
     -69,    68,   -69,    68,   -69,   140,   141,   -69,   142,   143,
     -69,   -69,   144,   147,   -69,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    32,     0,     0,     0,     0,     0,     6,     0,     2,
       4,     7,     8,     9,     0,     0,    27,    29,     0,    31,
      33,    34,     0,     0,     0,     0,     0,     1,     5,     0,
       0,     0,     0,    35,    23,     0,     0,     0,     0,     0,
       0,    26,     0,    43,    42,    22,     0,     0,     0,     0,
       0,     0,    39,    40,    30,    36,     0,     0,     0,     0,
       0,     0,     0,    45,    44,     0,     0,    37,     0,    20,
      51,    59,     0,     0,     0,     0,    41,    52,    54,    57,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,     0,    60,     0,     0,    46,    47,
      48,    49,    53,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    21,     0,    61,    62,
       0,    55,    56,     0,     0,     0,    18,     0,     0,     0,
      19,     0,    16,    63,    24,    24,     0,     0,     0,     0,
      17,     0,    25,     0,    12,     0,     0,    14,     0,     0,
      13,    15,     0,     0,    10,    11
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   -69,   145,   -69,   -69,   -69,   -38,   146,    15,
     -23,   -14,   105,   -69,   110,   -69,   -69,   148,   -55,   149,
      61,   -32,   -69,   -68,   -69,    70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    13,    50,    35,   141,
      14,    15,    81,    16,    17,    19,    20,    21,    66,    67,
      52,    53,    76,    77,    78,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      29,    38,    39,    84,    62,    95,    88,   102,    18,    43,
      44,    40,    45,    94,    63,    64,    65,   119,    96,    37,
      83,    46,    47,    87,     6,    60,    71,    48,    74,    90,
     120,    49,    27,    97,   114,   121,   122,   103,   104,     1,
      98,    99,   100,   101,     6,    92,   109,   110,   111,    43,
      44,    92,    45,   125,    26,    93,    22,   129,   101,    92,
     113,    46,    47,    43,    44,    23,    71,    48,    24,    25,
      43,    44,   137,   138,     1,    46,    47,    72,    73,    74,
      90,    48,    46,    47,    31,    91,    92,   117,    48,    30,
      70,    71,   123,   124,     1,     2,     3,     4,     5,     6,
      72,    73,    74,    75,    92,   131,    92,   136,     7,    92,
     139,   142,   142,    92,   145,    92,   146,    32,    34,    41,
      42,    56,    57,    58,    55,    59,    61,   148,    45,   149,
      68,    69,    80,   118,    71,    85,   116,    86,    89,   133,
     106,    54,   107,   108,   126,   112,     6,   127,   105,   128,
     143,   130,   132,   115,    28,   134,   135,   140,   144,   147,
     150,   151,    82,     0,   154,   152,   153,   155,    33,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51
};

static const yytype_int16 yycheck[] =
{
      14,    24,    25,    58,    42,     3,    61,    75,    29,     3,
       4,    25,     6,    68,    46,    47,    48,     3,    16,     6,
      58,    15,    16,    61,    11,    39,     6,    21,    17,    18,
      16,    25,     0,    31,    89,   103,   104,    17,    18,     6,
      72,    73,    74,    75,    11,    22,    23,    85,    86,     3,
       4,    22,     6,   108,     3,    26,    21,   112,    90,    22,
      23,    15,    16,     3,     4,    21,     6,    21,    21,    21,
       3,     4,   127,   128,     6,    15,    16,    15,    16,    17,
      18,    21,    15,    16,    28,    23,    22,    23,    21,    24,
       5,     6,   106,   107,     6,     7,     8,     9,    10,    11,
      15,    16,    17,    18,    22,    23,    22,    23,    20,    22,
      23,   134,   135,    22,    23,    22,    23,     3,     6,    27,
      24,    22,    22,    22,    30,     6,    22,   141,     6,   143,
      21,    20,     6,     3,     6,    22,    20,    22,    21,     3,
      22,    31,    22,    22,    20,    22,    11,    22,    78,    22,
     135,    20,    20,    92,     9,    22,    22,    20,    20,    20,
      20,    20,    57,    -1,    20,    23,    23,    20,    20,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    11,    20,    33,    34,
      35,    36,    37,    38,    42,    43,    45,    46,    29,    47,
      48,    49,    21,    21,    21,    21,     3,     0,    35,    43,
      24,    28,     3,    49,     6,    40,    40,     6,    42,    42,
      43,    27,    24,     3,     4,     6,    15,    16,    21,    25,
      39,    51,    52,    53,    46,    30,    22,    22,    22,     6,
      43,    22,    39,    53,    53,    53,    50,    51,    21,    20,
       5,     6,    15,    16,    17,    18,    54,    55,    56,    57,
       6,    44,    44,    39,    50,    22,    22,    39,    50,    21,
      18,    23,    22,    26,    50,     3,    16,    31,    53,    53,
      53,    53,    55,    17,    18,    57,    22,    22,    22,    23,
      39,    39,    22,    23,    50,    52,    20,    23,     3,     3,
      16,    55,    55,    43,    43,    50,    20,    22,    22,    50,
      20,    23,    20,     3,    22,    22,    23,    50,    50,    23,
      20,    41,    42,    41,    20,    23,    23,    20,    43,    43,
      20,    20,    23,    23,    20,    20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    34,    34,    35,    35,    35,    35,
      36,    36,    37,    37,    37,    37,    37,    37,    38,    38,
      38,    38,    39,    40,    41,    41,    42,    43,    44,    45,
      45,    46,    47,    47,    48,    48,    49,    50,    50,    51,
      52,    52,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    55,    55,    55,    56,    56,    57,
      57,    57,    57,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
      12,    12,     9,    10,     9,    10,     7,     8,     7,     7,
       4,     6,     1,     1,     0,     1,     3,     1,     1,     1,
       3,     2,     0,     1,     1,     2,     3,     1,     3,     1,
       1,     2,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     1,     1,     2,     1,     3,     3,     1,     2,     1,
       2,     3,     3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

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
#line 172 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { append_list(&all_mc_defs,(yyvsp[0].nodes)); }
#line 1411 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 4:
#line 177 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.nodes) = create_list((yyvsp[0].node)); }
#line 1417 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 5:
#line 178 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.nodes) = append_list((yyvsp[-1].nodes),(yyvsp[0].node)); }
#line 1423 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 6:
#line 183 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.node) = NULL; }
#line 1429 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 184 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].map); }
#line 1435 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 8:
#line 185 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].calib); }
#line 1441 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 9:
#line 186 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].user_calib); }
#line 1447 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 10:
#line 195 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-5].var),SID_MAP_UNPACK | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-2].var),SID_MAP_RAW);
	    /*const signal_id_info *rev_src_info  = get_signal_id_info($9,SID_MAP_RAW | SID_MAP_MIRROR_MAP | SID_MAP_REVERSE);*/
	      /*const signal_id_info *rev_dest_info = get_signal_id_info($7,SID_MAP_UNPACK);*/
	    delete (yyvsp[-5].var);
	    delete (yyvsp[-2].var);
	    (yyval.map) = new map_info(CURR_FILE_LINE,src_info,dest_info,
			      NULL,NULL/*,rev_src_info,rev_dest_info*/,
			      0,(yyvsp[-3].iValue));
          }
#line 1465 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 11:
#line 209 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-5].var),SID_MAP_UNPACK | SID_MAP_STICKY | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-2].var),SID_MAP_RAW | SID_MAP_STICKY);
	    /*const signal_id_info *rev_src_info  = get_signal_id_info($9,SID_MAP_RAW | SID_MAP_MIRROR_MAP | SID_MAP_REVERSE);*/
	      /*const signal_id_info *rev_dest_info = get_signal_id_info($7,SID_MAP_UNPACK);*/
	    delete (yyvsp[-5].var);
	    delete (yyvsp[-2].var);
	    (yyval.map) = new map_info(CURR_FILE_LINE,src_info,dest_info,
			      NULL,NULL/*,rev_src_info,rev_dest_info*/,
			      1,(yyvsp[-3].iValue));
          }
#line 1483 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 12:
#line 232 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    signal_id id;
	    dissect_name(CURR_FILE_LINE,(yyvsp[-6].strValue),id);
	    const signal_id_info *src_info  =
	      get_signal_id_info(&id,SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info(&id,SID_MAP_CAL);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),0);
          }
#line 1498 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 13:
#line 243 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    signal_id id;
	    dissect_name(CURR_FILE_LINE,(yyvsp[-6].strValue),id);
	    const signal_id_info *src_info  =
	      get_signal_id_info(&id,SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info(&id,SID_MAP_CAL);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),(yyvsp[-7].iValue));
          }
#line 1513 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 254 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),0);
          }
#line 1527 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 15:
#line 264 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),(yyvsp[-7].iValue));
          }
#line 1541 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 274 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),0);
          }
#line 1555 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 17:
#line 284 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),(yyvsp[-7].iValue));
          }
#line 1569 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 18:
#line 297 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    signal_id id;
	    dissect_name(CURR_FILE_LINE,(yyvsp[-4].strValue),id);
	    const signal_id_info *dest_info =
	      get_signal_id_info(&id,SID_MAP_CALIB);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-2].v_double_unit));
          }
#line 1581 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 19:
#line 305 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-4].var),SID_MAP_CALIB);
	    delete (yyvsp[-4].var);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-2].v_double_unit));
          }
#line 1592 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 20:
#line 312 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-3].var),SID_MAP_CALIB);
	    delete (yyvsp[-3].var);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-1].v_double_unit));
          }
#line 1603 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 21:
#line 319 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-5].var),SID_MAP_CALIB);
	    delete (yyvsp[-5].var);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-2].v_double_unit));
          }
#line 1614 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 336 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.iValue) = calib_param_type((yyvsp[0].strValue));
	    if (!(yyval.iValue)) { yyerror("Unknown calibration type."); YYERROR; } }
#line 1621 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 343 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.iValue) = 0; /* $$ = data_type($1); if (!$$) { yyerror("Unknown data type."); YYERROR; } */ }
#line 1627 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 347 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.iValue) = 0; }
#line 1633 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 352 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    if ((yyvsp[-1].iValue) == 1)      { (yyval.iValue) = 1; }
	    else if ((yyvsp[-1].iValue) == 2) { (yyval.iValue) = 2; }
	    else {
	      yyerror("Toggle # must be 1 or 2.");
	    }
	  }
#line 1645 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 362 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var) = new signal_id(); (yyval.var)->take_over((yyvsp[0].var_vect)); /* Note: this deletes $1! */ }
#line 1651 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 366 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var) = NULL; /* $$ = new signal_id(); dissect_name(0,$1,*$$); */ }
#line 1657 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 370 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var_vect) = (yyvsp[0].var_vect); }
#line 1663 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 371 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var_vect) = (yyvsp[-2].var_vect); (yyval.var_vect)->insert((yyval.var_vect)->end(),(yyvsp[0].var_vect)->begin(),(yyvsp[0].var_vect)->end()); delete (yyvsp[0].var_vect); }
#line 1669 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 376 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    (yyval.var_vect) = new sig_part_ptr_vector;
	    (yyval.var_vect)->push_back(new sig_part((yyvsp[-1].strValue)));
	    if ((yyvsp[0].var_vect))
	      {
		(yyval.var_vect)->insert((yyval.var_vect)->end(),(yyvsp[0].var_vect)->begin(),(yyvsp[0].var_vect)->end());
		delete (yyvsp[0].var_vect);
	      }
	  }
#line 1683 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 388 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var_vect) = NULL; }
#line 1689 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 389 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var_vect) = (yyvsp[0].var_vect); }
#line 1695 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 393 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var_vect) = new sig_part_ptr_vector; (yyval.var_vect)->push_back((yyvsp[0].var_part)); }
#line 1701 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 394 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyvsp[-1].var_vect)->push_back((yyvsp[0].var_part)); (yyval.var_vect) = (yyvsp[-1].var_vect); }
#line 1707 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 398 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.var_part) = new sig_part((yyvsp[-1].iValue)); }
#line 1713 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 410 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.v_double_unit) = (yyvsp[0].v_double_unit); }
#line 1719 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 411 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.v_double_unit) = (yyvsp[-2].v_double_unit); (yyval.v_double_unit)->push_back((yyvsp[0].du)); }
#line 1725 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 415 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.v_double_unit) = new vect_double_unit; (yyval.v_double_unit)->push_back((yyvsp[0].du)); }
#line 1731 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 419 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.du)._value = (yyvsp[0].fValue); (yyval.du)._unit = NULL; }
#line 1737 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 420 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.du)._value = (yyvsp[-1].fValue); (yyval.du)._unit = insert_units_exp(CURR_FILE_LINE,(yyvsp[0].strValue)); }
#line 1743 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 425 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[0].fValue); }
#line 1749 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 426 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[0].iValue); }
#line 1755 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 427 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = -(yyvsp[0].fValue); }
#line 1761 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 428 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[0].fValue); }
#line 1767 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 429 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[-2].fValue) + (yyvsp[0].fValue); }
#line 1773 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 430 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[-2].fValue) - (yyvsp[0].fValue); }
#line 1779 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 431 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[-2].fValue) * (yyvsp[0].fValue); }
#line 1785 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 433 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    {
	    if ((yyvsp[0].fValue) == 0.0)
	      yyerror("Warning: Division by zero.");
	    (yyval.fValue) = (yyvsp[-2].fValue) / (yyvsp[0].fValue);
	  }
#line 1795 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 50:
#line 438 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.fValue) = (yyvsp[-1].fValue); }
#line 1801 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 443 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1807 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 444 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1813 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 445 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = find_concat_str_strings("/",(yyvsp[0].strValue),""); }
#line 1819 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 449 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1825 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 450 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"*",(yyvsp[0].strValue)); }
#line 1831 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 451 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"/",(yyvsp[0].strValue)); }
#line 1837 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 455 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1843 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 456 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = find_concat_str_strings((yyvsp[-1].strValue)," ",(yyvsp[0].strValue)); }
#line 1849 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 460 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1855 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 461 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-1].strValue),tmp,""); }
#line 1862 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 463 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"-",tmp); }
#line 1869 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 465 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"^",tmp); }
#line 1876 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 467 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1652  */
    { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-3].strValue),"^-",tmp); }
#line 1883 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
    break;


#line 1887 "mc_gen_NovTest/y.tab.c" /* yacc.c:1652  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 471 "/u/jbormans/c4Root/unpack/exps/../../..//ucesb/mapcalib/mc_parser.y" /* yacc.c:1918  */


void yyerror(const char *s) {
  print_lineno(stderr,yylineno);
  fprintf(stderr," %s\n", s);
/*
  Current.first_line   = Rhs[1].first_line;
  Current.first_column = Rhs[1].first_column;
  Current.last_line    = Rhs[N].last_line;
  Current.last_column  = Rhs[N].last_column;
*/
  throw error();
}

bool parse_definitions()
{
  // yylloc.first_line = yylloc.last_line = 1;
  // yylloc.first_column = yylloc.last_column = 0;

  return yyparse() == 0;
}
