#include <SDL_net.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


int main(int argc, char**argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	IPaddress ip;

	//Returns: a valid TCPsocket on success
	//check if IP is valid.
	SDLNet_ResolveHost(&ip, NULL, 1234);


	TCPsocket server = SDLNet_TCP_Open(&ip);
	TCPsocket client = NULL;

	//message to be sent
	char *msg = "You connected to server.";

	cout << "Server is up" << endl;
	//One thread keeps listening for as long as we can connect clients
	do
	{
		client = SDLNet_TCP_Accept(server);
	} while (!client);

	
	SDLNet_TCP_Send(client, msg, strlen(msg) + 1);
	//This is a thread for each connection that is made.
	do
	{
		
		int recievedByteCount = SDLNet_TCP_Recv(client, msg, strlen(msg) + 1);
		if (recievedByteCount <= 0)
		{
			
		}
		else
		{
			cout << msg << endl;
		}
	} while (client);

	/*
	//thread will keep the connection going
	while (SDLNet_TCP_Recv(client, msg, strlen(msg) + 1)) {
		//wait for server to accept a connection from client
		
		//check if connection is accepted
		//if (client){
			//cout << "Client connected. Sending message." << endl;
			//send the Hello message
			//SDLNet_TCP_Send(client, msg, strlen(msg) + 1);
			//cout << "Message sent. Waiting for Client Input." << endl;
			cout << msg;
			
			/*
			if (strcmp(msg, "Received") == 0){
				cout << "Message recieved. Now exiting." << endl;
				break;
			}
			*/
			//cout << msg << "\n";

			//close client?
			//SDLNet_TCP_Close(client);

		//}
//	}

	SDLNet_TCP_Close(server);

	SDLNet_Quit();
	SDL_Quit();
	return 0;
};