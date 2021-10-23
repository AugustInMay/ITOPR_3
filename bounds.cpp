//
// Created by AugustInMay on 21/10/2021.
//

#include "bounds.h"

abstract_lower_bound::abstract_lower_bound(const order_task &task):task(task) {}
abstract_upper_bound::abstract_upper_bound(const order_task &task):task(task) {}

base_lower_bound::base_lower_bound(const order_task &task): abstract_lower_bound(task) {}
base_upper_bound::base_upper_bound(const order_task &task): abstract_upper_bound(task) {}

int base_lower_bound::count_lb(order_permutation op) {
    int prev_weight = op.get_weight();
    int ret = prev_weight;

    std::set<int> visited;
    std::set<int> not_visited;

    for(int i=0; i<op.get_gen_size(); i++){
        visited.emplace(op[i]);
    }

    for(int i=0; i<task.get_n(); i++){
        if(visited.find(i) == visited.end()){
            not_visited.emplace(i);
        }
    }

    for(int it : not_visited) {
        op.push_back(it);

        int cur_weight = op.get_weight();
        ret += (cur_weight - prev_weight);

        op.pop_back();
    }

    return ret;
}

order_permutation base_upper_bound::construct_ub_gen(order_permutation op) {
    std::set<int> visited;
    std::set<int> not_visited;

    for(int i=0; i<op.get_gen_size(); i++){
        visited.emplace(op[i]);
    }

    for(int i=0; i<task.get_n(); i++){
        if(visited.find(i) == visited.end()){
            not_visited.emplace(i);
        }
    }

    while(op.get_gen_size() != task.get_n()){
        int min_indx = -1;
        int min_dif = INT32_MAX;

        for(int it : not_visited) {
            op.push_back(it);
            int cur_time = op.get_time();
            int dest_time = task.get_dest_time(it);

            if(cur_time <= dest_time){
                if(dest_time - cur_time < min_dif){
                    min_dif = dest_time - cur_time;
                    min_indx = it;
                }
            }

            op.pop_back();
        }

        if(min_indx == -1){
            min_indx = *not_visited.begin();
        }

        op.push_back(min_indx);
        auto iter = not_visited.find(min_indx);
        not_visited.erase(iter);
        visited.emplace(min_indx);
    }

    return op;
}

int base_upper_bound::count_ub(order_permutation op) {
    return construct_ub_gen(op).get_weight();
}