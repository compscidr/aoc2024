//
// Created by jason on 12/3/24.
//
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

enum Direction { UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

/**
 *
 */
bool findXmas(std::vector<std::string> board, char nextLetter, int startingLine, int startingRow, Direction dir) {
  int nextLine;
  int nextRow;


  if (dir == UP || dir == UP_LEFT || dir == UP_RIGHT) {
    nextLine = startingLine -1;
  } else if (dir == DOWN || dir == DOWN_LEFT || dir == DOWN_RIGHT) {
    nextLine = startingLine + 1;
  } else {
    nextLine = startingLine;
  }

  if (dir == LEFT || dir == UP_LEFT || dir == DOWN_LEFT) {
    nextRow = startingRow - 1;
  } else if (dir == RIGHT || dir == DOWN_RIGHT || dir == UP_RIGHT) {
    nextRow = startingRow + 1;
  } else {
    nextRow = startingRow;
  }

  if (nextLine < 0 || nextLine >= board.size()) {
    //std::cout << "off board: nextLine: " << nextLine << " DIR: " << dir << std::endl;
    return false;
  }
  if (nextRow < 0 || nextRow >= board[0].size()) {
    //std::cout << "off board: nextRow: " << nextRow << " DIR: " << dir << std::endl;
    return false;
  }
  if (board[nextLine][nextRow] == nextLetter) {
    if (nextLetter == 'S') {
      //std::cout << "Found S at (" << nextLine << ", " << nextRow << ") DIR: " << dir << std::endl;
      return true;
    }
    if (nextLetter == 'M') {
      //std::cout << "Found M at (" << nextLine << ", " << nextRow << ") DIR: " << dir << std::endl;
      return findXmas(board, 'A', nextLine, nextRow, dir);
    }
    if (nextLetter == 'A') {
      //std::cout << "Found A at (" << nextLine << ", " << nextRow << ") DIR: " << dir << std::endl;
      return findXmas(board, 'S', nextLine, nextRow, dir);
    }
  }
  return false;
}

bool findLetter(std::vector<std::string> board, char nextLetter, int startingLine, int startingRow, Direction dir) {
  int nextLine;
  int nextRow;


  if (dir == UP || dir == UP_LEFT || dir == UP_RIGHT) {
    nextLine = startingLine -1;
  } else if (dir == DOWN || dir == DOWN_LEFT || dir == DOWN_RIGHT) {
    nextLine = startingLine + 1;
  } else {
    nextLine = startingLine;
  }

  if (dir == LEFT || dir == UP_LEFT || dir == DOWN_LEFT) {
    nextRow = startingRow - 1;
  } else if (dir == RIGHT || dir == DOWN_RIGHT || dir == UP_RIGHT) {
    nextRow = startingRow + 1;
  } else {
    nextRow = startingRow;
  }

  if (nextLine < 0 || nextLine >= board.size()) {
    //std::cout << "off board: nextLine: " << nextLine << " DIR: " << dir << std::endl;
    return false;
  }
  if (nextRow < 0 || nextRow >= board[0].size()) {
    //std::cout << "off board: nextRow: " << nextRow << " DIR: " << dir << std::endl;
    return false;
  }

  if (board[nextLine][nextRow] == nextLetter) {
    return true;
  }
  return false;
}

int main(int argc, char **argv) {
  std::cout << "DIR, RIGHT: " << RIGHT << std::endl;
  // auto filename = "day4/data/test-input.txt";
  auto filename = "day4/data/input.txt";
  std::ifstream input(filename);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }

  for (const auto& line : lines) {
    std::cout << line << std::endl;
  }

  int count = 0;
  for (int l = 0; l < lines.size(); l++) {
    for (int r = 0; r < lines[l].size() ; r++) {
      if (lines[l][r] == 'A') {
        // m's to the left
        if (findLetter(lines, 'M', l, r, UP_LEFT) && findLetter(lines, 'M', l, r, DOWN_LEFT) && findLetter(lines, 'S', l, r, UP_RIGHT) && findLetter(lines, 'S', l, r, DOWN_RIGHT)) {
          count++;
        }

        // m's on the bottom
        if (findLetter(lines, 'M', l, r, DOWN_LEFT) && findLetter(lines, 'M', l, r, DOWN_RIGHT) && findLetter(lines, 'S', l, r, UP_LEFT) && findLetter(lines, 'S', l, r, UP_RIGHT)) {
          count++;
        }

        // m's to the right
        if (findLetter(lines, 'M', l, r, UP_RIGHT) && findLetter(lines, 'M', l, r, DOWN_RIGHT) && findLetter(lines, 'S', l, r, UP_LEFT) && findLetter(lines, 'S', l, r, DOWN_LEFT)) {
          count++;
        }

        // m's on the top
        if (findLetter(lines, 'M', l, r, UP_LEFT) && findLetter(lines, 'M', l, r, UP_RIGHT) && findLetter(lines, 'S', l, r, DOWN_LEFT) && findLetter(lines, 'S', l, r, DOWN_RIGHT)) {
          count++;
        }
      }
    }
  }
  std::cout << "FOUND XMAS: " << count << std::endl;

  return 0;
}