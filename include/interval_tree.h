#include <vector>

namespace ds {

// Inclusive interval
template <class T> struct Interval {
  T lower;
  T upper;
};

template <class T> class IntervalTree {
private:
  struct Node {
    Interval<T> interval;
    T max;
    Node *left, *right;
  };

  Node *root = nullptr;

private:
  Node *insert(Node *node, Interval<T> &interval) {
    if (node == nullptr) {
      return {interval, interval.upper, nullptr, nullptr};
    }

    if (interval.upper < node->interval.lower) {
      // Insert on left side
      node->left = insert(node->left, interval);
    } else {
      // Insert on right side
      node->right = insert(node->right, interval);
    }

    // update the max value
    if (node->max < interval.upper)
      node->max = interval.upper;
		
		return node;
  }
	
	inline bool isOverlapping(const Interval<T>& a, const Interval<T>& b){
		return a.lower <= b.upper && a.upper >= b.lower;
	}

public:
  IntervalTree() = default;
  ~IntervalTree() = default;

  void insert(Interval<T> interval) { insert(root, interval); }
	//std::vector<Interval<T>> find(T query) {}
  std::vector<Interval<T>> find(Interval<T> query) {
		
	}
};
} // namespace ds
