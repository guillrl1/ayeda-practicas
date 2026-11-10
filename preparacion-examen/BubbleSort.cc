#include <vector>
void bubbleSort(std::vector<int>& v) {
  int n = v.size();
  for (int i = 1; i < n; i++){
    for (int j = n - 1; j >= i; j--) {
       if (v[j] < v[j-1])
           std::swap(v[j-1], v[j]);
    }
  }
}









