#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct account {
	char* name;
	float balance;
	int trusted;
} Account;

Account* mkAccount(const char* name, int trusted);

void withdraw(Account* a, float amt);

void deposit(Account* a, float amt);

void printAcc(Account* a);

void err_msg_w(Account* a, float amt);

void err_msg_d(Account* a, float amt);

void fFrSvAcc(Account* a, const char* filename);

#endif