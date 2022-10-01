/******************************************************************************************************************************************
Author: 	 Mohamed Shawky Ahmed
Description: Bank Management System - C console project providing some admin and user commands.
Version:     01
file:        app.c
Date:        31/08/2022
*******************************************************************************************************************************************/
#include "include/STD_TYPES.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/client.h"

/* Admin access data */
#define ADMIN_ACCOUNT 				"iti"
#define ADMIN_PWD					2022

void user_mode();
void admin_mode();

int main (){
	
	system ("cls");
	
	u32 mode = 0;
	
	BEGINNING:
		printf(" 0: USER MODE\n");
		printf(" 1: ADMIN MODE\n");
		printf(" 2: EXIT\n");
		MAIN:
		PRINTF(" COMMAND:   \t");
		SCANF("%d", &mode);
		switch(mode){
			case 0: 
				user_mode();
				mode = 0;
				goto BEGINNING;
				break;
			case 1:
				admin_mode();
				mode = 0;
				goto BEGINNING;
				break;
			case 2:
				exit(1);
			default:
				printf("\n>> Invalid input!\n");
				goto MAIN;
		}
}

void user_mode(){
	
	u32 command, id, id1, id2, old_pwd, new_pwd, user, pwd, count;
	s64 balance;
	
	USERMODE:
		if(count == 3){
			printf("\n>> No more tries!\n");
			return;}
	
	printf(" ACCOUNT ID: \t");
	SCANF("%d", &user);
	printf(" PASSWORD: \t");
	SCANF("%d", &pwd);

	if (get_client(user) && get_pwd(user,pwd)){
	u32 count;
	system("cls");
	CLIENTMODDE:
	printf("********* WELCOME TO BANK MANAGEMENT SYSTEM *********\n");
    printf(" 1: MAKE TRANSFER\n");
    printf(" 2: CHANGE ACCOUNT PASSWORD\n");
    printf(" 3: GET CASH\n");
    printf(" 4: DEPOSIT IN ACCOUNT \n");
	printf("-1: BACK\n");
	printf(" 0: EXIT\n");
	printf("*****************************************************\n");
	
	printf(" COMMAND:\t");
	scanf("%d", &command);
	
	switch(command){
		
		case -1: 
		
			system("cls");
			return;
			
		break;
		
		case 0:
		
			exit(1);
			
		break;
		
		case 1:
		
			count =0;	
			
		ID1:
		
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
			printf(" ACCOUNT ID 1: \t");
			scanf("%d", &id1);
			if ((id1 < MIN10DIGITS) || (id1 > MAX10DIGITS)){
				printf("\n>> Try again!\n");
				++count;
				goto ID1;}
				
			count = 0;	
		ID2:
		
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
				
				printf(" ACCOUNT ID 2: \t");
			scanf("%d", &id2);
			if ((id2 < MIN10DIGITS) || (id2 > MAX10DIGITS)){
				++count;
				printf("\n>> Try again!\n");
				goto ID2;}
			
			printf(" BALANCE = \t\t");
			scanf("%lld", &balance);
			
			make_transaction(id1,id2, balance);
			
			command = 0;
			
			goto CLIENTMODDE;
			
		break;
			
		case 2:	
		
			count = 0;
		ID:
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
			printf(" ACCOUNT ID : \t");
			scanf("%d", &id);
			
			if ((id < MIN3DIGITS) && (id > MAX5DIGITS)){
				printf("\n>> Try again!\n");
				++count;
				goto ID;}
				
			printf(" OLD PASSWORD: \t");
			scanf("%d",&old_pwd);
			
			printf(" NEW PASSWORD: \t");
			scanf("%d",&new_pwd);
			
			change_account_pwd(id, old_pwd, new_pwd);
			
			command = 0;
			
			goto CLIENTMODDE;
			
		break;
		
		case 3:
		
			count = 0;
		USER_WITHDRAW:
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
			printf(" Account ID = \t");
			scanf("%d", &id);
			if (!get_client(id)){
				printf("\n>> Invalid account!\n");
				count++;
			goto USER_WITHDRAW;}
			
			printf(" BALANCE = \t");
			scanf("%lld", &balance);
			
			withdraw(id, balance);
			
			command = 0;
			
			goto CLIENTMODDE;
			
		break;
		
		case 4:
		
			count = 0;
		USER_DEPOSIT:
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
			printf(" Account ID = \t");
			scanf("%d", &id);
			if (!get_client(id)){
				printf("\n>> Invalid account \n");
				count++;
			goto USER_DEPOSIT;}
			
			printf(" BALANCE = \t");
			scanf("%lld", &balance);
			
			deposit(id, balance);
			
			command = 0;
			
			goto CLIENTMODDE;
			
		break;
		
		default:
		
			printf("\n>> Invalid Input!");
			command = 0;
			goto CLIENTMODDE;
	}
	}else{
	printf("\n>> Invalid username or password, Try again!\n");}
	++count;
	goto USERMODE;}

