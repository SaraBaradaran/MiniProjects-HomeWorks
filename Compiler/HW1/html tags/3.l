

%{
	FILE *fp;
	int count = 0;
%} 
  
%% 

"<"[/]?[^>]*">" {printf("%s\n", yytext);count++;}
. {}
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
	printf("number of html tags = %d\n",count);
  
	return 0; 
} 



