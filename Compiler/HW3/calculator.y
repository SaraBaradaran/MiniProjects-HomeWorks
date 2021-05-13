%{
  #include <stdio.h>  
  #include <math.h>   
  #include "calc.h"   
  int yylex (void);
  void yyerror (char const *);
%}

/*%define api.value.type union*/
%token <double>  NUM  
%token <symrec*> VAR FUN 
%nterm <double>  exp

%left '='
%left '-' '+'
%left '*' '/'
   

%verbose
%define parse.trace

%printer { fprintf (yyo, "%s", $$->name); } VAR;
%printer { fprintf (yyo, "%s()", $$->name); } FUN;
%printer { fprintf (yyo, "%g", $$); } <double>;
%% 
input:
  
| input line
;

line:
  '\n'
| exp '\n'   { printf ("%g\n", $1); }
;

exp:
  NUM
| VAR                { $$ = $1->value.var;              }
| VAR '=' exp        { $$ = $3; $1->value.var = $3;     }
| FUN '(' exp ')'    { $$ = $1->value.fun ($3);         }
| exp '+' exp        { $$ = $1 + $3;                    }
| exp '-' exp        { $$ = $1 - $3;                    }
| exp '*' exp        { $$ = $1 * $3;                    }
| exp '/' exp        { $$ = $1 / $3;                    }
| '(' exp ')'        { $$ = $2;                         }
;

%%

struct init
{
  char const *name;
  func_t *fun;
};

struct init const arith_funs[] =
{

  { "exp",  exp  },
  { "log",   log  },
  { "sqrt", sqrt },
  { 0, 0 },
};

symrec *sym_table;

static void init_table (void)
{
  for (int i = 0; arith_funs[i].name; i++)
    {
      symrec *ptr = putsym (arith_funs[i].name, FUN);
      ptr->value.fun = arith_funs[i].fun;
    }
}

#include <stdlib.h> 
#include <string.h> 

symrec *putsym (char const *name, int sym_type)
{
  symrec *res = (symrec *) malloc (sizeof (symrec));
  res->name = strdup (name);
  res->type = sym_type;
  res->value.var = 0; 
  res->next = sym_table;
  sym_table = res;
  return res;
}

symrec *getsym (char const *name)
{
  for (symrec *p = sym_table; p; p = p->next)
    if (strcmp (p->name, name) == 0)
      return p;
  return NULL;
}

#include <ctype.h>
#include <stddef.h>

int yylex (void)
{
  int c = getchar ();

  while (c == ' ' || c == '\t')
    c = getchar ();

  if (c == EOF)
    return 0;

  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      scanf ("%lf", &yylval.NUM);
      return NUM;
    }

  if (isalpha (c))
    {
      static ptrdiff_t bufsize = 0;
      static char *symbuf = 0;
      ptrdiff_t i = 0;
      do
        {
          if (bufsize <= i)
            {
              bufsize = 2 * bufsize + 40;
              symbuf = realloc (symbuf, bufsize);
            }
          symbuf[i++] = c;
          c = getchar ();
        }
      while (isalnum (c));

      ungetc (c, stdin);
      symbuf[i] = '\0';

      symrec *s = getsym (symbuf);
      if (!s)
        s = putsym (symbuf, VAR);
      yylval.VAR = s;
      return s->type;
    }

  return c;
}

void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main (int argc, char const* argv[])
{
 
  int i;
  for (i = 1; i < argc; ++i)
    if (!strcmp(argv[i], "-p"))
      yydebug = 1;
	
  init_table ();
  return yyparse ();
}
