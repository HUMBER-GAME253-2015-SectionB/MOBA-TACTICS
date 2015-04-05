#include "Client.h"
//#include "Thread.h"
//#include <thread>

int main(int argc, char *argv[])
{

	Client *c;
	string receivedMessage;
	string messageToSend;

	c = new Client("127.0.0.1", 1234, 512); // IPAddres, Port, Buffersize.

	//Whatever log in stuff you need to do
	//When the connection needs to be made Call this method.
	
	c->connectToServer();

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


		c->sendData(messageToSend);

	} while (c->getShutdownStatus() == false);

	getchar();
	return 0;
}

