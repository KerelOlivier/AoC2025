#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

unsigned long int part1(std::vector<unsigned long int> &values,
                        std::vector<char> &operators) {
  unsigned long int res = 0;

	size_t cols = operators.size();
	size_t rows = values.size() / cols;
  for (int col = 0; col < cols; ++col) {
    unsigned long int sub_res = operators[col] == '*' ? 1 : 0;

		for(int row = 0; row < rows; ++row){
			size_t id = row * cols + col;

			if(operators[col] == '+'){
				sub_res += values[id];
			}else{
				sub_res *= values[id];
			}
		}

    res += sub_res;
  }

  return res;
}

int main(int argc, char **argv) {
  std::ifstream stream(argv[1]);
  std::string line;

  std::vector<unsigned long int> values;
  std::vector<char> operators;

  while (stream >> line) {
    if (std::isdigit(line[0]))
      values.push_back(std::stoul(line));
    else
      operators.push_back(line[0]);
  }
  std::cout << "Part 1: " << part1(values, operators) << std::endl;
}
