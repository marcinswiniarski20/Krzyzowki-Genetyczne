//  2016-12-12 Projekt 1 Œwiniarski Marcin AIR3 165631 Dev-C++ 5.11 TDM-GCC 4.9.2 64-bit

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

const int liczba_wszystkich_cech = 10;	//liczba wszystkich cech dominujacych/recesywnych
const int ile_cech = 3;					// liczba badanych cech minus daltonizm

//struktura osoby, ktora posiada 4 wyrozniajace ja cechy
struct osoba
{
	string kolor_oczu;
	string kolor_wlosow;
	string reka_dominujaca;
	string daltonizm;
};

void info();
void rys_menu();
void wydobywanie_cech(string, osoba&, osoba&);
void dom_czy_rec(char[], char[], osoba, osoba, string[], string[]);
void tabela(char*, char*);
void legenda(char*, char*, osoba, osoba, string);
void wydobywanie_cech_dziecka(string, osoba&);
bool test(osoba, osoba, osoba, string[], string[], string);
bool jaka_plec(string, osoba&);
void czyszczenie_zawartosci(osoba&, osoba&);

int main()
{
	//bazy danyh cech
	string cechy_dominujace[liczba_wszystkich_cech] = {"piwne", "zielone", "zlote", "duze", "krecone", "brazowe", "ciemne", "czarne", "praworecznosc", "brak daltonizmu"};
	string cechy_recesywne[liczba_wszystkich_cech] = {"niebieskie", "szare", "male", "proste", "czerwone", "rude", "blond", "jasne", "leworecznosc", "daltonizm"};
	string lancuch1, lancuch2, lancuch3;	//wprowadzane opisy sematyczne
	osoba mezczyzna, kobieta, dziecko;	//obiekty struktury osoba

	int wybor;
	while(1)
	{
		rys_menu();	//funkcja wyswietlajaca menu
		cout<<"Wybierz: ";
		cin >> wybor;
		switch(wybor)
		{
			case 1:
			{
				system("cls");
				info();	//informacje o projekcie
				break;
			}
			case 2:
			{
				system("cls");
				
				char cechy_meskie[4] = {' ', ' ', ' ', ' '};	//tablica trzech wybranych cech meskich
				char cechy_kobiece[4] = {' ', ' ', ' ', ' '};	//tablica trzech wybranych cech kobiecych

				cout << "Dostepne cechy: kolor oczu, wlosy(kolor/rodzaj), recznosc, daltonizm" << endl<<endl;
				cout << "Przyklad: "<< endl;
				cout << "mezczyzna: oczy niebieskie, wlosy blond, leworecznosc, daltonizm" << endl;
				cout << "kobieta: oczy piwne, wlosy brazowe, praworecznosc, brak daltonizmu" << endl<<endl;
				cout << "Podaj cechy badanych rodzicow: "<<endl;
				cin.clear();	//czyszczenie zawartosci strumienia wyjsciowego - czyszczenie flagi bledu
        		cin.ignore(256, '\n');	//pominiecie 256 znakow znajdujacych sie w buforze lub do napotkania znaku przejscia do nowej linii

				getline(cin, lancuch1);	//wczytanie danych z linii
				getline(cin, lancuch2);	//wczytanie danych z linii

				wydobywanie_cech(lancuch1, mezczyzna, kobieta);	//wydobywanie cech z wczytanego lancucha1
				wydobywanie_cech(lancuch2, mezczyzna, kobieta);	//wydobywanie cech z wczytanego lancucha2
				dom_czy_rec(cechy_meskie, cechy_kobiece, kobieta, mezczyzna, cechy_dominujace, cechy_recesywne); //kwalifikacja cech do dominujacych i recesywnych								
				tabela(cechy_meskie, cechy_kobiece);	//rysowanie tabeli
				legenda(cechy_meskie, cechy_kobiece, mezczyzna, kobieta, lancuch1); // opis skrotow w tablicy
				break;
			}
			case 3:
			{
				system("cls");
				
				cout << "Dostepne cechy: kolor oczu, wlosy(kolor/rodzaj), recznosc, daltonizm" <<endl<<endl;
				cout << "Przyklad: "<<endl;
				cout << "mezczyzna: oczy niebieskie, wlosy blond, leworecznosc, daltonizm" <<endl;
				cout << "kobieta: oczy piwne, wlosy brazowe, praworecznosc, brak daltonizmu" <<endl<<endl;
				cout << "Podaj cechy badanych rodzicow: "<<endl;
				cin.clear();	//czyszczenie zawartosci strumienia wyjsciowego - czyszczenie flagi bledu
        		cin.ignore(256, '\n');	//pominiecie 256 znakow znajdujacych sie w buforze lub do napotkania znaku przejscia do nowej linii
				getline(cin, lancuch1);	
				getline(cin, lancuch2);	
				wydobywanie_cech(lancuch1, mezczyzna, kobieta);	//wydobywanie cech z wczytanego lancucha1
				wydobywanie_cech(lancuch2, mezczyzna, kobieta);	//wydobywanie cech z wczytanego lancucha2
				
				cout<<endl<<"Podaj cechy dziecka (prosze uwzglednic plec chlopiec/dziewczynka): "<<endl;
				getline(cin, lancuch3);
				wydobywanie_cech_dziecka(lancuch3, dziecko);
				
				if(test(mezczyzna, kobieta, dziecko, cechy_dominujace, cechy_recesywne, lancuch3)) // funkcja sprawdzajaca zgodnosc cech dziecka z cechami rodzicow
					cout<<"Test na ojcostwo wykazal wynik pozytywny.";
				else
					cout<<"Test na ojcostwo wykazal wynik negatywny.";
				break;
			}
			case 4:
			{
				exit(0);
				break;
			}
			default:
				cout << "Nie ma takiej opcji w menu!" << endl;
		}
		getchar();getchar();
		system("cls");
		czyszczenie_zawartosci(mezczyzna, kobieta);
	
	}

	return 0;
}
//funkcja wypisujaca menu
void rys_menu()
{
	cout<<"|";
	for(int i=0; i<40; i++)
		cout<<"-";
	cout<<"|"<<endl;
	
	for(int i=0; i<12; i++) cout<<" ";
	cout<<"MENU GLOWNE PROGRAMU"<<endl;
	
	cout<<"|";
	for(int i=0; i<40; i++)
		cout<<"-";
	cout<<"|"<<endl;
	
	for(int i=0; i<10; i++) cout<<" ";	
	cout<<"1. Instrukcja o projekcie"<<endl;
	
	cout<<"|";
	for(int i=0; i<40; i++)
		cout<<"-";		
	cout<<"|"<<endl;
	
	for(int i=0; i<10; i++) cout<<" ";		
	cout<<"2. Kalkulacja cech potomstwa"<<endl;
	
	cout<<"|";
	for(int i=0; i<40; i++)
		cout<<"-";
	cout<<"|"<<endl;
	
	for(int i=0; i<10; i++) cout<<" ";		
	cout<<"3. Test na ojcostwo"<<endl;

	cout<<"|";
	for(int i=0; i<40; i++)
		cout<<"-";
	cout<<"|"<<endl;
	
	for(int i=0; i<10; i++) cout<<" ";		
	cout<<"4. Zamknij program";
	
	cout<<endl<<"|";
	for(int i=0; i<40; i++)
		cout<<"-";
	cout<<"|"<<endl;
}

