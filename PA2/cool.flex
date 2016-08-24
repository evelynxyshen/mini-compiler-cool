/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

int comments_nest_level = 0;

#undef STRING_LENGTH_CHECK
#define STRING_LENGTH_CHECK \
  if(string_buf_ptr >= (string_buf + MAX_STR_CONST)){ \
    cool_yylval.error_msg = "String constant too long"; \
    BEGIN(string_error);  \
  } else \

%}

/* start state for comments */
%x dash_comments
%x star_comments

/* start state for string */
%x string   
%x string_error

/*
 * Define names for regular expressions here.
 */

delim_no_newline     (' '|[\f\r\t\v])
white     (delim_no_newline)+

DARROW          =>
ASSIGN          <-

%%


 /*
  *  Nested comments
  */
"--"  { BEGIN(dash_comments); }
<dash_comments>.* {}
<dash_comments>\n  { BEGIN(INITIAL);  curr_lineno++;}

<dash_comments><<EOF>>  { 
  cool_yylval.error_msg = "EOF in comment";
  BEGIN(INITIAL); 
  return ERROR; 
}

"(*"                    { comments_nest_level ++;   BEGIN(star_comments); }

<star_comments>"("+[^*\n]*  {}

  /*  if "(" is followed by "*", this rule has the longest match */
<star_comments>"("+"*"  { comments_nest_level ++;  }

<star_comments>[^*\n(]*    {}

  /* "*** )" is not treated as end, also handle *\n case  */
<star_comments>"*"+[^*)\n(]* {}

  /* \n is specially treated to increase the line number */
<star_comments>[\n]       {  curr_lineno++; }

  /* ***) is the same as *). If there is [*]+[)], this match is the longest */
<star_comments>"*"+")"  { comments_nest_level --;
  if(comments_nest_level <= 0)  BEGIN(INITIAL); }

<star_comments><<EOF>>  { cool_yylval.error_msg = "EOF in comment";
  comments_nest_level = 0;
  BEGIN(INITIAL); return ERROR; }
  
  /* unmatched comments deliminator */
"*)"  { cool_yylval.error_msg = "Unmatched *)";
        return ERROR; }

 /* white space */
  /*{white}     {}*/
[ \f\r\t\v]+   {}
\n          {  curr_lineno++;  }

 /*
  *  The multiple-character operators.
  */
{DARROW}		{ return (DARROW);  }
{ASSIGN}    { return (ASSIGN);  }
"<="        { return LE;        }

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */

[cC][lL][aA][sS][sS]  { return CLASS;   }
[eE][lL][sS][eE]      { return ELSE;    }
[fF][iI]              { return FI;      }
[iI][fF]              { return IF;      }
[iI][nN]              { return IN;      }
[iI][nN][hH][eE][rR][iI][tT][sS]  { return INHERITS;}
[iI][sS][vV][oO][iI][dD]    { return ISVOID;  }
[lL][eE][tT]          { return LET;     }
[lL][oO][oO][pP]      { return LOOP;    }
[pP][oO][oO][lL]      { return POOL;    }
[tT][hH][eE][nN]      { return THEN;    }
[wW][hH][iI][lL][eE]  { return WHILE;   }
[cC][aA][sS][eE]      { return CASE;    }
[eE][sS][aA][cC]      { return ESAC;    }
[nN][eE][wW]          { return NEW;     }
[oO][fF]              { return OF;      }
[nN][oO][tT]          { return NOT;     }

t[rR][uU][eE]         { cool_yylval.boolean = true; return BOOL_CONST;  }
f[aA][lL][sS][eE]     { cool_yylval.boolean = false;  return BOOL_CONST;  }

  /* Integers */

[0-9]+  {
  cool_yylval.symbol = inttable.add_string(yytext);
  return INT_CONST; 
}

  /* Type identifiers, begin with capital letter */
[A-Z]([a-zA-Z]|[0-9]|"_")*  {
  cool_yylval.symbol = idtable.add_string(yytext);
  return TYPEID;
}

  /* Object identifiers, begin with lower case letter */
[a-z]([a-zA-Z]|[0-9]|"_")*  {
  cool_yylval.symbol = idtable.add_string(yytext);
  return OBJECTID;
}
  /* special notation */

"{"   { return '{'; }
"("   { return '('; }
")"   { return ')'; }
"}"   { return '}'; }
":"   { return ':'; }
";"   { return ';'; }
\.    { return '.'; }
"+"   { return '+'; }
"/"   { return '/'; }
"-"   { return '-'; }
"*"   { return '*'; }
"="   { return '='; }
"<"   { return '<'; }
"~"   { return '~'; }
","   { return ','; }
"@"   { return '@'; }


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */

\"    {
        string_buf_ptr = string_buf; /* ready to record this string */
        BEGIN(string);
}

<string>\"  {  /* copy string done, end this string and return */
  BEGIN(INITIAL);
  if(string_buf_ptr < string_buf + MAX_STR_CONST ){
    *string_buf_ptr = '\0';
    cool_yylval.symbol = stringtable.add_string(string_buf, MAX_STR_CONST);
    return STR_CONST;
  } else {
    cool_yylval.error_msg = "String constant too long";
    return ERROR;
  }
}
<string>\n    { 
    cool_yylval.error_msg = "Unterminated string constant";
    BEGIN(INITIAL);
    curr_lineno ++;
    return ERROR;
}
<string><<EOF>> { cool_yylval.error_msg = "EOF in string constant";
  BEGIN(INITIAL); return ERROR; }

<string_error>\"  { /* restart when meeting the second " */
  BEGIN(INITIAL);
  return ERROR;
}

<string_error>\n  {
    BEGIN(INITIAL);
    curr_lineno ++;
    return ERROR;
}
<string_error><<EOF>> { BEGIN(INITIAL); return ERROR; }

<string>\\n   { STRING_LENGTH_CHECK *string_buf_ptr++ = '\n'; }
<string>\\t   { STRING_LENGTH_CHECK *string_buf_ptr++ = '\t'; }
<string>\\b   { STRING_LENGTH_CHECK *string_buf_ptr++ = '\b'; }
<string>\\f   { STRING_LENGTH_CHECK *string_buf_ptr++ = '\f'; }
<string>\\[^\n\0]   { STRING_LENGTH_CHECK *string_buf_ptr++ = yytext[1]; }

  /* "  \(\n), then need to increase lineno */
<string>\\(\n)  { 
  STRING_LENGTH_CHECK {
    *string_buf_ptr++ = yytext[1]; 
    curr_lineno ++;  
  }  
}

<string>\\\0   {
      cool_yylval.error_msg = "String contains null character";
      BEGIN(string_error);
}


<string>"\0"   { 
      cool_yylval.error_msg = "String contains null character";
      BEGIN(string_error);
}

  /* when string matches, copy the matched regular expression to string buffer*/
<string>[^\\\n\"\0]+ {
  char *yyptr = yytext;
  while(*yyptr){
    if( string_buf_ptr  >= (string_buf + MAX_STR_CONST)){
      cool_yylval.error_msg = "String constant too long";
      BEGIN(string_error);
      break;
    }
    *string_buf_ptr++ = *yyptr++;	
  }
}
  /* Error string will terminate either by new line or another "*/
<string_error>[^\n\"]+   {   }

  /*  for any unmatched characters  */
. { cool_yylval.error_msg = yytext; return ERROR; }
%%

