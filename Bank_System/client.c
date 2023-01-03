#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "stdtypes.h"
#include "admin.h"



extern uint8 stat1[];
extern acc * head_ptr;

uint16 change_account_password(acc * acc_ptr)
{
	uint32 pass_o,pass_n; 
	uint16 count;
	count = 0;
	
	printf("Please enter the old password: ");
	do
	{
		scanf("%lu",&pass_o);
		if(acc_ptr -> pass == pass_o)		//check if the password is right
		{
			break;
		}
		else
		{
			count++;
			if(count >= 2)					//if enter wrong password 2 times 
			{
				printf("Your password is wrong the system will exit\n");
				return 0;
			}
			else
			{
				printf("Your password is wrong try again: ");		//if enter wrong password
			}	
		}
		
	}while(count != 2);
	printf("Please enter your new password: ");
	scanf("%lu",&pass_n);
	acc_ptr -> pass = pass_n;			//save new password
	printf("Your password is change successfully: %lu\n",acc_ptr -> pass);
	
	return 1;
}


uint16 open_existing_account_c(void)
{
	uint64 c_bid;
	uint32 c_pass,res_pass;
	uint16 i=0;
	uint8 ch_ac,ch1_ac;
	acc *current = head_ptr;
	
	printf("Please enter your bank id: ");
	scanf("%llu",&c_bid);
	while(current != NULL)
	{
		system("cls");
		printf("\n\t\t\tClient Window\n\n");
		if(current->b_id == c_bid && strcmp(current->status , stat1)==0)		//check if the entered id is exist and active
		{
			printf("Please enter your password: ");
			do
			{
				scanf("%lu",&c_pass);
				if(current -> pass == c_pass)		//check if the password is right
				{
					break;
				}
				else
				{
					i++;
					if(i >= 2)						//if enter wrong password 2 times 
					{
						printf("Your password is wrong the system will exit\n");
						return 2;
					}
					else					
					{
						printf("Your password is wrong try again: ");			//if enter wrong password
					}	
				}
				
			}while(i != 2);
			op:
			system("cls");
		    printf("\n\t\t\tClient Window\n\n");
			printf("1 --> Make transaction \n2 --> Chang account Password \n3 --> Get cash \n4 --> Deposit in account \n5 --> Return to main menu \n6 --> Exit system\n\n");
			printf("Please enter your choice: ");
			scanf("%d",&ch_ac);
			system("cls");
			printf("\n\t\t\tClient Window\n\n");
			switch(ch_ac)
			{
				case 1: make_transaction(current ); 
						printf("\nTo return to menu enter \"1\"\n");
						printf("Please enter your choice: ");
						scanf("%d",&ch1_ac);
						if (ch1_ac == 1)
						{
							goto op;
						}
						else
						{
							return 1;
						}  
						break;
				case 2: res_pass = change_account_password(current); 
						if(res_pass == 0)
						{
							return 2;
						}
						else
						{
							printf("\nTo return to menu enter \"1\"\n");
							printf("Please enter your choice: ");
							scanf("%d",&ch1_ac);
							if (ch1_ac == 1)
							{
								goto op;
							}
							else
							{
								return 1;
							}  
						}
						break;
				case 3: get_cash(current);  
						printf("\nTo return to menu enter \"1\"\n");
						printf("Please enter your choice: ");
						scanf("%d",&ch1_ac);
						if (ch1_ac == 1)
						{
							goto op;
						}
						else
						{
							return 1;
						}  
						break;
				case 4: deposit_in_acc(current);  
						printf("\nTo return to menu enter \"1\"\n");
						printf("Please enter your choice: ");
						scanf("%d",&ch1_ac);
						if (ch1_ac == 1)
						{
							goto op;
						}
						else
						{
							return 1;
						}  
						break;
				case 5: goto op; 
				case 6: return 1;
				default: printf("Wrong choice\n"); Sleep(1500); 
						 goto op;	   break;
			}	
			
		}
		else if (current->b_id == c_bid && strcmp(current->status , stat1)!=0)			//check if the entered id is not active
		{
			printf("Your account is not active\n");
			return 0;
		}
		else
		{
			current = current -> next;
		}
	}
	if(current == NULL)
	{
		printf("This id is not found\n");
	}
	else{}
	return 0;
}

