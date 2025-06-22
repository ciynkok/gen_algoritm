#include "Task_Kom.h"
#include <random>
#include <cmath>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>


Task_Kom::Task_Kom(int n, const string& filename)
{
	this->n = n;
	if (filename == "")
	{
		generate_coords();
	}
	else
	{
		read_file(filename);
	}
	fill_matrx();
}

const double Task_Kom::calculation_dist(vector<int> a, vector<int> b)
{
	if (a.size() != b.size())
	{
		cerr << "a and b are different sizes!" << endl;
		return 1;
	}
	double res = 0;
	for (int i = 0; i < a.size(); i++)
	{
		res += (a[i] - b[i]) * (a[i] - b[i]);
	}
	return sqrt(res);
}

const int Task_Kom::generate_rand(int a, int b)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(a, b);
	return dist(gen);
}

void Task_Kom::print_coords()
{
	for (int i = 0; i < n; i++)
	{
		cout << "x: " << this->coords[i][0] << ", " << "y: " << this->coords[i][1] << endl;
	}
}

void Task_Kom::print_matrx()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << this->matrx_dist[i][j] << " ";
		}
		cout << endl;
	}
}

void Task_Kom::create_data()
{
	ofstream file("data.csv");
	if (!file.is_open()) {
		std::cerr << "Error opening file: output.csv" << std::endl;
		return;
	}
	file << "x,y" << endl;
	for (int i = 0; i < n; i++)
	{
		file << this->coords[i][0] << "," << this->coords[i][1] << endl;
	}
	file.close();
}

vector<vector<double>> Task_Kom::get_matrx()
{
	return this->matrx_dist;
}


void Task_Kom::read_file(const string& filename)
{
	ifstream file(filename);

	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << std::endl;
		file.close();
	}

}

bool Task_Kom::check_coord(int x, int y)
{
	int size_c = this->coords.size();
	for (int i = 0; i < size_c; i++)
	{
		if (x == this->coords[i][0] && y == this->coords[i][1])
		{
			return true;
		}
	}
	return false;
}

void Task_Kom::generate_coords()
{
	int min_x = 0;
	int max_x = 50;
	int min_y = 0;
	int max_y = 50;
	for (int i = 0; i < n; i++)
	{
		int x = this->generate_rand(min_x, max_x);
		int y = this->generate_rand(min_y, max_y);
		while (this->check_coord(x, y))
		{
			x = this->generate_rand(min_x, max_x);
			y = this->generate_rand(min_y, max_y);
			cout << "5" << endl;
		}
		vector<int> vec = { x, y };
		this->coords.push_back(vec);
	}
}

void Task_Kom::fill_matrx()
{
	for (int i = 0; i < n; i++) 
	{
		vector<double> vec;
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				vec.push_back(0);
			}
			else
			{
				if (j < i)
				{
					vec.push_back(this->matrx_dist[j][i]);
				}
				else
				{
					vector<int> a = this->coords[i];
					vector<int> b = this->coords[j];
					vec.push_back(this->calculation_dist(a, b));
				}
			}
		}
		this->matrx_dist.push_back(vec);
	}
}


