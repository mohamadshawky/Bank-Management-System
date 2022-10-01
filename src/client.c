/********************************************************************************************************************************************
Author: 	 Mohamed Shawky Ahmed
Description: Bank Management System - C console project providing some admin and user commands.
Version:     01
file:        client.c
Date:        31/08/2022
*********************************************************************************************************************************************/
#include "../include/STD_TYPES.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/client.h"

/* This function inputs personal data of the client like:
	national ID, guardian national id, name, address, age,
	account ID, password, status & balance. */
void create_account(sClient_t* data){
	
	PRINTF("********** PERSONAL DATA OF A CLIENT *************\n");
	
	u32 count = 0;
	//enter national id
	NATIONAL_ID_FLAG:
	PRINTF(" NATIONAL ID: \t\t");
		scanf("%lld", &(data->national_id));
		if (!isdigit(data->national_id) && ((data->national_id < MIN14DIGITS) || (data->national_id > MAX14DIGITS))) {goto NATIONAL_ID_FLAG;}
	
	//enter name
	u32 count2 =0 ;
	NAME_FLAG:
	if (count2 == 3){return;}
	PRINTF(" FULL NAME:  \t\t");
      SCANF("%[^\n]s",data->name);
		u32 words_count = words(data->name);
		if (words_count < 4){
			PRINTF("\n>> Enter valid full name (4) words\n");
			++count2;
			goto NAME_FLAG;}
			
	//generate password																								
	srand(time(NULL));  
	data->acc_pwd = rand();

	//enter address
	u32 count3 = 0;
	words_count = 0;
	ADDR_FLAG:
	if (count3 == 3){
		printf("\n>> No more tries!");
		return;}
	printf(" FULL ADDRESS:\t\t");
      SCANF("%[^\n]s",data->addr);
	  words_count = words(data->addr);
	  if (words_count < 3){
			printf("\n>> Enter valid address!\n ST, City, Country\n");
			++count3;
			goto ADDR_FLAG;}
	
	//account status
	strcpy((data->acc_status),"active");
	
	//enter age & Gurdian national id
	u32 count4 = 0;
	AGE_FLAG:
	
	if (count4 == 3){return;}
	
		printf(" AGE:\t\t\t");
		SCANF("%f", &(data->age));
		
		if((data->age >= 1) && (data->age <= 100)){		
		
		if (data->age < 21){	/* GUARDIAN NATIONAL ID is required */
			GUARDIAN_NAT_ID:
			printf(" GUARDIAN NATIONAL ID: \t");
			SCANF("%lld", &(data->guardian_national_id));
		if (!isdigit(data->national_id) && ((data->guardian_national_id < MIN14DIGITS) || (data->guardian_national_id > MAX14DIGITS))){goto GUARDIAN_NAT_ID;}}
		else {data->guardian_national_id = 0x00;} }
		
		else{
			printf("\n>> Enter valid age!\n");
			++count4;
			goto AGE_FLAG;
		}
	
	//enter account balance
	u32 count5 = 0;
	BALANCE_FLAG:
	if (count5 == 3){return;}
	printf(" ACCOUNT BALANCE: \t");
		SCANF("%lld", &(data->acc_balance));
	if (!(data->acc_balance >= 1) || !(data->acc_balance <= 9223372036854)){
		printf("\n>> Enter valid balance!\n");
			++count5;
			goto BALANCE_FLAG;}
			
	//assign account id
	static u32 bank_id 	= 1000000000;
	data->acc_id = bank_id;
	bank_id ++;
	
	// Display created account data 
	PRINTF("\n********** CREATED ACOOUNT SUCCESSFULLY ***********\n");
	PRINTF(" FULL NAME:  \t\t%s\n", data->name);
	PRINTF(" NATIONAL ID: \t\t%lld\n", data->national_id);
	PRINTF(" FULL ADDRESS:\t\t%s\n", data->addr);
	PRINTF(" AGE:\t\t\t%.1f\n",data->age);
	PRINTF(" GUARDIAN NAT ID: \t%lld\n", data->guardian_national_id);
	PRINTF(" ACCOUNT ID:  \t\t%d\n",data->acc_id);
	PRINTF(" ACCOUNT STATUS:  \t%s\n",data->acc_status);
	PRINTF(" ACCOUNT BALANCE: \t%d$\n",data->acc_balance);
	PRINTF(" PASSWORD: \t\t%d\n\n",data->acc_pwd);
	PRINTF("\n******************************************************\n");
	PRINTF("<<DO NOT FORGET TO CAPTSURE A SCREENSHOOT (RAM STORAGE)>>");
	PRINTF("\n******************************************************\n");
}

