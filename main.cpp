#include <iostream>
#include "file_manager.h"
#include "order_permutation.h"

int main() {
    file_manager fm("task_2_01_n3");
    order_task task(3);
    task.read_from_file(fm);
    order_permutation perm(task);
    perm.change_indx(0, 3);
    perm.change_indx(1, 4);
    std::cout<<perm[1];

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
