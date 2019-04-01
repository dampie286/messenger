#include "checking.h"
#include<iostream>
#include<sstream>
bool checking::checkingdigit(const std::string &adress)
{

	if (adress == "Exit") //sprawdzenie czy u¿ytkownik, czasem nie chce wyjœæ
	{
		std::cout << "Jesli chcesz zamknac program nacisnij CTRL+C!\n";
		return false;
	}

	size_t prev_pos = 0;
	
	size_t pos = 0;
	
	std::string tmp;
	if (adress.size() > 15)		//sprawdzenie czy czasem u¿ytkownik nie wpisa³ za du¿o znaków
	{
		std::cout << "Za duzo cyfr lub wpisales litery!(np. poprawne: 192.168.0.1)\n";
		return false;
	}
	while ((pos = adress.find_first_of(".,-/", pos)) != std::string::npos)		//szukanie pozycji znaku
	{
		if (adress[pos] == '.')		//sprawdzenie czy znakiem na pewno jest kropka
			tmp = tmp + ' ' + adress.substr(prev_pos, pos - prev_pos);
		else {
			std::cout << "Znak oddzielajacy kolejne sekcje musi byc kropka! (np. 192.168.0.1)\n";	
			return false;
		}
		prev_pos = ++pos;
	}
	tmp = tmp + ' ' + adress.substr(prev_pos);		//ostatnia "sekcja" po kropce

	std::istringstream ss(tmp);
	
	int tmp1, tmp2, tmp3, tmp4;
	
	int max;
	
	std::string tp1, tp2, tp3, tp4;
	ss >> tp1 >> tp2 >> tp3 >> tp4;		//wpisanie z strumienia wejœciowego do stringów

	if (tp1.size() == tp2.size() && tp1.size() == tp3.size() && tp1.size() == tp4.size() && tp2.size() == tp3.size() && tp2.size() == tp4.size() && tp3.size() == tp4.size()) //sprawdzani, która zmienna jest najwiêksza
		max = tp1.size();
	else if (tp1.size() >= tp2.size() && tp1.size() >= tp3.size() && tp1.size() >= tp4.size())
		max = tp1.size();
	else if (tp2.size() >= tp1.size() && tp2.size() >= tp3.size() && tp2.size() >= tp4.size())
		max = tp2.size();
	else if (tp3.size() >= tp1.size() && tp3.size() >= tp2.size() && tp3.size() >= tp4.size())
		max = tp3.size();
	else
		max = tp4.size();
	if (max > 3) {
		std::cout << "Maksymalnie moga byc 3 cyfry w sekcji! (np.192.168.0.1)\n";
		return false;
	}
	//sprawdzanie, czy zmienne przechowuj¹ litery
	for (int i = 0; i < max; i++) {
	if (i<tp1.size())
	{
		if (tp1[i] < 47 || tp1[i]>58)
		{
			std::cout << "Musza byc podane cyfry, a nie litery!\n";
			return false;
		}
	}
		else if( i<tp2.size())
		{
			if (tp2[i] < 47 || tp2[i]>58)
			{
				std::cout << "Musza byc podane cyfry, a nie litery!\n";
				return false;
			}
		}
		else if (i<tp2.size())
		{
			if (tp3[i] < 47 || tp3[i]>58)
			{
				std::cout << "Musza byc podane cyfry, a nie litery!\n";
				return false;
			}
		}
		else if (i<tp4.size())
		{
			if (tp4[i] < 47 || tp4[i]>58)
			{
				std::cout << "Musza byc podane cyfry, a nie litery!\n";
				return false;
			}
		}
	}

	//konwersacja z stringa na int
	tmp1 = atoi(tp1.c_str());
	tmp2 = atoi(tp2.c_str());
	tmp3 = atoi(tp3.c_str());
	tmp4 = atoi(tp4.c_str());

	//sprawdzanie, czy cyfry znajduj¹ siê w danych przedzia³ach
	if (tmp1 < 1 && tmp1>255)	
	{
		std::cout << "Pierwsza 'sekcja' musi byc w przedziale od 1 do 255! (jesli jest to lokalny serwer polecany jest poczatek 127...)\n";
		return false;
	}
	else if (tmp2 < 0 && tmp2>255 && tmp3 < 0 && tmp3>255 && tmp4 < 0 && tmp4>255)
	{
		std::cout << "Druga,trzecia i czwarta  'sekcja' musi byc w przedziale od 0 do 255! (np. 192.168.0.1)\n";
		return false;
	}
	return true;

}
void checking::Help(const std::string &help)
{

	if (help == "-h") //sprawdzenie, czy u¿ytkownik chce siê dowiedzieæ informacji o serwerze
	{
		std::cout << "Nazwa programu: Serwer \n\n";
		std::cout << "Tworca Damian Pietryja , 15.01.2019 \n\n";
		std::cout << "Program sluzy do polaczenia miedzy uzytkownikami komunikatora sieciowego \n";
		std::cout << "Wylaczenie programu jest spowodowane nacisniecie 'CTRL+C' przed inicjalizacja serwera lub napisanie tekstu 'Exit' po inicjalizacji serwera \n\n\n";
		std::cout << "Aby otworzyc program wpisz w konsole  : Serwer.exe -i\nZadziala\n";
		std::cout << " Przykladowe wpisanie adresu IP: 127.0.0.1 \n Przykladowe wpisanie portu: 54000\n";
	}
	else //jeœli zosta³ wpisany z³y parametr zostanie wyœwietlony taki komunikat
	{
		std::cout << "Nazwa programu: Serwer \n\n";
		std::cout << "Tworca Damian Pietryja , 15.01.2019 \n\n";
		std::cout << "Program sluzy do polaczenia miedzy uzytkownikami komunikatora sieciowego \n";
		std::cout << "Wylaczenie programu jest spowodowane nacisniecie 'CTRL+C' przed inicjalizacja serwera lub napisanie tekstu 'Exit' po inicjalizacji serwera \n\n\n";
		std::cout << "Nie urochomiles programu. Zapewne nie uzyles odpowiedniego parametru. \nJak wpisujesz w konsole wpisz :  Serwer.exe -i \nZadziala";
	}
}

bool checking::CheckParams( int argc, char*argv[])
{
	
	std::string param_in = "-i";		

	std::string param_h = "-h";				
	
	bool user_used_h_param = argv[argc - 1] == param_h;

	bool user_used_i_param = argv[argc - 1] == param_in; //Flaga, która daje "true", jeœli u¿ytkownik wpisa³ parametr -i

	if (user_used_i_param) //jeœli u¿ytkownik wpisa³ parametr -i, program mo¿e dalej dzia³aæ
		return true;
	else if (user_used_h_param) //u¿ytkownik wywo³uje tzw. "helpa"
	{
		Help(param_h);
		return false;
	}
	else //jeœli zosta³ wpisany z³y parametr
	{
		Help(" ");
		return false;
	}
	
}