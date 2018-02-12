#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

#include "Network.h"

using namespace std;

//wczytanie do tablic danych wejsciowych
void setInputData(Neuron& neuron, vector<vector<double>> inputData, int numberOfInputs, int row);
//uczenie sieci
void learn(Network& layer, vector<vector<double>> inputData);
//testowanie sieci
void test(Network& layer, vector<vector<double>> inputData);
//wczytanie danych uczacych
void loadTrainingData(vector<vector<double>>&learningInputData, int numberOfInputs);
//wczytaniee danych testowych
void loadTestingData(vector<vector<double>>&testingInputData, int numberOfInputs);

//strumienie do plikow sluzace do wczytania danych uczacych oraz zapisu wynikow
fstream OUTPUT_FILE_LEARNING, OUTPUT_FILE_TESTING_DATA, OUTPUT_FILE_TESTING_NEURON;
fstream TRAINING_DATA, TESTING_DATA;

int main() {
	srand(time(NULL));

	//wektory z danymi uczacymi oraz testujacymi
	vector<vector<double>> trainData;
	vector<vector<double>> testData;
	int numberOfNeurons = 20;
	int numberOfInputs = 35;
	double learningRate = 0.3;
	int epoch = 50;
	//stworzenie sieci Kohonena
	Network kohonenNetwork(numberOfNeurons, numberOfInputs, learningRate, epoch);
	//wczytanie danych uczacych
	loadTrainingData(trainData, numberOfInputs);
	//wczytaniee danych testowych
	loadTestingData(testData, numberOfInputs);

	//"menu" programu
	do {
		cout << "1. Learn" << endl;
		cout << "2. Test" << endl;
		cout << "3. Exit" << endl;

		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			OUTPUT_FILE_LEARNING.open("output_learning_data.txt", ios::out);

			for (int epochNumber = 1, i = 0; i < epoch; i++, epochNumber++) {
				//uczenie
				learn(kohonenNetwork, trainData);
				OUTPUT_FILE_LEARNING << "Epoch: " << epochNumber << endl;
				cout << "Epoch: " << epochNumber << endl;
			}
			OUTPUT_FILE_LEARNING.close();
			break;
		case 2:
			OUTPUT_FILE_TESTING_DATA.open("output_testing_data.txt", ios::out);
			OUTPUT_FILE_TESTING_NEURON.open("output_testing_neuron.txt", ios::out);
			//testowanie
			test(kohonenNetwork, testData);
			break;
		case 3:
			OUTPUT_FILE_LEARNING.close();
			OUTPUT_FILE_TESTING_DATA.close();
			return 0;
		default:
			cout << "BAD BAD BAD" << endl;
		}
	} while (true);

	return 0;
}

//wczytanie do tablic danych wejsciowych
void setInputData(Neuron& neuron, vector<vector<double>> inputData, int numberOfInputs, int row)
{
	for (int i = 0; i < numberOfInputs; i++)
		neuron.inputs[i] = inputData[row][i];
}

//uczenie
void learn(Network& layer, vector<vector<double>> inputData)
{
	static int currentIteration = 0;
	for (int rowOfData = 0; rowOfData < inputData.size(); rowOfData++) {
		for (int i = 0; i < layer.numberOfNeurons; i++) {
			//wczytanie danych do tablic
			setInputData(layer.neurons[i], inputData, layer.neurons[i].getInputsSize(), rowOfData);
			//wyliczenie odleglosci euklidesowych
			layer.neurons[i].calculateScalarProduct();
		}
		//zmiana wag
		layer.changeWeights(currentIteration, true);

		OUTPUT_FILE_LEARNING << layer.winnerIndex << endl;
		cout << "Winner: " << layer.winnerIndex << endl;
		currentIteration++;
	}
}

//testowanie
void test(Network& layer, vector<vector<double>> inputData) {
	for (int rowOfData = 0; rowOfData < inputData.size(); rowOfData++) {
		for (int i = 0; i < layer.numberOfNeurons; i++) {
			//wczytanie danych do tablic
			setInputData(layer.neurons[i], inputData, layer.neurons[i].getInputsSize(), rowOfData);
			//wyliczenie odleglosci euklidesowych
			layer.neurons[i].calculateScalarProduct();
		}
		char letter = 'A';
		layer.changeWeights(0, false);
		OUTPUT_FILE_TESTING_DATA << layer.neurons[layer.winnerIndex].getInputsSize() << endl;
		OUTPUT_FILE_TESTING_NEURON << (char)(letter + rowOfData) << " " << layer.winnerIndex << endl;
		cout << (char)(letter + rowOfData) << " " << layer.winnerIndex << endl;
	}
}

//wczytanie danych uczacych z pliku
void loadTrainingData(vector<vector<double>> &inputData, int numberOfInputs) {
	TRAINING_DATA.open("data.txt", ios::in);
	vector<double> row;

	do {
		row.clear();

		for (int i = 0; i < numberOfInputs; i++) {
			double inputTmp = 0.0;
			TRAINING_DATA >> inputTmp;
			row.push_back(inputTmp);
		}

		//znormalizowanie danych uczacych
		double length = 0.0;

		for (int i = 0; i < numberOfInputs; i++)
			length += pow(row[i], 2);

		length = sqrt(length);

		for (int i = 0; i < numberOfInputs; i++)
			row[i] /= length;

		inputData.push_back(row);

	} while (!TRAINING_DATA.eof());

	TRAINING_DATA.close();
}

//wczytanie danych testujacych z pliku
void loadTestingData(vector<vector<double>> &testData, int numberOfInputs) {
	TESTING_DATA.open("datatest.txt", ios::in);
	vector<double> row;

	while (!TESTING_DATA.eof()) {
		row.clear();

		for (int i = 0; i < numberOfInputs; i++) {
			double inputTmp = 0.0;
			TESTING_DATA >> inputTmp;
			row.push_back(inputTmp);
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