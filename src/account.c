#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

Account* mkAccount(const char* name, int trusted) {
	Account* a = malloc(sizeof(Account));
	a -> name = malloc(sizeof(char) * strlen(name));
	strcpy(a -> name, name);
	a -> balance = 0;
	a -> trusted = trusted;
	return a;
}

void err_msg_w(Account* a, float amt) {
	printf("failed to withdraw $%.2f from %s's account.\n", amt, a -> name);
}

void err_msg_d(Account* a, float amt) {
	printf("failed to deposit $%.2f to %s's account.\n", amt, a -> name);
}

void withdraw(Account* a, float amt) {
	if(amt < 0) {
		err_msg_w(a, amt);
		return;
	}
	if(a -> balance - amt < 0) {
		if(!(a -> trusted)) {
			err_msg_w(a, amt);
			return;
		}
		if(a -> balance - amt < -1000) {
			err_msg_w(a, amt);
			return;
		}
	}
	a -> balance -= amt;
}

void deposit(Account* a, float amt) {
	if(amt < 0) {
		err_msg_d(a, amt);
		return;
	}
	a -> balance += amt;
}

void printAcc(Account* a) {
	char* t;
	if(a -> trusted) {
		t = "trusted";
	}
	else {
		t = "untrusted";
	}
	printf("%s (%s):\t\t$%.2f\n", a -> name, t, a -> balance);
}

void fFrSvAcc(Account* a, const char* filename) {
	char* t;
	if(a -> trusted) {
		t = "trusted";
	}
	else {
		t = "untrusted";
	}
	FILE* f = fopen(filename, "a");
	fprintf(f, "%s %s %f\n", a -> name, t, a -> balance);
	fclose(f);
}
