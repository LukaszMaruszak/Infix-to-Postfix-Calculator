//Łukasz Maruszak Projekt Odwrotna Notacja Polska

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

using namespace std;

const int maxlegth = 100;
typedef int elementtype;
typedef int position;

//Reprezentacja tablicowa struktury danych Stos
class Stos
{
protected:
	int S[maxlegth];
	position Top;//szczyt stosu
public:
	Stos();
	void Push(elementtype x);
	void Pop();
	bool Empty();
	elementtype TopElem();
	void Makenull();
};

Stos::Stos()
{
	Top = -1;
}// KONSTRUKTOR

void Stos::Makenull()
{
	Top = -1;
}// WYCZYSZCZENIE STOSU	

void Stos::Push(elementtype x)
{
	if (Top < maxlegth - 1)
	{
		Top++;
		S[Top] = x;
	}
}// PUSH

void Stos::Pop()
{
	if (Top >= 0) Top--;
}//POP

bool Stos::Empty()
{
	return (Top == -1);
}//Empty 

elementtype Stos::TopElem()
{
	if (Top >= 0) return S[Top];
}//Element na szczycie

//Funkcja do określania piorytetu znaku
int okresl_priorytet_operatora(char znak) {

	switch (znak)
	{
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	case '^':
		return 3;
		break;
	default:
		return 0;
	}
}

//Obliczanie wartosci w odwrotnej notacji polskiej
void odwrotna_notacja_polska(string obliczTo) {
	Stos stos = Stos();;

	int x = 0;
	int y = 0;
	int i = 0;
	string liczba = "";

	//nie koniec danych
	while (i < obliczTo.length()) {

		//Sprawdzam czy znak jest spacja jezeli tak to przechodze do nastepnego
		while (isspace(obliczTo[i])) {
			i++;
		}

		//Sprawdzam czy znak jest liczba i wstawiam ja na stos
		if (isdigit(obliczTo[i])) {
			while (isdigit(obliczTo[i])) {
				liczba += obliczTo[i];
				i++;
			}
			stos.Push(atoi(liczba.c_str()));
			liczba = "";
		}

		//Jezeli jest operandem to wykonuje odpowiedznie operacje na stosie
		if (obliczTo[i] == '+') {
			y = stos.TopElem();
			stos.Pop();
			x = stos.TopElem();
			stos.Pop();
			int suma = x + y;
			stos.Push(suma);
			i++;
		}

		if (obliczTo[i] == '-') {
			y = stos.TopElem();
			stos.Pop();
			x = stos.TopElem();
			stos.Pop();
			int roznica = x - y;
			stos.Push(roznica);
			i++;
		}

		if (obliczTo[i] == '*') {
			y = stos.TopElem();
			stos.Pop();
			x = stos.TopElem();
			stos.Pop();
			int iloczyn = x * y;
			stos.Push(iloczyn);
			i++;
		}

		if (obliczTo[i] == '/') {
			y = stos.TopElem();
			if (y == 0) {
				cout << "Nie mozna dzielic przez zero!!!" << endl;
				break;
			}
			stos.Pop();
			x = stos.TopElem();
			stos.Pop();
			int iloraz = x / y;
			stos.Push(iloraz);
			i++;
		}

		if (obliczTo[i] == '~') {
			y = stos.TopElem();
			stos.Pop();
			int minus = -1 * y;
			stos.Push(minus);
			i++;
		}

		if (obliczTo[i] == '^') {
			y = stos.TopElem();
			stos.Pop();
			x = stos.TopElem();
			stos.Pop();
			int potega = pow(x, y);
			stos.Push(potega);
			i++;
		}
		//Wypisanie wartosci wyrazenia kiedy trafie na =
		if (obliczTo[i] == '=') {
			int wynik = stos.TopElem();
			cout << "Wynik to: " << wynik << endl;
			stos.Makenull();
			break;
		}//obliczenie wyrazenia
	}
}

//Funkcja do konwersji wyrzenia na ONP
void konwertuj_wyrazenie_do_ONP(string konwertujTo) {

	Stos stos = Stos();
	string wynik = "";

	//Przechodze po cały wyrazeniu 
	for (int i = 0; i < konwertujTo.length(); i++)
	{
		///sprawdzamy czy jest liczba
		if (isdigit(konwertujTo[i])) {
			wynik += konwertujTo[i];
		}
		else if (konwertujTo[i] == '(') stos.Push(konwertujTo[i]);
		//Kiedy trafie na = zdejumuje operatory ze stosu na wynik i wypisuje go
		else if (konwertujTo[i] == '=') {
			while (!stos.Empty())
			{
				wynik += ' ';
				wynik += stos.TopElem();
				stos.Pop();
			}
			cout << "Wynik to: " << wynik << endl;
			break;
		}//obliczenie wyrazenia
		else if (konwertujTo[i] == ')')
		{
			//kiedy na stosie jest operator i nie jest to (
			while (!stos.Empty() && stos.TopElem() != '(')
			{
				wynik += ' ';
				wynik += stos.TopElem();
				stos.Pop();
			}
			stos.Pop();
		}
		else
		{
			//Sprawdzam, ktorym jest operatorem
			if (konwertujTo[i] == '+' || konwertujTo[i] == '-' || konwertujTo[i] == '*' || konwertujTo[i] == '/' || konwertujTo[i] == '^')
			{

				while (okresl_priorytet_operatora(konwertujTo[i]) <= okresl_priorytet_operatora(stos.TopElem()))
				{
					wynik += ' ';
					wynik += stos.TopElem();
					stos.Pop();
				}
				wynik += ' ';
				stos.Push(konwertujTo[i]);
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	string podane = " ";
	string cale_wyrazenie = "";
	char wybor;

	cout << "Cześć!!!" << endl;
	cout << "Oto Odwrotna Notacja Polska (ONP)" << endl;
	cout << "Wybierz a, żeby obliczyć wyrażenie w ONP" << endl;
	cout << "Wybierz b, żeby dokonać konwersji wyrazenia tradycyjnego na ONP." << endl;
	cout << "Wybierz q  żeby zakończyć!" << endl;

	
		cin >> wybor;
		if (wybor == 'q') {
			return 0;
		}

		if (wybor == 'a') {
			cout << "Wybrano obliczenie wyrazenia podaj je: np 2 2 + =" << endl;
			cale_wyrazenie = "";
			while (podane[podane.length() - 1] != '=') {
				cin >> podane;
				cale_wyrazenie += podane + " ";
			}

			odwrotna_notacja_polska(cale_wyrazenie);
		}//IF

		if (wybor == 'b') {
			cout << "Wybrano konwersje wyrazenia podaj je: np (3+6)*1=" << endl;
			cale_wyrazenie = "";
			while (podane[podane.length() - 1] != '=') {
				cin >> podane;
				cale_wyrazenie += podane;
			}
			konwertuj_wyrazenie_do_ONP(cale_wyrazenie);
		}//IF
	
	return 0;
}


