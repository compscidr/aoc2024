//
// Created by jason on 12/3/24.
//
#include <fstream>
#include <iostream>

/**
 * Checks that we actually have a number followed by ')' because stoi and atoi both blindly convert trash at the end
 */
bool checkNumber(std::string input) {
  for (auto ch : input) {
    if (ch < '0' || ch > '9') {
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv) {
  //auto filename = "day3/data/test-input.txt";
  auto filename = "day3/data/input.txt";
  std::ifstream input(filename);
  std::string buffer;
  std::string line;

  // read file fully in case there is input split across lines
  while (std::getline(input, line)) {
    buffer.append(line);
  }
  std::cout << buffer << std::endl;

  int total = 0;
  int currentPos = 0;
  size_t pos;
  do {
    pos = buffer.find("mul(", currentPos, 4);
    if (pos == std::string::npos) {
      break;
    }
    currentPos = pos + 4;
    size_t comma_pos = buffer.find(",", currentPos, 1);
    if (comma_pos == std::string::npos) {
      // didn't get what we want (a comma)
      currentPos = pos + 1;
      continue;
    }

    int n1;
    try {
      if (!checkNumber(buffer.substr(currentPos, comma_pos - currentPos))) {
        std::cout << "not number followed by ')'" << std::endl;
        continue;
      }
      n1 = stoi(buffer.substr(currentPos, comma_pos - currentPos));
      std::cout << "n1: " << n1 << std::endl;
    } catch (const std::invalid_argument& e) {
      std::cout << "failed to parse number: " << buffer.substr(currentPos, comma_pos - currentPos) << std::endl;
      // currentPos = currentPos + 1; // advance one and try to start again (in case we start we have mul(mul(),)
      continue;
    }
    currentPos = currentPos + (comma_pos - currentPos) + 1; // advance over the number and the comma

    size_t bracket_pos = buffer.find(")", currentPos, 1);
    if (bracket_pos == std::string::npos) {
      // currentPos = currentPos + 1;
      continue;
    }

    int n2;
    try {
      if (!checkNumber(buffer.substr(currentPos, bracket_pos - currentPos))) {
        std::cout << "not number followed by ')'" << std::endl;
        continue;
      }
      n2 = stoi(buffer.substr(currentPos, bracket_pos - currentPos));
      std::cout << "n2: " << n2 << std::endl;
    } catch (const std::invalid_argument& e) {
      std::cout << "failed to parse number: " << buffer.substr(currentPos, bracket_pos - currentPos) << std::endl;
      // currentPos = currentPos + 1; // advance one and try to start again (in case we start we have mul(mul(),)
      continue;
    }

    total += n1 * n2;
    std::cout << "currentPos: " << currentPos << std::endl;

  } while (pos != std::string::npos);

  std::cout << "total: " << total << std::endl;
}