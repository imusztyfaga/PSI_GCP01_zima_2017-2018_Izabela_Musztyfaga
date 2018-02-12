#include <iostream>
#include <vector>

using namespace std;

class Neuron {
public:
	vector<double> inputs; //wejscia
	vector <double> weights; //wagi
	double sumOfAllInputs; //obliczenie odleglosci skalarnych
	double outputValue; //wartosc wyjsciowa
	double learningRate; //wspolczynnik uczenia
	double valueOfNeighborhoodFunction; //wartosc funkcji sasiedztwa (Gaussian neighborhood function)
	double length; //odleglosc euklidesowa
	double neighbors; //odleglosc do sasiadow

	double calculateFirstWeights(); //wylosowanie poczatkowych wag z zakresu <0;1)
	void calculateNeighbors(); //oblicza wartosc funkcji sasiedztwa (Gaussian neighborhood function)
	void normalizeWeights(); //znormalizowanie zaktualizowanych wag

							 //stworzenie poczatkowych wejsc(ustawienie wejsc na 0, wykorzystanie metody calculateFirstWeights())
	void createInputs(int numberOfInputs);
	void activationFunction(); //funkcja sigmoidalna obliczajaca wyjscie
	void calculateNewWeights(); //obliczenie nowych wag
	double calculateScalarProduct(); //obliczenie odleglosci skalarnych
	void designateNeighbors(double radius, double currentIteration, double time); //wyznaczenie odleglosci do sasiadow

	int getInputsSize() { //zwraca rozmiar wejsc
		return inputs.size();
	}

	int getWeightsSize() { //zwraca rozmiar wejsci
		return weights.size();
	}

	Neuron(); //konstuktor
	Neuron(int numberOfInputs, double learningRate); //konstruktor
};