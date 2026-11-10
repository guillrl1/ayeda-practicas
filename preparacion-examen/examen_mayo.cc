#include <vector>

void Merge(std::vector<int>& sec) {
  SelectionSort(sec, sec.size()/2);
  InsertionSort(sec, sec.size()/2, sec.size());
  int i = sec.size()/2 - 1, j = sec.size()/2;
  std::vector<int> aux;
  while(i>=0 && j <= sec.size() - 1) {
    if(sec[i] <= sec[j]) 
      aux.push_back(sec[i--]);
    else
      aux.push_back(sec[j++]);
  }
  while(i>=0) 
    aux.push_back(sec[i--]);
  while(j<= sec.size() - 1)
     aux.push_back(sec[j++]);
  for(int k = 0; k < sec.size(); k++)
    sec[k] = aux[k]; 
    
}

void SelectionSort(std::vector<int>& sec, int size) {
  for (int i = 0; i < size; i++) {
    int max = i;
    for (int j = i+1; j < size; j++) {
      if(sec[max] > sec[j]) 
        max = j;
    }
    std::swap(sec[max], sec[i]);
  }
}

void InsertionSort(std::vector<int>& sec, int ini, int fin) {
  for (int i = fin-1; i >= ini; i--) {
    int aux = sec[i];
    int j = i+1;
    while(j < fin && aux > sec[j]) {
      sec[j-1] = sec[j];
      j++;
    }
    sec[j-1] = aux;
  }
}

