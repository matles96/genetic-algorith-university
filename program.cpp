// HEUEV0.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "UserInterface.h"
using namespace std;

int main()
{
	srand(static_cast <unsigned> (time(0)));
	UserInterface c;
	c.Run();
	return 0;
}
