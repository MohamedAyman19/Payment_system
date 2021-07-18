#include<stdio.h>
#include<string.h>
#include "TypeDef.h"

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef struct ST_terminalData_t
{
	f32_t transAmount;
	f32_t maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_transStat_t
{
	DECLINED,
	APPROVED
}EN_transStat_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t transData;
	EN_transStat_t transStat;
}ST_transaction;



typedef struct ST_accountBalance_t
{
	f32_t balance;
	uint8_t primaryAccountNumber[20];
}ST_accountBalance_t;

uint8_t Linear_search(ST_accountBalance_t*ptrtostruc,uint8_t size,uint8_t* number);
uint8_t expired_check(uint8_t transDate[11],uint8_t cardExpDate[6]);
uint8_t AccountBalance_check(uint8_t primAccNumber[20],f32_t bal,ST_accountBalance_t* Acc_Balance);


ST_accountBalance_t Acc[10];

const f32_t MaxAmmount=500;


void main(void)  
{

	Acc[0].balance=100;
	strcpy(Acc[0].primaryAccountNumber,"123456789");
	Acc[1].balance=6000;
	strcpy(Acc[1].primaryAccountNumber,"234567891");
	Acc[2].balance=3250.25;
	strcpy(Acc[2].primaryAccountNumber,"567891234");
	Acc[3].balance=1500.12;
	strcpy(Acc[3].primaryAccountNumber,"456789123");
	Acc[4].balance=500;
	strcpy(Acc[4].primaryAccountNumber,"258649173");
	Acc[5].balance=2100;
	strcpy(Acc[5].primaryAccountNumber,"654823719");
	Acc[6].balance=0;
	strcpy(Acc[6].primaryAccountNumber,"971362485");
	Acc[7].balance=1;
	strcpy(Acc[7].primaryAccountNumber,"793148625");
	Acc[8].balance=10.12;
	strcpy(Acc[8].primaryAccountNumber,"123123456");
	Acc[9].balance=0.55;
	strcpy(Acc[9].primaryAccountNumber,"456789321");


	ST_cardData_t Card;
	ST_terminalData_t Terminal;
	Terminal.maxTransAmount=MaxAmmount;
	uint8_t cont='y';
	
	do
	{
		printf("Please Enter Card Data:\n");
		printf("Please Enter the Card Holder Name:\n");
		scanf("%s",Card.cardHolderName);
		printf("Please Enter the Primary Account Number:\n");
		scanf("%s",Card.primaryAccountNumber);
		printf("Please Enter card Expiry Date mm/yy:\n");
		scanf("%s",Card.cardExpirationDate);
		printf("Please Enter Terminal Data:\n");
		printf("Please Enter the transaction Amount:\n");
		scanf("%f",&Terminal.transAmount);
		if(Terminal.transAmount>Terminal.maxTransAmount)
		{
			printf("The Transaction is DECLINED\n");
			
		}
		else
		{
			printf("Please Enter Terminal Date-dd/mm/yyyy-:\n");
			scanf("%s",Terminal.transactionDate);
			printf("Verifying Data from the server...\n");
			if(!(expired_check(Terminal.transactionDate,Card.cardExpirationDate)))
			{
				printf("The Transaction is DECLINED (expired)\n");
			}
			else if(!(AccountBalance_check(Card.primaryAccountNumber,Terminal.transAmount,Acc)))
			{
				printf("The Transaction is DECLINED\n");
			}
			else
			{
				printf("The Transaction is Approved\n");
			}
		}
		printf("do you want to continue(y/n)?\n");
		scanf("%s",&cont);
	}while(cont=='y');

}

uint8_t expired_check(uint8_t transDate[11],uint8_t cardExpDate[6])
{
	uint8_t tran;
	uint8_t card;
	card=(cardExpDate[3]-'0')*10+cardExpDate[4]-'0';
	tran=(transDate[8]-'0')*10+transDate[9]-'0';
	if(card<tran)
		return 0;
	if(card>tran)
		return 1;
	card=(cardExpDate[0]-'0')*10+cardExpDate[1]-'0';
	tran=(transDate[3]-'0')*10+transDate[4]-'0';
	if(card<tran)
		return 0;
	return 1;
}
uint8_t AccountBalance_check(uint8_t primAccNumber[20],f32_t bal,ST_accountBalance_t* Acc_Balance)
{
	uint8_t index=Linear_search(Acc_Balance,10,primAccNumber);
	if(index==255)
	{
		
		printf("account not found\n");
		return 0;
	}
	if(bal>Acc_Balance[index].balance)
	{
		printf("requred ammount not available\n");
		return 0;
	}
	printf("available \n");
	return 1;
}
uint8_t Linear_search(ST_accountBalance_t*ptrtostruc,uint8_t size,uint8_t* number)
{
	uint8_t j;
	for(uint8_t i=0;i<size;i++)
	{
		
		for(j=0;j<10;j++)
		{
			if(number[j]!=ptrtostruc[i].primaryAccountNumber[j])
				break;
		}
		if(j>9)
			
			return i;	
	}
	return 255;
}
