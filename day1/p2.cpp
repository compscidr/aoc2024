//
// Created by jason on 12/1/24.
//

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <unordered_set>

int main(int argc, char **argv) {
    // auto filename = "day1/data/test_input.txt";

    auto filename = "day1/data/input.txt";

    std::ifstream file(filename);
    std::string line;
    std::stringstream ss;
    // we separately keep track of the left and right frequencies because the similarity is:
    // left frequency * (value * right frequency)
    std::map<int, int> rightFrequency;
    std::map<int, int> leftFrequency;
    int n1;
    int n2;
    while (std::getline(file, line))
    {
        ss << line;
        ss >> n1;
        ss >> n2;

        if (leftFrequency.find(n1) == leftFrequency.end()) {
            leftFrequency[n1] = 1;
        } else {
            int frequency = leftFrequency[n1];
            leftFrequency[n1] = frequency + 1;
        }

        if (rightFrequency.find(n2) == rightFrequency.end()) {
            rightFrequency[n2] = 1;
        } else {
            int frequency = rightFrequency[n2];
            rightFrequency[n2] = frequency + 1;
        }
        ss.clear();
    }

    int simularityScore = 0;
    for (const auto &it : leftFrequency) {
        int key = it.first;
        int lf = it.second;
        int rf = rightFrequency[key];

        // std::cout << "KEY: " << key << " LF: " << lf << " RF: " << rf << std::endl;
        int score = lf * rf * key;
        simularityScore += score;
    }
    std::cout << simularityScore << std::endl;
}
