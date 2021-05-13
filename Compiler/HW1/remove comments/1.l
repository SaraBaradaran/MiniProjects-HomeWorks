

%{
	FILE *fp;
	FILE *newf;
%} 
  
%% 
"//"(.)* {} 
"/*"(([^*/]|[\n])*|([*][^/])*|[/]*)*"*/" {} 
. {fprintf(newf,"%s", yytext); }
[\n]+ {fprintf(newf,"\n"); }
%% 
int yywrap(){} 
 
int main(){ 
	 
	char filename[50]; 
	printf("Enter the filename or file address: \n"); 
	scanf("%s",filename); 
	fp = fopen(filename,"r"); 
	newf = fopen("new.cpp","w");
	yyin = fp;  
	yylex(); 
	fclose(fp);
	fclose(newf);
	remove(filename);
	rename("new.cpp", filename);
  
	return 0; 
} 

