#include "analyse.h"

float get_m(vector<int> config){
    float m_tot = 0.0;
    for (auto s:config){
        m_tot += s;
    }
    return m_tot / config.size();
}

float get_e(vector<int> config){
    float energy = 0;
    int N = config.size();
    int L = sqrt(N);
    int neighbour = 0;
    int spin_nn = 0;

    for (int site=0; site < N; site++){
        neighbour = (site < N - 1)? site + 1 : site + 1 - N; // right
        spin_nn = config[neighbour];

        neighbour = (site >= 1)? site - 1 : site - 1 + N; // left
        spin_nn += config[neighbour];

        neighbour = (site < N - L)? site + L : site + L - N; // bottom
        spin_nn += config[neighbour];

        neighbour = (site >= L)? site - L : site - L + N; // top
        spin_nn += config[neighbour];

        energy += -spin_nn * config[site];
    }
    return energy / 2;
}


float get_m_average(string fname){
   ifstream ist {fname};
   string line;
   vector<string> config_str;
   vector<int> config;
   int config_num = 0;
   float m_tot = 0.0;

   while (getline(ist, line)){
       config_str.clear();
       config.clear();
       boost::split(config_str, line, boost::is_any_of(",\t"));
       // this looks very wrong
       for (auto s:config_str) {
           config.push_back(stoi(s));
       }
       m_tot += get_m(config);
       config_num += 1;
   }
   return m_tot / config_num;
}

float get_moment(vector<float> data, int order){
    double result = 0;
    int count = 0;
    for (auto num : data){
        result += pow(num, order);
        count += 1;
    }
    return result / count;
}

float get_c(string fname, float beta){
    float e1 = 0;
    float e2 = 0;
    float var = 0;
    int N = 0;
    ifstream ist {fname}; string line;
    vector<string> config_str;
    vector<int> config;
    vector<float> energies;

    while (getline(ist, line)){
        config_str.clear();
        config.clear();
        boost::split(config_str, line, boost::is_any_of(",\t"));
        for (auto s:config_str) {
            config.push_back(stoi(s));
        }
        N = config.size();
        energies.push_back(get_e(config));
    }

    e1 = get_moment(energies, 1);
    e2 = get_moment(energies, 2);
    var = e2 - pow(e1, 2); // variance of energy
    return var * pow(beta, 2) / N;  // c = var / (N * T^2)
}
