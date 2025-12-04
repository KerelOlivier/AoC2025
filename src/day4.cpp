#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int count_surrounding(int row, int col, std::vector<std::vector<bool>> &map) {

  int rows = map.size();
  int cols = map[0].size();
  int res = 0;
  res += col > 0 && row > 0 && map[row - 1][col - 1];
  res += row > 0 && map[row - 1][col];
  res += col < cols - 1 && row > 0 && map[row - 1][col + 1];
  res += col > 0 && row < rows - 1 && map[row + 1][col - 1];
  res += row < rows - 1 && map[row + 1][col];
  res += col < cols - 1 && row < rows - 1 && map[row + 1][col + 1];
  res += col > 0 && map[row][col - 1];
  res += col < cols - 1 && map[row][col + 1];

  return res;
}

int part1(std::vector<std::vector<bool>> &map) {
  int res = 0;
  std::cout << std::endl;
  for (int row = 0; row < map.size(); ++row) {
    for (int col = 0; col < map[0].size(); ++col) {
      if (map[row][col]){
        std::cout << "\u001b[31m";
			}else{
				std::cout << ". ";
				continue;
			}

      int count = count_surrounding(row, col, map);
      if (count < 4){
        std::cout << "\u001b[34m";
        ++res;
			}

      std::cout << count << "\u001b[0m ";
    }
    std::cout << std::endl;
  }

  return res;
}
int part2(std::vector<std::vector<bool>> map) {
	int res = 0;
	int removed = 0;

	do{
		removed = 0;
		for (int row = 0; row < map.size(); ++row) {
			for (int col = 0; col < map[0].size(); ++col) {
				if(!map[row][col]) continue;
				int count = count_surrounding(row, col, map);
				if (count < 4){
					map[row][col] = false;
					++removed;
					++res;
				}
			}
		}
	}while(removed > 0);

  return res;
}

int main(int argc, char **argv) {
  std::vector<std::vector<bool>> map;

  std::ifstream stream(argv[1]);
  std::string line;

  while (stream >> line) {
    std::vector<bool> row;

    for (int i = 0; i < line.length(); ++i) {
      row.push_back(line[i] == '@');
    }

    map.push_back(row);
  }

  std::cout << map.size() << std::endl;

  std::cout << "Part 1: " << part1(map) << std::endl;
  std::cout << "Part 2: " << part2(map) << std::endl;
}
