#pragma once
#include<string>
/**
	Klasa odpowiedzialna za sprawdzenie parametr�w wprowadzonych przez u�ytkownika,
	w celu zabezpieczenia przed b��dami podczas procesu inicjalizacji serwera.
*/
class checking {
public:
	/**
		Metoda sprawdzaj�ca, czy u�ytkownik dobrze wpisa� adres IP.
		@param adress    Adres IP wpisany przez u�ytkownika
		@return  Flaga, czy zosta� dobrze wpisany adres.
	*/
	bool checkingdigit(const std::string &adress);	
	/**
		Metoda informuj�ca u�ytkownika o autorze programu, jak dzia�a program oraz jak trzeba poprawnie wpisa� parametry
		@param help Parametr help.
	*/
	void Help(const std::string &help);
	/**
		Metoda sprawdzj�ca, czy u�ytkownik wpisa� dobre parametry, aby uruchomi� program.
		@param argc Rozmiar tablicy argv.
		@param arg Parametr wpisany przez u�ytkownika.
		@return Flaga, czy zosta�y dobrze wpisane parametry przy starcie.
	*/
	bool CheckParams(int argc, char*argv[]);
};