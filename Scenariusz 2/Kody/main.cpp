//	Program realizuj�cy uczenie neuronowej sieci jednowarstwowej rozpoznawania wielko�ci liter. 
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
	
	double WspolczynnikUczenia = 0.1;					//warto�� wsp�czynnika uczenia

	DeltaRuleLearning delta(WspolczynnikUczenia);		//Stworzenie obiektu
	delta.Uczenie();									//Uczenie 
	delta.Testowanie();								//Testowanie


	//AdalineLearning adaline(WspolczynnikUczenia);		//Stworzenie obiektu
	//adaline.Uczenie();									//Uczenie 
	//adaline.Testowanie();								//Testowanie

	return 0;
} 