#include <fstream>
#include <iostream>
#include <string>
#include <vector>

unsigned long int get_battery_joltage(std::string bat) {
  unsigned long int res = 0;

  for (int i = 0; i < bat.length() - 1; ++i) {
    for (int j = i+1; j < bat.length(); ++j) {
			std::string s = "00";
			s[0] = bat[i];
			s[1] = bat[j];
			unsigned long int val = std::stoul(s);
			if(val > res){
				res = val;
			}
    }
  }
  return res;
}

unsigned long int part1(std::vector<std::string> input) {
  unsigned long int res = 0;
  for (const auto &battery : input) {
    res += get_battery_joltage(battery);
  }
  return res;
}

int main(int argc, char **argv) {
  std::ifstream stream(argv[1]);

  std::vector<std::string> input;
  std::string line;
  while (stream >> line)
    input.push_back(line);

  std::cout << "Part 1: " << part1(input) << std::endl;
  std::cout << "Part 1: " << part1(input) << std::endl;
}
