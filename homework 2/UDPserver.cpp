//winsoc UDP server program. This program opens a (registered) port
//wait for clients datagrams.Each arrived datagram will be displayed
// with clients IP addres and the whole datagram is then bounced back
//with servers name
#pragma comment(lib, "ws2_32.lib")//The #pragma comments indicates to the linker that the ws2_32.lib file is needed
#define _WINSOCK_DEPRECATED_NO_WARNINGS//before including winsock gear to avoid the warning and the rewrite
#define _CRT_SECURE_NO_WARNINGS//eliminate deprication warning for the older and less secure functions
#include <stdio.h>//header file for standrd sinput and output
#include<winsock2.h>//Header file contains most of the winsock functions, structures and definations

int main(int argc, char* argv[]) {// define the main function with argc as integer and argv[] as char parameter
	if (argc != 2) {// if statement will execute for the argument of argc not be equal to 2
		printf("Usage: %s [port_number]\n", argv[0]);// print a usage message to the user if argc is not 2
	return 1;// if the statement is true then return true
	}
	WSADATA ws;// create WSADATA object called ws
	int ret = WSAStartup(MAKEWORD(2, 2), &ws);//Initialize winsock by callig WSAstartup() function and return isa value as an integer and check for errors
	if (ret) {
		printf("WinSock API is not available.\n");//if WSAstartup() executed unsuccessfuly it provides this message
		return 1;//if this statement is true return 1 
	}
	printf("WinSock is ready!\n");//if WSAstartup() executed successfuly it provides this message
	//for a UDP server, we need to create asocket (DGRM), bind it with
	//desired local address (IP + port)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);//declare a socket and call the socket function and return its value to the sock variable
	if (sock == INVALID_SOCKET) {//check for errot to sure that the socket is a valied socket
		printf("Socket cannot be created.\n");//if the socket is invalied it provides this message
		WSACleanup();
		return 1;//if this statement is true return 1 
	}
	printf("Socket is good to go!\n");//if the socket is valied it provides this message 
	//make a bind
	SOCKADDR_IN ser;//declare a socadder_in object and set its values
	memset(&ser, 0, sizeof(ser));// set all the bytes to be zero
	ser.sin_family = AF_INET;		//IPv4 ; AF_INET is the Internet address family
	ser.sin_addr.s_addr = htonl(INADDR_ANY); // any address assigned to this host 
	ser.sin_port = htons(atoi(argv[1]));// a port number to which the socket will be bound 
	ret = bind(sock, (SOCKADDR *)&ser, sizeof(ser));//call the bind functipon, passing the created socket and the sockadder_in and containe the values to ret variable
	if (ret == SOCKET_ERROR) {//it will check the socket valiedity 
		printf("bind() failed\n"); return 1;//if the socket is invalied it shows the message and return the value 1
	}
	printf("bind is okey\n");//if the socket is valied it shows the message
	char hname[100], rbuf[1000], sbuf[1000];// declaration of three variables (Sbuf[], rbuf[], hname[]) which has string data type
	gethostname(hname, sizeof(hname));// use the function gethostname by using hname variable and its size
	printf("hostname: %s\n", hname);// print the hostname
	while (1) {//while true print those messages
		SOCKADDR_IN client;//declare a socadder_in object and set its values
		int clen = sizeof(client);//declaration of clen variable which contains integer value which is size of the client
		ret = recvfrom(sock, rbuf, sizeof(rbuf), 0, (SOCKADDR*)& client, &clen);//received from the server and contain the result in ret variable
		if (ret > 0) {//if ret grater then zero it will print the messaes
			printf("From %s: %s\n", inet_ntoa(client.sin_addr), rbuf);//print the message
			sprintf(sbuf, "%s: %s", hname, rbuf);// printf formate srting which referes to a control parameter
			sendto(sock, sbuf, strlen(sbuf), 0, (SOCKADDR*)& client, clen);//send from server
		}
		else {
			printf("Recvfrom returns error\n");// if error hapends print this message
		}
	}
	WSACleanup(); // WSACleanup function 
	return 0;//if program runs successfuly retun 0
}