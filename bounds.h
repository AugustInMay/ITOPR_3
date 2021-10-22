//
// Created by AugustInMay on 21/10/2021.
//

#ifndef ITOPR_3_BOUNDS_H
#define ITOPR_3_BOUNDS_H

#include "order_task.h"
#include <set>

class abstract_lower_bound {
protected:
    const order_task& task;
    abstract_lower_bound(const order_task& task);
public:
    virtual int count_lb(std::vector<int>& gen) = 0;
};

class abstract_upper_bound {
protected:
    const order_task& task;
    abstract_upper_bound(const order_task& task);
public:
    virtual int count_ub(std::vector<int>& gen) = 0;
};

class base_lower_bound:abstract_lower_bound {
public:
    int count_lb(std::vector<int>& gen) override;
};

class base_upper_bound:abstract_upper_bound {
public:
    int count_ub(std::vector<int>& gen) override;
};


#endif //ITOPR_3_BOUNDS_H
