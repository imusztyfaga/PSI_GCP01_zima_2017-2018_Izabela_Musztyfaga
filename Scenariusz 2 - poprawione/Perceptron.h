#include <cstdio> 
#include <cstdlib> 
#include <cmath> 
#include <ctime> 
#include <iostream> 
#include <fstream> 


using namespace std;

class Perceptron {

	int **Litery;    
	float *wagi;   
	int wyniki[20];   
	int ilosc_wejsc;   
	bool wynik;   
	float wsp_nauki;

public:  
	Perceptron();
	~Perceptron();
	void wczytywanie_danych_z_pliku();  
	float f_sumowania(int i);   
	void ucze();   
	void sprawdzam(int tab[]);		
};