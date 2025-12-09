#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Tile {
  int row;
  int col;
};

unsigned long int part1(std::vector<Tile> tiles) {
  unsigned long int res = 0;

  for (int i = 0; i < tiles.size() - 1; ++i) {
    for (int j = i + 1; j < tiles.size(); ++j) {
      unsigned long int area =
          ((unsigned long int)std::abs(tiles[i].row - tiles[j].row) + 1) *
          ((unsigned long int)std::abs(tiles[i].col - tiles[j].col) + 1);
      if (area > res) {
        res = area;
      }
    }
  }
  return res;
}

int main(int argc, char **argv) {
  std::vector<Tile> tiles;
  std::ifstream stream(argv[1]);

  std::string line;
  while (stream >> line) {
    auto sep = line.find(',');
    tiles.emplace_back(std::stoi(line.substr(0, sep)),
                       std::stoi(line.substr(sep + 1)));
  }

  std::cout << "Part 1: " << part1(tiles) << std::endl;
}
