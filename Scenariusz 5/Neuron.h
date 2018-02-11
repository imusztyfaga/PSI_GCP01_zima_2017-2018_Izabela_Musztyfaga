#include <iostream>
#include <vector>

using namespace std;

class Neuron 
{
public:

	vector<double> inputs; //wejscia
	vector<double> weights; //wagi
	double sumOfAllInputs; //suma wszystkich wejsc
	double outputValue; //wartosc wyjsciowa
	double learningRate; //wspolczynnik uczenia

	Neuron(); //konstruktor
	Neuron(int numberOfInputs, double learningRate); //konstruktor
	~Neuron();

	double firstWeight(); //wylosowanie poczatkowych wag z zakresu <0;1)
	void normalizeWeight(); //znormalizowanie wag (podczas procesu uczenia)
							//stworzenie poczatkowych wejsc (ustawienie wejsc na 0, wykorzystanie metody firstWeight())
	void createInputs(int numberOfInputs);
	void activationFunction(); //funkcja sigmoidalna obliczajaca wyjscie
	void calculateNewWeight(); //obliczenie nowej wagi dla zwycieskiego neuronu
	double calculateSumOfAllInputs(); //obliczenie sumy wszystkich wejsc

	int getNumberOfInputs() { //zwraca rozmiar wejsc
		return inputs.size();
	}

	int getNumberOfWeights() { //zwraca rozmiar wag
		return weights.size();
	}
};