//funkcja odpowiedzialna za wyodrebnianie cech z lancuchow znakow podawanych z konsoli
void wydobywanie_cech(string linia, osoba& mezczyzna, osoba& kobieta)
{
	bool kto = false;	// zmienna sprawdzajaca czy zostal podany mezczyzna czy kobieta - domyslnie mezczyzna
	size_t found1, found2, found3, found4, found5;	//indeksy znalezionych fragmentow tekstu
	size_t dlugosc;
	string temp1, temp2;	// zmienne tymczasowe

	found1 = linia.find("mezczyzna");	// szuka wyrazu mezczyzna w podanej linii

	if(found1 == string::npos)			
	{
		found1 = linia.find("kobieta");	//jesli nie znaleziono mezczyzny to znaczy, ze mamy do czynienia z kobieta
		kto = true;
	}
	
	found1 = linia.find(" ");
	linia = linia.substr(found1); // przypisuje do zmiennej linia ciag znakow od found1 do konca pobranej linii - pozbywamy sie plci w linii

	//wyodrebnianie cech z linii ; dziala wedlug schematu najpierw slowo oczy potem cecha, slowo wlosy potem cecha
	while(1)
	{
		found5 = linia.find(",");	//ustawia found5 na przecinek

		if(found5 == string::npos) 
		{
			found5 = linia.length(); //jesli nie znaleziono przecinka to ustaw found5 na ostatni znak linii
			temp1 = linia.substr(0, found5+1);
		}
		else
		{
			temp1 = linia.substr(0, found5); // jesli znaleziono to pobierz to co znajduje sie przed przecinkiem
			linia = linia.substr(found5+1);	// zmniejsz linie o temp1
		}
		
		//sprawdzamy jakie cechy znajduja sie w temp1
		found1 = temp1.find("oczy");
		found2 = temp1.find("wlosy");
		found3 = temp1.find("recznosc");
		found4 = temp1.find("daltonizm");

		if(found1 != string::npos)
		{
			dlugosc = found5 - found1 - 5; // jesli sa to oczy to ustaw dlugosc cechy 

			if(kto)	//przypisywanie podanych cech do odpowiednich obiektow struktur
				kobieta.kolor_oczu = temp1.substr(found1+5, dlugosc);	
			else
				mezczyzna.kolor_oczu = temp1.substr(found1+5, dlugosc);
		}
		else if(found2 != string::npos)
		{
			dlugosc = found5 - found2 - 6;	//jesli sa to wlosy to ustaw dlugosc cechy wlosy

			if(kto)	//przypisywanie podanych cech do odpowiednich obiektow struktur
				kobieta.kolor_wlosow = temp1.substr(found2+6, dlugosc);
			else
				mezczyzna.kolor_wlosow = temp1.substr(found2+6, dlugosc);
		}
		else if(found3 != string::npos)
		{
			if(kto)	//przypisywanie podanych cech do odpowiednich obiektow struktur
				kobieta.reka_dominujaca = temp1.substr(1, found5); // pobiera caly wyraz leworecznosc/praworecznosc
			else
				mezczyzna.reka_dominujaca = temp1.substr(1, found5);
		}
		else if(found4 != string::npos)
		{
			if(kto)	//przypisywanie podanych cech do odpowiednich obiektow struktur
				kobieta.daltonizm = temp1.substr(1, found5); // pobiera cale wyrazenie daltonizm/brak daltonizmu
			else
				mezczyzna.daltonizm = temp1.substr(1, found5);
		}

		if(found5 == linia.length()) // zakoncz petle jesli przeszukalismy cala linie
			break;
	}
}
//funkcja sprawdzajaca plec podanego dziecka
bool jaka_plec(string linia, osoba& dziecko)
{
	size_t found1;
	found1 =linia.find("chlopiec");
	if(found1!= string::npos)
		return 1;
	else 
		return 0;
}
//funkcja analogiczna do wydobywanie_cech(), tylko wydobywajaca cechy dziecka
void wydobywanie_cech_dziecka(string linia, osoba& dziecko)
{
	size_t found1, found2, found3, found4, found5;	//indeksy znalezionych fragmentow tekstu
	size_t dlugosc;
	string temp1, temp2;

	found1 = linia.find("chlopiec");	//szuka wyrazu chlopiec w calej linii

	if(found1 == string::npos)
	{
		found1 = linia.find("dziewczynka");	//jesli nie znaleziono wyrazu chlopiec to mamy do czynienia z dziewczynka
	}
	
	found1 = linia.find(" ");
	linia = linia.substr(found1); // przypisuje do zmiennej linia ciag znakow od found1 do konca pobranej linii - pozbywamy sie plci w linii

	// petla wydobywajaca cechy dziecka z lancucha znakow
	while(1)
	{
		found5 = linia.find(",");

		if(found5 == string::npos)
		{
			found5 = linia.length(); // jesli nie znaleziono przecinka to ustaw found5 na koniec linii
			temp1 = linia.substr(0, found5+1);
		}
		else
		{
			temp1 = linia.substr(0, found5);
			linia = linia.substr(found5+1);
		}

		found1 = temp1.find("oczy");
		found2 = temp1.find("wlosy");
		found3 = temp1.find("recznosc");
		found4 = temp1.find("daltonizm");

		if(found1 != string::npos)
		{
			dlugosc = found5 - found1 - 5;

			dziecko.kolor_oczu = temp1.substr(found1+5, dlugosc);
		}
		else if(found2 != string::npos)
		{
			dlugosc = found5 - found2 - 6;	//dlugosc znalezionej cechy
			dziecko.kolor_wlosow = temp1.substr(found2+6, dlugosc);
		}
		else if(found3 != string::npos)
		{
			dziecko.reka_dominujaca = temp1.substr(1, found5);
		}
		else if(found4 != string::npos)
		{
			dziecko.daltonizm = temp1.substr(1, found5);
		}

		if(found5 == linia.length())
			break;
	}
}

