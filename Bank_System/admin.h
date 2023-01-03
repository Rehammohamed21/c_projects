#ifndef  _ADMIN_H_
#define  _ADMIN_H_

typedef struct account
{
	uint8 name[50];
	uint8 address[50];
	uint64 n_id;
	uint16 age;
	uint64 g_id;
	uint64 balance;
	uint64 b_id;
	uint32 pass;
	uint8 status[20];
	struct account * next;
}acc;


uint16 check_name(const uint8* name_check);
uint16 check_id( uint64 id_check);
void create_new_acc(acc ** head);
uint16 open_existing_account(void);
void make_transaction(acc * acc_ptr );
void change_account_status(acc * acc_ptr);
void get_cash(acc * acc_ptr);
void deposit_in_acc(acc * acc_ptr);
void get_label(void);

#endif