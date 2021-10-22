//
// Created by AugustInMay on 19/10/2021.
//

#include "order_permutation.h"

order_permutation::order_permutation(const order_permutation &t):task(t.task), gen(t.gen), cost(t.cost), upper_bound(t.upper_bound),
                                                                 lower_bound(t.lower_bound) {}

order_permutation::order_permutation(const order_task &t):task(t) {
    gen.reserve(task.get_n());
}

order_permutation::order_permutation(const order_task &t, const std::vector<int> &g):task(t), gen(g) {
    count_cost();
}


void order_permutation::count_cost() {
    cost = task.get_cost_from(this->gen);
}

int order_permutation::get_cost() const{
    return cost;
}

int order_permutation::get_gen_size() const{
    return static_cast<int>(gen.size());
}

int order_permutation::get_lower_bound(){
    return lower_bound.count_lb(this);
}

int order_permutation::get_upper_bound() {
    return upper_bound.count_ub(this);
}

const order_task &order_permutation::get_task() const {
    return task;
}

void order_permutation::link_bounds(abstract_lower_bound lb, abstract_upper_bound ub) {
    lower_bound = lb;
    upper_bound = ub;
}

int order_permutation::operator[](int x) const{
    return gen[x];
}

void order_permutation::change_indx(const int &indx, const int &val) {
    if(indx >= task.get_n()){
        return;
    }

    int g_size = static_cast<int>(gen.size());
    while (g_size-1 < indx){
        gen.push_back(g_size);
        g_size = static_cast<int>(gen.size());
    }
    gen[indx] = val;
}