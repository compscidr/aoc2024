//
// Created by jason on 12/1/24.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

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

/**
 * Given two sorted lists ordered from smallest to largest, Determines the distance between each pair, and then
 * sums the distance. Assumes the two lists are the same size and are already sorted.
 *
 * @return the total distance
 */
int getTotalDistance(std::pair<std::vector<int>, std::vector<int>> lists)
{
  int totalDistance = 0;
  int position = 0;
  while (position < lists.first.size())
  {
    int n1 = lists.first[position];
    int n2 = lists.second[position];
    int distance = abs(n1 - n2);
    totalDistance += distance;
    position++;
  }
  return totalDistance;
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  // auto filename = "day1/test_input.txt";
  auto filename = "day1/input.txt";
  auto numberLists = processInputFile(filename);

  // std::cout << "LIST: " << std::endl;
  // printLists(numberLists);

  std::sort(numberLists.first.begin(), numberLists.first.end());
  std::sort(numberLists.second.begin(), numberLists.second.end());

  // std::cout << "SORTED LIST: " << std::endl;
  // printLists(numberLists);

  int totalDistance = getTotalDistance(numberLists);
  std::cout << "Total Distance: " << totalDistance << std::endl;

  return 0;
}