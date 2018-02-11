#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

#include "Network.h"

using namespace std;

//wczytanie do tablic danych wejsciowych
void setInputData(Neuron& neuron, vector<vector<double>> inputData, int numberOfInputs, int inputDataRow);
//uczenie sieci
void learn(Network& layer, vector<vector<double>> inputData);
//testowanie sieci
void test(Network& layer, vector<vector<double>> inputData);
//wczytanie danych uczacych
void loadTrainingData(vector<vector<double>>&learnData, int numberOfInputs);
//wczytaniee danych testowych
void loadTestingData(vector<vector<double>>&testData, int numberOfInpus);

//strumienie do plikow sluzace do wczytania danych uczacych oraz zapisu wynikow
fstream OUTPUT_FILE_LEARNING, OUTPUT_FILE_TESTING_SUM, OUTPUT_FILE_TESTING_WINNER;
fstream TRAINING_DATA, TESTING_DATA;

int main() 
{
	srand(time(NULL));

	//wektory z danymi uczacymi oraz testujacymi
	vector<vector<double>> trainData;
	vector<vector<double>> testData;
	int numberOfNeurons = 10;
	int numberOfInputs = 4;
	double learningRate = 0.01;
	//stworzenie sieci Kohonena
	Network kohonenNetwork(numberOfNeurons, numberOfInputs, learningRate);
	//wczytanie danych uczacych
	loadTrainingData(trainData, numberOfInputs);
	//wczytaniee danych testowych
	loadTestingData(testData, numberOfInputs);


	do {
		cout << "1. Learn" << endl;
		cout << "2. Test" << endl;
		cout << "3. Exit" << endl;

		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			OUTPUT_FILE_LEARNING.open("Dane_uczace_wyjscie.txt", ios::out);

			for (int epoch = 1, i = 0; i < 5; i++, epoch++) 
			{
				//uczenie
				OUTPUT_FILE_LEARNING << "Epoka: " << epoch << endl;
				cout << "Epoka: " << epoch << endl;
				learn(kohonenNetwork, trainData);
			}
			OUTPUT_FILE_LEARNING.close();
			break;
		case 2:
			OUTPUT_FILE_TESTING_SUM.open("Dane_testujace_wyjscie.txt", ios::out);
			//testowanie
			test(kohonenNetwork, testData);
			break;
		case 3:
			OUTPUT_FILE_LEARNING.close();
			OUTPUT_FILE_TESTING_SUM.close();
			OUTPUT_FILE_TESTING_WINNER.close();
			return 0;
		default:
			cout << "Blad" << endl;
		}
	} while (true);

	return 0;
}

//wczytanie do tablic danych wejsciowych
void setInputData(Neuron& neuron, vector<vector<double>> inputData, int numberOfInputs, int row)
{
	for (int i = 0; i < numberOfInputs; i++) {
		neuron.inputs[i] = inputData[row][i];
	}
}

//uczenie
void learn(Network& layer, vector<vector<double>> inputData)
{
	int counter = 0;
	for (int rowOfData = 0; rowOfData < inputData.size(); rowOfData++)
	{
		for (int i = 0; i < layer.numberOfNeurons; i++) 
		{
			//wczytanie danych do tablic
			setInputData(layer.neurons[i], inputData, layer.neurons[i].getNumberOfInputs(), rowOfData);
			//wyliczenie sumy wejscia
			layer.neurons[i].calculateSumOfAllInputs();
		}
		//zmiana wag
		layer.changeWeights(true);
		//przeskoczenie do kolejnego rodzaju kwiatka
		if (counter == 50) 
		{
			counter = 0;
			OUTPUT_FILE_LEARNING << "Nastepny kawiat" << endl;
			cout << "Nastepny kawiatr" << endl;
		} 

		OUTPUT_FILE_LEARNING << layer.winnerIndex << endl;
		cout << "Zwyciezca: " << layer.winnerIndex << endl;
		counter++;
	}
}

//testowanie
void test(Network& layer, vector<vector<double>> inputData) {
	int counter = 0;
	for (int wierszDanych = 0; wierszDanych < inputData.size(); wierszDanych++) {
		for (int i = 0; i < layer.numberOfNeurons; i++) {
			//wczytanie danych do tablic
			setInputData(layer.neurons[i], inputData, layer.neurons[i].getNumberOfInputs(), wierszDanych);
			//wyliczenia sumy wejscia
			layer.neurons[i].calculateSumOfAllInputs();
		}
		//przeskoczenie na kolejny rodzaj kwiatka (wyzerowanie licznika)
		if (counter == 15) 
		{
			counter = 0;
			OUTPUT_FILE_TESTING_WINNER << "Nastepny kawiat" << endl;
			cout << "Nastepny kawiat" << endl;
		}
		 
		//wagi nie beda zaktualiowane dla zwyciezcy
		layer.changeWeights(false);
		OUTPUT_FILE_TESTING_SUM << layer.neurons[layer.winnerIndex].sumOfAllInputs << endl;
		OUTPUT_FILE_TESTING_WINNER << layer.winnerIndex << endl;
		cout << "Zwyciezki neuron: " << layer.winnerIndex << endl;
		counter++;
	}
}

//wczytanie danych uczacych z pliku
void loadTrainingData(vector<vector<double>> &trainData, int numberOfInputs) {
	TRAINING_DATA.open("dane_uczace.txt", ios::in);
	vector<double> row;

	do {
		row.clear();
		for (int i = 0; i < numberOfInputs; i++) {
			double inputTmp = 0.0;
			TRAINING_DATA >> inputTmp;
			row.push_back(inputTmp);
			if (i == numberOfInputs - 1) {
				TRAINING_DATA >> inputTmp;
				//row.push_back(inputTmp);
			}
		}

		//znormalizowanie danych uczacych
		double length = 0.0;

		for (int i = 0; i < numberOfInputs; i++)
			length += pow(row[i], 2);

		length = sqrt(length);

		for (int i = 0; i < numberOfInputs; i++)
			row[i] /= length;

		trainData.push_back(row);

	} while (!TRAINING_DATA.eof());

	TRAINING_DATA.close();
}

//wczytanie danych testujacych z pliku
void loadTestingData(vector<vector<double>> &testData, int numberOfInputs) {
	TESTING_DATA.open("dane_testujace.txt", ios::in);
	vector<double> row;

	while (!TESTING_DATA.eof()) {
		row.clear();

		for (int i = 0; i < numberOfInputs; i++) {
			double inputTmp = 0.0;
			TESTING_DATA >> inputTmp;
			row.push_back(inputTmp);
			if (i == numberOfInputs - 1) {
				TRAINING_DATA >> inputTmp;
				//row.push_back(inputTmp);
			}
		}

		//znormalizowanie danych uczacych
		double length = 0.0;

		for (int i = 0; i < numberOfInputs; i++)
			length += pow(row[i], 2);

		length = sqrt(length);

		for (int i = 0; i < numberOfInputs; i++)
			row[i] /= length;

		testData.push_back(row);
	}

	TESTING_DATA.close();
}