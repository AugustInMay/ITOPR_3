//
// Created by AugustInMay on 21/10/2021.
//

#ifndef ITOPR_3_BRANCHING_H
#define ITOPR_3_BRANCHING_H

#include "order_permutation.h"
#include <set>

class abstract_branching {
public:
    virtual std::vector<order_permutation> branch(order_permutation inp) = 0;
};

class breadth_branching :public abstract_branching{
public:
    std::vector<order_permutation> branch(order_permutation inp) override;
};

class hybrid_branching :public abstract_branching{
public:
    std::vector<order_permutation> branch(order_permutation inp) override;
};

#endif //ITOPR_3_BRANCHING_H
