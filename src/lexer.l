%option noyywrap
%option reentrant

%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.hpp"
%}


ID          [a-zA-Z]+
WS          [ \t\r\n]+


%%

{ID}        {return TOKEN_ID;  }
{WS}        {                  } 
"+"         {return TOKEN_PLUS;}
"*"         {return TOKEN_MULT;}

.           {return UNKNOWN_TOKEN; }
            

