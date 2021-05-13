

%{

	#include<string.h>
	FILE* fp;
	int count = 0;
	char filename[50];
	char word[50];
	int s[100];
	int line = 1;
%} 
  
%% 
([a-z]|[A-Z])+ {
	if(strcmp(word,yytext)==0){
		s[count] = line;
		count++;
	}
}
[\n] {line++;}
. {}
%% 
int yywrap(){} 
 
int main(){ 

	printf("Enter the filename or file address: \n"); 
	scanf("%s",filename);	
	printf("Enter the word: \n"); 
	scanf("%s",word);
	fp = fopen(filename,"r");
	yyin = fp; 
	yylex(); 
	fclose(fp);
	printf("the number of %s = %d\n", word, count);
	
	char str[100];
	int c = 0, i = 1;
	fp = fopen(filename,"r");
	while(i <= s[count-1]){
	
		fgets(str, 100, fp);
		if(s[c] == i){
			printf("%d _ %s\n",i,str);
			c++;
		}
		i++;
	}
  
	return 0; 
} 

