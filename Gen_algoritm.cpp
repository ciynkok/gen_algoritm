#include "Gen_algoritm.h"
#include "Task_Kom.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;


Gen_algoritm::Gen_algoritm(vector<vector<double>> matrx, int size_populate, int seed)
{
	matrx_dist = matrx;
	n = matrx.size();
	this->seed = seed;
	init_gen(size_populate);
}

const double Gen_algoritm::calculate_len(vector<vector<double>> matrx, vector<int> chrom)
{
	double len = 0;
	for (int j = 0; j < n - 1; j++)
	{
		if (j == 0 or j == n - 2)
		{
			len += matrx[0][chrom[j]];
		}
		else
		{
			int from = chrom[j];
			int to = chrom[j + 1];
			len += matrx[from][to];
		}
	}
	return len;
}

const vector<double> Gen_algoritm::prob_population(vector<individ> populat)
{
	double sum = 0;
	vector<double> res(populat.size());

	for (int i = 0; i < populat.size(); i++)
	{
		sum += 1 / populat[i].len_way;
	}

	for (int i = 0; i < populat.size(); i++)
	{
		res[i] = 1 / populat[i].len_way / sum;
	}

	return res;
}

const bool Gen_algoritm::get_ber_destrib(double p)
{
	bernoulli_distribution dist(p);
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

const vector<individ> Gen_algoritm::selection_population(vector<individ> population)
{
	int size = population.size();
	double min_val;
	int index;
	vector<individ> res;
	individ b;

	for (int i = 0; i < size / 2; i++)
	{
		min_val = population[i].len_way;
		index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (population[j].len_way < min_val)
			{
				min_val = population[j].len_way;
				index = j;
			}
		}
		b = population[index];
		population[index] = population[i];
		population[i] = b;
		res.push_back(population[i]);
	}
	return res;
}

void Gen_algoritm::run_gen_algoritm(int num_gen)
{
	vector<individ> population = generations[0];
	vector<double> list_prob;
	for (int i = 0; i < num_gen; i++)
	{
		int par_1, par_2;
		individ ind;
		list_prob = prob_population(population);
		for (int j = 0; j < list_prob.size(); j++)
		{
			par_1 = get_par(list_prob);
			par_2 = get_par(list_prob);
			while (par_1 == par_2)
			{
				par_2 = get_par(list_prob);
			}
		
			ind = cross_par(population[par_1], population[par_2]);
			ind = mutation(ind);
			population.push_back(ind);
		}
		
		population = selection_population(population);
		generations.push_back(population);
		cout << "gen: " << i + 1 << endl;
	}
}

void Gen_algoritm::print_generations()
{
	cout << generations.size() << endl;
	for (int i = 0; i < generations.size(); i++)
	{
		cout << "gen: " << i + 1 << endl;
		for (int j = 0; j < generations[i].size(); j++)
		{
			cout << generations[i][j].len_way << " " << generations[i][j].chrom.size() << endl;
		}
		cout << endl;
	}
}

void Gen_algoritm::write_decision()
{
	ofstream file("decision.csv");
	if (!file.is_open()) {
		std::cerr << "Error opening file: decision.csv" << std::endl;
		return;
	}
	
	individ ind = selection_population(generations.back())[0];
	cout << "decision: " << ind.len_way << endl;
	for (int i = 0; i < ind.chrom.size() - 1; i++)
	{
		file << ind.chrom[i] << ',';
	}
	file << ind.chrom.back();
	file.close();
}

void Gen_algoritm::init_gen(int m)
{
	vector<int> points;
	vector<individ> population;
	random_device rd;
	mt19937 g(rd());

	for (int i = 1; i < n; i++)
	{
		points.push_back(i);
	}

	for (int i = 0; i < m; i++)
	{
		individ ind;
		vector<int> chrom = points;

		shuffle(chrom.begin(), chrom.end(), g);
		ind.chrom = chrom;
		
		ind.len_way = calculate_len(matrx_dist, chrom);

		population.push_back(ind);
	}

	generations.push_back(population);
}

int Gen_algoritm::get_par(vector<double> list_prob)
{
	while (1)
	{
		for (int i = 0; i < list_prob.size(); i++)
		{
			if (get_ber_destrib(list_prob[i]))
			{
				return i;
			}
		}
	}
}

individ Gen_algoritm::cross_par(individ par_1, individ par_2)
{
	individ res;
	int rand_i = Task_Kom::generate_rand(0, n - 3, seed);
	bool left_or_right = Task_Kom::generate_rand(0, 1, seed);
	int index;
	int j = 0;

	if (left_or_right)
	{
		individ b = par_1;
		par_1 = par_2;
		par_2 = b;
	}

	for (int i = 0; i < n - 1; i++)
	{
		int point;
		index = 0;
		if (i < rand_i + 1)
		{
			point = par_1.chrom[i];
		}
		else
		{
			while (j < res.chrom.size())
			{

				if (par_2.chrom[index] == res.chrom[j])
				{
					index += 1;
					j = 0;
				}
				else
				{
					j++;
				}
			}
			point = par_2.chrom[index];
			index = 0;
			j = 0;
		}

		res.chrom.push_back(point);
	}

	res.len_way = calculate_len(matrx_dist, res.chrom);
	return res;
}

individ Gen_algoritm::mutation(individ ind)
{
	int i1 = Task_Kom::generate_rand(0, ind.chrom.size() - 1, seed);
	int i2 = Task_Kom::generate_rand(0, ind.chrom.size() - 1, seed);
	while (i1 == i2)
	{
		i2 = Task_Kom::generate_rand(0, ind.chrom.size() - 1, seed);
	}
	int b = ind.chrom[i1];
	ind.chrom[i1] = ind.chrom[i2];
	ind.chrom[i2] = b;
	return ind;
}
