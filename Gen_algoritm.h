#pragma once
#include <vector>
#include <iostream>

using namespace std;

struct individ
{
	vector<int> chrom;
	double len_way;
};

class Gen_algoritm
{
public:
	Gen_algoritm(vector<vector<double>> matrx, int size_populate, int seed = 0);
	const double calculate_len(vector<vector<double>> matrx, vector<int> chrom);
	const vector<double> prob_population(vector<individ> populat);
	const bool get_ber_destrib(double p);
	const vector<individ> selection_population(vector<individ> population);
	void run_gen_algoritm(int num_gen);
	void print_generations();
	void write_decision();
private:
	int n;
	vector<vector<individ>> generations;
	vector<vector<double>> matrx_dist;
	int seed;
	void init_gen(int m);
	int get_par(vector<double> list_prob);
	individ cross_par(individ par_1, individ par_2);
	individ mutation(individ ind);
};

