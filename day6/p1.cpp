#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> parseFile(std::string fileName) {
  std::vector<std::string> result;
  std::ifstream file(fileName);
  std::string line;
  while (std::getline(file, line)) {
    result.push_back(line);
  }
  return result;
}

std::pair<int, int> findStartPosition(std::vector<std::string> map) {
  int mapHeight = map.size();
  int mapLength = map[0].size();
  std::cout << "Map is: " << mapHeight << "x" << mapLength << std::endl;

  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapLength; x++) {
      if (map[y][x] == '^') {
        return {x, y};
      }
    }
  }
  return std::make_pair(0, 0);
}

void printMap(std::vector<std::string> input, std::string move) {
  std::cout << move << std::endl;
  for (int y = 0; y < input.size(); y++) {
    for (int x = 0; x < input[y].size(); x++) {
      std::cout << input[y][x] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "--------------" << std::endl;
}

int countUnique(std::vector<std::string> map) {
  int count = 0;
  for (int y = 0; y < map.size(); y++) {
    for (int x = 0; x < map[0].size(); x++) {
      if (map[y][x] == 'X') {
        count++;
      }
    }
  }
  return count;
}

enum class Orientation {
  UP, DOWN, LEFT, RIGHT
};

int main(int argc, char **argv) {
  // auto filename = "day6/data/test-input.txt";
  auto filename = "day6/data/input.txt";
  auto map = parseFile(filename);
  auto position = findStartPosition(map);
  std::cout << "Start position: " << position.first << " " << position.second << std::endl;
  Orientation orientation = Orientation::UP;

  int mapHeight = map.size();
  int mapLength = map[0].size();

  // mark the first spot as visted
  map[position.second][position.first] = 'X';

  while(position.first < mapLength && position.first > 0 && position.second < mapHeight && position.second > 0) {
    int x = position.first;
    int y = position.second;
    if (orientation == Orientation::UP) {
      if (y - 1 < 0) {
        std::cout << "Reached out of map going up" << std::endl;
        break;
      }
      if (map[y-1][x] == '#') {
        printMap(map, "Rotate Right");
        // don't actually move, just rotate and move next time
        orientation = Orientation::RIGHT;
      } else if (map[y-1][x] == '.') {
        printMap(map, "Move up, unique");
        map[y-1][x] = 'X';
        position.second = y - 1;
      } else {
        printMap(map, "Move up, non-unique");
        // already visited
        position.second = y - 1;
      }
    } else if (orientation == Orientation::DOWN) {
      if (y + 1 >= mapHeight) {
        std::cout << "Reached out of map going down" << std::endl;
        break;
      }
      if (map[y+1][x] == '#') {
        printMap(map, "Rotate Left");
        // don't actually move, just rotate and move next time
        orientation = Orientation::LEFT;
      } else if (map[y+1][x] == '.') {
        printMap(map, "Move down, unique");
        map[y+1][x] = 'X';
        position.second = y + 1;
      } else {
        // already visited
        printMap(map, "Move down, non-unique");
        position.second = y + 1;
      }
    } else if (orientation == Orientation::LEFT) {
      if (x - 1 < 0) {
        std::cout << "Reached out of map going left" << std::endl;
        break;
      }
      if (map[y][x - 1] == '#') {
        printMap(map, "Rotate Up");
        orientation = Orientation::UP;
      } else if (map[y][x - 1] == '.') {
        printMap(map, "Move left, unique");
        map[y][x - 1] = 'X';
        position.first = x - 1;
      } else {
        printMap(map, "Move left, non-unique");
        position.first = x - 1;
      }
    } else {
      if (x + 1 >= mapLength) {
        std::cout << "Reached out of map going right" << std::endl;
      } else if (map[y][x + 1] == '#') {
        printMap(map, "Rotate Down");
        orientation = Orientation::DOWN;
      } else if (map[y][x + 1] == '.') {
        printMap(map, "Move right, unique");
        map[y][x + 1] = 'X';
        position.first = x + 1;
      } else {
        printMap(map, "Move right, non-unique");
        position.first = x + 1;
      }
    }
  }

  int uniquePositions = countUnique(map);
  std::cout << "Unique positions: " << uniquePositions << std::endl;

  return 0;
}