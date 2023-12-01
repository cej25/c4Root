/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 32 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"

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


#line 119 "mc_gen_onlyFATIMA/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#include "y.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_DOUBLE = 4,                     /* DOUBLE  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 6,                 /* IDENTIFIER  */
  YYSYMBOL_SIGNAL_MAPPING = 7,             /* SIGNAL_MAPPING  */
  YYSYMBOL_STICKY_MAPPING = 8,             /* STICKY_MAPPING  */
  YYSYMBOL_CALIB_PARAM = 9,                /* CALIB_PARAM  */
  YYSYMBOL_CALIB_PARAM_C = 10,             /* CALIB_PARAM_C  */
  YYSYMBOL_TOGGLE = 11,                    /* TOGGLE  */
  YYSYMBOL_UINT32 = 12,                    /* UINT32  */
  YYSYMBOL_UINT16 = 13,                    /* UINT16  */
  YYSYMBOL_UINT8 = 14,                     /* UINT8  */
  YYSYMBOL_15_ = 15,                       /* '+'  */
  YYSYMBOL_16_ = 16,                       /* '-'  */
  YYSYMBOL_17_ = 17,                       /* '*'  */
  YYSYMBOL_18_ = 18,                       /* '/'  */
  YYSYMBOL_UMINUS = 19,                    /* UMINUS  */
  YYSYMBOL_20_ = 20,                       /* ';'  */
  YYSYMBOL_21_ = 21,                       /* '('  */
  YYSYMBOL_22_ = 22,                       /* ','  */
  YYSYMBOL_23_ = 23,                       /* ')'  */
  YYSYMBOL_24_ = 24,                       /* '='  */
  YYSYMBOL_25_ = 25,                       /* '{'  */
  YYSYMBOL_26_ = 26,                       /* '}'  */
  YYSYMBOL_27_ = 27,                       /* ':'  */
  YYSYMBOL_28_ = 28,                       /* '.'  */
  YYSYMBOL_29_ = 29,                       /* '['  */
  YYSYMBOL_30_ = 30,                       /* ']'  */
  YYSYMBOL_31_ = 31,                       /* '^'  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_stmt_list = 34,                 /* stmt_list  */
  YYSYMBOL_stmt = 35,                      /* stmt  */
  YYSYMBOL_signal_mapping = 36,            /* signal_mapping  */
  YYSYMBOL_calib_param = 37,               /* calib_param  */
  YYSYMBOL_user_calib_param = 38,          /* user_calib_param  */
  YYSYMBOL_calib_type = 39,                /* calib_type  */
  YYSYMBOL_data_type = 40,                 /* data_type  */
  YYSYMBOL_toggle_null = 41,               /* toggle_null  */
  YYSYMBOL_toggle = 42,                    /* toggle  */
  YYSYMBOL_var_or_name = 43,               /* var_or_name  */
  YYSYMBOL_data_name = 44,                 /* data_name  */
  YYSYMBOL_var_ident_rec = 45,             /* var_ident_rec  */
  YYSYMBOL_var_ident = 46,                 /* var_ident  */
  YYSYMBOL_array_spec_list_null = 47,      /* array_spec_list_null  */
  YYSYMBOL_array_spec_list = 48,           /* array_spec_list  */
  YYSYMBOL_array_spec = 49,                /* array_spec  */
  YYSYMBOL_value_vector_np = 50,           /* value_vector_np  */
  YYSYMBOL_value_vector_np_single = 51,    /* value_vector_np_single  */
  YYSYMBOL_value_unit = 52,                /* value_unit  */
  YYSYMBOL_value = 53,                     /* value  */
  YYSYMBOL_unit = 54,                      /* unit  */
  YYSYMBOL_unit_part = 55,                 /* unit_part  */
  YYSYMBOL_unit_part_many = 56,            /* unit_part_many  */
  YYSYMBOL_unit_part_block = 57            /* unit_part_block  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   270


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "DOUBLE",
  "STRING", "IDENTIFIER", "SIGNAL_MAPPING", "STICKY_MAPPING",
  "CALIB_PARAM", "CALIB_PARAM_C", "TOGGLE", "UINT32", "UINT16", "UINT8",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'", "'('", "','", "')'", "'='",
  "'{'", "'}'", "':'", "'.'", "'['", "']'", "'^'", "$accept", "program",
  "stmt_list", "stmt", "signal_mapping", "calib_param", "user_calib_param",
  "calib_type", "data_type", "toggle_null", "toggle", "var_or_name",
  "data_name", "var_ident_rec", "var_ident", "array_spec_list_null",
  "array_spec_list", "array_spec", "value_vector_np",
  "value_vector_np_single", "value_unit", "value", "unit", "unit_part",
  "unit_part_many", "unit_part_block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    43,    45,    42,    47,   270,
      59,    40,    44,    41,    61,   123,   125,    58,    46,    91,
      93,    94
};
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
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
static const yytype_int8 yydefact[] =
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
static const yytype_uint8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    13,    50,    35,   141,
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
static const yytype_int8 yystos[] =
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
static const yytype_int8 yyr1[] =
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
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
      12,    12,     9,    10,     9,    10,     7,     8,     7,     7,
       4,     6,     1,     1,     0,     1,     3,     1,     1,     1,
       3,     2,     0,     1,     1,     2,     3,     1,     3,     1,
       1,     2,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     1,     1,     2,     1,     3,     3,     1,     2,     1,
       2,     3,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
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
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
  case 2: /* program: stmt_list  */
