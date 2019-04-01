#pragma once
#include<string>
/**
	Klasa odpowiedzialna za sprawdzenie parametrów wprowadzonych przez u¿ytkownika,
	w celu zabezpieczenia przed b³êdami podczas procesu inicjalizacji serwera.
*/
class checking {
public:
	/**
		Metoda sprawdzaj¹ca, czy u¿ytkownik dobrze wpisa³ adres IP.
		@param adress    Adres IP wpisany przez u¿ytkownika
		@return  Flaga, czy zosta³ dobrze wpisany adres.
	*/
	bool checkingdigit(const std::string &adress);	
	/**
		Metoda informuj¹ca u¿ytkownika o autorze programu, jak dzia³a program oraz jak trzeba poprawnie wpisaæ parametry
		@param help Parametr help.
	*/
	void Help(const std::string &help);
	/**
		Metoda sprawdzj¹ca, czy u¿ytkownik wpisa³ dobre parametry, aby uruchomiæ program.
		@param argc Rozmiar tablicy argv.
		@param arg Parametr wpisany przez u¿ytkownika.
		@return Flaga, czy zosta³y dobrze wpisane parametry przy starcie.
	*/
	bool CheckParams(int argc, char*argv[]);
};