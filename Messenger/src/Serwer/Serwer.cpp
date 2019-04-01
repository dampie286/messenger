#include"TcpListener.h"
#include<sstream>
#include<vld.h>
#include"checking.h"
int main(int argc, char * argv[])
{
	
	checking spr; //Zmienna klasy checking do sprawdzania parametrów
	std::string AD;
	bool ch = false; //Flaga do zwracanej wartoœci z klasy checking
	if (spr.CheckParams(argc, argv) == true)
	{
		std::cout << "Witam Cie w serwerze. Zaraz musisz podaæ parametry serwera!\n";
	}
	else {
		system("PAUSE");
		return 0;
	}
	while (!ch)
	{
		AD.clear();
		std::cout << "Podaj numer adresu IP ,na ktorym ma zostac utworzony serwer (przemysl to): ";
		std::getline(std::cin, AD);
		ch = spr.checkingdigit(AD);	//sprawdzanie czy jest tam liczba i czy dobrze, jest zapisny adres IP serwera 
	}
	
	std::cout << "Podaj numer portu ,na ktorym ma zostac utworzony serwer (przemysl to): ";
	int porcik; //Zmienna przechowuj¹ca wpisany port
	std::cin.clear();
	while (!(std::cin >> porcik)) //dopóki strumieñ jest w stanie b³êdu -> dopóki podawane s¹ b³êdne dane // nie dziala
	{
		std::cout << "Podaj liczbe, nie litery!" << std::endl;
		//ew komunikat b³êdu
		std::cin.clear(); //kasowanie flagi b³êdu strumienia
		std::cin.ignore(INT_MAX, '\n');
		porcik = 0;
		
	}
	TcpListener serw(AD, porcik);		//tworzenie serwera
	if (serw.Initialize()) //spprawdzanie czy biblioteka WinSocket zadziala
	{
		serw.Run(); //uruchamianie serwera
	}

	return 0;
	
	
}


