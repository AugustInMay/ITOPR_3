//
// Created by AugustInMay on 18/10/2021.
//

#ifndef ITOPR_3_ORDER_TASK_H
#define ITOPR_3_ORDER_TASK_H

#include <vector>
#include "file_manager.h"

class order_task {
    const int n;
    std::vector<int> tD;
    std::vector<int> t0_i;
    std::vector<std::vector<int>> t;
public:
    order_task(const int& n);

    void read_from_file(file_manager fm);

    int get_cost_from(const std::vector<int> x);
};


#endif //ITOPR_3_ORDER_TASK_H