#line 172 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                { append_list(&all_mc_defs,(yyvsp[0].nodes)); }
#line 1271 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 4: /* stmt_list: stmt  */
#line 177 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                { (yyval.nodes) = create_list((yyvsp[0].node)); }
#line 1277 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 5: /* stmt_list: stmt_list stmt  */
#line 178 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                { (yyval.nodes) = append_list((yyvsp[-1].nodes),(yyvsp[0].node)); }
#line 1283 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 6: /* stmt: ';'  */
#line 183 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                                   { (yyval.node) = NULL; }
#line 1289 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 7: /* stmt: signal_mapping  */
#line 184 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                                   { (yyval.node) = (yyvsp[0].map); }
#line 1295 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 8: /* stmt: calib_param  */
#line 185 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                                   { (yyval.node) = (yyvsp[0].calib); }
#line 1301 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 9: /* stmt: user_calib_param  */
#line 186 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                                   { (yyval.node) = (yyvsp[0].user_calib); }
#line 1307 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 10: /* signal_mapping: SIGNAL_MAPPING '(' data_type ',' data_name ',' var_or_name ',' toggle_null var_or_name ')' ';'  */
#line 195 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
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
#line 1325 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 11: /* signal_mapping: STICKY_MAPPING '(' data_type ',' data_name ',' var_or_name ',' toggle_null var_or_name ')' ';'  */
#line 209 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
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
#line 1343 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 12: /* calib_param: CALIB_PARAM '(' IDENTIFIER ',' calib_type ',' value_vector_np ')' ';'  */
#line 232 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
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
#line 1358 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 13: /* calib_param: CALIB_PARAM '(' toggle IDENTIFIER ',' calib_type ',' value_vector_np ')' ';'  */
#line 243 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
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
#line 1373 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 14: /* calib_param: CALIB_PARAM_C '(' var_or_name ',' calib_type ',' value_vector_np ')' ';'  */
#line 254 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),0);
          }
#line 1387 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 15: /* calib_param: CALIB_PARAM_C '(' toggle var_or_name ',' calib_type ',' value_vector_np ')' ';'  */
#line 264 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),(yyvsp[-7].iValue));
          }
#line 1401 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 16: /* calib_param: var_or_name '=' calib_type '(' value_vector_np ')' ';'  */
#line 274 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),0);
          }
#line 1415 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 17: /* calib_param: toggle var_or_name '=' calib_type '(' value_vector_np ')' ';'  */
#line 284 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *src_info  =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_RAW | SID_MAP_MIRROR_MAP);
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-6].var),SID_MAP_CAL);
	    delete (yyvsp[-6].var);
	    (yyval.calib) = new calib_param(CURR_FILE_LINE,src_info,dest_info,
				 (yyvsp[-4].iValue),(yyvsp[-2].v_double_unit),(yyvsp[-7].iValue));
          }
#line 1429 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 18: /* user_calib_param: CALIB_PARAM '(' IDENTIFIER ',' value_vector_np ')' ';'  */
#line 297 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    signal_id id;
	    dissect_name(CURR_FILE_LINE,(yyvsp[-4].strValue),id);
	    const signal_id_info *dest_info =
	      get_signal_id_info(&id,SID_MAP_CALIB);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-2].v_double_unit));
          }
