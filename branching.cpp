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

std::vector<order_permutation> hybrid_branching::branch(order_permutation inp) {

}