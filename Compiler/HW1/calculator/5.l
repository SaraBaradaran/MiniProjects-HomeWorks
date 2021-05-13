

%{
	float calculate(char*);
%} 
  
%% 

[1-9]+[0-9]*[-+*/][1-9]+[0-9]* {printf("\n%s = %f" ,yytext, calculate(yytext));}
. {}
%% 
int yywrap(){} 
 
int main(){ 
	 
	yylex(); 
	return 0; 
} 

float calculate(char* s){
	int i = 0;
	float x = 0 , y = 0;
	char sign;
	for(i; s[i] !='+' && s[i] != '-' && s[i] != '*' && s[i] != '/'; i++){
		x *= 10;
		x += s[i] - '0'; 
	}
	sign = s[i];
	for(++i; s[i] != '\0'; i++){
		y *= 10;
		y += s[i] - '0'; 
	}
	switch(sign){
	
		case '+':
			return x + y;
		case '-':
			return x - y;
		case '/':
			return x / y;
		case '*':
			return x * y;
	}

}