//
// Created by AugustInMay on 21/10/2021.
//

#include "bounds.h"

int base_lower_bound::count_lb(const order_permutation &perm) {

}

int base_upper_bound::count_ub(const order_permutation &perm) {
    const order_task& task(perm.get_task());
    int n = task.get_n();
    int gen_size = perm.get_gen_size();

    if(gen_size == n){
        return perm.get_cost();
    }


    int j = 0;
    std::vector<int> gen;
    std::set<int> visited;
    std::set<int> not_visited;

    gen.reserve(gen_size);

    for(int i=0; i<gen_size; i++){
        gen.push_back(perm[i]);
        visited.emplace(perm[i]);
    }

    for(int i=0; i<task.get_n(); i++){
        if(visited.find(i) == visited.end()){
            not_visited.emplace(i);
        }
    }

//    while(gen.size()+j != n){
//        for(auto it = c.begin(); it != c.end(); ) {
//            if(*it % 2 != 0)
//                it = c.erase(it);
//            else
//                ++it;
//        }
//
//    }
}