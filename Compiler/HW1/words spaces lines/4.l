

%{
	FILE *fp;
	int word = 0;
	int space = 0;
	int line = 1;
%} 
  
%%
[\n] {line++;printf("I see endl \n");} 
[ ] {space++;}
[^ \n]* {word++;printf("%s\n", yytext);}

%% 
int yywrap(){} 
 
int main(){ 
	 
	char filename[50];
	printf("Enter the filename: \n"); 
	scanf("%s",filename);
	fp = fopen(filename,"r"); 
	yyin = fp;  
	yylex(); 
	fclose(fp);
	printf("----------------------------------------------\n");
	printf("word = %d\nspace = %d\nline = %d\n",word, space, line);
  
	return 0; 
} 




