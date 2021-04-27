#include <algorithm>
#include <iostream>
#include <vector>

#include "sort_utilities.cpp"

void bubbleSortAiv(std::vector<int>& v, int n) {
  bool isSorted = false;
  for (int i = 0; !isSorted && i < n - 1; ++i) {
    isSorted = true;
    for (int j = 0; j < n - i - 1; ++j) {
      if (v[j] > v[j+1]) {
        std::swap(v[j], v[j+1]);
        isSorted = false;
      }
    }
  }
}

void bubbleSortAivLog(std::vector<int>& v, int n) {
  bool isSorted = false;
  int64_t comparisons = 0, swaps = 0;
  for (int i = 0; !isSorted && i < n - 1; ++i) {
    isSorted = true;
    for (int j = 0; j < n - i - 1; ++j) {
    ++comparisons;
      if (v[j] > v[j+1]) {
        ++swaps;
        std::swap(v[j], v[j+1]);
        isSorted = false;
      }
    }
  }
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nSwaps: " << swaps << '\n';
  std::clog << "T_p: " << comparisons + swaps << '\n';
}

void cocktailShakerSort(std::vector<int>& v, int n) {
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    for (int i = left; i < right; ++i) {
      if (v[i] > v[i+1]) {
        std::swap(v[i], v[i+1]);
      }
    }
    --right;
    for (int i = right - 1; i >= left; --i) {
      if (v[i] > v[i+1]) {
        std::swap(v[i], v[i+1]);
      }
    }
    ++left;
  }
}

void cocktailShakerSortIverLog(std::vector<int>& v, int n) {
  int left = 0;
  int right = n - 1;
  bool isSorted = false;
  int64_t comparisons = 0, swaps = 0;
  while (left <= right && !isSorted) {
    ++comparisons;
    isSorted = true;
    for (int i = left; i < right; ++i) {
    ++comparisons;
      if (v[i] > v[i+1]) {
        ++swaps;
        isSorted = false;
        std::swap(v[i], v[i+1]);
      }
    }
    --right;
    for (int i = right - 1; i >= left; --i) {
    ++comparisons;
      if (v[i] > v[i+1]) {
        ++swaps;
        isSorted = false;
        std::swap(v[i], v[i+1]);
      }
    }
    ++left;
  }
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nSwaps: " << swaps << '\n';
  std::clog << "T_p: " << comparisons + swaps << '\n';
}

void cocktailShakerSortLog(std::vector<int>& v, int n) {
  int left = 0;
  int right = n - 1;
  int64_t comparisons = 0, swaps = 0;
  while (left <= right) {
    ++comparisons;
    for (int i = left; i < right; ++i) {
      ++comparisons;
      if (v[i] > v[i+1]) {
        ++swaps;
        std::swap(v[i], v[i+1]);
      }
    }
    --right;
    for (int i = right - 1; i >= left; --i) {
      ++comparisons;
      if (v[i] > v[i+1]) {
        ++swaps;
        std::swap(v[i], v[i+1]);
      }
    }
    ++left;
  }
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nSwaps: " << swaps << '\n';
  std::clog << "T_p: " << comparisons + swaps << '\n';
}

void merge(int l, int m, int r, std::vector<int>& v);

void mergeSort(int left, int right, std::vector<int>& v) {
  if (left >= right) {
    return;
  }
  int middle = (left + right) / 2;
  mergeSort(left, middle, v);
  mergeSort(middle+1, right, v);
  merge(left, middle, right, v);
}

void merge(int l, int m, int r, std::vector<int>& v) {
  int n1 = m - l + 1, n2 = r - m;
  std::vector<int> left_arr(n1), right_arr(n2);
  for (int i = 0; i < n1; i++) {
      left_arr[i] = v[l + i];
  }
  for (int j = 0; j < n2; j++) {
      right_arr[j] = v[m + 1 + j];
  }
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (left_arr[i] < right_arr[j]) {
      v[k++] = left_arr[i++];
    } else {
      v[k++] = right_arr[j++];
    }
  }
  while (i < n1) {
    v[k++] = left_arr[i++];
  }
  while (j < n2) {
    v[k++] = right_arr[j++];
  }
}

void mergeLog(int l, int m, int r, std::vector<int>& v, int64_t& comparisons, int64_t& moves);

void mergeSortLog(int left, int right, std::vector<int>& v, int64_t& comparisons, int64_t& moves) {
  ++comparisons;
  if (left >= right) { return; }
  int middle = (left + right) / 2;
  mergeSortLog(left, middle, v, comparisons, moves);
  mergeSortLog(middle+1, right, v, comparisons, moves);
  mergeLog(left, middle, right, v, comparisons, moves);
}
void mergeLog(int l, int m, int r, std::vector<int>& v, int64_t& comparisons, int64_t& moves) {
  int n1 = m - l + 1, n2 = r - m;
  std::vector<int> left_arr(n1), right_arr(n2);
  for (int i = 0; i < n1; i++) {
      left_arr[i] = v[l + i]; ++moves;
  }
  for (int j = 0; j < n2; j++) {
      right_arr[j] = v[m + 1 + j]; ++moves;
  }
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    comparisons += 2;
    if (left_arr[i] < right_arr[j]) {
      v[k++] = left_arr[i++]; ++moves;
    } else {
      v[k++] = right_arr[j++]; ++moves;
    }
  }
  while (i < n1) {
      ++comparisons; ++moves;
    v[k++] = left_arr[i++];
  }
  while (j < n2) {
      ++comparisons; ++moves;
    v[k++] = right_arr[j++];
  }
}

void mergeSortLogOutput(int left, int right, std::vector<int>& v) {
  int64_t comparisons = 0, moves = 0;
  mergeSortLog(left, right, v, comparisons, moves);
  std::clog << "Comparisons: " << comparisons;
  std::clog << "\nMoves: " << moves;
  std::clog << "\nT_p: " << comparisons + moves << '\n';
}

/*
void cocktailShakerSortIt(std::vector<int>& v, int n) {
  for (int i = 0; i < n; ++i) {
    for (auto j = v.begin(); j != v.end() - 1; ++j) {
      if (*j > *(j+1)) {
        std::iter_swap(j, j+1);
      }
    }
    for (auto j = v.rbegin(); j != v.rend() - 1; ++j) {
      if (*j > *(j+1)) {
        std::iter_swap(j, j+1);
      }
    }
  }
}
*/

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cout << "Enter the size of an array: ";
  std::cin >> n;
  std::vector<int> arr(n);

//  fillAscendVector(arr);
 fillDescendVector(arr);
  {
      TimeCounter tc;

      cocktailShakerSortLog(arr, n);
  }
  return 0;
}
