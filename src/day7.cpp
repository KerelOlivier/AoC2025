#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>


struct Coord{
	int row;
	int col;
};

unsigned long int part1(std::vector<std::vector<unsigned int>> map){
	std::queue<Coord> q;
	// figure out first split
	size_t center = map[0].size()/2;
	size_t diff = map[map.size()-2][center];

	q.emplace(map.size()-2-diff, center);
	
	unsigned long int res = 0;
	std::unordered_set<unsigned long int> visited;

	while(!q.empty()){
		Coord cur = q.front();
		q.pop();
		unsigned long int id = cur.row * map[0].size() + cur.col;
		if(visited.contains(id)) continue;
		visited.insert(id);
		++res;

		// Add child splits
		// Left
		int row = cur.row - map[cur.row][cur.col - 1];
		int col = cur.col - 1;
		if(col > 0 &&  row >= 0){
			q.emplace(row, col);
		}

		// Right
		row = cur.row - map[cur.row][cur.col + 1];
		col = cur.col + 1 ;
		if(col < map[0].size() &&  row >= 0){
			q.emplace(row, col);
		}
	}


	return res;
}

int main(int argc, char** argv){
	std::ifstream stream(argv[1]);
	std::string line;
	
	std::vector<std::string> lines;
	while(stream>>line){
			lines.push_back(line);
	}
	
	std::vector<std::vector<unsigned int>> map;
	for(int i = lines.size() - 1; i >= 0; --i){
		std::vector<unsigned int> row;
		
		for(int j = 0; j < lines[i].length(); ++j){
			char c = lines[i][j];
			if(i == lines.size() - 1){
				if(c == '.') row.push_back(1);
				else row.push_back(0);
			}else{
				if(c == '.') row.push_back(map[map.size()-1][j] + 1);
				else row.push_back(0);
			}
		}
		map.push_back(row);
	}

	std::cout << "Part 1: " << part1(map) << std::endl;

}