#line 1441 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 19: /* user_calib_param: CALIB_PARAM_C '(' var_or_name ',' value_vector_np ')' ';'  */
#line 305 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-4].var),SID_MAP_CALIB);
	    delete (yyvsp[-4].var);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-2].v_double_unit));
          }
#line 1452 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 20: /* user_calib_param: var_or_name '=' value_vector_np_single ';'  */
#line 312 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-3].var),SID_MAP_CALIB);
	    delete (yyvsp[-3].var);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-1].v_double_unit));
          }
#line 1463 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 21: /* user_calib_param: var_or_name '=' '{' value_vector_np '}' ';'  */
#line 319 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    const signal_id_info *dest_info =
	      get_signal_id_info((yyvsp[-5].var),SID_MAP_CALIB);
	    delete (yyvsp[-5].var);
	    (yyval.user_calib) = new user_calib_param(CURR_FILE_LINE,dest_info,(yyvsp[-2].v_double_unit));
          }
#line 1474 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 22: /* calib_type: IDENTIFIER  */
#line 336 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                     { (yyval.iValue) = calib_param_type((yyvsp[0].strValue));
	    if (!(yyval.iValue)) { yyerror("Unknown calibration type."); YYERROR; } }
#line 1481 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 23: /* data_type: IDENTIFIER  */
#line 343 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                     { (yyval.iValue) = 0; /* $$ = data_type($1); if (!$$) { yyerror("Unknown data type."); YYERROR; } */ }
#line 1487 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 24: /* toggle_null: %empty  */
#line 347 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                      { (yyval.iValue) = 0; }
#line 1493 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 26: /* toggle: TOGGLE INTEGER ':'  */
#line 352 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                             {
	    if ((yyvsp[-1].iValue) == 1)      { (yyval.iValue) = 1; }
	    else if ((yyvsp[-1].iValue) == 2) { (yyval.iValue) = 2; }
	    else {
	      yyerror("Toggle # must be 1 or 2.");
	    }
	  }
#line 1505 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 27: /* var_or_name: var_ident_rec  */
#line 362 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                        { (yyval.var) = new signal_id(); (yyval.var)->take_over((yyvsp[0].var_vect)); /* Note: this deletes $1! */ }
#line 1511 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 28: /* data_name: IDENTIFIER  */
#line 366 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                     { (yyval.var) = NULL; /* $$ = new signal_id(); dissect_name(0,$1,*$$); */ }
#line 1517 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 29: /* var_ident_rec: var_ident  */
#line 370 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                      { (yyval.var_vect) = (yyvsp[0].var_vect); }
#line 1523 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 30: /* var_ident_rec: var_ident_rec '.' var_ident  */
#line 371 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                      { (yyval.var_vect) = (yyvsp[-2].var_vect); (yyval.var_vect)->insert((yyval.var_vect)->end(),(yyvsp[0].var_vect)->begin(),(yyvsp[0].var_vect)->end()); delete (yyvsp[0].var_vect); }
#line 1529 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 31: /* var_ident: IDENTIFIER array_spec_list_null  */
#line 376 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    (yyval.var_vect) = new sig_part_ptr_vector;
	    (yyval.var_vect)->push_back(new sig_part((yyvsp[-1].strValue)));
	    if ((yyvsp[0].var_vect))
	      {
		(yyval.var_vect)->insert((yyval.var_vect)->end(),(yyvsp[0].var_vect)->begin(),(yyvsp[0].var_vect)->end());
		delete (yyvsp[0].var_vect);
	      }
	  }
