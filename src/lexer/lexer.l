%{
#include "tokens.hpp"
using namespace SLR;
%}

%option noyywrap
%option c++


SYMBOLS     [a-zA-Z]+
DIGITS      (0|[1-9][0-9]*)(\.[0-9]+)?
WS          [ \t\r\n]+


%%
{SYMBOLS}   {return static_cast<int>(TokenType::ID);         }
{DIGITS}    {return static_cast<int>(TokenType::ID);         }
{WS}        {                                                } 

"+"         {return static_cast<int>(TokenType::PLUS);       }
"-"         {return static_cast<int>(TokenType::MINUS);      }
"*"         {return static_cast<int>(TokenType::MULT);       }
"/"         {return static_cast<int>(TokenType::DIV);        }

"("         {return static_cast<int>(TokenType::L_BRACKET);  }
")"         {return static_cast<int>(TokenType::R_BRACKET);  }   

<<EOF>>     {return static_cast<int>(TokenType::END_OF_FILE);}

.           {return static_cast<int>(TokenType::UNKNOWN);    }
            

