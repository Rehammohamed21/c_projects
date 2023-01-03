#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "stdtypes.h"
#include "admin.h"


#define MIN_ID		20000000000000
#define MAX_ID		99999999999999


uint8 stat1[]="Active";
uint8 stat2[]="Restricted";
uint8 stat3[]="Closed";
static uint64 bank_id = 1000000000;

acc * head_ptr = NULL;

void create_new_acc(acc ** head)
{

	acc * new = (acc *)malloc(sizeof(acc));
	if(new != NULL)
	{
		fflush(stdin);
		printf("please enter the quadruple name: ");
		scanf("%[^\n]s", new -> name);
		fflush(stdin);
		while(check_name(new -> name) < 3)                //check if the name is quadruple
		{
			printf("Invalid, please enter quadruple name: ");
			scanf("%[^\n]s", new -> name);
		}
		fflush(stdin);
		printf("please enter the address: ");
		scanf("%[^\n]s", new -> address);
		fflush(stdin);
		printf("please enter the national id: ");
		scanf("%llu", &new -> n_id);
		while(check_id(new -> n_id) != 2)				//check if the id is equal 14 digits
		{
			printf("Invalid, please enter national id with 14 numbers: ");
			scanf("%llu", &new -> n_id);
			
		}
		printf("please enter the age: ");
		scanf("%hu", &new -> age);
		if(new -> age < 21)
		{
			printf("please enter guardian id: ");
			scanf("%llu", &new -> g_id);
			while(check_id(new -> g_id) != 2)
			{
				printf("Invalid ,please enter guardian id with 14 numbers: ");
				scanf("%llu", &new -> g_id);
			}
		}
		else
		{
			new -> g_id = 0;
		}
		printf("please enter the balance: ");
		scanf("%llu", &new -> balance);
		new -> b_id = bank_id;
		srand(time(0));
		new -> pass = rand();
		strcpy(new -> status, "Active");
		system("cls");
		printf("\t\t\tAdmin Window\n\n");
		printf("The account is created successfully\n\n");
		printf("Name        --> %s\n",new -> name);
		printf("Address     --> %s\n",new -> address);
		printf("National ID --> %llu\n",new -> n_id);
		printf("Age         --> %hu\n",new -> age);
		printf("Guardian ID --> %llu\n",new -> g_id);
		printf("Balance     --> %llu EGP\n",new -> balance);
		printf("Bank id     --> %llu\n",new -> b_id);
		printf("Password    --> %lu\n",new -> pass);
		printf("Status      --> %s\n",new -> status);
		bank_id++;
		
		new -> next = NULL;
		
		if(*head == NULL)
		{
			*head = new;
		}
		else
		{
			acc * current = * head;
			while(current -> next != NULL)
			{
				current = current -> next;
			}
			current -> next = new;
		}
		
	}
	else
	{
		printf("There is an error\n");
	}
}

void make_transaction(acc * acc_ptr )
{
	uint64  c2_bid, bal;
	acc *client2 = head_ptr;
	
	printf("Please enter client2 bank id: ");
	scanf("%llu",&c2_bid);
	if(acc_ptr -> b_id == c2_bid)				//check if the 2 accounts are the same
	{
		printf("Invalid , the id of client2 is the same as the id of client1\n");
	}
	else
	{
		if(client2 != NULL)
		{
			if(client2 -> b_id == c2_bid && strcmp(client2->status , stat1)==0)    		//check if client2 id is exist and active
			{
				printf("The account balance of client1 is %llu EGP\n",acc_ptr -> balance);
				printf("The account balance of client2 is %llu EGP\n",client2 -> balance);
				printf("Please enter the amount of transfered money: ");
				scanf("%ld",&bal);
				if(acc_ptr->balance >= bal)										//check if there is enough money to transfer
				{
					client2 -> balance = client2 -> balance + bal;				//add the transferred money to client2
					acc_ptr -> balance = acc_ptr -> balance - bal;				//decrease the balance of client1 by the amount of transferred money 
					printf("The account balance of client1 is %llu EGP\n",acc_ptr -> balance);
					printf("The account balance of client2 is %llu EGP\n",client2 -> balance);
				}
				else
				{
					printf("There is not enough money in the account\n");
				}	
			}
			else if(client2 -> b_id == c2_bid && strcmp(client2->status , stat1)!=0)      //check if client2 account is not active
			{
				printf("the client2 account status is: %s\n",client2->status);
				printf("You cannot take any action\n");
			}
			else
			{
				client2 = acc_ptr -> next;
			}
		}
		else
		{
			printf("there is no account with this id\n");
		}
	}		
}

void change_account_status(acc * acc_ptr )
{
	uint8 stat[20];
	
	printf("the status of the account is: %s\n",acc_ptr->status);
	printf("Enter:\n");
	printf("\"Active\"     --> to change status of the account to Active\n");
	printf("\"Restricted\" --> to change status of the account to Restricted\n");
    printf("\"Closed\"     --> to change status of the account to Closed\n\n");
	printf("Please enter the new status: ");
	fflush(stdin);
	scanf("%[^\n]s",stat);
	if(strcmp(stat , stat1)== 0 || strcmp(stat , stat2)== 0 || strcmp(stat , stat3)== 0)    
	{
		strcpy(acc_ptr->status,stat);
	    printf("The new account status is: %s\n",acc_ptr->status);
	}
	else
	{
		printf("Invalid choice\n");
	}
}