//funkcja wyprowadzajaca na standardowe wyjscie opis mozliwych kombinacji w postaci tabelki
void tabela(char* cechy_meskie, char* cechy_kobiece)
{
	string tablica[ile_cech*2][ile_cech];	//tablica wszystkich kombinacji cech obiektow
	char tab[6] = {' ', ' ', ' ', ' ', ' ', '\0'};	//tablica zawierajaca pojedyncze kombinacje cech np. A-oczy piwne, b - wlosy blond

	for(int i=0; i<ile_cech; i++)	//laczenie cech obiektow, aby mogly zostac wyswietlone w tabelce
	{
		for(int j=0; j<ile_cech; j++)
		{
			tab[0] = cechy_meskie[i];
			tab[1] = cechy_kobiece[j];
			tab[2] = 'X';
			tab[3] = cechy_meskie[3];
			tab[4] = 'X';
			tab[5] = cechy_kobiece[3];

			tablica[i][j] = tab; // tablica dla potomstwa plci zenskiej
			tab[3] = cechy_kobiece[3];
			tab[4] = 'Y';
			tab[5] = ' ';
			
			tablica[i+ile_cech][j] = tab; // tablica dla potomswa plci meskiej
		}
	}
	
	//wyswietlanie kombinacji cech w postaci tabelki
	cout<<endl<<"!----------Krzyzowka genetyczna----------!"<<endl;
	cout << "------------------------------------------" << endl;
	cout << "|  M\\K  |   " << cechy_kobiece[0] << "X" << cechy_kobiece[3] << "    |   " << cechy_kobiece[1] << "X" << cechy_kobiece[3] << "    |   " << cechy_kobiece[2] << "X" << cechy_kobiece[3] << "    |" << endl;
	cout << "------------------------------------------" << endl;
	cout << "|  " << cechy_meskie[0] << "X" << cechy_meskie[3] << "  |  " << tablica[0][0] << "  |  " << tablica[0][1] << "  |  " << tablica[0][2] << "  |  " << endl;
	cout << "------------------------------------------" << endl;
	cout << "|  " << cechy_meskie[1] << "X" << cechy_meskie[3] << "  |  " << tablica[1][0] << "  |  " << tablica[1][1] << "  |  " << tablica[1][2] << "  |  " << endl;
	cout << "------------------------------------------" << endl;
	cout << "|  " << cechy_meskie[2] << "X" << cechy_meskie[3] << "  |  " << tablica[2][0] << "  |  " << tablica[2][1] << "  |  " << tablica[2][2] << "  |  " << endl;
	cout << "------------------------------------------" << endl;
	cout << "|  " << cechy_meskie[0] << "Y" << cechy_meskie[3] << "  |  " << tablica[3][0] << "  |  " << tablica[3][1] << "  |  " << tablica[3][2] << "  |  " << endl;
	cout << "------------------------------------------" << endl;
	cout << "|  " << cechy_meskie[1] << "Y" << cechy_meskie[3] << "  |  " << tablica[4][0] << "  |  " << tablica[4][1] << "  |  " << tablica[4][2] << "  |  " << endl;
	cout << "------------------------------------------" << endl;
	cout << "|  " << cechy_meskie[2] << "Y" << cechy_meskie[3] << "  |  " << tablica[5][0] << "  |  " << tablica[5][1] << "  |  " << tablica[5][2] << "  |  " << endl;
	cout << "------------------------------------------" << endl;

}
//funkcja opisujaca skroty w tabeli
void legenda(char* cechy_meskie, char* cechy_kobiece, osoba mezczyzna, osoba kobieta, string linia)
{
	size_t found1;
	found1 = linia.find("oczy");
	cout<<"XX - dziewczynka"<<endl;
	cout<<"XY - chlopiec"<<endl;
	if(found1 != string::npos)
	{	
		cout<<cechy_meskie[0]<<" - oczy "<<mezczyzna.kolor_oczu<<endl; //jesli znaleziono oczy to wypisz oczy
		cout<<cechy_kobiece[0]<<" - oczy "<<kobieta.kolor_oczu<<endl;
	}
	found1=linia.find("wlosy");
	if(found1 != string::npos)
	{
		cout<<cechy_meskie[1]<<" - wlosy "<<mezczyzna.kolor_wlosow<<endl; //jesli znaleziono wlosy to wypisz wlosy
		cout<<cechy_kobiece[1]<<" - wlosy "<<kobieta.kolor_wlosow<<endl;
	}
	found1=linia.find("recznosc");
	if(found1 != string::npos)
	{
		cout<<cechy_meskie[2]<<" - "<<mezczyzna.reka_dominujaca<<endl; //jesli znaleziono recnznosc to wypisz reke dominujaca
		cout<<cechy_kobiece[2]<<" - "<<kobieta.reka_dominujaca<<endl;
	}
	found1=linia.find("daltonizm");
	if(found1 != string::npos)
	{
		cout<<cechy_meskie[3]<<" - "<<mezczyzna.daltonizm<<endl; //jesli znaleziono daltonizm to wypisz daltonizm
		cout<<cechy_kobiece[3]<<" - "<<kobieta.daltonizm<<endl;
	}
}