#line 1543 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 32: /* array_spec_list_null: %empty  */
#line 388 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.var_vect) = NULL; }
#line 1549 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 33: /* array_spec_list_null: array_spec_list  */
#line 389 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.var_vect) = (yyvsp[0].var_vect); }
#line 1555 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 34: /* array_spec_list: array_spec  */
#line 393 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.var_vect) = new sig_part_ptr_vector; (yyval.var_vect)->push_back((yyvsp[0].var_part)); }
#line 1561 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 35: /* array_spec_list: array_spec_list array_spec  */
#line 394 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyvsp[-1].var_vect)->push_back((yyvsp[0].var_part)); (yyval.var_vect) = (yyvsp[-1].var_vect); }
#line 1567 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 36: /* array_spec: '[' INTEGER ']'  */
#line 398 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.var_part) = new sig_part((yyvsp[-1].iValue)); }
#line 1573 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 37: /* value_vector_np: value_vector_np_single  */
#line 410 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                            { (yyval.v_double_unit) = (yyvsp[0].v_double_unit); }
#line 1579 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 38: /* value_vector_np: value_vector_np ',' value_unit  */
#line 411 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                            { (yyval.v_double_unit) = (yyvsp[-2].v_double_unit); (yyval.v_double_unit)->push_back((yyvsp[0].du)); }
#line 1585 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 39: /* value_vector_np_single: value_unit  */
#line 415 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                            { (yyval.v_double_unit) = new vect_double_unit; (yyval.v_double_unit)->push_back((yyvsp[0].du)); }
#line 1591 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 40: /* value_unit: value  */
#line 419 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.du)._value = (yyvsp[0].fValue); (yyval.du)._unit = NULL; }
#line 1597 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 41: /* value_unit: value unit  */
#line 420 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.du)._value = (yyvsp[-1].fValue); (yyval.du)._unit = insert_units_exp(CURR_FILE_LINE,(yyvsp[0].strValue)); }
#line 1603 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 42: /* value: DOUBLE  */
#line 425 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[0].fValue); }
#line 1609 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 43: /* value: INTEGER  */
#line 426 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[0].iValue); }
#line 1615 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 44: /* value: '-' value  */
#line 427 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = -(yyvsp[0].fValue); }
#line 1621 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 45: /* value: '+' value  */
#line 428 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[0].fValue); }
#line 1627 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 46: /* value: value '+' value  */
#line 429 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[-2].fValue) + (yyvsp[0].fValue); }
#line 1633 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 47: /* value: value '-' value  */
#line 430 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[-2].fValue) - (yyvsp[0].fValue); }
#line 1639 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 48: /* value: value '*' value  */
#line 431 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[-2].fValue) * (yyvsp[0].fValue); }
#line 1645 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 49: /* value: value '/' value  */
#line 433 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
          {
	    if ((yyvsp[0].fValue) == 0.0)
	      yyerror("Warning: Division by zero.");
	    (yyval.fValue) = (yyvsp[-2].fValue) / (yyvsp[0].fValue);
	  }
#line 1655 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 50: /* value: '(' value ')'  */
#line 438 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                  { (yyval.fValue) = (yyvsp[-1].fValue); }
#line 1661 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 51: /* unit: STRING  */
#line 443 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                        { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1667 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 52: /* unit: unit_part  */
#line 444 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                        { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1673 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 53: /* unit: '/' unit_part  */
#line 445 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                        { (yyval.strValue) = find_concat_str_strings("/",(yyvsp[0].strValue),""); }
#line 1679 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 54: /* unit_part: unit_part_many  */
#line 449 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1685 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 55: /* unit_part: unit_part_many '*' unit_part  */
#line 450 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"*",(yyvsp[0].strValue)); }
#line 1691 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 56: /* unit_part: unit_part_many '/' unit_part  */
#line 451 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                       { (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"/",(yyvsp[0].strValue)); }
#line 1697 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 57: /* unit_part_many: unit_part_block  */
#line 455 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                         { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1703 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 58: /* unit_part_many: unit_part_many unit_part_block  */
#line 456 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                         { (yyval.strValue) = find_concat_str_strings((yyvsp[-1].strValue)," ",(yyvsp[0].strValue)); }
#line 1709 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 59: /* unit_part_block: IDENTIFIER  */
#line 460 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                 { (yyval.strValue) = (yyvsp[0].strValue); }
#line 1715 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 60: /* unit_part_block: IDENTIFIER INTEGER  */
#line 461 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                 { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-1].strValue),tmp,""); }
#line 1722 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 61: /* unit_part_block: IDENTIFIER '-' INTEGER  */
#line 463 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                 { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"-",tmp); }
#line 1729 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 62: /* unit_part_block: IDENTIFIER '^' INTEGER  */
#line 465 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                     { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-2].strValue),"^",tmp); }
#line 1736 "mc_gen_onlyFATIMA/y.tab.c"
    break;

  case 63: /* unit_part_block: IDENTIFIER '^' '-' INTEGER  */
#line 467 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"
                                     { char tmp[32];
	    sprintf (tmp,"%d",(yyvsp[0].iValue)); (yyval.strValue) = find_concat_str_strings((yyvsp[-3].strValue),"^-",tmp); }
#line 1743 "mc_gen_onlyFATIMA/y.tab.c"
    break;


#line 1747 "mc_gen_onlyFATIMA/y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 471 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"


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