void get_cash(acc * acc_ptr)
{
	uint64 n_bal;
	
	printf("The account balance is: %llu EGP\n",acc_ptr -> balance);
	printf("Enter the cash amount you want: ");
	scanf("%llu",&n_bal);
	if(acc_ptr->balance < n_bal)					//check if there is not enough money to get
	{
		printf("There is not enough money in the account\n");
	}
	else
	{
		acc_ptr -> balance = acc_ptr -> balance - n_bal;
		printf("The new account balance is %llu EGP\n",acc_ptr -> balance);
	}	
		
}

void deposit_in_acc(acc * acc_ptr)
{
	uint64 a_bal;
		
	printf("The account balance is: %llu EGP\n",acc_ptr -> balance);
	printf("Enter the cash amount you want to add: ");
	scanf("%llu",&a_bal);
	acc_ptr -> balance = acc_ptr -> balance + a_bal;
	printf("The new account balance is %llu EGP\n",acc_ptr -> balance);
}

uint16 open_existing_account(void)
{
	uint64 c_bid;
	uint8 ch_a,ch1_a,ch2_a;
	acc *current = head_ptr;
	
	printf("Please enter client bank id: ");
	scanf("%llu",&c_bid);
		
	while(current != NULL)
	{
		system("cls");
		printf("\n\t\t\tAdmin Window\n\n");
		if( current->b_id == c_bid && strcmp(current->status , stat1)==0)    //check if the entered id is exist and active
		{
			op:
			system("cls");
			printf("\n\t\t\tAdmin Window\n\n");
			printf("1 --> Make transaction \n2 --> Chang account status \n3 --> Get cash \n4 --> Deposit in account \n5 --> Return to main menu \n\n");
			printf("Please enter your chosen number: ");
			scanf("%d",&ch_a);
			system("cls");
			printf("\n\t\t\tAdmin Window\n\n");
			switch(ch_a)
			{
				case 1: make_transaction(current );
						printf("\nTo return to menu enter \"1\"\n");
						printf("Please enter your choice: ");
						scanf("%d",&ch2_a);
						if (ch2_a == 1)
						{
							goto op;
						}
						else
						{
							return 1;
						} 
						break;
				case 2: change_account_status(current);   
						printf("\nTo return to menu enter \"1\"\n");
						printf("Please enter your choice: ");
						scanf("%d",&ch2_a);
						if (ch2_a == 1)
						{
							goto op;
						}
						else
						{
							return 1;
						}  
						break;
				case 3: get_cash(current); 
						printf("\nTo return to menu enter \"1\"\n");
						printf("Please enter your choice: ");
						scanf("%d",&ch2_a);
						if (ch2_a == 1)
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
						scanf("%d",&ch2_a);
						if (ch2_a == 1)
						{
							goto op;
						}
						else
						{
							return 1;
						}  
						break;
				case 5: return 1; 
				default: printf("Wrong choice\n");  
						 Sleep(1500);
						 goto op; break;
			}	
			
		}
		else if (current->b_id == c_bid && strcmp(current->status , stat1)!=0)
		{
			if(strcmp(current->status , stat2)==0)				//check if the account is restricted
			{
				printf("The account is Restricted if you want to change the status enter 1\n");
				scanf("%d",&ch1_a);
				system("cls");
				printf("\n\t\t\tAdmin Window\n\n");
				if(ch1_a==1)
				{
					change_account_status(current);
					printf("\nTo return to menu enter \"1\"\n");
					printf("Please enter your choice: ");
					scanf("%d",&ch2_a);
					if (ch2_a == 1)
					{
						goto op;
					}
					else
					{
						return 1;
					}  
				}
				else
				{
					return 1;
				}
			}
			else if(strcmp(current->status , stat3)==0)   		//check if the account is closed
			{
				printf("The account is closed or Not found there is no action can take\n");
				return 0;
			}
			
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


uint16 check_name(const uint8* name_check)			
{
	uint16 i,c,flag;
	c = 0;
	flag = 0;
	for(i=0; name_check[i]!='\0' ; ++i)
	{
		if(isdigit(name_check[i])==0)       //check if there is no character in the name
		{
			if(name_check[i] == ' ' && name_check[i+1] != ' ')    //check if there is spaces in the string and count it
			{
				c++;
			}
		}
		else
		{
			flag = 1;
			break;
		}
	}
	if(flag ==1)
	{
		printf("Invalid, there is a number in the name\n");
	}
	
	return c;			//return number of spaces in the string
}

uint16 check_id( uint64 id_check)
{
	
	if(id_check > MIN_ID && id_check < MAX_ID)    //check if id is 14 digit between the 2 macros that we define them
	{
		return 2;
	}	
		
	return 1;
	
}

