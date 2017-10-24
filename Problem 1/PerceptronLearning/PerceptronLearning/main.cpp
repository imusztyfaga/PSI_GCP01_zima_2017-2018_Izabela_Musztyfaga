#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	float w[3];													//tablica z wagami
	float t, o;
	double eta = 0.8; 
	int i;
	int count = 0;
	bool correct = 0;
	int x0, x1, x2;												//zmienne przechowuj¹ce wejœcia
	float weightsum, deltaw0, deltaw1, deltaw2;

																
	//int train [4] [3] = {0, 0, 0,								//logiczny AND
	//0, 1, 0,
	//1, 0, 0,
	//1, 1, 1 };

	int train[4][3] = { 0, 0, 0,								//logiczny OR
		0, 1, 1,
		1, 0, 1,
		1, 1, 1 };

	ofstream outfile;											//zapisywanie wykików w pliku
	outfile.open("sigout.txt");

	if (outfile.fail())
	{
		cout << "file failed to open";
		abort();
	}

	srand((unsigned)(time(0)));									//generator liczb losowych

	rand();

	x0 = -1;													//PROG??????????????


	w[0] = (float)(rand()) / (32767 / 2) - 1;


	for (i = 1; i < 3; ++i)
		w[i] = (float)(rand()) / (32767 / 2) - 1;

	cout << "INITIAL WEIGHTS" << endl
		<< "---------------" << endl;

	cout << "w0 = " << w[0] << endl;
	cout << "w1 = " << w[1] << endl;
	cout << "w2 = " << w[2] << endl;


	while (!correct)											//procesz uczenia perceptronu
	{
		correct = 1;
		count++;

		for (i = 0; i < 4; ++i)									//wpisanie danych
		{

			x1 = train[i][0];
			x2 = train[i][1]; 

			weightsum = x0 * w[0] + x1 * w[1] + x2 * w[2];		//dobór wag

			if (weightsum >= 0) o = 1;							//okreslenie wyjscia
			else o = 0;

			t = train[i][2];									//poprawne wyjscie - z danych z f.logicznych

			if (o != t)											//jesli wyjscie jest niepoprawne - dostosuj wagi
			{
				deltaw0 = eta * (t - o) * x0;
				w[0] = w[0] + deltaw0;

				deltaw1 = eta * (t - o) * x1;
				w[1] = w[1] + deltaw1;

				deltaw2 = eta * (t - o) * x2;
				w[2] = w[2] + deltaw2;

				correct = 0;
			}
		}
	}


	//OUTPUT
	cout << endl << endl;
	cout << "FINAL WEIGHTS" << endl
		<< "-------------" << endl;
	cout << "w0 = " << w[0] << endl;
	cout << "w1 = " << w[1] << endl;
	cout << "w2 = " << w[2] << endl;

	cout << "The delta rules were invoked " << count << " times" << endl;

	outfile << w[0] << endl;									//zapis wyniku do pliku
	outfile << w[1] << endl;
	outfile << w[2] << endl;
	outfile << "The delta rules were invoked " << count << " times" << endl;

	outfile.close();											//zamkniecie pliku


	return 0;
}





