#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringmethods.h"

int amtWords(const char* str) {
	int amt = 0;
	char* str_ = strdup(str);
	for(int i = 0; i < strlen(str); i++) {
		if(str_[i] == ' ') {
			amt++;
		}
	}
	return ++amt;
}

char* nthWord(const char* str, int n) {
	if(n >= amtWords(str)) {
		return NULL;
	}
	char* token = strtok(strdup(str), " ");
	for(int i = 0; i < n; i++) {
		token = strtok(NULL, " ");
	}
	return token;
}  