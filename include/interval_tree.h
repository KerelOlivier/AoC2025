#include <vector>

namespace ds{

// Inclusive interval
template <class T>
struct Interval{
	T lower;
	T upper;
};

template<class T>
class IntervalTree{
	public:
		IntervalTree() = default;
		~IntervalTree() = default;

		void insert(Interval<T> input){}
		std::vector<Interval<T>> find(T query){}
		std::vector<Interval<T>> find(Interval<T> query){}
};
}
