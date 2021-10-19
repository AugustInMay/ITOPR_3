//
// Created by AugustInMay on 18/10/2021.
//

#include "file_manager.h"

void file_manager::read_from_file() {
    std::vector<std::string> row;
    std::string line, word;

    getline(file, line);

    n = std::stoi(line);
    t.reserve(n);
    t0_i.reserve(n);
    tD.reserve(n);

    getline(file, line);
    std::stringstream s(line);

    while (std::getline(s, word, ' ')){
        tD.push_back(std::stoi(word));
    }
}


file_manager::file_manager(const std::string &fn){
    file.open(fn+".txt");
    read_from_file();
}