//funkcja zawierajaca informacje na temat projektu
void info()
{
	cout << "!----Krzyzowki genetyczne----!" << endl;
	cout << "Program okresla mozliwe cechy potomstwa dziedziczone po rodzicach." << endl;
	cout << "Kalkulacja cech potomstwa odbywa sie za pomoca krzyzowki genetycznej." << endl;
	cout << "Program po podaniu cech obojga rodzicow wyprowadza wszystkie mozliwe kombinacje cech potomstwa." << endl;
	cout << "Cechami przewodnimi w projekcie beda: kolor oczu, wlosy(kolor/rodzaj), reka dominujaca, daltonizm" << endl;
	cout << "Cechy podawane sa sematycznie(np. mezczyzna: oczy niebieskie, wlosy ciemne, praworecznosc, brak daltonizmu)."<<endl;
	cout << "Dla programu nie ma znaczenia czy cechy podawane sa w kolejnosci czy tez nie."<<endl;
	cout << "Wymagane sa spacje oraz przecinki pomiedzy wypisywanymi cechami"<<endl<<" - jak w przykladzie."<<endl;
	cout << "Dodatkowo program jest w stanie przeprowadzic test na ojcostwo" << endl;
	cout << "- sprawdza zgodnosc cech rodzicow z cechami dziecka." << endl<<endl;
	cout << "Aby przejsc do Menu glownego wcisnij ENTER!" << endl;
}
// funkcja przeprowadzajaca test na ojcostwo
// wykaze wynik negatywny tylko wtedy gdy oboje rodzice maja cechy recesywne a dziecko dominujace
bool test(osoba mezczyzna, osoba kobieta, osoba dziecko, string cechy_dominujace[], string cechy_recesywne[], string lancuch3)
{
	bool buf=true;	
	for(int i=0; i<liczba_wszystkich_cech; i++)
	{				
		if(mezczyzna.kolor_oczu == cechy_recesywne[i])
			if(kobieta.kolor_oczu == cechy_recesywne[i])
				if(dziecko.kolor_oczu == cechy_dominujace[i])
					buf=false;

		if(mezczyzna.kolor_wlosow == cechy_recesywne[i])
			if(kobieta.kolor_wlosow == cechy_recesywne[i])
				if(dziecko.kolor_wlosow == cechy_dominujace[i])
					buf=false;

		if(mezczyzna.reka_dominujaca == cechy_recesywne[i])
			if(kobieta.reka_dominujaca == cechy_recesywne[i])
				if(dziecko.reka_dominujaca == cechy_dominujace[i])		
					buf=false;
		
		//daltonizm przekazywany jest za pomoca chromosomu X zatem musimy znac plec dziecka
		if(kobieta.daltonizm == cechy_recesywne[i])
			if(jaka_plec(lancuch3, dziecko)==0)
			{
				if(mezczyzna.daltonizm == cechy_dominujace[i])
					if(dziecko.daltonizm == cechy_recesywne[i])
						buf=false;
				if(mezczyzna.daltonizm == cechy_recesywne[i])
					if(dziecko.daltonizm == cechy_dominujace[i])
						buf=false;
			}			
		if(kobieta.daltonizm == cechy_dominujace[i])
			if(dziecko.daltonizm == cechy_recesywne[i])
			{
				buf=false;
				cout<<"Dziecko nie nalezy do matki!"<<endl;
			}
	}
	return buf;
}
//funkcja sprawdza, czy podana cecha jest cecha dominujaca, czy tez recesywna
void dom_czy_rec(char cechy_meskie[], char cechy_kobiece[], osoba kobieta, osoba mezczyzna, string cechy_dominujace[], string cechy_recesywne[])
{	
	for(int i=0; i<liczba_wszystkich_cech; i++)	//petla przeszukujaca bazê danych cech i przypisuje odpowiednie indeksy aby moznabylo zapisac je w tabeli
	{
		if(mezczyzna.kolor_oczu == cechy_dominujace[i])
			cechy_meskie[0] = 'A';
		else if(mezczyzna.kolor_oczu == cechy_recesywne[i])
			cechy_meskie[0] = 'a';

		if(mezczyzna.kolor_wlosow == cechy_dominujace[i])
			cechy_meskie[1] = 'B';
		else if(mezczyzna.kolor_wlosow == cechy_recesywne[i])
			cechy_meskie[1] = 'b';

		if(mezczyzna.reka_dominujaca == cechy_dominujace[i])
			cechy_meskie[2] = 'C';
		else if(mezczyzna.reka_dominujaca == cechy_recesywne[i])
			cechy_meskie[2] = 'c';

		if(mezczyzna.daltonizm == cechy_dominujace[i])
			cechy_meskie[3] = 'D';
		else if(mezczyzna.daltonizm == cechy_recesywne[i])
			cechy_meskie[3] = 'd';

		if(kobieta.kolor_oczu == cechy_dominujace[i])
			cechy_kobiece[0] = 'A';
		else if(kobieta.kolor_oczu == cechy_recesywne[i])
			cechy_kobiece[0] = 'a';

		if(kobieta.kolor_wlosow == cechy_dominujace[i])
			cechy_kobiece[1] = 'B';
		else if(kobieta.kolor_wlosow == cechy_recesywne[i])
			cechy_kobiece[1] = 'b';

		if(kobieta.reka_dominujaca == cechy_dominujace[i])
			cechy_kobiece[2] = 'C';
		else if(kobieta.reka_dominujaca == cechy_recesywne[i])
			cechy_kobiece[2] = 'c';

		if(kobieta.daltonizm == cechy_dominujace[i])
			cechy_kobiece[3] = 'D';
		if(kobieta.daltonizm == cechy_recesywne[i])
			cechy_kobiece[3] = 'd';
	}	
}
//czyszczenie zawartosci struktur, aby program wypisywal poprawna tabelke za n-tym razem uzycia funkcji kalkukacja cech
void czyszczenie_zawartosci(osoba& m, osoba& k)
{
	m.kolor_oczu=" ";
	m.kolor_wlosow=" ";
	m.reka_dominujaca=" ";
	m.daltonizm=" ";
	k.kolor_oczu=" ";
	k.kolor_wlosow=" ";
	k.reka_dominujaca=" ";
	k.daltonizm=" ";
}
