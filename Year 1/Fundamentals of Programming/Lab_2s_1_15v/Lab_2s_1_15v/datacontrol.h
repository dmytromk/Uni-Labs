#pragma once

namespace control
{
	enum Menu {
		ADD = 1, 
		DIVIDE = 2, 
		INSERT = 3
	};

	struct User
	{
		int id;
		char type[20];
		char login[20];
		char password[20];
		bool showflag;
		void printInfo();
		User(char* const type, char* const name, char* const password, 
			int id = 1, bool showflag = true);
	};

	struct City
	{
		char name[20];
		char type[20];
		long int population;
		long int coordinates;
		int idx;
		bool showflag;
		void printInfo();
		City(char* const name, char* const type, long int population, 
			long int coordinates, int idx = 1, bool showflag = true);
	};

	bool checkLoginInFile(control::User user, char* const USER_DATA, int& idx);
	bool authentication(control::User user, char* const USER_DATA);
	bool createAccount(control::User& user, char* const USER_DATA);
	bool city_exists(control::City city, char* const CITY_DATA, int& idx);


	void printCityType(char* const type, char* const CITY_DATA);
	void printCityPop(long int population, char* const CITY_DATA);
	void printCityCoord(long int population, char* const CITY_DATA);

#pragma region ***Admin***
	void addCity(control::City& city, char* const CITY_DATA);
	void delCityIdx(int idx, char* const CITY_DATA);
	void delCityName(char* const name, char* const CITY_DATA);
#pragma endregion

	void welcome_menu(char* const USER_DATA, char* const CITY_DATA);
	void main_menu(char* const USER_DATA, char* const CITY_DATA);
	void admin_menu(char* const USER_DATA, char* const CITY_DATA);

	void printAllUsers(char* const USER_DATA);
	void printAllCities(char* const CITY_DATA);
}