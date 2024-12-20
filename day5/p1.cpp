//
// Created by jason on 12/5/24.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// https://stackoverflow.com/a/14266139/5166430
std::vector<int> split(std::string& s, const std::string& delimiter) {
  std::vector<int> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(stoi(token));
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(stoi(s));

  return tokens;
}

int main(int argc, char **argv) {
  //auto filename = "day5/data/test-input.txt";
  auto filename = "day5/data/input.txt";
  std::ifstream infile(filename);
  std::string line;

  std::unordered_map<int, std::unordered_set<int>> before_data;
  std::vector<std::vector<int>> ordering;

  std::stringstream ss;
  bool first = true;
  while (std::getline(infile, line)) {
    if (line.empty()) {
      std::cout << "empty line" << std::endl;
      first = false;
      continue;
    }
    if (first) {
      std::vector<int> tokens = split(line, "|");
      int key = tokens[0];
      int value = tokens[1];
      if (before_data.find(key) == before_data.end()) {
        before_data[key] = std::unordered_set<int>();
      }
      before_data[key].insert(value);
    } else {
      std::vector<int> tokens = split(line, ",");
      ordering.push_back(tokens);
    }
  }

  // start end second last and work backwards to see if we have have wrong ordering
  int middlePageSum = 0;
  for (auto tokens : ordering) {
    bool badOrder = false;
    for (int i = tokens.size() - 1; i >= 0; i--) {
      int currentPage = tokens[i];
      for (int j = i + 1; j < tokens.size(); j++) {
        if (before_data[tokens[j]].find(currentPage) != before_data[tokens[j]].end()) {
          std::cout << tokens[j] << " should come after " << currentPage << std::endl;
          badOrder = true;
          break;
        }
      }
      if (badOrder) {
        break;
      }
    }
    if (!badOrder) {
      int middlePage = tokens[tokens.size() / 2];
      middlePageSum += middlePage;
    }
  }
  std::cout << middlePageSum << std::endl;
}