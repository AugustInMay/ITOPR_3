//
// Created by AugustInMay on 21/10/2021.
//

#include "branching.h"

int breadth_branching::branch(const std::vector<order_permutation>& inp) {
    int indx = 0;
    int gen_size = inp[0].get_gen_size();

    for(int i=0; i<inp.size(); i++){
        if(inp[i].get_gen_size() < gen_size){
            indx = i;
            gen_size = inp[i].get_gen_size();
        }
    }

    return indx;
}

hybrid_branching::hybrid_branching(const std::vector<int>& lb, const std::vector<int>& ub): lb(lb), ub(ub) {}

int hybrid_branching::branch(const std::vector<order_permutation>& inp) {
    int indx = 0;
    double cur_ratio = double(lb[0])/ub[0];

    for(int i=0; i<inp.size(); i++){
        double next_ratio = double(lb[i])/ub[i];
        if(next_ratio >= cur_ratio){
            indx = i;
            cur_ratio = next_ratio;
        }
    }

    return indx;
}

std::vector<order_permutation> neighbourhood(order_permutation inp){
    std::vector<order_permutation> ret;
    std::set<int> visited;
    int n = inp.get_task().get_n();

    for(int i=0; i<inp.get_gen_size(); i++){
        visited.emplace(inp[i]);
    }

    for(int i=0; i<n; i++){
        if(visited.find(i) == visited.end()){
            inp.push_back(i);
            ret.emplace_back(inp);
            inp.pop_back();
        }
    }

    return ret;
}