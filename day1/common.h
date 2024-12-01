//
// Created by jason on 12/1/24.
//

#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <iostream>

std::pair<std::vector<int>, std::vector<int>> processInputFile(const std::string& fileName);
void printLists(std::pair<std::vector<int>, std::vector<int>> lists);

#endif //COMMON_H
