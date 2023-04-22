#include "polynomlist.h";

int main()
{
	polmult::PolList pol1, pol2, pol3;
	char NAME1[] = "pol1.txt";
	char NAME2[] = "pol2.txt";

	pol1 = polmult::read(NAME1);
	pol2 = polmult::read(NAME2);

	pol3 = polmult::multiply(pol1, pol2);
	pol3.removeDup();
	pol3.printList();
}