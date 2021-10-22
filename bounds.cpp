//
// Created by AugustInMay on 21/10/2021.
//

#include "bounds.h"

int base_lower_bound::count_lb(std::vector<int>& gen) {

}

int base_upper_bound::count_ub(std::vector<int>& gen) {
    int n = task.get_n();
    int gen_size = gen.size();

    if(gen_size == n){
        return task.get_cost_from(gen);
    }


    int j = 0;
    std::set<int> visited;
    std::set<int> not_visited;

    gen.reserve(gen_size);

    for(int i=0; i<gen_size; i++){
        visited.emplace(gen[i]);
    }

    for(int i=0; i<n; i++){
        if(visited.find(i) == visited.end()){
            not_visited.emplace(i);
        }
    }

    while(gen.size()+j != n){
        int min_indx;
        int min_dif = INT32_MAX;

        for(auto it = not_visited.begin(); it != not_visited.end(); ) {
            gen.push_back(*it);
            int cur_cost = task.get_cost_from(gen);

            gen.pop_back();
        }

        for(auto it = not_visited.begin(); it != not_visited.end(); ) {
            if(*it % 2 != 0)
                it = not_visited.erase(it);
            else
                ++it;
        }
    }
}