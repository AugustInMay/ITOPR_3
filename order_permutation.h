//
// Created by AugustInMay on 19/10/2021.
//

#ifndef ITOPR_3_ORDER_PERMUTATION_H
#define ITOPR_3_ORDER_PERMUTATION_H

#include "order_task.h"
#include "bounds.h"

class order_permutation {
    const order_task& task;
    std::vector<int> gen;
    abstract_lower_bound* lower_bound;
    abstract_upper_bound* upper_bound;

    int cost;
public:
    order_permutation(const order_permutation& op);
    order_permutation(const order_task& t);
    order_permutation(const order_task& t, const std::vector<int>& g);

    void count_cost();
    int get_lower_bound();
    int get_upper_bound();
    int get_cost() const;
    int get_gen_size() const;
    const order_task& get_task() const;

    void link_bounds(abstract_lower_bound* lb, abstract_upper_bound* ub);
    int operator[] (int x) const;
    void change_indx(const int& indx, const int& val);
};


#endif //ITOPR_3_ORDER_PERMUTATION_H
