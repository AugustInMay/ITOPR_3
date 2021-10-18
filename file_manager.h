//
// Created by AugustInMay on 18/10/2021.
//

#ifndef ITOPR_3_FILE_MANAGER_H
#define ITOPR_3_FILE_MANAGER_H

#include <string>
#include <vector>

class file_manager {
    const std::string file_name;

    std::vector<int> tD;
    std::vector<int> t0_i;
    std::vector<std::vector<int>> t;

    void read_from_file();
public:
    file_manager(const std::string& fn);

    std::vector<int> get_tD();
    std::vector<int> get_t0_i();
    std::vector<std::vector<int>> get_t();
};


#endif //ITOPR_3_FILE_MANAGER_H
