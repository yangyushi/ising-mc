/*
 * numerically calculate partition function of 5x5 2D ising model
 */
#include "monte_carlo.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void dump_config(vector<int> config, string fname){
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

void clear_file(string fname){
    ofstream output(fname, ios::out | ios::trunc);
    output.close();
}

int main(){
    float beta = 0.5;
    int before_eq = 20000;
    int sample_sweep = 1000;
    string file_name = "configure.csv";

    vector<int> config(400, 1); // 5x5 lattice

    map<int, float> p_table = get_prob_table(beta);

    clear_file(file_name);

    for (int i=0; i<before_eq; i++){
        config = sweep(config, beta, p_table);
    }

    for (int i=0; i<sample_sweep; i++){
        config = sweep(config, beta, p_table);
        dump_config(config, file_name);
    }
    return 0;
}
