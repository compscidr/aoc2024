//
// Created by jason on 12/1/24.
//
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

std::vector<int> parseReport(std::string line) {
  std::vector<int> result;
  std::stringstream ss;
  ss << line;
  int n;
  while (ss >> n) {
    result.push_back(n);
  }
  return result;
}

std::vector<std::vector<int>> parseFile(std::string filename) {
    std::vector<std::vector<int>> result;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> level = parseReport(line);
        result.push_back(level);
    }
    return result;
}

void printReport(std::vector<int> report) {
  std::cout << "Report: " << report.size() << std::endl;
  for (auto n : report) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

// assume report has at least two levels
bool increasing(std::vector<int> report) {
  if (report[0] < report[1]) {
    return true;
  }
  return false;
}

bool isSafe(std::vector<int> report) {
  int maxDiff = 3;
  bool fail = false;
  bool isIncreasing = increasing(report);
  int lastValue = report[0];
  for (int i = 1; i < report.size(); i++) {
    if (abs(report[i] - lastValue) > maxDiff) {
      std::cout << "LV: " << lastValue << " CV: " << report[i] << " exceeded maxdiff: " << maxDiff << std::endl;
      fail = true;
      break;
    }
    if (isIncreasing) {
      if (report[i] < lastValue) {
        std::cout << "LV: " << lastValue << " CV: " << report[i] << ", but should be increasing" << std::endl;
        fail = true;
        break;
      }
    } else {
      if (report[i] > lastValue) {
        std::cout << "LV: " << lastValue << " CV: " << report[i] << ", but should be decreasing" << std::endl;
        fail = true;
        break;
      }
    }
    if (lastValue == report[i]) {
      std::cout << "LV: " << lastValue << " CV: " << report[i] << " - can't have equal values" << std::endl;
      fail = true;
      break;
    }
    lastValue = report[i];
  }

  if (!fail) {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char **argv) {
  //auto filename = "day2/data/test-input.txt";
  auto filename = "day2/data/input.txt";
  auto result = parseFile(filename);

  int goodReports = 0;
  for (auto report : result) {
    printReport(report);

    if (isSafe(report)) {
      goodReports++;
    } else {
      // so dumb, but lets just remove a level one a time from the report and see if it becomes safe

      // this is the index we'll skip
      for (int i = 0; i < report.size(); i++) {
        auto newReport = std::vector<int>();
        for (int j = 0; j < report.size(); j++) {
          if (j != i) {
            newReport.push_back(report[j]);
          }
        }
        printReport(newReport);
        if (isSafe(newReport)) {
          goodReports++;
          break;
        }
      }
    }
  }
  std::cout << "Good reports: " << goodReports << std::endl;
  return 0;
}