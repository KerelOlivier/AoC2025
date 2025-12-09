#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Tile {
  int x;
  int y;
};

struct Edge {
  Tile src;
  Tile trg;
};

std::ostream &operator<<(std::ostream &stream, const Tile &tile) {
  return stream << "[" << tile.x << ", " << tile.y << "]";
}

bool operator==(const Tile &a, const Tile &b) {
  return a.x == b.x && a.y == b.y;
}

bool operator<(const Edge &a, const Edge &b) {
  if (a.src.y == b.src.y)
    return a.src.x < b.src.x;
  return a.src.y < b.src.y;
}

unsigned long int part1(std::vector<Tile> &tiles) {
  unsigned long int res = 0;

  for (int i = 0; i < tiles.size() - 1; ++i) {
    for (int j = i + 1; j < tiles.size(); ++j) {
      unsigned long int area =
          ((unsigned long int)std::abs(tiles[i].x - tiles[j].x) + 1) *
          ((unsigned long int)std::abs(tiles[i].y - tiles[j].y) + 1);
      if (area > res) {
        res = area;
      }
    }
  }
  return res;
}

bool pointInPoly(std::vector<Edge> &edges, Tile tile) {
  size_t count = 0;

  for (const auto &e : edges) {
    int min_x = std::min(e.src.x, e.trg.x);
    int min_y = std::min(e.src.y, e.trg.y);
    int max_x = std::max(e.src.x, e.trg.x);
    int max_y = std::max(e.src.y, e.trg.y);

    if (tile.x <= max_x && tile.x >= min_x && tile.y <= max_y &&
        tile.y >= min_y)
      return true;

    // Check for intersection
    if (e.src.x == e.trg.x) {
      if (tile.x <= e.src.x && tile.y < max_y && tile.y >= min_y) {
        ++count;
      }
    }
  }
  return count % 2 == 1;
}

bool lineInPoly(std::vector<Edge> &edges, Tile &a, Tile &b) {
  if (a == b)
    return true;
  // Check if it is already a known edge
  for (const auto &e : edges) {
    if ((e.src == a && e.trg == b) || (e.trg == a && e.src == b))
      return true;
  }

  int x_min = std::min(a.x, b.x);
  int x_max = std::max(a.x, b.x);
  int y_min = std::min(a.y, b.y);
  int y_max = std::max(a.y, b.y);

  for (int x = x_min; x <= x_max; ++x) {
    for (int y = y_min; y <= y_max; ++y) {
      if (!pointInPoly(edges, Tile(x, y))) {
        return false;
      }
    }
  }
  return true;
}

bool isContained(std::vector<Edge> &edges, Tile &a, Tile &b) {

  Tile c = Tile(a.x, b.y);
  Tile d = Tile(b.x, a.y);

  if (!lineInPoly(edges, a, c)) {
    return false;
  }
  if (!lineInPoly(edges, a, d)) {
    return false;
  }
  if (!lineInPoly(edges, b, c)) {
    return false;
  }
  if (!lineInPoly(edges, b, d)) {
    return false;
  }

  return true;
}

unsigned long int part2(std::vector<Tile> &tiles) {
  unsigned long int res = 0;
  int min_x = 100000;
  int min_y = 100000;
  int max_x = 0;
  int max_y = 0;

  // Initialize map
  std::vector<Edge> edges;
  Tile prev = tiles[0];
  for (int i = 1; i <= tiles.size(); ++i) {
    Tile curr = tiles[i % tiles.size()];
    edges.emplace_back(prev, curr);
    prev = curr;
  }
  std::cout << std::endl;
  // std::cout << isContained(edges, tiles[1], tiles[6]) << std::endl;;
  for (int y = 0; y < 9; ++y) {
    for (int x = 0; x < 14; ++x) {
      Tile t(x, y);
      if (pointInPoly(edges, t)) {
        std::cout << "X";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }

	unsigned int mx = (tiles.size() * (tiles.size()-1))/2;
	size_t counter = 1;
  for (int i = 0; i < tiles.size() - 1; ++i) {
    for (int j = i + 1; j < tiles.size(); ++j) {
			std::cout << counter << "/" << mx << std::endl;
			counter++;
      unsigned long int area =
          ((unsigned long int)std::abs(tiles[i].x - tiles[j].x) + 1) *
          ((unsigned long int)std::abs(tiles[i].y - tiles[j].y) + 1);

      if (area > res) {
        // Check if valid square
        bool contained = isContained(edges, tiles[i], tiles[j]);
        if (contained) {
          res = area;
        }
      }
    }
  }

  return res;
}

int main(int argc, char **argv) {
  std::vector<Tile> tiles;
  std::ifstream stream(argv[1]);

  std::string line;
  while (stream >> line) {
    auto sep = line.find(',');
    tiles.emplace_back(std::stoi(line.substr(0, sep)),
                       std::stoi(line.substr(sep + 1)));
  }

  std::cout << "Part 1: " << part1(tiles) << std::endl;
  std::cout << "Part 2: " << part2(tiles) << std::endl;
}
