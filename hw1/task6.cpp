/*
Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <cassert>
#include <iostream>

template <typename T, typename Comparator = std::less<T>>
int findMedian(T *arr, int l, int r, Comparator cmp = Comparator()) {
    int centerElemIndex = (l + r) / 2;
    if (cmp(arr[l], arr[r])) {
        if (cmp(arr[centerElemIndex], arr[l])) {
            return l;
        }

        if (arr[centerElemIndex], arr[r]) {
            return centerElemIndex;
        } else {
            return r;
        }
    }

    if (cmp(arr[centerElemIndex], arr[r])) {
        return r;
    }

    if (arr[centerElemIndex], arr[l]) {
        return centerElemIndex;
    } else {
        return l;
    }
}

template <typename T, typename Comparator = std::less<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
    assert(arr != nullptr);
    int pivotIndex = findMedian(arr, l, r, cmp);
    std::swap(arr[pivotIndex], arr[r]);
    T pivot = arr[r];
    
    int i = 0;
    int j = 0;
    while (i < r && j < r) {
        if (cmp(pivot, arr[j])) {
            j++;
        } else {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }

    std::swap(arr[i], arr[r]);
    return i;
}

template <typename T, typename Comparator = std::less<T>>
T kth_stat(T *arr, int k, int l, int r, Comparator cmp = Comparator()) {
    int pivot_pos = partition(arr, l, r, cmp);

    while (pivot_pos != k) {
        if (pivot_pos > k) {
            r = pivot_pos - 1;
            pivot_pos = partition(arr, l, r, cmp);
        } else if (pivot_pos < k) {
            l = pivot_pos + 1;
            pivot_pos = partition(arr, l, r, cmp);
        }
    }

    return arr[pivot_pos];
}

void task(std::istream &input, std::ostream &output) {
    int n = 0;
    input >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        input >> arr[i];
    }

    int p10 = kth_stat(arr, 10 * n / 100, 0, n - 1);
    int pm = kth_stat(arr, n / 2, 0, n - 1);
    int p90 = kth_stat(arr, 90 * n / 100, 0, n - 1);

    output << p10 << std::endl << pm << std::endl << p90 << std::endl;

    delete[] arr;
}

int main(int argc, const char *argv[]) {
    task(std::cin, std::cout);
    return 0;
}