#include <climits>
#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

int partition(vector<int> &arr, int l, int r, int pivot) {
  int pivotIndex =
      distance(arr.begin(), find(arr.begin() + l, arr.begin() + r, pivot));
  swap(arr[pivotIndex], arr[r]);

  int i = l - 1;
  for (int j = l; j < r; j++) {
    if (arr[j] <= pivot) {
      swap(arr[++i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[r]);

  return i + 1;
}

int findMedian(vector<int> &arr, int l, int r) {
  sort(arr.begin() + l, arr.begin() + r + 1);

  return arr[l + (r - l) / 2];
}

int BFPRT(vector<int> &arr, int l, int r, int k, int G) {
  if (l == r)
    return arr[l];

  int size = r - l + 1;
  vector<int> medians;
  int rounds = size / G;
  for (int i = 0; i < rounds; ++i) {
    int start = l + i * G;
    medians.push_back(findMedian(arr, start, start + G - 1));
  }
  if (size % G != 0) {
    medians.push_back(findMedian(arr, l + rounds * G, r));
  }
  int sizeM = medians.size();
  int median = BFPRT(medians, 0, sizeM - 1, sizeM / 2, G);

  int p = partition(arr, l, r, median);
  int q = p - l + 1;
  if (q == k) {
    return arr[p];
  } else if (q > k) {
    return BFPRT(arr, l, p - 1, k, G);
  } else {
    return BFPRT(arr, p + 1, r, k - q, G);
  }
}

int randomizedPartition(vector<int> &arr, int l, int r) {
  int randomIndex = rand() % (r - l + 1) + l;

  return partition(arr, l, r, arr[randomIndex]);
}

int randomizedSelect(vector<int> &arr, int l, int r, int k) {
  if (l == r)
    return arr[l];

  int p = randomizedPartition(arr, l, r);
  int q = p - l + 1;
  if (q == k) {
    return arr[p];
  } else if (q > k) {
    return randomizedSelect(arr, l, p - 1, k);
  } else {
    return randomizedSelect(arr, p + 1, r, k - q);
  }
}

int main() {
  //   string input;
  //   int N, K, G;
  //   getline(cin, input);
  //   size_t pos1 = input.find(' ');
  //   N = stoi(input.substr(0, pos1));
  //   size_t pos2 = input.find(' ', pos1 + 1);
  //   K = stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
  //   G = stoi(input.substr(pos2 + 1));
  //   cout << N << " " << K << " " << G << endl;
  int N = 10000000, K = 9527;
  int groups[] = {3, 5, 7, 9};

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(0, INT_MAX);

  vector<int> arr(N);
  for (int i = 0; i < N; i++) {
    arr[i] = dist(gen);
  }

  clock_t start, end;
  int repeat = 100;
  int clockCount = 0;
  int kth;
  while (repeat--) {
    start = clock();
    kth = randomizedSelect(arr, 0, N - 1, K);
    end = clock();
    clockCount += end - start;
  }
  printf("Find %dth smallest element = %d with Randomized Select in %fsec\n", K,
         kth, (double)clockCount / CLOCKS_PER_SEC / 100);

  for (int G : groups) {
    int repeat = 100;
    int clockCount = 0;
    int kth;
    while (repeat--) {
      start = clock();
      kth = BFPRT(arr, 0, N - 1, K, G);
      end = clock();
      clockCount += end - start;
    }
    printf("Find %dth smallest element = %d with group size = %d in %fsec\n", K,
           kth, G, (double)clockCount / CLOCKS_PER_SEC / 100);
  }

  // sort(arr.begin(), arr.end(), [](int &a, int &b) { return a < b; });
  // cout << arr[K - 1] << endl;

  return 0;
}
