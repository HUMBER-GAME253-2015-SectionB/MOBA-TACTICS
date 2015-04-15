#include "Client.h"

// Static constants
const std::string  Client::SERVER_NOT_FULL			= "OK";			// Server's response when there are free spots a client can join
const std::string  Client::SERVER_FULL				= "FULL";		// Server's response when there are not free spots, so a client cannot join
const std::string  Client::SHUTDOWN_SIGNAL			= "/shutdown";	// What you type to shutdown server (a command)
const std::string  Client::QUIT_SIGNAL				= "/quit";		// What you type to shutdown the client (a command)
const unsigned int Client::CONNECTION_TIMEOUT_PERIOD= 10000;		// (10000ms) 10 second connection timeout
const unsigned int Client::SOCKET_SET_POLL_PERIOD	= 10;			// 10ms, so poll 100 times/second

// Client constructor
Client::Client(string theServerAddress, unsigned int theServerPort, unsigned int theBufferSize)
{
	debug			= true;
	shutdownClient	= false;

	// The host name of the server
	// This can be either a dot-quad like 127.0.0.1 or a hostname like "localhost"
	serverHostname = theServerAddress;

	serverPort = theServerPort; // The port on the server to connect to
	bufferSize = theBufferSize; // The maximum message size

	inputLength = 0;

	try
	{
		pBuffer = new char[bufferSize]; // Create the transmission buffer character array

		// Create a socket set big enough to hold the server socket and our own client
		socketSet = SDLNet_AllocSocketSet(2);

		// If we couldn't create the socket set then throw and exception
		if (socketSet == NULL)
		{
			string msg = "Failed to allocate the socket set in Client constructor: ";
			msg += SDLNet_GetError();

			SocketException e(msg);
			throw e;
		}
	}
	catch (SocketException e)
	{
		// Re-throw the ecveption to be dealt with appropriately elsewhere
		throw e;
	}

}

// Client destructor
Client::~Client()
{
	// Close our server and client sockets
	SDLNet_TCP_Close(serverSocket);
	SDLNet_TCP_Close(clientSocket);

	// Free our socket set
	SDLNet_FreeSocketSet(socketSet);

	// Release any properties on the heap
	delete pBuffer;
}

void Client::connectToServer()
{
	// Try to resolve the hostname to an IP address, it it's already an IP address then that's fine
	// If successful, this places the connection details in the serverIP object
	int hostResolved = SDLNet_ResolveHost(&serverIP, serverHostname.c_str(), serverPort);

	// If we couldn;t resolve the hostname then throw an error
	if (hostResolved == -1)
	{
		string msg = "Error: Failed to resolve the server hostname to an IP address.";

		SocketException e(msg);
		throw e;
	}
	else // otherwise if we successfully resolved the hostname...
	{
		// ...get our IP address in a dot-quad format by breaking up the 32-bit unsigned host address
		// and splitting it into an array of four 8-bit unsigned numbers...
		Uint8 * dotQuad = (Uint8*)&serverIP.host;

		dotQuadString += toString((unsigned short)dotQuad[0]);
		dotQuadString += ".";
		dotQuadString += toString((unsigned short)dotQuad[1]);
		dotQuadString += ".";
		dotQuadString += toString((unsigned short)dotQuad[2]);
		dotQuadString += ".";
		dotQuadString += toString((unsigned short)dotQuad[3]);

		// ...and then outputting them. Then read the last 16 bits of the serverIP object to get the port number
		if (debug)
		{
			cout << "We ****ing did it! Successfully resolved server to IP: " << dotQuadString;
			cout << ", will use port " << SDLNet_Read16(&serverIP.port) << endl;

			// Try to resolve the hostname from the IP addres, just for kicks
			const char *pHostname;
			if (!(pHostname = SDLNet_ResolveIP(&serverIP)))
			{
				cout << "What a srcub! Failed to resolve the server IP to hostname: " << SDLNet_GetError() << endl;
				cout << "Attempting to continue as we have a (technically) valid IP address..." << endl;
			}
			else
			{
				serverHostname = toString(pHostname);
				cout << "Successfully resolved IP to hostname: " << serverHostname << endl;
			}
		}
	}

	// Try to open a connection between the client and the server - quit out if we can't connect
	clientSocket = SDLNet_TCP_Open(&serverIP);
	if (!clientSocket)
	{
		string msg = "Error: Failing to open connection to server: ";
		msg += SDLNet_GetError();

		SocketException e(msg);
		throw e;
	}
	else // If we successfully opened a connection then check for the server response to our connection
	{
		if (debug)
		{
			cout << "Connection okay, about to read connection status from the server..." << endl;
		}

		// Add our socket to the socket set for polling
		SDLNet_TCP_AddSocket(socketSet, clientSocket);

		// Wait for up to five seconds for a response from the server
		// Note: If we don't check the socket set and WAIT for the response, we'll be checking before the
		// server can respond, and it'll look as if the server sent us nothing back!
		int activeSockets = SDLNet_CheckSockets(socketSet, Client::CONNECTION_TIMEOUT_PERIOD);

		if (debug)
		{
			cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl;
		}

		// Check if we got a response from the server
		int gotServerResponse = SDLNet_SocketReady(clientSocket);

		if (gotServerResponse != 0)
		{
			// Read the message on the client socket
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);

			if (debug)
			{
				cout << "Message from server: " << pBuffer << "(" << serverResponseByteCount << " bytes)" << endl;
			}

			// Get the contents of the buffer as a string
			string bufferContents = pBuffer;

			// If we got the SERVER_NOT_FULL response form the server then we can join!
			if (pBuffer == Client::SERVER_NOT_FULL)
			{
				if (debug)
				{
					cout << "Damn we found it! Joining server now..." << endl;
				}
			}
			else // Otherwise we must have got the SERVER_FULL response so we can't
			{
				string msg = "Error: Server is full... FAILURE";

				SocketException e(msg);
				throw e;
			}
		}
		else // If there's no activity on the client then we've failed to connect
		{
			string msg	 = "Error: No response from server: ";
			msg			+= serverHostname;
			msg			+= " at IP: ";
			msg			+= dotQuadString;
			msg			+= " on port ";
			msg += SDLNet_Read16(&serverIP.port);

			SocketException e(msg);
			throw e;
		}
	} // End of if we managed to open a conncetion to the server condition
}

