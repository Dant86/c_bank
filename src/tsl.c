#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "stringmethods.h"

void tsl_addAcc(HashTable* t, const char* name, int trusted) {
	if(name == NULL) {
		printf("Failed to add %s.\n", name);
	}
	Account* a = tableSearch(t, name);
	if(a != NULL) {
		printf("%s already has an account in this bank.\n", name);
		return;
	}
	Account* b = mkAccount(strdup(name), trusted);
	tableAdd(t, strdup(name), b);
}

void tsl_mkDep(HashTable* t, const char* name, float amt) {
	Account* a = tableSearch(t, name);
	if(a == NULL) {
		printf("%s does not have an account in this bank.\n", name);
	}
	else {
		deposit(a, amt);
	}
}

void tslWdraw(HashTable* t, const char* name, float amt) {
	Account* a = tableSearch(t, name);
	if(a == NULL) {
		printf("%s does not have an account in this bank.\n", name);
	}
	else {
		withdraw(a, amt);
	}
}

void tsl_printAcc(HashTable* t, const char* name) {
	Account* a = tableSearch(t, name);
	if(a == NULL) {
		printf("%s does not have an account in this bank.\n", name);
	}
	else {
		printAcc(a);
	}
}

int tsl_save(const HashTable* t, const char* filename) {
	FILE* f = fopen(filename, "w");
	fclose(f);
	List* allAccs = entries(t);
	Node* curr = allAccs -> head;
	while(curr != NULL) {
		fFrSvAcc(curr -> value, filename);
		curr = curr -> next;
	}
	return 1;
}

int tsl_load(HashTable* t, const char* filename) {
	if(t == NULL || filename == NULL) {
		printf("Failed to load file.\n");
		return 0;
	}
	FILE* f = fopen(filename, "r");
	if(f == NULL) {
		printf("file with name %s not found in current directory.\n", filename);
		return 0;
	}
	char* name = malloc(sizeof(char) * 200);
	float balance = 0;
	char* trusted = malloc(sizeof(char) * 200);
	int inty = 0;
	char line[200];
	char* resp = malloc(sizeof(char) * 200);
	while(fgets(line, 200, f) != NULL) {
		line[strlen(line)-1] = '\0';
		strcpy(resp, line);
		name = nthWord(resp, 0);
		trusted = nthWord(resp, 1);
		balance = atof(nthWord(resp, 2));
		if(strcmp(trusted, "trusted") == 0) {
			inty = 1;
		}
		tsl_addAcc(t, name, inty);
		tsl_mkDep(t, name, balance);
	}
	fclose(f);
	return 1;
}

void tsl_printTable(const HashTable* t) {
	List* accounts = entries(t);
	Node* curr = accounts -> head;
	while(curr != NULL) {
		printAcc(curr -> value);
		curr = curr -> next;
	}
}

void tsl_wrtMsg(const char* msg) {
	/*
		NULL check to see if ledger file
		exists already made in main.
	 */
	FILE* ledger = fopen("ledger.txt", "a");
	fprintf(ledger, "%s\n", msg);
	fclose(ledger);
}
