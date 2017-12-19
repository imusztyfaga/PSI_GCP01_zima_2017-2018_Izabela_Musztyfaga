#include "DeltaRuleLearning.h"

DeltaRuleLearning::DeltaRuleLearning()											//konstruktor bezparametrowy
{
	
}

DeltaRuleLearning::DeltaRuleLearning(double _learningRate)						//konstruktor
{
	IloscWagLiter = 35;
	IloscLiter = 20;
	WspolczynnikUczenia = _learningRate;
	WagiLiter = new double[IloscWagLiter];

	WczytanieDanychTestowych();													//wczytanie z pliku danych uczacych

	for (int i = 0; i < 35; i++)
	{
		this->WagiLiter[i] = LosoweWagiPoczatkowe();
	}
}

DeltaRuleLearning::~DeltaRuleLearning()											//destruktor
{

}

double DeltaRuleLearning::LosoweWagiPoczatkowe()										//poczatkowe, losowe wagi wejsc
{
	double Waga = ((double)rand() / (double)RAND_MAX);
	return Waga;
}

void DeltaRuleLearning::WczytanieDanychTestowych()											//wczytywanie danych z pliku
{
	std::fstream file;
	file.open("Dane.txt");

	while (!file.eof())													
		for (int i = 0; i < 20; i++)									//20 liter
		{ 
			for (int j = 0; j < 35; j++)								//35 pikseli/wag
			{
				file >> this->DaneWejsciowe[i][j];
			}
			file >> this->OczekiwanyRezultat[i];						//reszta okresla czy litera jest duza czy mala
		}

	file.close();														//zamknięcie pliku
}


double DeltaRuleLearning::FunkcjaAktywacji(double sum)							//funkcja aktywacji 
{
	return (1 / (1 + exp(-1.0 * sum)));
}

double DeltaRuleLearning::Pochodna(double sum)									//pochodna funkcji 
{
	return (1.0*exp(-1.0*sum)) / (pow(exp(-1.0*sum) + 1, 2));
}

//zwraca sume danego wejscia
double DeltaRuleLearning::SumaWejscia(int letter[], double * weights)
{
	double sum = 0.0;
	for (int i = 0; i < IloscWagLiter; i++)
	{
		sum += letter[i] * weights[i];
	}

	return sum;
}

//funkcja uczaca
void DeltaRuleLearning::Uczenie() {
	std::cout << std::endl << "DELTA RULE LEARNING" << std::endl;

	bool AkceptowalnaWartoscBledu = false; //zmienna, stwierdzajaca czy blad jest mozliwy do zaakceptowania
	int epoka = 0; 

	do {
		epoka++; 
		BladSredniokwadratowy = 0.0; 
		for (int i = 0; i < IloscLiter; i++)
		{
			//wynik otrzymany
			WartoscWyjscia = FunkcjaAktywacji(SumaWejscia(DaneWejsciowe[i], WagiLiter));

			//obliczanie roznicy pomiedzy wynikiem oczekiwanym a wynikiem otrzymanym
			delta = OczekiwanyRezultat[i] - WartoscWyjscia;

			//aktualizowanie wag weglug wzoru 
			for (int j = 0; j < IloscWagLiter; j++)
			{
				WagiLiter[j] += WspolczynnikUczenia*delta*DaneWejsciowe[i][j] * Pochodna(SumaWejscia(DaneWejsciowe[i], WagiLiter));
			}		
			
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

	std::cout << "Wspolczynnik uczenia sieci: " << WspolczynnikUczenia << std::endl;
	std::cout << "Numer epoki: " << epoka << std::endl;
	std::cout << "Blad Sredniokwadratowy: " << BladSredniokwadratowy << std::endl << std::endl;
}


void DeltaRuleLearning::Testowanie()											//testowanie + drukowanie wyniku
{
	std::cout << "Czy litera jest wielka?" << std::endl << std::endl;
	for (int i = 0; i < IloscLiter; i++) 
	{
		std::cout << setTestLetters[i] << " - ";
		if (FunkcjaAktywacji(SumaWejscia(DaneDoPorownania[i], WagiLiter)) > 0.5)
		{
			std::cout << "Tak";
		}
		else {
			std::cout << "Nie";
		}
		std::cout << std::endl;
	}
}