%option noyywrap
%option reentrant

%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.hpp"
%}


SYMBOLS     [a-zA-Z]+
DIGITS      (0|[1-9][0-9]*)(\.[0-9]+)?
WS          [ \t\r\n]+


%%

{SYMBOLS}   {return TOKEN_ID;      }
{DIGITS}    {return TOKEN_ID;      }


{WS}        {                      } 

"+"         {return TOKEN_PLUS;    }
"-"         {return TOKEN_MINUS;   }
"*"         {return TOKEN_MULT;    }
"/"         {return TOKEN_DIV;     }

"("         {return TOKEN_LBRACKET;}
")"         {return TOKEN_RBRACKET;}        

.           {return UNKNOWN_TOKEN; }
            

