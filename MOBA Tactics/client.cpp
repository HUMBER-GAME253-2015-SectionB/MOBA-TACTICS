#include <SDL_net.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#define MAXMSGLEN 1024

int main(int argc, char**argv)
{

	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	IPaddress ip;
	char msg[MAXMSGLEN];


	// check for connection
	SDLNet_ResolveHost(&ip, "127.0.0.1", 1234);

	//create the socket for client
	TCPsocket server = SDLNet_TCP_Open(&ip);


	
	//Thread for receiving information from server
	do
	{
		cout << "I am doing" << endl;
		int recievedByteCount = SDLNet_TCP_Recv(server, msg, strlen(msg) + 1);
		if (recievedByteCount <= 0)
		{
			
			cout << "I am here" << endl;

		}
		else
		{
			cout << "I am else" << endl;
		}

	} while (server);
	//SDLNet_TCP_Send(client, "Client has exited loop.", MAXMSGLEN);

	//close the socket
	SDLNet_TCP_Close(server);

	SDLNet_Quit();
	SDL_Quit();
	return 0;
};