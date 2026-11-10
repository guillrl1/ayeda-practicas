#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include "nif.h"
#include "sort_method.h"

using namespace std;
using namespace chrono;

const unsigned NUM_ELEMENTS = 100000;

template <typename SortT>
void BenchmarkSort(const staticSequence<nif>& original_seq, const string& name) {
  staticSequence<nif> seq_copy = original_seq;  // Copia original para cada sort
  unique_ptr<SortMethod<nif>> sorter = make_unique<SortT>(seq_copy, false);

  auto start = high_resolution_clock::now();
  sorter->sort();
  auto end = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(end - start);
  cout << name << " → Tiempo: " << duration.count() << " µs\n";
  cout << "Primeros 10 NIFs ordenados: ";
  for (unsigned i = 0; i < min(10u, sorter->getSeq().getSize()); ++i)
    cout << sorter->getSeq()[i] << " ";
  cout << "\n\n";
}

int main() {
  cout << "Generando " << NUM_ELEMENTS << " NIFs aleatorios...\n";
  staticSequence<nif> original_seq(NUM_ELEMENTS);
  for (unsigned i = 0; i < NUM_ELEMENTS; ++i)
    original_seq.insert(nif{});

  BenchmarkSort<InsertionSort<nif>>(original_seq, "InsertionSort");
  BenchmarkSort<ShakerSort<nif>>(original_seq, "ShakerSort");
  BenchmarkSort<QuickSort<nif>>(original_seq, "QuickSort");
  BenchmarkSort<HeapSort<nif>>(original_seq, "HeapSort");
  BenchmarkSort<ShellSort<nif>>(original_seq, "ShellSort");

  return 0;
}
