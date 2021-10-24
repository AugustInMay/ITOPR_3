//
// Created by AugustInMay on 21/10/2021.
//

#include "branching.h"

std::vector<order_permutation> breadth_branching::branch(order_permutation inp) {
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

hybrid_branching::hybrid_branching(abstract_lower_bound *lb, abstract_upper_bound *ub): lb(lb), ub(ub) {}

std::vector<order_permutation> hybrid_branching::branch(order_permutation inp) {
    double cur_ratio = double(lb->count_lb(inp))/ub->count_ub(inp);

    std::vector<order_permutation> ret;
    std::set<int> visited;
    int n = inp.get_task().get_n();

    for(int i=0; i<inp.get_gen_size(); i++){
        visited.emplace(inp[i]);
    }

    for(int i=0; i<n; i++){
        if(visited.find(i) == visited.end()){
            inp.push_back(i);
            double next_ratio = double(lb->count_lb(inp))/ub->count_ub(inp);
            if(next_ratio >= cur_ratio){
                ret.emplace_back(inp);
            }
            inp.pop_back();
        }
    }

    return ret;
}