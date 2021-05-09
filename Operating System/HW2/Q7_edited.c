
#include<stdio.h>
#include<string.h>

int main(){
	
	char buff[6];
	int pass = 0;
	printf("\n Enter the password : \n");
	fgets(buff, 6, stdin);
	
	if(buff[strlen(buff)-1] == '\n')
		buff[strlen(buff)-1] = '\0';
		
	if(strcmp(buff, "pass"))
		printf("\n Wrong Password \n");
	else{
		
		printf("\n Correct Password \n");
		pass = 1;
	}
	if(pass == 'a')
		printf("\n Successful Login as Admin : ) \n");
	else if(pass)
		printf("\n Successful Login \n");
	else
		printf("\n Failed to Login \n");
		
	
	
}
