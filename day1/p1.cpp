//
// Created by jason on 12/1/24.
//

#include "common.h"
#include <algorithm>

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

/**
 * Assumes we run from the folder we build from. I've been testing with a build folder in the root:
 * - cmake ..
 * - make
 * and then ./day1/p1
 */
int main(int argc, char **argv) {
  // auto filename = "day1/data/test_input.txt";
  auto filename = "day1/data/input.txt";
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