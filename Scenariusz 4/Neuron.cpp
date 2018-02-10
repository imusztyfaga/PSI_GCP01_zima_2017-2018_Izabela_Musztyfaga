#include "Neuron.h"

Neuron::Neuron(double learningRate)				//konstruktor
{
	this->learningRate = learningRate;
	//Zerowanie tablic wag,sum oraz pomocnicza do testow
	for (int i = 0; i<HOW_MANY_EMOTICONS; i++)
		for (int j = 0; j < HOW_MANY_BITS; j++) 
		{
			weights[i][j] = 0;
			sumOfInput[i] = 0;
			emoticonTest[i] = 0;
		}

	//Losowanie wag poczatkowych z przedzia³u od 0 do 1
	srand(time(NULL));
	for (int i = 0; i<HOW_MANY_BITS; i++) {
		weights[0][i] = (double)rand() / (double)RAND_MAX;//dla emotki 1 dla wszytkich "komponentow" itd dalej dla 2,3,4 emotki
		weights[1][i] = (double)rand() / (double)RAND_MAX;
		weights[2][i] = (double)rand() / (double)RAND_MAX;
		weights[3][i] = (double)rand() / (double)RAND_MAX;
	}

	//Wczytanie danych uczacych
	int whichEmoticon = 0, whichBit = 0, bit;//pomocnicze
	fstream file;
	file.open("dane.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			//Jesli wczytano juz wszystkie bity (100=10x10) danej emotikony, przejscie do wczytywania bitow kolejnej
			if (whichBit == 225) {
				whichBit = 0; whichEmoticon++;
			}
			//Jesli wczytano wszystkie (4) emotikony, zakoncz wczytywanie
			if (whichEmoticon == HOW_MANY_EMOTICONS)
				break;

			file >> bit;
			emoticons[whichEmoticon][whichBit] = bit;
			whichBit++;
		}
		file.close();
	}

	//Wczytanie danych testujacych
	fstream file2;
	file2.open("dane_testowe.txt");
	if (file2.is_open()) {
		while (!file2.eof()) {

			if (whichBit == 225) {
				whichBit = 0; whichEmoticon++;
			}

			if (whichEmoticon == HOW_MANY_EMOTICONS)
				break;

			file2 >> bit;
			emoticonsTest[whichEmoticon][whichBit] = bit;
			whichBit++;
		}
		file2.close();
	}
}

Neuron::~Neuron()		//destruktor
{

}

//Funkcja aktywacji - progowa unipolarna
int Neuron::activationFunction(double sum) 
{
	return (sum >= 0) ? 1 : 0;					//1 gdy x>=wartosc progowa, 0 gdy x<wart.prog, wart.prog=0 - moze byc inna 
}

//Ustawienie sum (wejscie*waga) na wartosc poczatkowa = 0
void Neuron::resetSum() 
{
	int i = 0;
	for (i = 0; i<HOW_MANY_BITS; i++)
		sumOfInput[i] = 0.;
}

//Uczenie regula Hebba (bez zapominania)
void Neuron::learnDontForget() 
{
	
	int epoch = 0; //Epok
	double globalError = 0.; //Blad globalny
	double localErr = 0.; //Blad lokalny
	double sum = 0.; //Przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //Ustawienie wartosci poczatkowych dla wektora sumOfInput
	cout << "Uczenie regula Hebba (bez zapominania)" << endl;

	do {
		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];
				sumOfInput[j] = (weights[i][j] * emoticons[i][j]);

				//Aktualizacja wag
				weights[i][j] = weights[i][j] + this->learningRate*sumOfInput[j] * emoticons[i][j];

				if (localErr == abs(sum - sumOfInput[j]))
					break;
				localErr = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localErr, 2);

			}

		}
		epoch++;

	} while (globalError != 0 && epoch < 3000);

	cout << endl << "Liczba epok: " << epoch << endl << endl << endl;

	test();
}

//Uczenie regu³a Hebba (z zapominaniem)
void Neuron::learnForget() {

	int epoch = 0; //Epoka
	double FORGET_RATE = 0.5; //Wspolczynnik zapominania
	double globalError = 0.; //Blad globalny
	double localErr = 0.; //Blad lokalny
	double sum = 0.; //Przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //Ustawienie wartosci poczatkowych dla wektora sumOfInput

	cout << "Uczenie regula Hebba (z zapominanianiem)" << endl;

	do {
		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];

				sumOfInput[j] = (weights[i][j] * emoticons[i][j]);

				//Aktualizacja wag
				weights[i][j] = weights[i][j] * (1 - FORGET_RATE) + this->learningRate*sumOfInput[j] * emoticons[i][j];

				if (localErr == abs(sum - sumOfInput[j])) break;
				localErr = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localErr, 2);
			}

		}
		epoch++;

	} while (globalError != 0 && epoch < 3000);

	cout << endl << "Liczba epok: " << epoch << endl;

	test();

	cout << endl << "Wspolczynnik zapominania = " << FORGET_RATE << endl;
}

//Przetestowanie nauczenia danej emotikony
void Neuron::test() 
{
	double globalError = 0.;
	double localErr = 0.;
	double sum = 0.;
	int epoch = 0;

	resetSum();

	cout << endl << "Testowana emotikona: 1" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[0][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localErr = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localErr, 2);
		}


	} while (globalError != 0 && epoch<1);


	result();

	resetSum();

	cout << endl << "Testowana emotikona: 2" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];//suma wejsc
			sumOfInput[i] = (weights[0][i] * emoticonsTest[1][i]);//s=w*dane_ucz

			emoticonTest[i] = activationFunction(sumOfInput[i]);//f(s)
			localErr = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localErr, 2);
		}


	} while (globalError != 0 && epoch<1);

	result();

	resetSum();

	cout << endl << "Testowana emotikona: 3" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[2][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localErr = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localErr, 2);
		}


	} while (globalError != 0 && epoch<1);

	result();

	resetSum();

	cout << endl << "Testowana emotikona: 4" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[3][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localErr = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localErr, 2);
		}


	} while (globalError != 0 && epoch<1);

	result();
}

//Sprawdzenie czy dobrze rozpoznaje emotikony
void Neuron::result() 
{

	int tmp[HOW_MANY_EMOTICONS];

	for (int i = 0; i<HOW_MANY_EMOTICONS; i++)
		tmp[i] = 0;

	for (int i = 0; i<HOW_MANY_BITS; ++i) {
		if (emoticonTest[i] == emoticons[0][i]) tmp[0]++;
		if (emoticonTest[i] == emoticons[1][i]) tmp[1]++;
		if (emoticonTest[i] == emoticons[2][i]) tmp[2]++;
		if (emoticonTest[i] == emoticons[3][i]) tmp[3]++;
	}


	if (tmp[0] > tmp[1] && tmp[0] > tmp[2] && tmp[0] > tmp[3])
		cout << "Rozpoznana emotikona: 1" << endl;

	if (tmp[1] > tmp[0] && tmp[1] > tmp[2] && tmp[1] > tmp[3])
		cout << "Rozpoznana emotikona: 2" << endl;

	if (tmp[2] > tmp[0] && tmp[2] > tmp[1] && tmp[2] > tmp[3])
		cout << "Rozpoznana emotikona: 3" << endl;

	if (tmp[3] > tmp[0] && tmp[3] > tmp[1] && tmp[3] > tmp[2])
		cout << "Rozpoznana emotikona: 4" << endl;
}