//
// Created by AugustInMay on 18/10/2021.
//

#include "file_manager.h"

void file_manager::read_from_file() {
    std::vector<std::string> row;
    std::string line, word;

    getline(file, line);

    n = std::stoi(line);
    t.resize(n);
    t0_i.reserve(n);
    tD.reserve(n);

    getline(file, line);
    std::stringstream s(line);

    while (std::getline(s, word, ' ')) {
        tD.push_back(std::stoi(word));
    }


    getline(file, line);
    s = std::stringstream(line);
    std::getline(s, word, '\t');

    while (std::getline(s, word, '\t')) {
        t0_i.push_back(std::stoi(word));
    }


    for(int i=0; i<n; i++){
        t[i].reserve(n);

        getline(file, line);
        s = std::stringstream(line);
        std::getline(s, word, '\t');
        while (std::getline(s, word, '\t')){
            t[i].push_back(std::stoi(word));
        }
    }
}


file_manager::file_manager(const std::string &fn){
    file.open(fn+".txt");
    read_from_file();
}


std::vector<int> file_manager::get_tD() const{
    return tD;
}

std::vector<int> file_manager::get_t0_i() const{
    return t0_i;
}

std::vector<std::vector<int>> file_manager::get_t() const{
    return t;
}