// Quick Sort.
// Method:
//  1. Use recursive.
//  2. Use stack.
//  3. Use queue.
//  4. label the used pivot cell. After a pivot is selected and finished
//     partition work, label it in the other array.

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;


class Sorter {
 public:
  void QuickSort(vector<int> &array);
 private:
  int Partition(vector<int> &a, int low, int high);
  void SortByStack(vector<int> &array);
};

void Sorter::QuickSort(vector<int> &array) {
  SortByStack(array);
}

// pivot's left is less than right.
int Sorter::Partition(vector<int> &a, int low, int high) {
  int pivot = a[low];
  while (low < high) {
    while(low < high && a[high] >= pivot) high--;
    a[low] = a[high];
    while(low < high && a[low] < pivot) low++;
    a[high] = a[low];
  }
  //now low==high
  a[low] = pivot;
  return low;
}

void Sorter::SortByStack(vector<int> &array) {
  if (array.size() <= 1) return;

  stack<pair<int, int> > st;
  st.push(make_pair<int, int>(0, array.size() - 1));
  while(!st.empty()){
    pair<int, int> index = st.top();
    st.pop();
    int pivot = Partition(array, index.first, index.second);
    if(index.first < pivot - 1) {
      st.push(make_pair<int, int>(index.first, pivot - 1));
    }
    if(pivot + 1 < index.second) {
      st.push(make_pair<int, int>(pivot + 1, index.second));
    }
  }
}

void Print(const vector<int> array) {
  for (int i = 0; i < array.size(); ++i) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main(int argv, char** argc) {
  int n = 10;
  Sorter sorter;
  vector<int> array;
  for(int i = 0; i < n; ++i) array.push_back(rand() % 1000);
  random_shuffle(array.begin(),array.end());
  clock_t t1 = clock();
  sorter.QuickSort(array);
  clock_t t2 = clock();
  Print(array);
  cout << "Cost time: "<< 1.0 * (t2 - t1) / CLOCKS_PER_SEC << " s."<< endl;

  return 0;
}
