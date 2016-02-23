/*
C socket server example
*/
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <bits/stdc++.h>
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
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

using namespace std;

void sig_handler(int signo)
{
 	// if (signo == SIGINT )
	 //    cout << "Received Signal\n";

  	if (signo == SIGXCPU)
  		cout << "Recieved Time Limit Exceed\n";

  	else cout << "In FUnction exiting\n";

	close(1);
	close(0);
	close(2);
	exit(55);
}

int getrlimit(int resource, struct rlimit *rlim); 
int setrlimit(int resource, const struct rlimit *rlim);


int main(int argc , char *argv[])
{

	pid_t pid = fork();

	if(pid == 0){

			// Signal Handlers

			if (signal(SIGXCPU , sig_handler) == SIG_ERR)
		        printf("\ncan't catch SIGINT\n");

		    if (signal(SIGXFSZ , sig_handler) == SIG_ERR)
		        printf("\ncan't catch SIGINT\n");
		    // if (signal(SIGKILL , sig_handler) == SIG_ERR)
		    //     printf("\ncan't catch SIGINT\n");
		    if (signal(SIGINT , sig_handler) == SIG_ERR)
		        printf("\ncan't catch SIGINT\n");

		    if (signal(SIGSEGV , sig_handler) == SIG_ERR)
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
		close(file_read); 

		// Setting Up Resource Limit.

		struct rlimit rl; 
		
		// First get the time limit on CPU 
		getrlimit (RLIMIT_CPU, &rl); 
		
		printf("\n Default value is : %lld\n", (long long int)rl.rlim_cur); 
		
		// Change the time limit 
		rl.rlim_cur = time_limit; 
		rl.rlim_max = time_limit + 1; 
		// Now call setrlimit() to set the  
		// changed value. 

		setrlimit (RLIMIT_CPU, &rl); 
		
		// Again get the limit and check 
		getrlimit (RLIMIT_CPU, &rl); 
		
		printf("\n Default value now is : %lld %lld\n", (long long int)rl.rlim_cur, (long long int)rl.rlim_max); 
		
		// char ww*	 = path.c_str();
		char * args[] = {(char *)path.c_str() , NULL};
		// char *const args[] = {argv[1] , NULL};
	    char * envs[] = {"LD_PRELOAD=./EasySandbox.so", NULL};

	    cout << "Path : " << path << endl;
	    sleep(1);
	    execve(path.c_str(), args, envs);
	    perror("execve");
	    exit(5);
	}

	else{

		// sleep(4);
		int status = 5;
		if ( waitpid(pid, &status, 0) == -1 ) {
		    perror("waitpid failed");
		    return EXIT_FAILURE;
		}

		if ( WIFEXITED(status) ) {
		    const int es = WEXITSTATUS(status);
		    printf("exit status was %d\n", es);
		}

		cout << "Stats : " << status << endl;






//  -------------------------------------------------------------------------------------------------------------
		// 	Socket FOr Sending The Data
	sleep(10);
	int sock;
	char message[] = "Message In Cpp";
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
	server.sin_port = htons( 6031 );

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
	// scanf("%99[^\n]" , message);


	// Json::Value fromScratch;
	// Json::Value array;
	// array.append("hello");
	// array.append("world");
	// fromScratch["hello"] = "world";
	// fromScratch["number"] = 2;
	// fromScratch["array"] = array;
	// fromScratch["object"]["hello"] = "world";


	// Json::FastWriter fastWriter;
	// std::string output = fastWriter.write(fromScratch);

	// strcpy(message, output.c_str());
	// std::cout << "Sending Data: " << message << std::endl;
	// cout << "Strlen " << strlen(message) << std::endl;	

	//Send some data

	if( send(sock , message , strlen(message) +1, 0) < 0)
	{
	puts("Send failed");
	return 1;
	}

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
	// return 0;
}
