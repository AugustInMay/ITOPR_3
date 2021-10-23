//
// Created by AugustInMay on 19/10/2021.
//

#ifndef ITOPR_3_ORDER_PERMUTATION_H
#define ITOPR_3_ORDER_PERMUTATION_H

#include "order_task.h"
#include <iostream>

class order_permutation {
    const order_task& task;
    std::vector<int> gen;

    int time;
    int weight;
public:
    order_permutation(const order_permutation& op);
    order_permutation(const order_task& t);
    order_permutation(const order_task& t, const std::vector<int>& g);

    int get_time() const;
    int get_weight() const;
    int get_gen_size() const;
    const order_task& get_task() const;

    int operator[] (int x) const;
    order_permutation& operator=(const order_permutation& p);
    void push_back(const int& el);
    void pop_back();

    void show_permutation();
};


#endif //ITOPR_3_ORDER_PERMUTATION_H
