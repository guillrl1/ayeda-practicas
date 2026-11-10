#include <vector>
void ShakeSort(std::vector<int>& v) {
  int ini = 1;
  int fin = v.size() - 1;
  int cam = 0;

  while(ini < fin) {
    for (int j = fin; j >= ini; j--) {
      if (v[j] < v[j-1]) {
        std::swap(v[j-1], v[j]);
        cam = j;
      }
    }
    ini = cam + 1;
    for (int j = ini; j <= fin; j++) {
      if (v[j] < v[j-1]) {
        std::swap(v[j+1], v[j]);
        cam = j;
      }
    }
    fin = cam - 1;
  }
}






