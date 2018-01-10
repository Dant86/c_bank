bank: main.o stringmethods.o tsl.o hashtable.o linkedlist.o account.o
	gcc -o bank main.o stringmethods.o tsl.o hashtable.o linkedlist.o account.o

main.o: main.c stringmethods.h tsl.h hashtable.h linkedlist.h account.h
	gcc -c main.c

stringmethods.o: stringmethods.c stringmethods.h
	gcc -c stringmethods.c

tsl.o: tsl.c tsl.h hashtable.h linkedlist.h account.h stringmethods.h
	gcc -c tsl.c

hashtable.o: hashtable.c hashtable.h linkedlist.h account.h
	gcc -c hashtable.c

linkedlist.o: linkedlist.c linkedlist.h account.h
	gcc -c linkedlist.c

account.o: account.c account.h
	gcc -c account.c