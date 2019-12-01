a.out: main_v1.o functions.o
	gcc main_v1.o functions.o -o a.out
main_v1.o: main_v1.c
	gcc -c main_v1.c
functions.o: functions.c
	gcc -c functions.c
