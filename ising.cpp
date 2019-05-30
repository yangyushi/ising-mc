/*
 * numerically calculate partition function of 5x5 2D ising model
 */
#include "monte_carlo.h"
#include "analyse.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void dump_config(vector<int> config, string fname){
    // save the configuration as csv file
    ofstream output(fname, ios_base::app);
    int count = 0;
    for (auto item : config) {
        count += 1;
        if (count == config.size()){
            output << item;
        } else {
            output << item << ',';
        }
    }
    output << '\n';
    output.close();
}

void dump_result(vector<float> result, string fname){
    // append an 1D array to a csv file
    ofstream output(fname, ios_base::app);
    int count = 0;
    for (auto item : result) {
        count += 1;
        if (count == result.size()){
            output << item;
        } else {
            output << item << ',';
        }
    }
    output << '\n';
    output.close();
}

void clear_file(string fname){
    ofstream output(fname, ios::out | ios::trunc);
    output.close();
}

int main(){
    string result_name = "result.csv";
    string movie_name = "movie.csv";
    int lattice_size = 25;
    int before_eq = 2000;
    int sample_sweep = 2000;
    vector<float> result;
    clear_file(result_name);
    clear_file(movie_name);
    
    for (float T = 0.2; T < 4.0; T += 0.2){
        float beta = 1 / T;
        map<int, float> p_table = get_prob_table(beta);
        string config_name = string("configure_beta_") + to_string(beta) + string(".csv");
        vector<int> config(lattice_size * lattice_size, 1);
        clear_file(config_name);

        for (int i=0; i<before_eq; i++){
            config = sweep(config, beta, p_table);
            if (i % 100 == 0) dump_config(config, movie_name);
        }  // from 0K temperature to equilibrium

        for (int i=0; i<sample_sweep; i++){
            config = sweep(config, beta, p_table);
            dump_config(config, config_name);
        }  // getting results in equilibrium state

        float m = get_m_average(config_name);
        float c = get_c(config_name, beta);
        cout << "T = " << T << "\tm = " << m << "\tc = " << c << '\n';
        result.clear();
        result.push_back(T);
        result.push_back(m);
        result.push_back(c);
        dump_result(result, result_name);
    }
    return 0;
}
