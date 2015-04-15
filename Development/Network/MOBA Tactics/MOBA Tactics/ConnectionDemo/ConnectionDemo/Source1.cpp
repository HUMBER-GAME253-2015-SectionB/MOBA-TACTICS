#include "Server.h"
#include "Thread.h"
#include <thread>

Server *s;
string message;
bool shutDown;
int activeClient;

void thread_1()
{
	do{
		s->connectionThread();
		
	} while (shutDown != true);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	try
	{
		// Not try to instantiate the server socket
		// Parameters: port number, buffer size (i.e. max message size), max sockets
		s = new Server(1234, 512, 4); //Port, BufferSize, ClientNumber 
	}
	catch (SocketException e)
	{
		std::cerr << "Something went wrong creating a SocketServer object." << std::endl;
		std::cerr << "Error is: " << e.what() << std::endl;
		std::cerr << "Terminating application." << std::endl;
		getchar();
		exit(-1);
	}
	
	message = "I CAUSE ERRORS";
	shutDown = false;
	thread t1(thread_1);
	//thread
	
	do{
		activeClient = -1;
		do{
			activeClient = s->checkForActivity(); // ActiveClient is the client number
			//cout << "We have checked for activity" << endl;
			if (activeClient != -1)
			{
				
				message = s->storeActivity();
				message = "Test";
				//*Server code that deals with activity stuff
				cout << message << endl;

				string dataToSend = message;

				s->sendData(dataToSend); // will send data from above to all clients.
			}

		} while (activeClient != -1);

	} while (shutDown != true);
	
	getchar();

	SDLNet_Quit();
	SDL_Quit();
	return 0;
}

