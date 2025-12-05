#include <fstream>
#include <interval_tree.h>
#include <iostream>
#include <string>
#include <vector>

int part1(std::vector<ds::Interval<unsigned long int>> intervals,
          std::vector<unsigned long int> items) {

	int res = 0;
  for (const auto &item : items) {
    for (const auto &interval : intervals) {
      if(item >= interval.lower && item <= interval.upper){
				++res;
				break;
			}
    }
  }

  return res;
}

int part2() { return 1; }

int main(int argc, char **argv) {
  std::ifstream stream(argv[1]);
  std::string line;

  std::vector<ds::Interval<unsigned long int>> intervals;
  std::vector<unsigned long int> items;

  bool is_item = false;
  while (stream >> line) {
    if (line.empty())
      is_item = true;

    auto iter = line.find('-');
    if (iter >= line.size()) {
      items.push_back(std::stoul(line));
    } else {
      intervals.emplace_back(std::stoul(line.substr(0, iter)),
                             std::stoul(line.substr(iter + 1)));
    }
  }

  std::cout << "Part 1: " << part1(intervals, items) << std::endl;
}
