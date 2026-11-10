#include <vector>
void Chungo(std::vector<int>& sec) {
  QuickSort(sec);
  int pivote = sec.size() / 2 - 1;
  InsertionSort(sec, pivote-1);
  SelectionSort(sec, pivote+1);
}

void QuickSort(std::vector<int>& sec) {
  int pivote = sec[(sec.size() - 1) / 2];
  int i = 0, f = sec.size() - 1;
  while(i<=f) {
    while(sec[i] < pivote) i++;
    while(sec[f] > pivote) f--;
    if(i <= f)
      std::swap(sec[i++], sec[f--]);
  }
}

void InsertionSort(std::vector<int>& sec, int n) {
  for (int i = 1; i < n; i++) {
    int aux = sec[i];
    int j = i - 1;
    while(j <= 0 && sec[j] < aux) {
      sec[j+1] = sec[j];
      j--;
    }
    sec[j+1] = aux;
  }
}

void SelectionSort(std::vector<int>& sec, int n) {
  for(int i = 0; i < n-1; i++) {
    int min = i;
    for(int j = i+1; i < n; j++) {
      if (sec[j] < sec[min]) min = j;
    }
    std::swap(sec[i], sec[min]);
  }
}