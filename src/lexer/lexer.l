%option noyywrap
%option reentrant

%{
#include "tokens.hpp"

#define YY_DECL SLR::TokenType yylex(yyscan_t yyscanner)
#define YY_NULL SLR::TokenType::END_OF_FILE

using namespace SLR;
%}


SYMBOLS     [a-zA-Z]+
DIGITS      (0|[1-9][0-9]*)(\.[0-9]+)?
WS          [ \t\r\n]+


%%

{SYMBOLS}   {return TokenType::ID;      }
{DIGITS}    {return TokenType::ID;     }


{WS}        {                           } 

"+"         {return TokenType::PLUS;    }
"-"         {return TokenType::MINUS;   }
"*"         {return TokenType::MULT;    }
"/"         {return TokenType::DIV;     }

"("         {return TokenType::L_BRACKET;}
")"         {return TokenType::R_BRACKET;}        

.           {return TokenType::UNKNOWN; }
            

