// first task of socket programming.This program takes in an IPv4 address
// in dotted decimal format, and the program tells which class this address
// belongs to

#include <stdio.h>												// is a statement which tells the compiler to insert the content of stdio and its the header file for standard input-output
#include <stdlib.h>												// is a header file for standard library like memory allocation, process controll, conversions and others

int main(int argc, char* argv[]) {								// define the main function with argc as integer and argv[] as char parameter
	if (argc != 2) {											// if statement will execute for the argument of argc not be equal to 2 
		printf("Usage: %s dotted-decimal-address\n", argv[0]); // print a usage message to the user if argc is not 2
		return 1;												// if the statement is true then return true
	}
	// we shoul analyse the address
	printf("address is %s\n", argv[1]);							// print the given address
	char part1[4] = "\0";										// define parameter part1[4] as char type and inatialised it by null char
	for (int i = 0; ; i++) {									// using for loop but don't know the final value of i
		if (argv[1][i] != '.') part1[i] = argv[1][i];			// the argv[1][i] = part[i] till get '.' the program will continue the if statement otherwise it breaks and comeout from the loop
		else break;
	}
	int va = atoi(part1);										// the atoi() function returns the integer representation of string part1 and stroage the value in int va 
	if (va >= 0 && va <= 127) printf("Class A\n");				// if statement that shows the range of classes and print according to class here show Class A if value of va >= 0 and va <= 127
	if (va >= 128 && va <= 191) printf("Class B\n");			// if statement which show Class B if the value of va >= 128 and va <= 191 
	if (va >= 192 && va <= 223) printf("Class C\n");			// if statement show Class C if value of va>=192 and va <= 223
	if (va >= 224) printf("Unknown Class\n");					// if statement shows Unknown Class if the value of  va >= 224
	return 0;													// this return 0 statement tells the os that the program has closed succesfully
}

