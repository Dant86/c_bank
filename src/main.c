#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "stringmethods.h"
#include "tsl.h"

void prcsMsg(char* msg, HashTable* t) {
	if(msg == NULL || t == NULL) {
		return;
	}
	/*
		All necessary null checks when
		accessing accounts are made in
		tsl.c
	*/
	int words = amtWords(msg);
	char* ting = nthWord(msg, 1);
	switch(words) {
		case 2:
			if(strcmp(nthWord(msg, 1), "print") != 0) {
				printf("Invalid message: %s\n", msg);
				break;
			}
			if(strcmp(nthWord(msg, 0), "bank") == 0) {
				tsl_printTable(t);
			}
			else {
				tsl_printAcc(t, nthWord(msg, 0));
			}
			break;
		case 3:
			if(strcmp(ting, "joins") == 0) {
				if(strcmp(nthWord(msg, 2), "trusted") == 0) {
					tsl_addAcc(t, nthWord(msg, 0), 1);
					break;
				}
				else if(strcmp(nthWord(msg, 2), "untrusted") == 0) {
					tsl_addAcc(t, nthWord(msg, 0), 0);
					break;
				}
				else {
					printf("Invalid message: %s\n", msg);
					break;
				}
			}
			else if(strcmp(ting, "deposits") == 0) {
				tsl_mkDep(t, nthWord(msg, 0), atof(nthWord(msg, 2)));
				break;
			}
			else if(strcmp(ting, "withdraws") == 0) {
				tslWdraw(t, nthWord(msg, 0), atof(nthWord(msg, 2)));
				break;
			}
			else {
				printf("Invalid message: %s\n", msg);
				break;
			}
			break;
		default:
			printf("Invalid message: %s\n", msg);
			break;
	}
}

int main(int argc, char* argv[]) {
	HashTable* t = mkTable();
	/*
		I have a char[] and char*
		because the functions in
		stringmethods use char*s,
		while it's easy to use
		fgets with a char[].
	*/
	char* response = malloc(sizeof(char) * 50);
	char str[80];
	// Load accounts at the start.
	if(tsl_load(t, "saved.txt") == 0) {
		printf("saved.txt not found. No previous information will be loaded into the bank.\n");
	}
	// Check to see if there is a ledger file,
	// otherwise print some error and exit.
	FILE* ledger = fopen("ledger.txt", "r");
	if(ledger == NULL) {
		printf("Ledger file not found.\n");
		return 0;
	}
	// If a file  with instructions is provided,
	if(argc == 2) {
		FILE* f = fopen(argv[1], "r");
		if(f == NULL) {
			// If we're being trolled and file doesn't exist,
			printf("file with name %s not found.\n", argv[1]);
			return 0;
		}
		while(fgets(str, 80, f) != NULL) {
			str[strlen(str)-1] = '\0';
			strcpy(response, str);
			prcsMsg(response, t);
			tsl_wrtMsg(response);
		}
		// Save and exit.
		tsl_save(t, "saved.txt");
		fclose(f);
		return 0;
	}
	// If no file provided,
	while(1) {
		fgets(str, 80, stdin);
		str[strlen(str)-1] = '\0';
		strcpy(response, str);
		if(strcmp(response, "QUIT") == 0) {
			// Save and exit.
			tsl_save(t, "saved.txt");
			return 0;
		}
		prcsMsg(response, t);
		tsl_wrtMsg(response);
	}
	return 0;
}