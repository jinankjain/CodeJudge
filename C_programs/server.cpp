/*
C socket server example
*/
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <bits/stdc++.h>
#include <unistd.h>
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
#include <iostream>
#include "dist/json/json.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("received SIGINT\n");
}


int main(int argc , char *argv[])
{

	pid_t pid = fork();

	if(pid == 0){

			// Signal Handlers

			if (signal(SIGINT, sig_handler) == SIG_ERR)
		        printf("\ncan't catch SIGINT\n");

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
			//print the error message
				perror("bind failed. Error");
				return 1;
			}
			puts("bind done");

			//Listen
			listen(socket_desc , 3);

			//Accept and incoming connection
			puts("Waiting for incoming connections...");
			c = sizeof(struct sockaddr_in);

			//accept connection from an incoming client
			client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
			if (client_sock < 0)
			{
				perror("accept failed");
				return 1;
			}
			puts("Connection accepted");

			Json::Value root;   
			Json::Reader reader;

			//Receive a message from client
			while( (read_size = recv(client_sock , client_message , 20000 , 0)) > 0 )
			{
			//Send the message back to client
				std:: cout << " Strlen : " << strlen(client_message) << std::endl;


				bool parsingSuccessful = reader.parse( client_message, root );     //parse process
				    if ( !parsingSuccessful )
				    {
				        std::cout  << "Failed to parse"
				               << reader.getFormattedErrorMessages();
				        return 0;
				    }
				    // std::cout << root.get("hello", "A Default Value if not exists" ).asString() << std::endl;
				    cout << client_message << endl;

				   	//Parsing of the function json received:
				   	// 	 temp = simplejson.dumps({
					   	//   'id': sol.id, 
			      		//	'path' : str(os.getcwd()),
			      		//	'filename': str(name[:-4]),
			      		//	'input': input,
			      		//	'output': output,
			      		//  'time': p.timeLimit})

			}	

			if(read_size == 0)
			{
				puts("Client disconnected");
				fflush(stdout);
			}
			else if(read_size == -1)
			{
				perror("recv failed");
			}

			int time_limit = root.get("time", "5").asInt();
			string filename = root.get("filename", "error").asString();
			string input = root.get("input", "").asString();
			string output = root.get("output", "5").asString();
			string path = root.get("path", "5").asString();

			cout << path << endl;

			path += "/" + filename;


			std::ofstream file("input.txt");
			file << input;
			file.close();
			
			std::ofstream file_o("output.txt");
			file_o << output;
			file_o.close();

		// Child Process
		int file_read = open("input.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		int file_write = open("out.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

		dup2(file_read, 0);
		dup2(file_write, 1);   // make stdout go to file
		dup2(file_write, 2);   // make stderr go to file - you may choose to not do this
		               // or perhaps send stderr to another file

		close(file_write);     // file_write no longer needed - the dup'ed handles are sufficient

		char *const args[] = {argv[1] , NULL};
	    char *const envs[] = {"LD_PRELOAD=./EasySandbox.so",NULL};

	    execve(argv[1], args, envs);
	    execve(path.c_str(), args, envs);
	}

	else{
		sleep(10);
	}
	return 0;
}
