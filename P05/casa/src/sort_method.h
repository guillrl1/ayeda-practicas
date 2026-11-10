#ifndef SORT_METHOD_H
#define SORT_METHOD_H

#include "sequence.h"
#include "ordenation_methods.h"

template <typename Key>
class SortMethod {
 protected:
  staticSequence<Key> seq_; // Secuencia a ordenar
  bool trace_;
 public:
  SortMethod(const staticSequence<Key>& seq, bool trace = false)
    : seq_(seq), trace_(trace) {}

  virtual void sort() = 0;

  const staticSequence<Key>& getSeq() const {
    return seq_;
  }

  virtual ~SortMethod() = default;
};


template <typename Key>
class InsertionSort : public SortMethod<Key> {
 public:
  InsertionSort(const staticSequence<Key>& seq, bool trace = false)
    : SortMethod<Key>(seq, trace) {}

  void sort() override {
    InsertionSort_func<Key>(this->seq_, this->seq_.getSize(), this->trace_);
  }
};

template <typename Key>
class ShakerSort : public SortMethod<Key> {
 public:
  ShakerSort(const staticSequence<Key>& seq, bool trace = false)
    : SortMethod<Key>(seq, trace) {}

  void sort() override {
    ShakerSort_func<Key>(this->seq_, this->seq_.getSize(), this->trace_);
  }
};

template <typename Key>
class QuickSort : public SortMethod<Key> {
 public:
  QuickSort(const staticSequence<Key>& seq, bool trace = false)
    : SortMethod<Key>(seq, trace) {}

  void sort() override {
    QuickSort_func<Key>(this->seq_, this->seq_.getSize(), this->trace_);
  }
};

template <typename Key>
class HeapSort : public SortMethod<Key> {
 public:
  HeapSort(const staticSequence<Key>& seq, bool trace = false)
    : SortMethod<Key>(seq, trace) {}

  void sort() override {
    HeapSort_func<Key>(this->seq_, this->seq_.getSize(), this->trace_);
  }
};

template <typename Key>
class ShellSort : public SortMethod<Key> {
 public:
  ShellSort(const staticSequence<Key>& seq, bool trace = false)
    : SortMethod<Key>(seq, trace) {}

  void sort() override {
    ShellSort_func<Key>(this->seq_, this->seq_.getSize(), this->trace_);
  }
};

#endif // SORT_METHOD_H
