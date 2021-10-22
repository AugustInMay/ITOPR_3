//
// Created by AugustInMay on 21/10/2021.
//

#include "branching.h"

std::vector<order_permutation> breadth_branching::branch(const order_permutation &inp) {
    std::vector<int> gen;
    std::vector<order_permutation> ret;
    std::set<int> visited;
    int gen_size = inp.get_gen_size();

    gen.reserve(gen_size);

    for(int i=0; i<gen_size; i++){
        gen.push_back(inp[i]);
        visited.emplace(inp[i]);
    }

    const order_task& task(inp.get_task());

    for(int i=0; i<task.get_n(); i++){
        if(visited.find(i) == visited.end()){
            gen.push_back(i);
            ret.emplace_back(task, gen);
            gen.pop_back();
        }
    }

    return ret;
}

std::vector<order_permutation> hybrid_branching::branch(const order_permutation &inp) {

}