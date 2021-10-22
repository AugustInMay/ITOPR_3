//
// Created by AugustInMay on 21/10/2021.
//

#ifndef ITOPR_3_BOUNDS_H
#define ITOPR_3_BOUNDS_H

#include "order_permutation.h"
#include <set>

class abstract_lower_bound {
    virtual int count_lb(const order_permutation& perm) = 0;
};

class abstract_upper_bound {
    virtual int count_ub(const order_permutation& perm) = 0;
};

class base_lower_bound:abstract_lower_bound {
    int count_lb(const order_permutation& perm) override;
};

class base_upper_bound:abstract_upper_bound {
    int count_ub(const order_permutation& perm) override;
};


#endif //ITOPR_3_BOUNDS_H
