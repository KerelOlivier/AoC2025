#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

struct Range {
  unsigned long int lower;
  unsigned long int upper;
};

int count_digits(unsigned long int val) { return std::log10(val) + 1; }

long unsigned int part1(std::vector<Range> ranges) {
  long unsigned int res = 0;
  for (const auto &range : ranges) {
    long unsigned int half =
        range.lower / std::pow(10, std::ceil(count_digits(range.lower) / 2.0));
    long unsigned int sum = 0;
    while (sum <= range.upper) {
      int digits = count_digits(half);
      sum = half * std::pow(10, digits) + half;
      if (sum >= range.lower && sum <= range.upper) {
        res += sum;
      }
      ++half;
    }
  }
  return res;
}

long unsigned int get_repeat_num(unsigned long int base, unsigned int repetitions){
	if(repetitions == 0) return 0;
	if(repetitions == 1) return base;

	unsigned long int res = base;
	unsigned long int digits = count_digits(base);
	
	for(unsigned int i = 1; i < repetitions; ++i){
			res *= std::pow(10, digits);
			res += base;
	}

	return res;
}

long unsigned int part2(std::vector<Range> ranges){
  long unsigned int res = 0;

	std::unordered_set<long unsigned int> visited;

  for (const auto &range : ranges) {
    long unsigned int half =
        range.upper / std::pow(10, (count_digits(range.upper) / 2));
		
		for(int i = 1; i <= half; ++i){
			int digits = count_digits(i);
			int blocks = std::ceil(count_digits(range.lower)/(float)digits);
			long unsigned int num = 0;
			while(num <= range.upper){
				num = get_repeat_num(i, blocks);
				++blocks;
				if(!visited.contains(num) && num >= range.lower && num <= range.upper){
					res += num;
					visited.insert(num);
				}
			}
		}
  }
  return res;
}

int main(int argc, char **argv) {
  std::ifstream stream(argv[1]);

  std::string data;
  stream >> data;

  std::vector<Range> ranges;

  unsigned long int lower;
  unsigned long int upper;

  int start = 0;
  for (int i = 0; i < data.length(); ++i) {
    if (data[i] == '-') {
      lower = std::stoul(data.substr(start, i));
      start = i + 1;
    } else if (data[i] == ',') {
      upper = std::stoul(data.substr(start, i));
      start = i + 1;
      ranges.emplace_back(lower, upper);
    }
  }
  upper = std::stoul(data.substr(start));
  ranges.emplace_back(lower, upper);

  std::cout << "Part 1: " << part1(ranges) << std::endl;
  std::cout << "Part 2: " << part2(ranges) << std::endl;
}
