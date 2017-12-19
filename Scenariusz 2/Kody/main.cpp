//	Program realizuj¹cy uczenie neuronowej sieci jednowarstwowej rozpoznawania wielkoœci liter. 
//
//
//	Data utworzenia pliku: 19.12.2017			Autor: Izabela Musztyfaga
//
//	Autor modyfikacji				Co zostalo zmienione								Data
//
//***********************************************************************************************************************

#include "DeltaRuleLearning.h"
#include "AdalineLearning.h"

int main()
{
	
	double WspolczynnikUczenia = 0.1;					//wartoœæ wspó³czynnika uczenia

	DeltaRuleLearning delta(WspolczynnikUczenia);		//Stworzenie obiektu
	delta.Uczenie();									//Uczenie 
	delta.Testowanie();								//Testowanie


	//AdalineLearning adaline(WspolczynnikUczenia);		//Stworzenie obiektu
	//adaline.Uczenie();									//Uczenie 
	//adaline.Testowanie();								//Testowanie

	return 0;
} 