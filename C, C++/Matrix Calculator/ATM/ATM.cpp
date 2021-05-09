#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define num 1000
#define maxnumtransaction 20
void wait()
{
	printf("\n\t\t\t\t w");
	Sleep(200);
	printf("a");
	Sleep(200);
	printf("i");
	Sleep(200);
	printf("t");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
}
void thank_you()
{
	printf("\n\t\t\t\t T");
	Sleep(200);
	printf("h");
	Sleep(200);
	printf("a");
	Sleep(200);
	printf("n");
	Sleep(200);
	printf("k");
	Sleep(200);
	printf(" ");
	Sleep(200);
	printf("Y");
	Sleep(200);
	printf("o");
	Sleep(200);
	printf("u\n\n\n\n\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
char *GETDATE(char*a)
{
	char*z,date[15],month[15],day[15],year[15];
	int y=0;
	z=strtok(a," ");
	while(z!=NULL)
	{
		if(y==1)
		{
			if(!strcmp(z,"Jan"))
			strcpy(month,"1");
			if(!strcmp(z,"Feb"))
			strcpy(month,"2");
			if(!strcmp(z,"Mar"))
			strcpy(month,"3");
			if(!strcmp(z,"Apr"))
			strcpy(month,"4");
			if(!strcmp(z,"May"))
			strcpy(month,"5");
			if(!strcmp(z,"Jun"))
			strcpy(month,"6");
			if(!strcmp(z,"Jul"))
			strcpy(month,"7");
			if(!strcmp(z,"Aug"))
			strcpy(month,"8");
			if(!strcmp(z,"Sep"))
			strcpy(month,"9");
			if(!strcmp(z,"Oct"))
			strcpy(month,"10");
			if(!strcmp(z,"Nov"))
			strcpy(month,"11");
			if(!strcmp(z,"Dec"))
			strcpy(month,"12");
		}
		if(y==4)
			strcpy(year,z);
		else if(y==2)
			strcpy(day,z);
		if(y==3)
		z=strtok(NULL,"\n");
		else
		z=strtok(NULL," ");
		y++;
	}
	strcpy(date,strcat(year,"/"));
	strcpy(date,strcat(date,month));
	strcpy(date,strcat(date,"/"));
	strcpy(date,strcat(date,day));
	
	return date;
}//the function convert system's date
////////////////////////////////////////////////////////////////////////////////////////////////////
char* ltoa(long long int a)
{
	char s[10],s1[10];
	int i;
	if(!a)
	strcpy(s1,"0");
	else
	{
		for(i=0;a!=0;i++,a=a/10)
		{
			s[i]=(a%10)+'0';
		}
		s[i]='\0';
		int j;
		for(j=strlen(s)-1;j>=0;j--,i--)
		s1[j]=s[strlen(s)-i];
		s1[strlen(s)]='\0';
	}
	return s1;
}//the function conver integer to string
////////////////////////////////////////////////////////////////////////////////////////////////////
int Isalpha(const char *s)
{
	int i=0;
	for(i;s[i]!='\0';i++)
	{
		if(!isalpha(s[i]) && s[i]!=' ')
		return 0;
	}
	return 1;
}//the function of checking alphabet
////////////////////////////////////////////////////////////////////////////////////////////////////
int Isdigit(const char *s)
{
	int i=0;
	for(i;s[i]!='\0';i++)
	{
		if(!isdigit(s[i]))
		return 0;
	}
	return 1;
}//the function of checking digits
////////////////////////////////////////////////////////////////////////////////////////////////////
struct transaction
{
	char Date[11];//date of transaction for example(96/3/15)
	char Money[10];
	char Type[30];//type of transaction(reseived,deposited,deposited to another card,received from another card)
	char DOScardNo[10];//destination or source card number
};
////////////////////////////////////////////////////////////////////////////////////////////////////
struct card
{
	char Accounts[10];//balance
	char CardNo[10];
	char Pass[5];//card number and password
	char Name[51];
	struct transaction Date1[maxnumtransaction];//transactions
	int ctr;//the counter of transcations
};
////////////////////////////////////////////////////////////////////////////////////////////////////
void delet_transaction(struct transaction Date[],int n)
{
	for(int i=1;i<n;i++)
	Date[i-1]=Date[i];
}//function of deleting transaction if the number of transaction is more than 20
////////////////////////////////////////////////////////////////////////////////////////////////////
void change_Pass(FILE *fptr,struct card *ptr,char *crdn)//change password
{
	system("cls");
	char newpassword[5],currentpassword[5];
	printf(" Enter password :");
	scanf("%s",currentpassword);//get current pass
	fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
	fread(ptr,sizeof(struct card),1,fptr);
	if(!strcmp((*ptr).Pass,currentpassword))//if enterd pass was correct
	{
		system("cls");
		printf(" Enter new password (2 digits):");
		scanf("%s",newpassword);//get new pass
		while(strlen(newpassword)!=2 || !Isdigit(newpassword))//check if new pass contains digits only and check number of digits
		{
			system("cls");
			system("color c");
			if(strlen(newpassword)!=2 && Isdigit(newpassword))
				puts(" new password must be 2 digits please try again !\n");
			else if(!Isdigit(newpassword))
				puts(" Wrong password ! you must use digits only\n");
				printf(" Enter new password (2 digits):");
				scanf("%s",newpassword);
		}//end of while(strlen(newpassword)!=2 || !Isdigit(newpassword))
		char temp[5];
		strcpy(temp,newpassword);
		system("cls");
		system("color b");
		printf(" Enter new password again (2 digits):");
		scanf("%s",newpassword);//get new pass again
		if(!strcmp(temp,newpassword))//check 2 enterd new pass are equal or not
		{
			strcpy((*ptr).Pass,newpassword);//replace card pass with new pass 
			fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
			fwrite(ptr,sizeof(struct card),1,fptr);
			system("cls");
			system("color a");
			puts(" password successfully changed\n");
		}//end of if(!strcmp(temp,newpassword))
		else
		{
			system("cls");
			system("color c");
			puts(" 2 new password enterd was not equal !\n");
		}//end of else
	}//end of if(!strcmp((*ptr).Pass,currentpassword))
	else
	{
		system("color c");
		puts("\n password is wrong !\n");
	}//end of else
	printf(" Press any key to return to the previous page");
}//end of change password
////////////////////////////////////////////////////////////////////////////////////////////////////
void show_account(FILE *fptr,struct card *ptr, char *crdn)//show balance
{
	fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
	fread(ptr,sizeof(struct card),1,fptr);
	system("cls");
	printf(" Card Number :%s\n\n",(*ptr).CardNo);
	printf(" Name :%s\n\n",(*ptr).Name);
	printf(" Balance :%s\n\n",(*ptr).Accounts);
	printf(" Press any key to return to the previous page");
}//end of show balance
////////////////////////////////////////////////////////////////////////////////////////////////////withdrawn
void receive_money(FILE *fptr,struct card *ptr, char *crdn)//receive money
{
	char money[10];
	char select;
	system("cls");
	printf(" Enter amount of money :");
	scanf("%s",money);//get amount of money wich you want to receive from card
	fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
	fread(ptr,sizeof(struct card),1,fptr);
	wait();
	if(Isdigit(money))//check if amount of money is correct or not
	{
		if(atol((*ptr).Accounts)-atol(money)>=0 && atol(money) <=2000000)//check balance and amount of money
		{
			system("cls");
			time_t a;
			time(&a);
			char *m=ctime(&a);
			strcpy((*ptr).Date1[(*ptr).ctr].Date,GETDATE(m));
			system("cls");
			printf(" Received money :%s\n\n",money);
			puts(" Do you confirm the transaction ?\n");
			puts(" 1)YES\t 2)NO\n");
			scanf("%c",&select);
			while(select=='\n'||select==' ')
			scanf("%c",&select);
			if(select=='1')
			{
				system("cls");
				if((*ptr).ctr==maxnumtransaction)//if the number of transaction is more than 20
				{
					delet_transaction((*ptr).Date1,maxnumtransaction);
					(*ptr).ctr=maxnumtransaction-1;
				}
				strcpy((*ptr).Accounts,ltoa((atol((*ptr).Accounts))-(atol(money))));//replace card balance with new balance
				strcpy((*ptr).Date1[(*ptr).ctr].Money,money);
				strcpy((*ptr).Date1[(*ptr).ctr].Type,"Received");
				strcpy((*ptr).Date1[(*ptr).ctr].DOScardNo," ");
				(*ptr).ctr++;
				fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
				fwrite(ptr,sizeof(struct card),1,fptr);
				system("color a");
				puts(" Transaction successfuly was compeleted\n");
				printf(" Received money :%s\n\n",money);
				printf(" New balance :%s\n\n",(*ptr).Accounts);
			}//end of if(select=='1')
			else if(select=='2')
			{
				system("cls");
				system("color c");
				puts(" The transaction of receiving money was canceled\n");
			}//end of else if(select=='2')
			else
			{
				system("color c");
				system("cls");
				puts(" Incorrect selection !\n");
			}//end of else
		}//end of if(atol((*ptr).Accounts)-atol(money)>=0 && atol(money) <=2000000)
		else if(!atol((*ptr).Accounts))
		{
			system("color c");
			system("cls");
			puts(" Your account has no stock !\n");
		}//end of else if(!atol((*ptr).Accounts))
		else if(atol(money)>2000000)//check money
		{
			system("color c");
			system("cls");
			puts("\n You can get at most 2000000 rials via ATM !\n");
		}//end of else if(atol(money)>2000000)
		else if(atol((*ptr).Accounts)-atol(money)<0)//check balance and money
		{
			system("color c");
			system("cls");
			printf("\n your balance is %s rials and you can not get more than it ! \n\n",(*ptr).Accounts);
		}//end of else if(atol((*ptr).Accounts)-atol(money)<0)
	}
	else
	{
		system("color c");
		system("cls");
		puts(" The amount of money is wrong ! you must use digits only !\n");
	}//end of else
	printf(" Press any key to return to the previous page");
}//end of receive money
////////////////////////////////////////////////////////////////////////////////////////////////////
void deposite_money(FILE *fptr,struct card *ptr, char *crdn)//deposite money
{
	char money[10];
	char select;
	system("cls");
	printf(" Enter amount of money :");
	scanf("%s",money);//get money wich you want to deposite to card
	fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
	fread(ptr,sizeof(struct card),1,fptr);
	wait();
	if(Isdigit(money))//check if amount of money is correct or not
	{
		if( atol(money) <=30000000)//check money
		{
			system("cls");
			time_t a;
			time(&a);
			char *m=ctime(&a);
			strcpy((*ptr).Date1[(*ptr).ctr].Date,GETDATE(m));
			system("cls");
			printf(" Deposited money :%s\n\n",money);
			puts(" Do you confirm the transaction ?\n");
			puts(" 1)YES\t 2)NO\n");
			scanf("%c",&select);
			while(select=='\n'||select==' ')
			scanf("%c",&select);
			if(select=='1')
			{
				system("cls");
				if((*ptr).ctr==maxnumtransaction)//if the number of transaction is more than 20
				{
					delet_transaction((*ptr).Date1,maxnumtransaction);
					(*ptr).ctr=maxnumtransaction-1;
				}
				strcpy((*ptr).Accounts,ltoa((atol((*ptr).Accounts))+(atol(money))));//replace card balance with new balance
				strcpy((*ptr).Date1[(*ptr).ctr].Money,money);
				strcpy((*ptr).Date1[(*ptr).ctr].Type,"Deposited");
				strcpy((*ptr).Date1[(*ptr).ctr].DOScardNo," ");
				(*ptr).ctr++;
				fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
				fwrite(ptr,sizeof(struct card),1,fptr);
				system("color a");
				puts(" Transaction successfuly was compeleted\n");
				printf(" Deposited money :%s\n\n",money);
				printf(" New balance is %s \n\n",(*ptr).Accounts);
			}//end of if(select=='1')
			else if(select=='2')
			{
				system("cls");
				system("color c");
				puts(" The transaction of depositing money was canceled\n");
			}//end of else if(select=='2')
			else
			{
				system("color c");
				system("cls");
				puts(" Incorrect selection !\n");
			}//end of else
		}//end of if( atol(money) <=30000000)
		else
		{
			system("color c");
			system("cls");
			puts("\n You can deposite at most 30000000 rials via ATM\n");
		}//end of else
	}//end of if(Isdigit(money))
	else
	{
		system("color c");
		system("cls");
		puts(" The amount of money is wrong ! you must use digits only !\n");
	}//end of else
	printf(" Press any key to return to the previous page");
}//end of deposite money
////////////////////////////////////////////////////////////////////////////////////////////////////
void deposite_C(FILE *fptr,struct card *ptr,char *crdn)//deposide from card to card
{
	char destinationcrdn[10],money[10],Date[10];
	char select;
	system("cls");
	printf(" Enter destination card number :");
	scanf("%s",destinationcrdn);//get destination card number
	fseek(fptr,(atoi(destinationcrdn)-num)*sizeof(struct card),SEEK_SET);
	fread(ptr,sizeof(struct card),1,fptr);
	if(!strcmp((*ptr).CardNo,destinationcrdn))//check destination card number is defineded or not
	{
		system("cls");
		printf(" Enter amount of money :");
		scanf("%s",money);//get money wich you want to deposite to another card
		fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
		fread(ptr,sizeof(struct card),1,fptr);
		wait();
		if(Isdigit(money))//check if amount of money is correct or not
		{
			if(atol((*ptr).Accounts)-atol(money)>=0 && atol(money)<=500000000)//check balance and money
			{
				system("cls");
				fseek(fptr,(atoi(destinationcrdn)-num)*sizeof(struct card),SEEK_SET);
				fread(ptr,sizeof(struct card),1,fptr);
				system("cls");
				printf(" CardNumber :%s\n\n Name :%s\n\n Money :%s\n\n",(*ptr).CardNo,(*ptr).Name,money);
				puts(" Do you confirm the transaction ?\n");
				puts(" 1)YES\t 2)NO\n");
				scanf("%c",&select);
				while(select=='\n'||select==' ')
				scanf("%c",&select);
				if(select=='1')
				{
					time_t a;
					time(&a);
					char *m=ctime(&a);
					system("cls");
					if((*ptr).ctr==maxnumtransaction)//if the number of transaction is more than 20
					{
						delet_transaction((*ptr).Date1,maxnumtransaction);
						(*ptr).ctr=maxnumtransaction-1;
					}
					fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
					fread(ptr,sizeof(struct card),1,fptr);
					strcpy((*ptr).Accounts,ltoa((atol((*ptr).Accounts))-(atol(money))));//replace card balance with new balance
					strcpy((*ptr).Date1[(*ptr).ctr].Money,money);
					strcpy((*ptr).Date1[(*ptr).ctr].Date,GETDATE(m));
					strcpy((*ptr).Date1[(*ptr).ctr].Type,"Deposited to card");
					strcpy((*ptr).Date1[(*ptr).ctr].DOScardNo,destinationcrdn);
					(*ptr).ctr++;
					fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
					fwrite(ptr,sizeof(struct card),1,fptr);
					time_t b;
					time(&b);
					char *n=ctime(&b);
					fseek(fptr,(atoi(destinationcrdn)-num)*sizeof(struct card),SEEK_SET);
					fread(ptr,sizeof(struct card),1,fptr);
					strcpy((*ptr).Accounts,ltoa((atol((*ptr).Accounts))+(atol(money))));//replace destination card balance with new balance
					strcpy((*ptr).Date1[(*ptr).ctr].Money,money);
					strcpy((*ptr).Date1[(*ptr).ctr].Date,GETDATE(n));
					strcpy((*ptr).Date1[(*ptr).ctr].Type,"Received from card");
					strcpy((*ptr).Date1[(*ptr).ctr].DOScardNo,crdn);
					(*ptr).ctr++;
					fseek(fptr,(atoi(destinationcrdn)-num)*sizeof(struct card),SEEK_SET);
					fwrite(ptr,sizeof(struct card),1,fptr);
					system("color a");
					printf(" Transaction successfuly compeleted\n\n");
					printf(" Origin card :%s\n\n destination card :%s\n\n money :%s\n\n",crdn,destinationcrdn,money);
				}//end of if(select=='1')
				else if(select=='2')
				{
					system("cls");
					system("color c");
					printf(" The transaction of depositing money to another card was canceled\n\n");
				}//end of else if(select=='2')
				else
				{
					system("color c");
					system("cls");
					puts(" Incorrect selection !\n");
				}//end of else
			}//end of if(atol((*ptr).Accounts)-atol(money)>=0 && atol(money)<=500000000)
			else if(!atol((*ptr).Accounts))
			{
				system("color c");
				system("cls");
				puts(" Your account has no stock !\n");
			}//end of else if(!atol((*ptr).Accounts))
			else if(atol((*ptr).Accounts)-atol(money)<0)//check balance and money
			{
				system("color c");
				system("cls");
				printf("\n Your balance is %s rials and you can not deposite more than it ! \n\n",(*ptr).Accounts);
			}//end of else if(atol((*ptr).Accounts)-atol(money)<0)
			else if(atol(money)>500000000)//check money
			{
				system("color c");
				system("cls");
				printf("\n You can deposite at most 500000000 rials to another card via ATM\n\n");
			}//end of else if(atol(money)>500000000)
		}//end of if(atol((*ptr).Accounts)-atol(money)>=0 && atol(money)<=500000000)
		else
		{
			system("color c");
			system("cls");
			puts(" The amount of money is wrong ! you must use digits only !\n");
		}//end of else
		printf(" Press any key to return to the previous page");
	}//end of if(!strcmp((*ptr).CardNo,destinationcrdn))
	else
	{
		system("color c");
		puts("\n Dectination card number is wrong !\n");
	}//end of else	
}//end of deposide from card to card
////////////////////////////////////////////////////////////////////////////////////////////////////
void show_transaction(FILE *fptr,struct card *ptr,char *crdn)//show transaction
{
	int numtr;//number of transactin you want to visit
	system("color b");
	system("cls");
	printf(" Enter the number of transaction you want to visit:");
	scanf("%d",&numtr);
	system("cls");
	fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
	fread(ptr,sizeof(struct card),1,fptr);
	if((*ptr).ctr==0)
	{
		system("color c");
		puts(" There is no transcation !\n");
	}//end of if((*ptr).ctr==0)
	else if((*ptr).ctr>=numtr)
	{
		system("color b");
		puts(" Date \t\t\tMoney \t\tType \t\t\tDOScardNO\n");
		int i=(*ptr).ctr-1;
		for(i;numtr>0;i--,numtr--)
		{
			printf("%s\t\t",(*ptr).Date1[i].Date);
			printf("%s\t\t",(*ptr).Date1[i].Money);
			printf("%s\t",(*ptr).Date1[i].Type);
			printf("%s\n\n",(*ptr).Date1[i].DOScardNo);
		}
	}//end of else if((*ptr).ctr>=numtr)
	else if((*ptr).ctr==1)
	{
		system("color c");
		puts(" Only 1 transcation is visible\n");
		puts(" Date \t\t\tMoney \t\tType \t\t\tDOScardNO\n");
		printf("%s\t\t",(*ptr).Date1[0].Date);
		printf("%s\t\t",(*ptr).Date1[0].Money);
		printf("%s\t",(*ptr).Date1[0].Type);
		printf("%s\n\n",(*ptr).Date1[0].DOScardNo);	
	}//end of else if((*ptr).ctr==1)
	else
	{
		system("color c");
		printf(" Only %d transcations are visible\n\n",(*ptr).ctr);
		puts(" Date \t\t\tMoney \t\tType \t\t\tDOScardNO\n");
		int i=(*ptr).ctr-1;
		for(i;i>=0;i--)
		{
			printf("%s\t\t",(*ptr).Date1[i].Date);
			printf("%s\t\t",(*ptr).Date1[i].Money);
			printf("%s\t",(*ptr).Date1[i].Type);
			printf("%s\n\n",(*ptr).Date1[i].DOScardNo);
		}//end of for(i;i>=0;i--)
	}//end of else
	printf(" Press any key to return to the previous page");
}//end of show transaction
////////////////////////////////////////////////////////////////////////////////////////////////////
void enter_card(FILE *fptr,struct card *ptr,char *crdn)
{
	int select;
	do
	{
		system("color b");
		system("cls");
		puts("1) Show account \t\t2) Receive money\n");
		puts("3) Deposite money\t\t4) Change password\n");
		puts("5) Deposite from card to card\t6) show transactions\n");
		puts("7) previous page\n");
		printf(" Please select the number:");
		scanf("%d",&select);
		switch(select)
		{
		
			case 1:
				{
					show_account(fptr,ptr,crdn);
					getch();
					break;
				}
			case 2:
				{
					receive_money(fptr,ptr,crdn);
					getch();
					break;
				}
			case 3:
				{
					deposite_money(fptr,ptr,crdn);
					getch();
					break;
				}
			case 4:
				{
					change_Pass(fptr,ptr,crdn);
					getch();
					break;
				}
			case 5:
				{
					deposite_C(fptr,ptr,crdn);//deposite money from card to another card
					getch();
					break;
				}
			case 6:
				{
					show_transaction(fptr,ptr,crdn);
					getch();
					break;
				}
			case 7:
				{
					break;
				}	
			default:
				{
					system("cls");
					system("color c");
					puts("!! Incorrect selection !!\n");
					printf(" Press any key to return to the previous page");
					getch();
					break;
				}
		}//end of switch
	}//end of do while
	while(select!=7);
}//end of enter_card
////////////////////////////////////////////////////////////////////////////////////////////////////
void new_card(FILE *fptr,struct card *ptr)//creat a new card
{
	char crdn[10];//card number
	char select;
	int cwc=3,cwp=3,cwn=3,cwb=3; //counter of wrong card numbers & counter of wrong pass & counter of wrong name
	while(1)
	{
		puts(" press 0 if you want to exit\n");
		printf(" Enter Card Number (4 Digits):");
		scanf("%s",crdn);
		if(!strcmp(crdn,"0"))//if user wants to exite
		break;
		if(!Isdigit(crdn))//check if card number is correct or not(correct card number must contains digits only)
		{
			if(cwc>1)//check if user enter wrong card number less than 3 time
			{
				system("cls");
				system("color c");
				cwc--;
				printf(" wrong cardno ! you must use digits only (%d)\n\n",cwc);
				continue;
			}//end of if(cwc>1)
			else if(cwc==1)
			break;
		}//end of if(!Isdigit(crdn))
		if(strlen(crdn)!=4)//check the digits of card number
		{
			if(cwc>1)//check if user enter wrong card number less than 3 time
			{
				system("cls");
				system("color c");
				cwc--;
				printf("!! Card Number must be 4 digits please enter again!!(%d)\n\n",cwc);
				continue;
			}//end of if(cwc>1)
			else if(cwc==1)
			break;
		}//end of if(strlen(crdn)!=4)
		system("color b");
		fseek(fptr,(atoi(crdn)-num)*sizeof(struct card),SEEK_SET);
		fread(ptr,sizeof(struct card),1,fptr);
		if(strcmp((*ptr).CardNo,"0"))//check account with this card number is empty or not
		{
			system("cls");
			system("color c");
			printf(" Account %s already contains information please select another Card Number\n\n",crdn);
			continue;
		}//end of if(strcmp((*ptr).CardNo,"0"))
		else
		{
			system("color b");
			system("cls");
			puts(" press 0 if you want to exit\n");
			printf(" Enter Password (2 Digits):");
			scanf("%s",&(*ptr).Pass);
			while((!Isdigit((*ptr).Pass) || strlen((*ptr).Pass)!=2))//check if pass is correct or not(correct password contains 2 digits only)
			{
				if(!strcmp((*ptr).Pass,"0"))//if user wants to exite
				break;
				system("cls");
				system("color c");
				cwp--;
				if(cwp>0 && !Isdigit((*ptr).Pass))//check if user enter wrong pass less than 3 time
					printf(" password is wrong ! you must use digits only (%d)\n\n",cwp);
				else if(cwp>0 && strlen((*ptr).Pass)!=2)//check if user enter wrong pass less than 3 time
					printf("!! Password must be 2 digits please enter again!!(%d)\n\n",cwp);
				else if(!cwp)//if user has enterd wrong pass 3 time
					break;	
					puts(" press 0 if you want to exit\n");
					printf(" Enter Password (2 Digits):");
					scanf("%s",&(*ptr).Pass);
			}//end of while((!Isdigit((*ptr).Pass) || strlen((*ptr).Pass)!=2))
			if(!strcmp((*ptr).Pass,"0") || !cwp)//if user wants to exite or if user has enterd wrong pass 3 time
			break;
			system("color b");
			system("cls");
			puts(" press 0 if you want to exit\n");
			printf(" Enter Name :");
			gets((*ptr).Name);
			gets((*ptr).Name);
			while(!Isalpha((*ptr).Name))
			{
				if(!strcmp((*ptr).Name,"0"))//if user wants to exite 
				break;
				system("cls");
				system("color c");
				cwn--;
				if(cwn>0)//check if user enter wrong pass less than 3 time
					printf(" Name is wrong ! please enter again(%d) \n\n",cwn);
				else if(!cwn)//if user has enterd wrong pass 3 time
				break;
				puts(" press 0 if you want to exit\n");
				printf(" Enter Name :");
				gets((*ptr).Name);
			}//end of while(!Isalpha((*ptr).Name))
			if(!strcmp((*ptr).Name,"0") || !cwn)//if user wants to exite or if user has enterd wrong pass 3 time
			break;
			system("color b");
			system("cls");
			puts(" press 0 if you want to exit\n");
			printf(" Enter Balance :");
			scanf("%s",&(*ptr).Accounts);
			while(!Isdigit((*ptr).Accounts))//check if balance is correct or not(correct balance contains digits only)
			{
				system("cls");
				system("color c");
				cwb--;
				if(cwb>0)//check if user enter wrong pass less than 3 time
					printf(" Balance is wrong ! please enter again(%d) \n\n",cwb);
				else if(!cwb)//if user has enterd wrong pass 3 time
				break;
				puts(" press 0 if you want to exit\n");
				printf(" Enter balance :");
				scanf("%s",&(*ptr).Accounts);
			}//end of while(!Isalpha((*ptr).Name))
			if(!strcmp((*ptr).Accounts,"0") || !cwb)//if user wants to exite or if user has enterd wrong pass 3 time
			break;
			system("cls");
			system("color b");
			strcpy((*ptr).CardNo,crdn);	
			puts(" Are you sure you want to record a new_card with below information ?\n");
			printf(" CardNO : %s\n\n Password : %s\n\n Name : %s\n\n Balance : %s\n\n",(*ptr).CardNo,(*ptr).Pass,(*ptr).Name,(*ptr).Accounts);
			puts(" 1)YES\t2)NO ");
			scanf("%c",&select);
			while(select=='\n'||select==' ')
			scanf("%c",&select);
			if(select=='1')
			{
				fseek(fptr,(atol(crdn)-num)*sizeof(struct card),SEEK_SET);
				fwrite(ptr,sizeof(struct card),1,fptr);
				system("cls");
				system("color a");
				puts(" New card succcessfully added\n");
				printf(" CardNO : %s\n\n Password : %s\n\n Name : %s\n\n Balance : %s\n\n",(*ptr).CardNo,(*ptr).Pass,(*ptr).Name,(*ptr).Accounts);
			}//end of if(select=='1')
			else if(select=='2')
			{
				system("color c");
				system("cls");
				puts(" new_card recording was canceld !\n");
			}//end of else if(select=='2')
			else
			{
				system("color c");
				system("cls");
				puts(" Incorrect selection !\n");
			}//end of else
			printf(" Press any key to return to the previous page");
			getch();
			break;
		}//end of else
	}//end of while(1)
}//end of new card
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int select;
	FILE *fptr;
	if((fptr=fopen("data1.txt","r+"))==NULL)// open file
		printf("Error");//file could not been opened
	else
	{
		do
		{
			system("color b");
			system("cls");
			printf("1) New card\t2) Enter card\n\n3) Exit \t4) Reset data\n\n please select the number:");
			scanf("%d",&select);
			system("cls");
			struct card nc={"0","0","0","0"};
			switch(select)
			{	
				case 1:
				{
					new_card(fptr,&nc);// creat a new record
					break;
				}// end of case 1
				case 2:
				{
					system("cls");
					char crdn[10],password[5];//card number & password
					printf(" Enter Card Number (4 Digits):");
					scanf("%s",crdn);
					fseek(fptr,sizeof(struct card)*(atoi(crdn)-num),SEEK_SET);
					fread(&nc,sizeof(struct card),1,fptr);
					if(strcmp(nc.CardNo,"0") && strlen(crdn)==4 && Isdigit(crdn))//check if card number defined or not
					{
						system("cls");
						printf(" Enter Password (2 Digits):");
						scanf("%s",password);
						int counter=1;//counter of wrong password
						fseek(fptr,sizeof(struct card)*(atoi(crdn)-num),SEEK_SET);
						fread(&nc,sizeof(struct card),1,fptr);
						if(strcmp(nc.Pass,password))//check if pass is wrong or not
						{
							while(strcmp(nc.Pass,password)&& counter!=3)//if user enterd wrong pass less than 3 time
							{
								system("cls");
								system("color c");
								printf(" The password is wrong try again (%d)!!\n\n",3-counter);
								printf(" Enter the password : ");
								scanf("%s",password);
								if(!strcmp(nc.Pass,password))//if password is correct
								{
									enter_card(fptr,&nc,crdn);
									strcpy(password,nc.Pass);//for function of chang pass
								}//end of if(!strcmp(nc.Pass,password))
								else
									counter++;
							}//end of while(strcmp(nc.Pass,password)&& counter!=3)
							if(counter==3)
							{
								system("cls");
								system("color c");
								puts(" The password is wrong and your card was recorded by ATM !\n");
								printf(" Press any key to return to the previous page");
								getch();
							}//end of if(counter==3)
						}//end of if(strcmp(nc.Pass,password))
						else
						enter_card(fptr,&nc,crdn);
					}//end of if(strcmp(nc.CardNo,"0") && Number_len(atoi(crdn))==4)
					else
					{
						system("color c");
						puts("\n This card is not defined!\n");
						printf(" Press any key to return to the previous page");
						getch();
					}//end of else
					printf(" Press any key to return to the previous page");
					break;
				}//end of case2
				case 3:
					system("color a");
					thank_you();
					fclose(fptr);
					return 0;//end of case3
				case 4:
				{
					for(int i=0;i<10000-num;i++)
					{
						fseek(fptr,i*sizeof(struct card),SEEK_SET);
						fwrite(&nc,sizeof(struct card),1,fptr);
					}//end of for
					system("cls");
					system("color a");
					puts(" Datas successfully was reseted\n");
					printf(" Press any key to return to the previous page");
					getch();
					break;
				}//end of case4	
				default ://if the user enter number out of range
				{
					system("cls");
					system("color c");
					puts("!! Incorrect selection !!\n");
					printf(" Press any key to return to the previous page");
					getch();
					break;
				}//end of default
			}//end of switch
		}//end of do while
		while(select!=3);
	}//end of else
}//end of main