// Function to check for any incoming messages
string Client::checkForIncomingMessages()
{
	// Define a string with a blank message (If not value, there will be errors)
	string receivedMessage = "";

	// Poll for messages for a specified time (default: 10ms)
	// Basically its checking if a message is being sent
	int activeSockets = SDLNet_CheckSockets(socketSet, Client::SOCKET_SET_POLL_PERIOD);

	// Debug output, used to check if the code is acting up
	if (debug)
	{
		cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl;
	}

	if (activeSockets != 0)
	{
		// Check if we got a message from the server
		int gotMessage = SDLNet_SocketReady(clientSocket);

		if (gotMessage != 0)
		{
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);
			
			if (debug)
			{
				cout << endl << "Got message: " << pBuffer << " (" << serverResponseByteCount << " bytes)" << endl;
			}

			if (serverResponseByteCount != 0)
			{
				receivedMessage = toString(pBuffer);

				// If we've received the shutdown signal set the flag appropriately
				if (receivedMessage == Client::SHUTDOWN_SIGNAL)
				{
					if (debug)
					{
						cout << "Setting shutdownClient is true" << endl;
					}
					shutdownClient = true;
				}
			}
			else // If we've received a 0 byte message from the server then we've lost the connection!
			{
				// ...generate a suitable error message...
				string msg = "Damn you lost the connection, go get better wifi! (Connection lost to the server)";

				// ...and then throw it as an exception!
				SocketException e(msg);
				throw e;				
			} 
		} // End of if (gotMessage != 0)
	} // End of if (activeSockets != 0)	

	// Return the message, to see if its actually a message, or whether it's a blank
	return receivedMessage;
}

// Function to display a received message and then blank the message
// Don't need this, unless you want to use console.!~~
void Client::displayMessage(string &receivedMessage)
{
	// Display the message and then ...
	cout << endl << "Received: " << receivedMessage << endl;

	// Blank it! Because we pass a reference to a string into this function
	// it's the actual receivedMessage that's blanked and not just a copy
	receivedMessage = "";
}

// Function is not being used right now
void Client::sendData(string dataToSend)
{

	strcpy_s(pBuffer, sizeof(dataToSend) ,dataToSend.c_str());

	SDLNet_TCP_Send(clientSocket, pBuffer, bufferSize);
	
}

// Fuction to display the prompt + any user unput that hasn't been sent yet
// Don't need this, unless you want to use console.!~~
void Client::displayPrompt()
{
	cout << "Write something please >>> " << getCurrentUserInputContents();
	fflush(stdout);
}

// Function to get user input in a non-blocking manner
void Client::getUserInput()
{
	// If we've detected that the user has pressed a key...
	int status = _kbhit();

	cout << "status is: " << status << endl;

	if (status != 0)
	{
		cout << "key was pressed: " << status << endl;

		// Read what key was pressed
		char theChar = _getch();

		// Output the character to stdout
		cout << theChar;

		// Flush the character to the screen
		fflush(stdout);

		// If the key pressed wasn't returned then add the character to our message string
		if ((int)theChar != 13)
		{
			cout << "Got the character: " << theChar << " (which is number: " << int(theChar) << ")" << endl;

			// Add the character to our input string
			userInput += theChar;
		}
		else // Otherwise (if the user pressed enter) then send the message
		{
			if (debug)
			{
				cout << "User pressed ENTER - wil attempt to send your message!" << endl;
			}

			//Copy our user's string into our char array called "buffer"
			strcpy_s(pBuffer, sizeof(userInput), userInput.c_str());

			// Calculate the length of our input and then add 1 (for the terminating character) to get the total number of characters we need to send
			inputLength = strlen(pBuffer) + 1;

			// If we've got normal input then..
			if (userInput != Client::QUIT_SIGNAL)
			{
				// ...attempt to send the message to the server
				if (SDLNet_TCP_Send(clientSocket, (void *)pBuffer, inputLength) < inputLength)
				{
					string msg	= "Error: Failed to send message: ";
					msg += SDLNet_GetError();

					SocketException e(msg);
					throw e;
				}
				else
				{
					if (debug)
					{
						cout << "Message sent successfully." << endl;
					}

					// Reset for the next message
					cout << endl;
					cout << "Type something scrub >>> ";
					fflush(stdout);
					userInput = "";
				}
			}
			else // We've been asked to quit, so set the exit flag appropriately
			{
				shutdownClient = true;
			}
		} // End of message sending section
	} // End of if the user pressed a key test
}

// Function to return the contents of any user input (before being sent)
// Used to keep what we've typed so far displayed at the prompt when receiving incoming messages
string Client::getCurrentUserInputContents()
{
	return userInput;
}

// Function to return the shutdownStatus, used by our main loop
bool Client::getShutdownStatus()
{
	return shutdownClient;
}