/********************************************************************************************************************************************
Author: 	 Mohamed Shawky Ahmed
Description: Bank Management System - C console project providing some admin and user commands.
Version:     01
file:        client.h
Date:        31/08/2022
*********************************************************************************************************************************************/
#ifndef CLIENT_H
#define CLIENT_H

#include "STD_TYPES.h"
			
/* Verification data for national id & password */
#define MIN14DIGITS 	10000000000000		
#define MAX14DIGITS 	99999999999999
#define MIN10DIGITS 	1000000000
#define MAX10DIGITS 	9999999999	
#define MIN5DIGITS 		10000	
#define MAX5DIGITS 		99999
#define MIN3DIGITS		100
#define MAX3DIGITS		999

#define PRINTF(...)		{fflush(stdout); \
						fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}

#define SCANF(...)		{fflush(stdout); \
						fflush(stdin); \
						scanf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}

typedef struct sClient{
	
	u64 national_id;		
	u64 guardian_national_id;
	u8 name[50];
	u8 addr[50];
	f32 age;
	u32 acc_id;				
	u32 acc_pwd;				
	u8 acc_status[50];
	u64 acc_balance;	

}sClient_t;

/* Global data */
sClient_t stakeholder[50];
u32 size;

/* APIs */
void create_account(sClient_t*);	
void make_transaction(u32, u32, u64);
void deposit(u32, u64);
void withdraw(u32, u64);
void set_account_status(u32, u8*);		//admin mode
u32 change_account_pwd(u32, u32, u32);	//client mode

/* utilities functions */
int words(const char*);
sClient_t* get_client(u32);
u32 get_pwd(u32, u32;);

#endif	/* CLIENT_H */

