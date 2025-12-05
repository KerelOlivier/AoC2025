#include <algorithm>
#include <fstream>
#include <interval_tree.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int part1(const std::vector<ds::Interval<unsigned long int>> &intervals,
          std::vector<unsigned long int> items) {

  int res = 0;
  for (const auto &item : items) {
    for (const auto &interval : intervals) {
      if (item >= interval.lower && item <= interval.upper) {
        ++res;
        break;
      }
    }
  }

  return res;
}

unsigned long int part2(std::vector<ds::Interval<unsigned long int>> intervals) {
  // Sort by starting id
  struct{
    bool operator()(ds::Interval<unsigned long int> a,
                    ds::Interval<unsigned long int> b) const {
			if(a.lower != b.lower) return a.lower < b.lower;
			else return a.upper < b.upper;
    }
  } comparator;

  std::sort(intervals.begin(), intervals.end(), comparator);

	unsigned long int res = 0;

	unsigned long int bound = 0;

	for(const auto& interval:intervals){

		if(interval.upper <= bound) continue; // interval is contained already
		
		
		unsigned long int vals = interval.upper - interval.lower + 1;


		if(interval.lower <= bound){
			// Remove the already processed values from return
			vals -= bound - interval.lower + 1;

		}

		res += vals;
		bound = interval.upper;
	}

  return res;
}

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
  std::cout << "Part 2: " << part2(intervals) << std::endl;
}
