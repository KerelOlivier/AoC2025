#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Junction {
  long int x;
  long int y;
  long int z;
};

struct Connection {
  size_t src;
  size_t trg;
  double length;
};

struct Edge {
  unsigned long int src;
  unsigned long int trg;
  double w;
};

double dist(const Junction &a, const Junction &b) {

  long int dx = a.x - b.x;
  long int dy = a.y - b.y;
  long int dz = a.z - b.z;

  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

unsigned long int part1(std::vector<Junction> &junctions,
                        std::vector<Connection> &edges,
                        unsigned long int connections) {
  struct edge_comp {
    inline bool operator()(const Connection &e1, const Connection &e2) {
      return (e1.length < e2.length);
    }
  };

  // Sort the edges by length;
  std::sort(edges.begin(), edges.end(), edge_comp());

  // Create the graph
  std::unordered_map<unsigned long int, unsigned long int> labels;
  std::unordered_map<unsigned long int, unsigned long int> label_count;

  long unsigned int counter = 0;
  long unsigned int edge_counter = 0;
  long unsigned int label_counter = 0;
  while (counter < connections) {
    Connection &e = edges[edge_counter];
    ++edge_counter;

    if (!labels.contains(e.src))
      labels[e.src] = label_counter++;
    if (!labels.contains(e.trg))
      labels[e.trg] = label_counter++;

    // Check if already in the same circuit, if so skip them
    if (labels[e.src] == labels[e.trg]) {
      ++counter;
      continue;
    }

    // Determine new label
    unsigned long int new_label = std::min(labels[e.src], labels[e.trg]);
    unsigned long int old_label = std::max(labels[e.src], labels[e.trg]);

    // Set labels
    for (auto &pair : labels) {
      if (pair.second == old_label)
        pair.second = new_label;
    }

    if (!label_count.contains(new_label))
      label_count[new_label] = 1;
    if (!label_count.contains(old_label))
      label_count[old_label] = 1;

    label_count[new_label] += label_count[old_label];
    label_count.erase(old_label);

    ++counter;
  }

  unsigned long int a = 0, b = 0, c = 0;

  for (auto &pair : label_count) {
    if (pair.second >= c) {
      if (pair.second >= b) {
        if (pair.second >= a) {
					c = b;
					b = a;
					a = pair.second;
        }else{
					c = b;
					b = pair.second;
				}
      } else {
        c = pair.second;
      }
    }
  }
  return a * b * c;
}

int main(int argc, char **argv) {
  std::ifstream stream(argv[1]);
  std::string line;

  unsigned long int connections = std::stoul(argv[2]);

  std::vector<Junction> junctions;
  std::vector<Connection> edges;

  while (stream >> line) {
    auto iter = line.find(',');

    unsigned long int x = std::stoul(line.substr(0, iter));
    line = line.substr(iter + 1);
    iter = line.find(',');

    unsigned long int y = std::stol(line.substr(0, iter));
    unsigned long int z = std::stol(line.substr(iter + 1));

    junctions.emplace_back(x, y, z);
  }

  for (int i = 0; i < junctions.size() - 1; ++i) {
    for (int j = i + 1; j < junctions.size(); ++j) {
      edges.emplace_back(i, j, dist(junctions[i], junctions[j]));
    }
  }

  std::cout << "Part 1: " << part1(junctions, edges, connections) << std::endl;
}