void admin_mode(){
	
	u8 admin_account[50];
	u32 admin_pwd, count = 0;
	
	IDMODE:
		if(count == 3){
			printf("\n>> No more tries\n");
			return;}	
	printf(" USER NAME: \t");
	SCANF("%s", &admin_account);
	printf(" PASSWORD: \t");
	SCANF("%d", &admin_pwd);

	if ((strcmp(admin_account,ADMIN_ACCOUNT) == 0) && (admin_pwd == ADMIN_PWD)){
	u32 count;
	system("cls");
	ADMINMODE:
	printf("********* WELCOME TO BANK MANAGEMENT SYSTEM *********\n");
    printf(" 1: CREATE NEW ACCOUNT\n");
    printf(" 2: MAKE TRANSFER\n");
    printf(" 3: CHANGE ACCOUNT STATUS \n");
    printf(" 4: Get CASH\n");
	printf(" 5: DEPOSIT IN ACCOUNT\n");
	printf("-1: BACK\n");
	printf(" 0: EXIT\n");
	printf("*****************************************************\n");
	
	u32 command, id, id1, id2;
	s64 balance;
	u8 name[50], status[50];
	
	printf(" COMMAND:\t");
	scanf("%d", &command);
	system("cls");

	switch(command){
		case -1: 
			system("cls");
			return;
		break;
		
		case 0:
			exit(1);
		break;
		
		case 1:
		
		count = 0;
		
		CLIENTSNUMBER:
			if (count == 3){
				printf("\n>> No more tries!");
				return;}
			printf(" NUMBER OF CLIENTS = \t");
			scanf("%d", &size);
			if (size >= 50 || size <= 0){
				printf("\n>> Enter size within 1-50!\n");
				++count;
				goto CLIENTSNUMBER;}
				
			for (u32 i = 0; i < size; i++){create_account(&stakeholder[i]);}
			printf("\n>> %d ACCOUNTS ARE CREATED SUCCESSFULLY...\n", size);
			
			command = 0;
			
			goto ADMINMODE;
			
		break;
			
		case 2:	
		
			count = 0;
		ID1:
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
			printf(" ACCOUNT ID 1: \t");
			scanf("%d", &id1);
			if ((id1 < MIN10DIGITS) || (id1 > MAX10DIGITS)){
				printf("\n>>Try again!\n");
				++count;
				goto ID1;}
				
				count = 0;
		ID2:
			
			if(count == 3){
				printf("\n>> No more tries!\n");
				return;}
			printf(" ACCOUNT ID 2: \t");
			scanf("%d", &id2);
			if ((id2 < MIN10DIGITS) || (id2 > MAX10DIGITS)){
				printf(" Try again!\n");
				++count;
				goto ID2;}
			
			printf(" BALANCE = \t");
			scanf("%d", &balance);
			
			make_transaction(id1,id2, balance);
			
			command = 0;
			
			goto ADMINMODE;
		break;
		
		case 3:
		
			count = 0;
			
		ADMINGETSTATUS:
			if(count == 3){
				printf ("\n>> No more tries!\n");
				return;}
			printf(" Account ID = \t");
			scanf("%d", &id);
			if (!get_client(id)){
				printf(" Invalid account\n");
				count++;
			goto ADMINGETSTATUS;}
			
			PRINTF(" STATUS:  \t");
			SCANF("%s", &status);
			
			set_account_status(id,status);
			
			command = 0;
			
			goto ADMINMODE;
			
		break;
		
		case 4:
		
			count = 0;
			
		ADMINWITHDRAW:
			if(count == 3){
				printf ("\n>> No more tries!\n");
				return;}
			printf(" Account ID = \t");
			scanf("%d", &id);
			if (!get_client(id)){
				printf("\n>> Invalid account\n");
				count++;
			goto ADMINWITHDRAW;}
			
			printf(" BALANCE = \t");
			scanf("%lld", &balance);
			
			withdraw(id, balance);
			
			command = 0;
			
			goto ADMINMODE;
			
		break;
		
		case 5:
		
			count = 0;
			
		ADMINDEPOSIT:
			if(count == 3){
				printf ("\n>> No more tries!\n");
				return;}
			printf(" Account ID = \t");
			scanf("%d", &id);
			if (!get_client(id)){
				printf("\n>> Invalid account\n");
				count++;
				goto ADMINDEPOSIT;}
				
			printf(" BALANCE = \t");
			scanf("%lld", &balance);
			
			deposit(id, balance);
			
			command = 0;
			
			goto ADMINMODE;
			
		break;
		
		default:
		
			printf("\n>> Invalid Input!");
			command = 0;
			goto ADMINMODE;
	}	
}else {
	printf("\n>> Invalid username or password, Try again!\n");
	++count;
	goto IDMODE;} 
}
