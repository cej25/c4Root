/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MC_GEN_ONLYFATIMA_Y_TAB_H_INCLUDED
# define YY_YY_MC_GEN_ONLYFATIMA_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INTEGER = 258,                 /* INTEGER  */
    DOUBLE = 259,                  /* DOUBLE  */
    STRING = 260,                  /* STRING  */
    IDENTIFIER = 261,              /* IDENTIFIER  */
    SIGNAL_MAPPING = 262,          /* SIGNAL_MAPPING  */
    STICKY_MAPPING = 263,          /* STICKY_MAPPING  */
    CALIB_PARAM = 264,             /* CALIB_PARAM  */
    CALIB_PARAM_C = 265,           /* CALIB_PARAM_C  */
    TOGGLE = 266,                  /* TOGGLE  */
    UINT32 = 267,                  /* UINT32  */
    UINT16 = 268,                  /* UINT16  */
    UINT8 = 269,                   /* UINT8  */
    UMINUS = 270                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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
#line 80 "/u/jlarsson/ucesb/mapcalib/mc_parser.y"

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

#line 122 "mc_gen_onlyFATIMA/y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MC_GEN_ONLYFATIMA_Y_TAB_H_INCLUDED  */
