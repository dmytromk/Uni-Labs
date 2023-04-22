#include "datacontrol.h"

#include <fstream>
#include <string>
#include <iostream>

void control::User::printInfo()
{
	std::cout << this->type << " " << this->login << " " << this->password << " " << this->id << "\n\n";
}

control::User::User(char* const type, char* const login, char* const password, int, bool showflag)
{
	strcpy_s(this->type, type);
	strcpy_s(this->login, login);
	strcpy_s(this->password, password);
	this->id = id;
	this->showflag = showflag;
}

void control::City::printInfo()
{
	if (this->showflag == false) return;
	std::cout << this->name << "\n";
	std::cout << "Type: " << this->type << "\n";
	std::cout << "Population: " << this->population << "\n";
	std::cout << "Coordinates: " << this->coordinates << "\n";
	std::cout << "Index: " << this->idx << "\n\n";
}

control::City::City(char* const name, char* const type, long int population, long int coordinates, int idx, bool showflag)
{
	strcpy_s(this->name, name);
	strcpy_s(this->type, type);
	this->population = population;
	this->coordinates = coordinates;
	this->idx = idx;
	this->showflag = showflag;
}

bool control::checkLoginInFile(control::User user, char* const USER_DATA, int& idx)
{
	std::ifstream out(USER_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::User buffer(temp, temp, temp, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;
		//buffer.printInfo();
		if (!strcmp(buffer.login, user.login)) return false;
	}
	idx = 1 + buffer.id;
	out.close();
	return true;
}

bool control::authentication(control::User user, char* const USER_DATA)
{
	std::ifstream out(USER_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::User buffer(temp, temp, temp, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;
		if (!strcmp(buffer.login, user.login))
		{
			if (strcmp(buffer.password, user.password))
			{
				std::cout << "Incorrect password.\n";
				return false;
			}
			else if (strcmp(buffer.type, user.type))
			{
				std::cout << "This account doesn't have such status.\n";
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	std::cout << "Such account doesn't exist\n";
	out.close();
	return false;
}

bool control::createAccount(control::User& user, char* const USER_DATA)
{
	std::ofstream in(USER_DATA, std::ofstream::binary | std::ofstream::app);

	int idx = 0;

	if (checkLoginInFile(user, USER_DATA, idx))
	{
		user.id = idx;
		in.write((char*)&user, sizeof(user));
		std::cout << "The new user is succesfully added.\n\n";
		in.close();
		return true;
	}
	else std::cout << "Unfortunale, user with such login already exists. Try again? Or something else?\n\n";
	in.close();
	return false;
}

bool control::city_exists(control::City city, char* const CITY_DATA, int& idx)
{
	std::ifstream out(CITY_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;
		buffer.printInfo();
		if (!strcmp(buffer.name, city.name)) return true;
	}
	idx = 1 + buffer.idx;
	out.close();
	return false;
};

void control::printCityType(char* const type, char* const CITY_DATA)
{
	//print city with the type as in the argument
	std::ifstream out(CITY_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;	
		if (!strcmp(buffer.type, type)) buffer.printInfo();;
	}
	out.close();
	return;
};

void control::printCityPop(long int population, char* const CITY_DATA)
{
	//print city with more population then in the argument
	std::ifstream out(CITY_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;		
		if (buffer.population >= population) buffer.printInfo();
	}

	out.close();
	return;
};

void control::printCityCoord(long int coordinates, char* const CITY_DATA)
{
	//print city with the coordinates as in the argument
	std::ifstream out(CITY_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;
		if (buffer.coordinates == coordinates) buffer.printInfo();
	}
	out.close();
	return;
};

void control::addCity(control::City& city, char* const CITY_DATA)
{
	std::ofstream in(CITY_DATA, std::ofstream::binary | std::ofstream::app);

	int idx = 1;

	if (!city_exists(city, CITY_DATA, idx))
	{
		city.idx = idx;
		in.write((char*)&city, sizeof(city));
		std::cout << "The new city is succesfully added.\n\n";
		in.close();
		return;
	}
	else std::cout << "Unfortunale, city with such name already exists. Try again? Or something else?\n\n";
	in.close();
	return;
}

void control::delCityIdx(int idx, char* const CITY_DATA)
{
	std::fstream file;
	file.open(CITY_DATA, std::fstream::in | std::fstream::out | std::fstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!file.eof())
	{
		file.read((char*)&buffer, sizeof(buffer));
		if (!file.good()) break;
		//buffer.printInfo();
		if (buffer.idx == idx)
		{
			buffer.showflag = false;
			int size = static_cast<int>(sizeof(buffer));
			file.seekg(-size, std::ios::cur);
			file.write((char*)&buffer, sizeof(buffer));
			std::cout << "City succesfully deleted.";
			return;
		}
	}
	std::cout << "City with such index doesn't exist.";
	return;
}

void control::delCityName(char* const name, char* const CITY_DATA)
{
	std::fstream file;
	file.open(CITY_DATA, std::fstream::in | std::fstream::out | std::fstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!file.eof())
	{
		file.read((char*)&buffer, sizeof(buffer));
		if (!file.good()) break;
		//buffer.printInfo();
		if (!strcmp(buffer.name, name))
		{
			buffer.showflag = false;
			int size = static_cast<int>(sizeof(buffer));
			file.seekg(-size, std::ios::cur);
			file.write((char*)&buffer, sizeof(buffer));
			std::cout << "City succesfully deleted.";
			return;
		}
	}
	std::cout << "City with such name doesn't exist.";
	return;
}

void control::welcome_menu(char* const USER_DATA, char* const CITY_DATA)
{
	while (true)
	{
		std::cout <<
			"Enter 1 to create new account.\n" <<
			"Enter 2 to log in.\n" << 
			"Enter any other symbol to exit.\n";

		int ans;
		std::cin >> ans;

		if (ans == 1)
		{
			char type[20];
			char login[20];
			char password[20];
			std::cin >> type >> login >> password;

			control::User new_user(type, login, password);
			if (control::createAccount(new_user, USER_DATA))
			{
				if (!strcmp(type, "admin"))
				{				
					control::admin_menu(USER_DATA, CITY_DATA);
					return;
				}
				else 
				{
					control::main_menu(USER_DATA, CITY_DATA);
					return;
				}
			}
			else continue;
		}

		else if (ans == 2)
		{
			char type[20];
			char login[20];
			char password[20];
			std::cin >> type >> login >> password;

			control::User new_user(type, login, password);
			if (control::authentication(new_user, USER_DATA))
			{
				if (!strcmp(type, "admin"))
				{
					control::admin_menu(USER_DATA, CITY_DATA);
					return;
				}
				else
				{
					control::main_menu(USER_DATA, CITY_DATA);
					return;
				}
			}
			else continue;
		}

		else return;
	}
}

void control::main_menu(char* const USER_DATA, char* const CITY_DATA)
{
	while (true)
	{
		std::cout <<
			"Enter 1 to print city after the type.\n" <<
			"Enter 2 to print city with more population than you choose.\n" <<
			"Enter 3 to print city after the coordinates .\n" <<
			"Enter any other symbol to end the session.\n";

		int ans;
		std::cin >> ans;

		if (ans == 1)
		{
			std::cout << "Enter the type.\n";
			char type[20];
			std::cin >> type;
			control::printCityType(type, CITY_DATA);
			continue;
		}

		else if (ans == 2)
		{
			std::cout << "Enter the population.\n";
			int population;
			std::cin >> population;
			control::printCityPop(population, CITY_DATA);
			continue;
		}

		else if (ans == 3)
		{
			std::cout << "Enter the coordinates.\n";
			int coordinates;
			std::cin >> coordinates;
			control::printCityCoord(coordinates, CITY_DATA);
			continue;
		}

		else return;
	}
}

void control::admin_menu(char* const USER_DATA, char* const CITY_DATA)
{
	while (true)
	{
		std::cin.clear();
		std::cout <<
			"Enter 1 to enter the main menu.\n" <<
			"Enter 2 to add city.\n" <<
			"Enter 3 to delete city after the index.\n" <<
			"Enter 4 to delete city after the name.\n" <<
			"Enter 5 to print all cities.\n" <<
			"Enter any other symbol to end the session.\n";

		int ans = 0;
		std::cin >> ans;

		switch (ans)
		{
		case Menu::ADD:
			break;
		}

		if (ans == Menu::ADD)
		{
			main_menu(USER_DATA, CITY_DATA);
			return;
		}

		else if (ans == 2)
		{
			std::cout << "Enter the NAME, TYPE, POPULATION AND COORDINATES.\n";
			char name[20], type[20];
			int population, coordinates;
			std::cin >> name >> type >> population >> coordinates;
			control::City new_city(name, type, population, coordinates);
			control::addCity(new_city, CITY_DATA);
			continue;
		}

		else if (ans == 3)
		{
			std::cout << "Enter the INDEX.\n";
			int index;
			std::cin >> index;
			delCityIdx(index, CITY_DATA);
			continue;
		}

		else if (ans == 4)
		{
			std::cout << "Enter the NAME.\n";
			char name[20];
			std::cin >> name;
			delCityName(name, CITY_DATA);
			continue;
		}

		else if (ans == 5)
		{
			control::printAllCities(CITY_DATA);
			continue;
		}

		else return;
	}
}

void control::printAllUsers(char* const USER_DATA)
{
	//print city with the type as in the argument
	std::ifstream out(USER_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::User buffer(temp, temp, temp);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;	
		buffer.printInfo();
	}
	out.close();
	return;
}

void control::printAllCities(char* const CITY_DATA) 
{
	//print city with the type as in the argument
	std::ifstream out(CITY_DATA, std::ifstream::in | std::ifstream::binary);

	char temp[] = "";
	control::City buffer(temp, temp, 0, 0);

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		if (!out.good()) break;
		buffer.printInfo();
	}
	out.close();
	return;
}
