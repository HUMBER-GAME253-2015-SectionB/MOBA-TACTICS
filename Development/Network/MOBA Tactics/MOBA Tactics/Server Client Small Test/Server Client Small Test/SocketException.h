#include <string>

// Custome simple exception class, this is needed to compile successfully
// In windows there is a msvcrt library, which contains the standard exception
// class - instead we created this
class SocketException
{
private:
	std::string msg;

public:
	SocketException(const std::string theErrorMsg)
	{
		msg = theErrorMsg;
	}

	std::string what()
	{
		return msg;
	}
};