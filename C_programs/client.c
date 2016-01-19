
/*
C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h> //strlen
#include<sys/socket.h> //socket
#include<arpa/inet.h> //inet_addr

#include <bits/stdc++.h>
#include <unistd.h>
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
#include <unistd.h>
#include <iostream>

using namespace std;
int main(int argc , char *argv[])
{
int sock;
char message[10000];
struct sockaddr_in server;
// char message[1000] , server_reply[2000];

//Create socket
sock = socket(AF_INET , SOCK_STREAM , 0);
if (sock == -1)
{
printf("Could not create socket");
}
puts("Socket created");

server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_family = AF_INET;
server.sin_port = htons( 9999 );

//Connect to remote server
if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
{
perror("connect failed. Error");
return 1;
}

puts("Connected\n");

//keep communicating with server
while(1)
{
printf("Enter message : ");
scanf("%99[^\n]" , message);


Json::Value fromScratch;
Json::Value array;
array.append("hello");
array.append("world");
fromScratch["hello"] = "world";
fromScratch["number"] = 2;
fromScratch["array"] = array;
fromScratch["object"]["hello"] = "world";


Json::FastWriter fastWriter;
std::string output = fastWriter.write(fromScratch);

strcpy(message, output.c_str());
std::cout << "Sending Data: " << message << std::endl;
cout << "Strlen " << strlen(message) << std::endl;	

//Send some data
if( send(sock , message , strlen(message) +1, 0) < 0)
{
puts("Send failed");
return 1;
}

std :: cin >> message;
//Receive a reply from the server
// if( recv(sock , server_reply , 2000 , 0) < 0)
// {
// 	puts("recv failed");
// 	break;
// }
}

close(sock);
return 0;
}
