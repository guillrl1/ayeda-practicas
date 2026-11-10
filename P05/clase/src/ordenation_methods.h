#ifndef ORDENATION_METHODS_H
#define ORDENATION_METHODS_H

#include "sequence.h"
#include "nif.h"
#include <algorithm>
#include <iostream>

template <typename Key>
void InsertionSort_func(Sequence<Key>& seq, unsigned size, bool trace = false) {
    for (unsigned i = 1; i < size; ++i) {
        Key key = seq[i];
        int j = i - 1;
        while (j >= 0 && seq[j] > key) {
            seq[j + 1] = seq[j];
            --j;
        }
        seq[j + 1] = key;

        if (trace) {
            std::cout << "Paso " << i << ": ";
            for (unsigned k = 0; k < size; ++k)
                std::cout << seq[k] << " ";
            std::cout << std::endl;
        }
    }
}

template <typename Key>
void ShakerSort_func(Sequence<Key>& seq, unsigned size, bool trace = false) {
    bool swapped = true;
    unsigned start = 0;
    unsigned end = size - 1;

    while (swapped) {
        swapped = false;
        for (unsigned i = start; i < end; ++i) {
            if (seq[i] > seq[i + 1]) {
                std::swap(seq[i], seq[i + 1]);
                swapped = true;
            }
        }
        if (trace) {
            std::cout << "Paso adelante: ";
            for (unsigned k = 0; k < size; ++k)
                std::cout << seq[k] << " ";
            std::cout << std::endl;
        }

        if (!swapped) break;
        swapped = false;
        --end;

        for (unsigned i = end; i > start; --i) {
            if (seq[i] < seq[i - 1]) {
                std::swap(seq[i], seq[i - 1]);
                swapped = true;
            }
        }
        if (trace) {
            std::cout << "Paso atrás: ";
            for (unsigned k = 0; k < size; ++k)
                std::cout << seq[k] << " ";
            std::cout << std::endl;
        }

        ++start;
    }
}

template <typename Key>
void QuickSort_func(Sequence<Key>& seq, unsigned size, bool trace = false) {
    if (size > 0)
        QuickSortRecursive(seq, 0, size - 1, trace);
}

template <typename Key>
void QuickSortRecursive(Sequence<Key>& seq, int low, int high, bool trace) {
    if (low < high) {
        int pi = partition(seq, low, high);

        if (trace) {
            std::cout << "Partición en índice " << pi << ": ";
            for (unsigned k = 0; k <= high; ++k)
                std::cout << seq[k] << " ";
            std::cout << std::endl;
        }

        QuickSortRecursive(seq, low, pi - 1, trace);
        QuickSortRecursive(seq, pi + 1, high, trace);
    }
}

template <typename Key>
int partition(Sequence<Key>& seq, int low, int high) {
    Key pivot = seq[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (seq[j] < pivot) {
            ++i;
            std::swap(seq[i], seq[j]);
        }
    }
    std::swap(seq[i + 1], seq[high]);
    return i + 1;
}

template <typename Key>
void HeapSort_func(Sequence<Key>& seq, unsigned size, bool trace = false) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(seq, size, i);
    }

    for (int i = size - 1; i > 0; --i) {
        std::swap(seq[0], seq[i]);
        heapify(seq, i, 0);

        if (trace) {
            std::cout << "Extraído " << i << ": ";
            for (unsigned k = 0; k < size; ++k)
                std::cout << seq[k] << " ";
            std::cout << std::endl;
        }
    }
}

template <typename Key>
void heapify(Sequence<Key>& seq, unsigned size, unsigned i) {
    unsigned largest = i;
    unsigned left = 2 * i + 1;
    unsigned right = 2 * i + 2;

    if (left < size && seq[left] > seq[largest]) {
        largest = left;
    }
    if (right < size && seq[right] > seq[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(seq[i], seq[largest]);
        heapify(seq, size, largest);
    }
}

template <typename Key>
void ShellSort_func(Sequence<Key>& seq, unsigned size, bool trace = false) {
    for (unsigned gap = size / 2; gap > 0; gap /= 2) {
        for (unsigned i = gap; i < size; ++i) {
            Key temp = seq[i];
            unsigned j;

            for (j = i; j >= gap && seq[j - gap] > temp; j -= gap) {
                seq[j] = seq[j - gap];
            }
            seq[j] = temp;
        }

        if (trace) {
            std::cout << "Gap " << gap << ": ";
            for (unsigned k = 0; k < size; ++k)
                std::cout << seq[k] << " ";
            std::cout << std::endl;
        }
    }
}

#endif // ORDENATION_METHODS_H
