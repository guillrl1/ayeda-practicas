for (int i = 1; i < n; i++) {
  int j = i;
  int x = v[i];
  ini = 0;
  fin = i - 1;
  while (ini <= fin) {
    int mid = (ini+fin) / 2;
    if (v[mid] < x)
      ini = mid+1;
    else 
      fin = mid-1;
  }
  for (int j = i-1; j >= ini; j--) 
    v[j+1] = v[j];
  v[ini] = x;
} 
