//
// Created by jason on 12/3/24.
//
#include <fstream>
#include <iostream>
#include <set>

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

bool isEnabled(int currentPos, std::set<int> dos, std::set<int> donts) {
  // get closest "do" before us
  int latestDo;
  for (auto n : dos) {
    if ((n > latestDo) && (n < currentPos)) {
      latestDo = n;
    }
  }

  // get closest "dont" before us
  int latestDont = -1;
  for (auto n : donts) {
    if ((n > latestDont) && (n < currentPos)) {
      latestDont = n;
    }
  }

  std::cout << "current pos: " << currentPos << " latestDo: " << latestDo << " latestDont: " << latestDont << std::endl;

  // see which one is bigger
  if (latestDont == -1) {
    return true;
  }
  if (latestDo > latestDont) {
    return true;
  }
  return false;
}

int main(int argc, char **argv) {
  //auto filename = "day3/data/test-input2.txt";
  auto filename = "day3/data/input.txt";
  std::ifstream input(filename);
  std::string buffer;
  std::string line;

  // read file fully in case there is input split across lines
  while (std::getline(input, line)) {
    buffer.append(line);
  }
  std::cout << buffer << std::endl;

  std::set<int> dos;
  dos.insert(0);
  size_t dopos = 0;
  do {
    // this will just get the next do / dont, but there could be mul instructions before them
    size_t _do = buffer.find("do()", dopos, 4);
    if (_do != std::string::npos) {
      //std::cout << "do: " << _do << std::endl;
      dos.insert(_do);
      dopos = _do + 4;
    } else {
      break;
    }
    //std::cout << "dopos: " << dopos << std::endl;
  } while (dopos != std::string::npos);

  std::cout << "Dos: ";
  for (auto n : dos) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  std::set<int> donts;
  size_t dontpos = 0;
  do {
    // this will just get the next do / dont, but there could be mul instructions before them
    size_t _dont = buffer.find("don't()", dontpos, 6);
    if (_dont != std::string::npos) {
      //std::cout << "dont: " << _dont << std::endl;
      donts.insert(_dont);
      dontpos = _dont + 6;
    } else {
      break;
    }
    //std::cout << "dontpos: " << dontpos << std::endl;
  } while (dontpos != std::string::npos);

  std::cout << "Donts: ";
  for (auto n : donts) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  int total = 0;
  size_t currentPos = 0;
  bool enabled = true;
  do {
    currentPos = buffer.find("mul(", currentPos, 4);
    if (currentPos == std::string::npos) {
      break;
    }
    enabled = isEnabled(currentPos, dos, donts);
    currentPos = currentPos + 4;
    size_t comma_pos = buffer.find(",", currentPos, 1);
    if (comma_pos == std::string::npos) {
      // didn't get what we want (a comma)
      currentPos = currentPos + 1;
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

    if (enabled == true) {
      total += n1 * n2;
    } else {
      std::cout << "not enabled, skipping" << std::endl;
    }

    std::cout << "currentPos: " << currentPos << std::endl;

  } while (currentPos != std::string::npos);

  std::cout << "total: " << total << std::endl;
}