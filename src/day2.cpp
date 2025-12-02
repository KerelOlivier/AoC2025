#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
    std::cout << range.lower << " - " << range.upper << " -> " << half << ", "
              << std::ceil(count_digits(range.lower) / 2.0) << std::endl;
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
}
