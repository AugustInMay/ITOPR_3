//
// Created by AugustInMay on 21/10/2021.
//

#ifndef ITOPR_3_BOUNDS_H
#define ITOPR_3_BOUNDS_H

#include "order_permutation.h"
#include <set>
#include <algorithm>

class abstract_lower_bound {
protected:
    const order_task& task;

    abstract_lower_bound(const order_task& task);
public:
    virtual int count_lb(order_permutation op) = 0;
};

class abstract_upper_bound {
protected:
    const order_task& task;
    
    abstract_upper_bound(const order_task& task);
public:
    virtual order_permutation construct_ub_gen(order_permutation op) = 0;
    virtual int count_ub(order_permutation op) = 0;
};

class base_lower_bound:public abstract_lower_bound {
public:
    base_lower_bound(const order_task& task);

    int count_lb(order_permutation op) override;
};

class exclusive_lower_bound:public abstract_lower_bound{
public:
    exclusive_lower_bound(const order_task& task);

    int count_lb(order_permutation op) override;
};

class base_upper_bound:public abstract_upper_bound {
public:
    base_upper_bound(const order_task& task);

    order_permutation construct_ub_gen(order_permutation op) override;
    int count_ub(order_permutation op) override;
};

class ls_upper_bound:public abstract_upper_bound{
    int par;
public:
    ls_upper_bound(const order_task& task, const int& p);

    order_permutation construct_ub_gen(order_permutation op) override;
    int count_ub(order_permutation op) override;
};


#endif //ITOPR_3_BOUNDS_H
