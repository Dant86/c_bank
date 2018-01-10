#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "stringmethods.h"

void tsl_addAcc(HashTable* t, const char* name, int trusted);

void tsl_mkDep(HashTable* t, const char* name, float amt);

void tslWdraw(HashTable* t, const char* name, float amt);

void tsl_printAcc(HashTable* t, const char* name);

int tsl_save(const HashTable* t, const char* filename);

int tsl_load(HashTable* t, const char* filename);

void tsl_printTable(const HashTable* t);

void tsl_wrtMsg(const char* msg);