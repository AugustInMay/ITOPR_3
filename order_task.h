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

    void read_from_file(const file_manager& fm);

    int get_n() const;
    int get_dest_time(const int& indx) const;
    int get_t0(const int& indx) const;
    int get_t(const int& i, const int& j) const;
    int get_cost_from(const std::vector<int>& x) const;
    int get_time_from(const std::vector<int>& x) const;
};


#endif //ITOPR_3_ORDER_TASK_H
