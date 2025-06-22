#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Task_Kom
{
public:
	Task_Kom(int n, const string& filename = "");
	const double calculation_dist(vector<int> a, vector<int> b);
	const int generate_rand(int a, int b);
	void print_coords();
	void print_matrx();
	void create_data();
	vector<vector<double>> get_matrx();
private:
	int n;
	vector<vector<int>> coords;
	vector<vector<double>> matrx_dist;
	void read_file(const string& filename);
	bool check_coord(int x, int y);
	void generate_coords();
	void fill_matrx();
};


