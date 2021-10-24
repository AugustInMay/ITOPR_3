//
// Created by AugustInMay on 21/10/2021.
//

#ifndef ITOPR_3_BRANCHING_H
#define ITOPR_3_BRANCHING_H

#include "bounds.h"

class abstract_branching {
public:
    virtual std::vector<order_permutation> branch(order_permutation inp) = 0;
};

class breadth_branching :public abstract_branching{
public:
    std::vector<order_permutation> branch(order_permutation inp) override;
};

class hybrid_branching :public abstract_branching{
    abstract_lower_bound* lb;
    abstract_upper_bound* ub;
public:
    hybrid_branching(abstract_lower_bound* lb, abstract_upper_bound* ub);

    std::vector<order_permutation> branch(order_permutation inp) override;
};

#endif //ITOPR_3_BRANCHING_H
