//
// Created by AugustInMay on 18/10/2021.
//

#include "order_task.h"

order_task::order_task(const int &n):n(n) {}

void order_task::read_from_file(const file_manager& fm) {
    tD = fm.get_tD();
    t0_i = fm.get_t0_i();
    t = fm.get_t();
}

int order_task::get_cost_from(const std::vector<int>& x) const{
    int gen_time = 0;
    int overlap = 0;

    gen_time += t0_i[x[0]];

    if(gen_time > tD[x[0]]){
        overlap++;
    }

    for(int i=0; i<n-1; i++){
        gen_time += t[x[i]][x[i+1]];

        if(gen_time > tD[x[i+1]]){
            overlap++;
        }
    }

    return overlap;
}

int order_task::get_time_from(const std::vector<int> &x) const {
    int gen_time = 0;

    gen_time += t0_i[x[0]];

    for(int i=0; i<x.size()-1; i++){
        gen_time += t[x[i]][x[i+1]];
    }

    return gen_time;
}

int order_task::get_n() const{
    return n;
}

int order_task::get_dest_time(const int &indx) const{
    return tD[indx];
}