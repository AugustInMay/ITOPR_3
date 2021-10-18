//
// Created by AugustInMay on 18/10/2021.
//

#include "file_manager.h"

void file_manager::read_from_file() {

}


file_manager::file_manager(const std::string &fn):file_name(fn+".txt") {
    read_from_file();
}
