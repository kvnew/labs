#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;



// 轴pivot左边小于右边
int Partition(vector<int> &a, int low, int high){
  int pivot = a[low];
  while (low < high) {
    while(low<high && a[high] >= pivot) high--;
    a[low] = a[high];
    while(low<high && a[low] < pivot) low++;
    a[high] = a[low];
  }
  //low==high
  a[low] = pivot;
  return low;
}

void SortByStack(vector<int> &array) {
  stack<pair<int, int> > st;
  int low, high;

  if (array.size() <= 1) return;
  low = 0;
  high = array.size() - 1;

  int pivot = Partition(array, low, high);
  if(low < pivot - 1){
    st.push(make_pair<int, int>(low, pivot - 1));
  }
  if(pivot + 1 < high){
    st.push(make_pair<int, int>(pivot + 1, high));
  }
  while(!st.empty()){
    pair<int, int> index = st.top();
    st.pop();
    pivot = Partition(array, index.first, index.second);
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
  vector<int> array;
  for(int i = 0; i < n; ++i) array.push_back(rand() % 1000);
  clock_t t1 = clock();
  SortByStack(array);
  clock_t t2 = clock();
  Print(array);
  cout<<"Cost time: "<< 1.0 * (t2 - t1) / CLOCKS_PER_SEC << " s."<< endl;

  random_shuffle(array.begin(),array.end());

  return 0;
}
