#include "Neuron.h"
#include <ctime>
#include <cmath>

//konstruktor
Neuron::Neuron() {
	this->inputs.resize(0);
	this->weights.resize(0);
	this->sumOfAllInputs = 0.0;
	this->outputValue = 0.0;
	this->learningRate = 0.0;
}

//konstruktor
Neuron::Neuron(int numberOfInputs, double learningRate) {
	createInputs(numberOfInputs);
	normalizeWeight();
	this->learningRate = learningRate;
	this->sumOfAllInputs = 0.0;
	this->outputValue = 0.0;
}

Neuron::~Neuron()
{

}

//stworzenie poczatkowych wejsc (ustawienie wejsc na 0, wykorzystanie metody firstWeight())
void Neuron::createInputs(int numberOfInputs) 
{
	for (int j = 0; j < numberOfInputs; j++) {
		this->inputs.push_back(0);
		this->weights.push_back(firstWeight());
	}
}

//obliczenie sumy wszystkich wejsc
double Neuron::calculateSumOfAllInputs() 
{
	this->sumOfAllInputs = 0.0;
	for (int i = 0; i < getNumberOfInputs(); i++)
		this->sumOfAllInputs += inputs[i] * weights[i];
	return sumOfAllInputs;
}

//funkcja sigmoidalna obliczajaca wyjscie
void Neuron::activationFunction() {
	double beta = 1.0;
	this->outputValue = (1.0 / (1.0 + (exp(-beta * this->sumOfAllInputs))));
}

//obliczenie nowych wag
void Neuron::calculateNewWeight() {
	for (int i = 0; i < getNumberOfWeights(); i++)
		this->weights[i] += this->learningRate*(this->inputs[i] - this->weights[i]);
	normalizeWeight();
}

//ustalenie poczatkowych wag dla wszystkich wejsc - zakres <0;1)
double Neuron::firstWeight() {
	double max = 1.0;
	double min = 0.0;
	double weight = ((double(rand()) / double(RAND_MAX))*(max - min)) + min;
	return weight;
}

//znormalizowanie nowo obliczonej wagi zwycieskiego neuronu
void Neuron::normalizeWeight() {
	double vectorLength = 0.0;

	for (int i = 0; i < getNumberOfWeights(); i++)
		vectorLength += pow(this->weights[i], 2);

	vectorLength = sqrt(vectorLength);
	for (int i = 0; i < getNumberOfWeights(); i++)
		this->weights[i] /= vectorLength;
}