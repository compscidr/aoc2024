//
// Created by jason on 12/1/24.
//
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * Given the filename, read a file which has two columns of numbers separated by some amount of whitespace (more than
 * a single space), and return two vectors of numbers.
 *
 * @param fileName the file to process
 * @return a vector from each column in the file.
 */
std::pair<std::vector<int>, std::vector<int>> processInputFile(const std::string& fileName) {
    std::vector<int> column1;
    std::vector<int> column2;
    std::ifstream file(fileName);
    std::string line;
    std::stringstream ss;
    int n1;
    int n2;
    while (std::getline(file, line)) {
        ss << line;

        // get first number from line
        ss >> n1;
        column1.push_back(n1);

        // get second number from line
        ss >> n2;
        column2.push_back(n2);
        ss.clear();
    }
    return std::make_pair(column1, column2);
}

void printLists(std::pair<std::vector<int>, std::vector<int>> lists) {
    for (int i = 0; i < lists.first.size(); i++) {
        std::cout << lists.first[i] << " " << lists.second[i] << std::endl;
    }
}