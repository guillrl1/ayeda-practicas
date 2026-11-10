
#include <vector>

void Qsort(std::vector<int>& sec, int ini, int fin) {
  int i = ini;
  int f = fin;
  int p = sec[(i+f)/2];
  while (i <= f){
     while (sec[i] < p) i++ ;
     while (sec[f] > p) f-- ;
     if (i <= f) {
        std::swap(sec[i++],sec[f--]) ;
     } 
  } 
  if (ini < f) Qsort(sec, ini, f) ; 
  if (i < fin) Qsort(sec, i, fin) ; 
} ;
