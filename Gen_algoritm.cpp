#include "Gen_algoritm.h"
#include <iostream>

using namespace std;

Gen_algoritm::Gen_algoritm()
{
	cout << "Create object" << endl;
	this->matx_distance = new int*[10];
	for (int i = 0; i < 10; i++) 
	{
		this->matx_distance[i] = new int[5];
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			this->matx_distance[i][j] = 1;
		}
	}
	cout << this->matx_distance[9][4] << endl;
}
