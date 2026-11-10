#include <vector>

void insertionSort(std::vector<int> v, int n) {
  for (int i = 1; i < n; i++) {
     int key = v[i];
     int j = i - 1;
     while (j > 0 && v[j] > key) {
      v[j + 1] = v[j];
      j = j - 1;
     }
     v[j + 1] = key;
  }
}






