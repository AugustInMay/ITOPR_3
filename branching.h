//
// Created by AugustInMay on 21/10/2021.
//

#ifndef ITOPR_3_BRANCHING_H
#define ITOPR_3_BRANCHING_H

#include "bounds.h"

class abstract_branching {
public:
    virtual int branch(const std::vector<order_permutation>& inp) = 0;
};

class breadth_branching :public abstract_branching{
public:
    int branch(const std::vector<order_permutation>& inp) override;
};

class hybrid_branching :public abstract_branching{
    const std::vector<int>& lb;
    const std::vector<int>& ub;
public:
    hybrid_branching(const std::vector<int>& lb, const std::vector<int>& ub);

    int branch(const std::vector<order_permutation>& inp) override;
};

std::vector<order_permutation> neighbourhood(order_permutation inp);

#endif //ITOPR_3_BRANCHING_H
