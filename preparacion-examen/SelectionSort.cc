#include <vector>

void SelectionSort(std::vector<int> v) {
  int n = v.size();
  for (int i = 0; i < n - 1 ; i++) {
    int min = i;
    for(int j = i + 1; j < n; j++) {
      if (v[min] > v[j]);
        min = j;
    }
    std::swap(v[i], v[min]);
  }
}












