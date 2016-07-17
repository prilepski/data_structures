#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<long long> data_;
  vector<long long> data_best;
  vector< pair<long long, long long> > swaps_;
  vector< pair<long long, long long> > swaps_best;

  void WriteResponse() const {
    cout << swaps_best.size() << "\n";
//    for (long long i = 0; i < swaps_.size(); ++i) {
//      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
//    }

    for (long long i = 0; i < swaps_best.size(); ++i) {
      cout << swaps_best[i].first << " " << swaps_best[i].second << "\n";
    }
  }

  void ReadData() {
    long long n;
    cin >> n;
    data_.resize(n);
    data_best.resize(n);
    for(long long i = 0; i < n; ++i){
      cin >> data_[i];
      data_best[i] = data_[i];
    }
  }

  void MinHeapify(){
    long long curr_node = data_best.size() / 2;
    long long left = -1, right = -1, minimum = -1;
    for (long long i = data_best.size() / 2; i >= 0; --i){
      for (curr_node = i;;){
        left = 2 * curr_node + 1; // get id of left child
        right = 2 * curr_node + 2;
        minimum = curr_node;
        if (left < data_best.size() && data_best[left] < data_best[minimum]){
          minimum = left;
        }

        if (right < data_best.size() && data_best[right] < data_best[minimum]){
          minimum = right;
        }

        if (minimum != curr_node){
          long long tmp = data_best[curr_node];
          data_best[curr_node] = data_best[minimum];
          data_best[minimum] = tmp;
          swaps_best.push_back(make_pair(curr_node, minimum));
        }

        if (curr_node == minimum)
          break;
        else
          curr_node = minimum;
      }
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array long longo a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (long long i = 0; i < data_.size(); ++i)
      for (long long j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

 public:
  void Solve() {
    ReadData();
//    GenerateSwaps();
    MinHeapify();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
