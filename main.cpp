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

    std::vector<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};

    // words2 == words1
    std::vector<std::string> words2(words1.begin(), words1.end()-1);
    for(int i=0; i<words2.size(); i++){
        std::cout<<words2[i];
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
