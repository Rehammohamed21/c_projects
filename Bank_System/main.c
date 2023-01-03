#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "stdtypes.h"
#include "admin.h"
#include "client.h"

extern acc * head_ptr;

int main(void)
{
	uint8 ch,ch1,ch2,ch3;
	uint16 res1, res2;
	//clear screan
	system("cls");
	goto options;
	
	options:
	printf("\n1 --> For admin \n2 --> For client \n0 --> For exit \n\n");
	printf("Please enter your choice: ");
	scanf("%d",&ch1);
	system("cls");
	if (ch1 == 1)
	{
		Admin:
		system("cls");
		printf("\n\t\t\tWelcome to Admin Window\n\n");
		printf("1 --> Create new account \n2 --> Open existing account \n3 --> Return main menue \n4 --> Exit system \n\n");
		printf("Please enter your choice: ");
		scanf("%d",&ch2);
		system("cls");
		printf("\n\t\t\tAdmin Window\n\n");
		switch(ch2)
		{
			case 1: create_new_acc(&head_ptr);
					printf("\nTo return  to main menu enter \"1\" or any to exit\n");
					printf("Please enter your choice: ");
					scanf("%d",&ch3);
					if (ch3 == 1)			//return to main menu
					{
						goto Admin;
					}
					else
					{
						system("cls");
						goto end;			//exit
					}
					break;
			case 2: res1 = open_existing_account();
					if(res1 == 0)
					{
						Sleep(1500);
					}
					goto Admin;
					break;
			case 3: goto options;
			case 4: system("cls");
					goto end;
					break;
			default: printf("Wrong choice\n"); 
					 Sleep(1500);
					 goto Admin; 				//if the entered choice is not exist it will return to menu 
					 break;
		}
	}
	else if (ch1 == 2)
	{
		Client:
		system("cls");
		printf("\n\t\t\tWelcome to Client Window\n\n");
		res2 = open_existing_account_c();
		if(res2 == 0 || res2 == 2)
		{
			Sleep(1500);
			system("cls");
			goto end;
		}
		else if(res2 == 1)
		{
			system("cls");
			goto end;
		}
	}
	else if(ch1 == 0)
	{
		system("cls");
		goto end;
		
	}
	else
	{
		printf("\nWrong choice To try again enter \"1\" or any to exit\n");		//if the entered choice is not exist
		printf("Please enter your choice: ");
		scanf("%d",&ch);
		if (ch == 1)
		{
			system("cls");
			goto options;
		}
		else
		{
			system("cls");
			goto end;
			
		}
	}
	end:
	printf("\n\n\n\t\t\t*** Thank you for using our Application ***\n\n");
	
	return 0;
}