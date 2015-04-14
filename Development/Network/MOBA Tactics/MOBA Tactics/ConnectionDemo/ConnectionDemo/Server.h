#include <iostream>
#include <string>
#include <sstream>
#include "SDL_net.h"

#include "SocketException.h"

using namespace std;

class Server
{
	private:
		bool debug;

		unsigned int port; // The port number
		unsigned int bufferSize; // Size of message to be sent over
		unsigned int maxSockets; // Number of Sockets to create
		unsigned int maxClients; // Number of clients to connect 
	
		IPaddress serverIP;  // The IP of the socket server 
		TCPsocket serverSocket; // The Server socket.
		string dotQuadString;  // The IP address of the server as a dot-quad string i.e. "127.0.0.1"

		TCPsocket *clientSocket; // points to array 
		bool *socketIsFree; // points to array telling us if connected or not.
		char *buffer; // points to what the buffer recieves *Change to template?

		SDLNet_SocketSet socketSet; // Set of sockets

		unsigned int clientCount; // How many clients are connected

	public:
		// When server is created we take in a Port number, size of the buffer, and how many sockets we want to create.
		Server(unsigned int port, unsigned int bufferSize, unsigned int maxSockets); 

		~Server();
		// Will Loop to Connect Clients
		void connectionThread(); 

		// Checks for number of active clients or -1 if no clients with activity to process
		int checkForActivity(); 

		// Do something when client is detected, accepting a client to do the activity with.
		string storeActivity(unsigned int clientNumber);


		void sendData(string dataToSend);

};

// Template function to convert anything to a string
template<class T>
std::string toString(const T& t)
{
	std::ostringstream stream;
	stream << t;
	return stream.str();
}