/* This function inputs accoint id 1, account id 2 & balance to transfer */
void make_transaction(u32 id1, u32 id2, u64 balance){	
		 sClient_t* client1 = get_client(id1);
		 sClient_t* client2 = get_client(id2);
if ((strcmp(client1->acc_status, "active") == 0) && (strcmp(client2->acc_status, "active") == 0) && (balance <= (client1->acc_balance))){
	(client2->acc_balance) += balance;
	(client1->acc_balance) -= balance;
	printf(" Account ID %d balance = %lld$\n", id1, client1->acc_balance);
	printf(" Account ID %d balance = %lld$\n", id2, client2->acc_balance);	
}else{printf(" Sorry! Account ID %d has not sufficient balance or any of account ID %d or %d is not active! \n",id1, id1, id2);}
}

/* This function deposit balance of an account */
void deposit(u32 id, u64 balance){		
	sClient_t* client = get_client(id);
	if ((client) && (client->acc_status)){client->acc_balance += balance;
	printf(" Account ID %d balance = %d$\n", id, client->acc_balance);}
	else {printf(" Account ID %d is not active!\n");}
}

/* This function withdraw balance of an account*/
void withdraw(u32 id, u64 balance){	
	sClient_t* client = get_client(id);
	if ((client) && (client->acc_status) && ((balance) <= (client->acc_balance))){
	client->acc_balance -= balance;
	printf(" Account ID %d balance = %d$\n", id, client->acc_balance);}
	else {printf(" Account ID %d is not active or entered balance > account balance!\n",id);}	
}		

/* This fuction set the account satuts */		
void set_account_status(u32 id, u8* status){
	sClient_t* client = get_client(id);
	if (client && strcmp("active", client->acc_status) == 0){	
			if(strcmp("active", status) == 0){
				strcpy(client->acc_status, status);
				printf(" Account ID %d status becomes %s\n", client->acc_id, client->acc_status);
			}else if (strcmp("restricted", status) == 0){
				strcpy(client->acc_status, status);
				printf(" Account ID %d status becomes %s\n", client->acc_id, client->acc_status);
			}else if (strcmp("closed", status) == 0){
				strcpy(client->acc_status, status);
				printf(" Account ID %d status becomes %s\n", client->acc_id, client->acc_status);
			}else {
				printf("\n>> Invalid Input!\n");
	}}else{printf(" Account ID %d does not exist!\n", id);}
}

/* This function changes password of an account */		
u32 change_account_pwd(u32 id, u32 old_psw, u32 new_pwd){
	sClient_t* client = get_client(id);
	if (client && strcmp("active", client->acc_status) == 0){
		if (old_psw == client->acc_pwd){client->acc_pwd = new_pwd;
			printf(" NEW PASSWORD FOR ACCOUNT ID %d is %d\n", id, client->acc_pwd);}
	else{printf(" Password is not correct, Try again\n");} }
	else{printf(" Account ID %d is not active!\n", id);}
}

/* This function counts words in a string */	
int words(const char* sent){		
	u32 count = 0, i = 0;
	const u8* str = sent;
	u32 is_word = 0;
	do {
		switch(*str){
			case '\0':
			case ' ' :
			case '\t':
			case '\n':
			case '\r':
				if (is_word){
					is_word = 0;
					count++;}
			break;
			default: is_word = 1;
		}}while(*str++);
	
return count;
}	

/* This function return specified client if exists using id */ 
sClient_t* get_client(u32 id){
	for (u32 i = 0; i < size; i++){
			if (stakeholder[i].acc_id == id){
				return &stakeholder[i];
			}
	}
	return NULL;
}

/* This function checks on client password */ 
u32 get_pwd(u32 id, u32 pwd){
	u32 res = 0;
	sClient_t* client = get_client(id);
	res = (client -> acc_pwd) == pwd ? 1 : 0;
	return res;
}
