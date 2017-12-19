#include "AdalineLearning.h"

AdalineLearning::AdalineLearning()
{

}

AdalineLearning::~AdalineLearning()
{

}

AdalineLearning::AdalineLearning(double WspolczynnikUczenia_)
{
	IloscWagLiter = 35;
	IloscLiter = 20;
	WspolczynnikUczenia = WspolczynnikUczenia_;
	WagiLiter = new double[IloscWagLiter];								//tablica przechowujaca wagi

	for (int i = 0; i < 35; i++)										//przypisanie losowych wag poczatkowych
	{
		this->WagiLiter[i] = LosoweWagiPoczatkowe();
	}

	WczytanieDanychTestowych();											//wczytanie danych z pliku
}

void AdalineLearning::WczytanieDanychTestowych()						//wczytanie danych z pliku - metoda
{
	std::fstream file;
	file.open("Dane.txt");

	while (!file.eof())
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 35; j++)
			{
				file >> this->DaneWejsciowe[i][j];
			}

			file >> this->OczekiwanyRezultat[i];						//0 lub 1 w pliku mowi, czy litera jest duza czy mala
		}

	file.close();
}

double AdalineLearning::LosoweWagiPoczatkowe()							//ustawienie wag poczatkowych			
{
	double Waga = ((double)rand() / (double)RAND_MAX);
	return Waga;
}

bool AdalineLearning::FunkcjaAktywacji(double sum)						//funkcja aktywacji
{
	if (sum > 0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//zwraca sume danego wejscia
double AdalineLearning::getSum(int Litery[], double * Wagi)
{
	double sum = 0.0;
	for (int i = 0; i < IloscWagLiter; i++)
	{
		sum += Litery[i] * Wagi[i];
	}

	return sum;
}

//funkcja uczaca
void AdalineLearning::Uczenie()
{
	std::cout << "ADALINE" << std::endl;

	bool AkceptowalnaWartoscBledu = true; //zmienna, stwierdzajaca czy blad jest mozliwy do zaakceptowania

	int epoka = 0;

	do {
		epoka++;
		BladSredniokwadratowy = 0.0;
		for (int i = 0; i<IloscLiter; i++)
		{
			//obliczanie roznicy pomiedzy wynikiem oczekiwanym a wynikiem otrzymanym
			delta = OczekiwanyRezultat[i] - getSum(DaneWejsciowe[i], WagiLiter);

			//aktualizowanie wag
			for (int j = 0; j < IloscWagLiter; j++)
			{
				WagiLiter[j] += WspolczynnikUczenia*delta*DaneWejsciowe[i][j];
			}

			//aktualizowanie bledu glownego
			BladSredniokwadratowy += delta*delta;
		}

		BladSredniokwadratowy /= 2;

		//porownywanie bledu z progiem
		if (BladSredniokwadratowy > 0.1)
		{
			AkceptowalnaWartoscBledu = false;
		}
		else
		{
			AkceptowalnaWartoscBledu = true;
		}
	} while (!AkceptowalnaWartoscBledu);

	std::cout << "Ilosc epok:  " << epoka << std::endl;
	std::cout << "Blad Sredniokwadratowy: " << BladSredniokwadratowy << std::endl << std::endl;
}

void AdalineLearning::Testowanie()
{
	std::cout << "Czy litera jest wielka?" << std::endl << std::endl;
	for (int i = 0; i<IloscLiter; i++)
	{
		std::cout << Litery[i] << " - ";
		if (FunkcjaAktywacji(getSum(DaneTestowe[i], WagiLiter)))
		{
			std::cout << "Tak";
		}
		else
		{
			std::cout << "Nie";
		}
		std::cout << std::endl;
	}
}