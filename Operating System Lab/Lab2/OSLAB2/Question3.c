
//Sara Baradaran 9624193

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	int v1, v2;
	scanf("%d %d", &v1, &v2);
	char prefix[20];
	scanf("%s", prefix);
	strcat(prefix, "-");
	char file_address[100];
	scanf("%s", file_address);
	char adduser_cmd[100] = "sudo useradd -m ";
	char str[10];
	char command[100];

	strcat(adduser_cmd, prefix);
	for(int i=v1; i<=v2; i++){
		
  		sprintf(str, "%d", i);
		strcpy(command, adduser_cmd);
		strcat(command, str);
		system(command);
	}
	char copy_cmd[100] = "sudo cp ";
	strcat(copy_cmd, file_address);
	strcat(copy_cmd, " /home/");
	strcat(copy_cmd, prefix);
	for(int i=v1; i<=v2; i++){

		sprintf(str, "%d", i);
		strcpy(command, copy_cmd);
	        strcat(command, str);
		system(command);	
	}
	
	printf("end of program");
	return 0;

}
