#include "monte_carlo.h"

map<int, float> get_prob_table(float beta){
    /*
     * only 2 energy differences are worth writing down: +2J and +4J
     * all non positive energy diff would yield A = 1
     */
    map<int, float> prob_table;
    for (int i=1; i<3; i++){
        prob_table[2 * i] = exp(-2 * beta * i);
    }
    return prob_table;
}

vector<int> sweep(vector<int> config, float beta, map<int, float> prob_table){
    int neighbour = 0;
    int spin_sum = 0;
    int delta_energy = 0;
    int N = config.size();
    int L = sqrt(N);

    for (int k=0; k < N; k++){
        float rand_num = (float) rand() / RAND_MAX;  // random num ~(0, 1)
        int site = rand_num * N;

        neighbour = (site < N - 1)? site + 1 : site + 1 - N; // right
        spin_sum = config[neighbour];

        neighbour = (site >= 1)? site - 1 : site - 1 + N; // left
        spin_sum += config[neighbour];

        neighbour = (site < N - L)? site + L : site + L - N; // bottom
        spin_sum += config[neighbour];

        neighbour = (site >= L)? site - L : site - L + N; // top
        spin_sum += config[neighbour];

        delta_energy = spin_sum * config[site];

        rand_num = (float) rand() / RAND_MAX;  // random num ~(0, 1)

        if (delta_energy <= 0) { // accept
            config[site] = -config[site];
        } else if (rand_num < prob_table[delta_energy]){
            config[site] = -config[site];
        }
    }
    return config;
}
