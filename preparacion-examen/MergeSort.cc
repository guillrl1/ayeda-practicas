#include <vector>

void Msort (std::vector<int>& sec, int ini, int fin){
  if (ini < fin){
     int cen = (ini + fin) / 2 ;
     Msort(sec, ini, cen) ;
     Msort(sec, cen+1, fin) ;
     Mezcla(sec, ini, cen, fin) ;
  } 
}

void Mezcla(std::vector<int>& sec, int ini, int cen, int fin) {
    std::vector<int> temp(fin - ini + 1);
    int i = ini, j = cen + 1, k = 0;

    while (i <= cen && j <= fin) {
        if (sec[i] <= sec[j]) {
            temp[k++] = sec[i++];
        } else {
            temp[k++] = sec[j++];
        }
    }

    while (i <= cen) {
        temp[k++] = sec[i++];
    }

    while (j <= fin) {
        temp[k++] = sec[j++];
    }

    for (k = 0; k < temp.size(); ++k) {
        sec[ini + k] = temp[k];
    }
}
