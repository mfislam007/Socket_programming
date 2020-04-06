// winsock UDP client program. This program sends user inputs as datagrams to an udp server
//when userr enters "quit", the program stops
#pragma comment(lib, "ws2_32.lib") //The #pragma comments indicates to the linker that the ws2_32.lib file is needed
#define _WINSOCK_DEPRECATED_NO_WARNINGS //before including winsock gear to avoid the warning and the rewrite
#define _CRT_SECURE_NO_WARNINGS //eliminate deprication warning for the older and less secure functions
#include <stdio.h> //header file for standrd sinput and output
#include<winsock2.h> //Header file contains most of the winsock functions, structures and definations

int main(int argc, char* argv[]) {// define the main function with argc as integer and argv[] as char parameter
	if (argc != 3) {// if statement will execute for the argument of argc not be equal to 3
		printf("Usage: %s [server_IP] [port]\n", argv[0]);// print a usage message to the user if argc is not 3
		return 1;// if the statement is true then return true
	}
	}
	WSADATA wsa;// create WSADATA object called wsa 
	int ret = WSAStartup(0x00020002, &wsa);//Initialize winsock by callig WSAstartup() function and return isa value as an integer and check for errors
	if (ret) {
		printf("winsock API is not okey\n"); return 1;//if WSAstartup() executed unsuccessfuly it provides this message and return 1 
	}
	printf("winsock API is ready\n");//if WSAstartup() executed successfuly it provides this message
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);//declare a socket and call the socket function and return its value to the sock variable
	if (sock == INVALID_SOCKET) {//check for errot to sure that the socket is a valied socket
		printf("can not create a socket\n"); return 1;//if the socket is invalied it provides this message and return 1
	}
	printf("a socket is created\n"); return 1;//if the socket is valied it provides this message and return 1
	SOCKADDR_IN ser;//declare a socadder_in object and set its values
	ser.sin_family = AF_INET;//AF_INET is the Internet address family
	ser.sin_port = htons(atoi(argv[2]));// a port number to which the socket will be bound
	//ret = inet_aton(argv[1], &ser.sin_addr);
	ser.sin_addr.s_addr = inet_addr(argv[1]);// agrv[1] will contain the local IP address to which the socket will be bound
	if (ret == 0) {//it will check the local IP address valiedity 
		printf("Address is not valied\n"); return 1;//if IP address is not valied it shows the message and return the value 1
	}
	printf("welcome to UDP communications! enter QUIT will stop the program\n\n");//if IP address is valied it shows the message
	char sbuf[1000], rbuf[1000];// declaration of two variables (Sbuf[], rbuf[]) which has string data type
	int slen = sizeof(ser);// declaration of variable slen contains size of ser in integer data 
	while (1) {//while true print those messages
		printf("message>> ");// print message>>
		scanf("%s", sbuf)// print from keyboard the message
		if (strcmp(sbuf, "QUIT") == 0) break;//for breaking the while loop need QUIT
		sendto(sock, sbuf, strlen(sbuf), 0, (SOCKADDR*)& ser, slen);// send to the server
		recvfrom(sock, rbuf, sizeof(rbuf), 0, (SOCKADDR*)& ser, &slen);//received from the server
		printf("\t%s\n", rbuf);// print the receieved values
	}
	printf("bay-bay nina\n");// print bay-bay nina
	WSACleanup();//Call WSACleanup() before the program stops


}