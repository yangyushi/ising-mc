#ifndef ANALYSE_H
#define ANALYSE_H
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <cmath>
#include <boost/algorithm/string.hpp>

using namespace std;

float get_m(vector<int> config);    // magnetisation
float get_e(vector<int> config);    // energy
float get_m_average(string fname);  // average magnetisation per spin
float get_c(string fname, float beta);          // heat capacity
float get_chi(string fname, float beta);        // susceptibility
float get_moment(vector<float> data, int order);   // first moment

#endif
