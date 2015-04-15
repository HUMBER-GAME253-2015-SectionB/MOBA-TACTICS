#include "Client.h"
#include "SDL_net.h"
//#include "Thread.h"
//#include <thread>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	Client *c;
	string receivedMessage;
	string messageToSend;
	try
	{
		c = new Client("127.0.0.1", 1234, 512); // IPAddres, Port, Buffersize.
	}
	catch (SocketException e)
	{
		std::cerr << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cerr << "Error is: " << e.what() << std::endl;
		std::cerr << "Terminating application." << std::endl;
		exit(-1);
	}
	

	//Whatever log in stuff you need to do
	//When the connection needs to be made Call this method.
	try
	{
		c->connectToServer();
	}
	catch (SocketException e)
	{
		std::cerr << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cerr << "Error is: " << e.what() << std::endl;
		std::cerr << "Terminating application." << std::endl;
		getchar();
		exit(-1);
	}
	


	do
	{
		receivedMessage = c->checkForIncomingMessages();

		// You dont need this because you may not need to display 
		// the message to the console, 
		// you need to code that display stuff yourself.
		if (receivedMessage != "")
		{

			c->displayMessage(receivedMessage);

		}

		getchar();
		c->sendData(messageToSend);

	} while (c->getShutdownStatus() == false);

	getchar();
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}

