
#include "Decoder.h"

int main()
{
	std::string test = "Hello/I/am/here/and/so/are/you./";

	Decoder::Decode(5, test);

	system("pause");
	return 0;
}