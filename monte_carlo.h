#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;

map<int, float> get_prob_table(float beta);
vector<int> sweep(vector<int> config, float beta, map<int, float> prob_table);

#endif
