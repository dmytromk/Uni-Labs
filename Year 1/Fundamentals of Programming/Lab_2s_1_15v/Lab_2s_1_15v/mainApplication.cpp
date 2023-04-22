#include "datacontrol.h"

#include <fstream>
#include <iostream>

//by default, 

int main()
{
	char USER_DATA[20] = "user.dat"; // you can change default name of the binary file with user data here
	char CITY_DATA[20] = "city.dat"; // you can change default name of the binary file with city data here

	control::welcome_menu(USER_DATA, CITY_DATA);

	//control::printAllUsers(USER_DATA);
	//control::printAllCities(CITY_DATA);

}

