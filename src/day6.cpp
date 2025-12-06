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
		
    for (int row = 0; row < rows; ++row) {
      size_t id = row * cols + col;

      if (operators[col] == '+') {
        sub_res += values[id];
      } else {
        sub_res *= values[id];
      }
    }

    res += sub_res;
  }

  return res;
}

unsigned long int part2(std::vector<std::vector<unsigned long int>> &vals,
                        std::vector<char> &operators) {

  unsigned long int res = 0;

	for(int col = 0; col < vals.size(); ++col){
		unsigned long int sub_res = operators[col] == '+' ? 0 : 1;
		if(operators[col] == '+'){
			for(const auto& v: vals[col]){
				sub_res += v;
			}
		}else{
			for( const auto& v : vals[col])
				sub_res *= v;
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
    if (std::isdigit(line[0])) {
      values.push_back(std::stoul(line));
    } else {
      operators.push_back(line[0]);
    }
  }
  std::cout << "Part 1: " << part1(values, operators) << std::endl;

	std::vector<std::vector<unsigned long int>> values2;
	std::vector<std::string> lines;
	size_t mx_size = 0;
	stream = std::ifstream(argv[1]);
  while (std::getline(stream, line)) {
		lines.push_back(line);
		if(mx_size < line.length()) mx_size = line.length();
  }
	
	std::vector<unsigned long int> vals;
	for(int col = 0; col < mx_size; ++col){
		std::string str;
		bool is_break = true;
		for(int row = 0; row < lines.size() - 1; ++row){
			if(std::isdigit(lines[row][col])) is_break = false;
			str.push_back(lines[row][col]);

		}
		if(is_break){
			values2.push_back(vals);
			vals.clear();
		}else{
			vals.push_back(std::stoul(str));
		}
		str.clear();
	}
	values2.push_back(vals);

  std::cout << "Part 2: " << part2(values2, operators) << std::endl;
}
