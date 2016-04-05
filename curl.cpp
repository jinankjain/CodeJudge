#include <stdio.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <bits/stdc++.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h> 
#include <sys/wait.h>

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */

    // Socket ---


    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[20000];

    // Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
      printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    // Put here the port number.
    server.sin_port = htons( 6030 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
      perror("bind failed. Error");
      return 1;
    }
    puts("bind done");

    // system("./xx.sh");
    listen(socket_desc , 1);

    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client

    const char *comm = "curl -H \"Content-Type: application/json\" -X GET -d '{\"username\":\"amit\",\"password\":\"amit\"}' http://localhost:8000/judge/update_result/";
    printf("%s\n", comm);
    system("./xx.sh");


    printf("SentCurl Requet\n");

    // client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    // if (client_sock < 0)
    // {
    //   perror("accept failed");
    //   return 1;
    // }
    puts("Connection accepted");
    send(socket_desc, "Hello, world!\n", 1024, 0);

    //Receive a message from client
    
    close(client_sock);
    close(socket_desc);

  }
  return 0;
}