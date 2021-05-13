
%{ 
int count = 0; 
%} 
  
%% 
[A-Z] {printf("%s capital letter\n", yytext); 
       count++;} //heloo
       
.     {printf("%s not a capital letter\n", yytext);} 
\n    {return 0;} 
%% 

  	
int yywrap(){} 

/*** Rule Section has three rules, first rule  
matches with capital letters, second rule 
matches with any character except newline and  
third rule does not take input after the enter***/
int main(){
	
	
}//hello
  
yylex(); 
printf("\nNumber of Captial letters " 
      "in the given input - %d\n", count); 
	/*** Rule Section has three rules, first rule  
matches with capital letters, second rule 
matches with any character except newline and  
third rule does not take input after the enter***/ 
return 0; 
} 
