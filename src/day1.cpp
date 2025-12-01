#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Instruction {
  bool dir;  // 0: left, 1: right
  int steps; // The number of steps in the given direction
};

int part1(std::vector<Instruction> instructions) {
  int pos = 50;
  int res = 0;
  for (const auto &instruction : instructions) {
    if (instruction.dir) {
      pos = (pos + instruction.steps) % 100;
    } else {
      pos = (pos - instruction.steps) % 100;
      if (pos < 0)
        pos += 100;
    }

    if (pos == 0)
      ++res;
  }
  return res;
}

int part2(std::vector<Instruction> instructions) {
  int pos = 50;
  int res = 0;
  int prev = 0;
  for (const auto &instruction : instructions) {
    prev = pos;

    int full_rotations = instruction.steps / 100;
    int remainder = instruction.steps % 100;
    if (instruction.dir) {
      pos = (pos + remainder);
      if (pos > 100) {
        if (prev != 0)
          ++res;
      }
      pos %= 100;
    } else {
      pos = (pos - remainder);
      if (pos < 0) {
        if (prev != 0)
          ++res;
        pos += 100;
      }
      pos %= 100;
    }

    if (pos == 0)
      ++res;

    res += full_rotations;

  }
  return res;
}

int main(int argc, char **argv) {
  std::cout << "Day 1" << std::endl;

  std::ifstream stream(argv[1]);
  std::string str;

  // Read the data into an instruction list
  std::vector<Instruction> instructions;
  while (stream >> str) {
    bool dir = str[0] == 'R';
    int steps = std::stoi(str.substr(1));
    instructions.emplace_back(dir, steps);
  }

  std::cout << "Part 1: " << part1(instructions) << std::endl;
  std::cout << "Part 2: " << part2(instructions) << std::endl;
}
