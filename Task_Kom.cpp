#include "Task_Kom.h"
#include <random>
#include <cmath>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>


Task_Kom::Task_Kom(int n, const string& filename, int seed)
{
	this->n = n;
	this->seed = seed;
	if (filename == "")
	{
		if (n == 0)
		{
			cerr << "Invalid parameters" << endl;
		}
		generate_coords();
		fill_matrx();
		create_data();
	}
	else
	{
		read_file(filename);
		fill_matrx();
	}
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

int Task_Kom::generate_rand(int a, int b, int seed)
{
	uniform_int_distribution<> dist(a, b);
	if (seed == 0)
	{
		random_device rd;
		mt19937 gen(rd());
		return dist(gen);
	}
	else
	{
		mt19937 gen(seed);
		return dist(gen);
	}
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
		std::cerr << "Error opening file: data.csv" << std::endl;
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
		cerr << "Error opening file: data.csv" << filename << std::endl;
		file.close();
	}
	string line;
	getline(file, line);

	while (getline(file, line))
	{
		vector<int> row;
		stringstream ss(line);
		string val;
		while (getline(ss, val, ','))
		{
			row.push_back(stod(val));
		}
		coords.push_back(row);
	}

	this->n = this->coords.size();
	file.close();
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
		int x = generate_rand(min_x, max_x, seed);
		int y = generate_rand(min_y, max_y, seed);
		while (check_coord(x, y))
		{
			x = generate_rand(min_x, max_x, seed);
			y = generate_rand(min_y, max_y, seed);
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
