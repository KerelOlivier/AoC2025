#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#define progress std::pair<unsigned int, unsigned long int>

struct Config {
  unsigned int lights;
  unsigned int light_count;
  std::vector<unsigned int> buttons;
  std::vector<unsigned int> battery;
};

unsigned long int getMinPresses(const Config &config) {

  std::unordered_map<unsigned int, unsigned long int> mem;
  std::queue<progress> dfs;


  // First state to the stack
  dfs.emplace(0, 0);
  mem[config.lights] = UINT32_MAX;

  //std::cout << "Case: " << std::bitset<8>(config.lights) << " -> "
  //          << std::bitset<8>(config.lights) << std::endl;

  while (!dfs.empty()) {
    progress curr = dfs.front();
    dfs.pop();
		//std::cout << std::string(curr.second, '.') << std::bitset<8>(curr.first) << std::endl;
    if (curr.second >= mem[config.lights] || (mem.contains(curr.first) && curr.second >= mem[curr.first])){
      continue;
		}else{
			for (const auto &button : config.buttons) {
				//std::cout << std::string(curr.second, '-') << std::bitset<8>(button) << std::endl;
				dfs.emplace(curr.first ^ button, curr.second + 1);
			}
			mem[curr.first] = curr.second;
		}
  }

  return mem[config.lights];
}

unsigned long int part1(std::vector<Config> &configs) {
  unsigned long int res = 0;

  for (const auto &config : configs) {
    unsigned long int presses = getMinPresses(config);
    //std::cout << "presses: " << presses << std::endl;
    res += presses;
  }

  return res;
}

int main(int argc, char **argv) {
  std::vector<Config> input;
  std::ifstream stream(argv[1]);
  std::string line;

  Config curr;

  unsigned int max_val = 0;

  while (stream >> line) {
    if (line[0] == '[') {
      curr.light_count = line.length() - 2;
      unsigned int lights = 0;
      for (int i = 1; i < line.length() - 1; ++i) {
        lights <<= 1;
        lights += line[i] == '#';
      }
      curr.lights = lights;
    } else if (line[0] == '(') {
      unsigned int button = 0;
      line = line.substr(1);
      if (line.length() - 1 > max_val)
        max_val = line.length() - 1;
      while (line.length() > 0) {
        unsigned int next = line.find(',');
        if (next > line.length()) {
          button |= 1 << (curr.light_count - 1 -
                          std::stoi(line.substr(0, line.length() - 1)));
          line = "";
        } else {
          button |=
              1 << (curr.light_count - 1 - std::stoi(line.substr(0, next)));
          line = line.substr(next + 1);
        }
      }
      curr.buttons.push_back(button);
    } else {
      input.push_back(curr);
			curr = Config();
    }
  }
  std::cout << "Part 1: " << part1(input) << std::endl;
}
