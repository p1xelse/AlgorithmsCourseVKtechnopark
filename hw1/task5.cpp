#include <assert.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

/*
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти
сумму длин частей числовой прямой, окрашенных ровно в один слой. N ≤ 10000. Li,
Ri — целые числа в диапазоне [0, 10^9].
*/

template <typename T, typename Comp = std::less<T>>
void merge(T* arr1, int len1, T* arr2, int len2, T* newArr, Comp cmp = Comp()) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < len1 && j < len2) {
        if (cmp(arr1[i], arr2[j])) {
            newArr[k] = arr1[i];
            i++;
        } else {
            newArr[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        newArr[k] = arr1[i];
        i++;
        k++;
    }

    while (j < len2) {
        newArr[k] = arr2[j];
        j++;
        k++;
    }
}

template <typename T, typename Comp = std::less<T>>
void mergeSort(T* arr, int len, Comp cmp = Comp()) {
    if (len <= 1) {
        return;
    }

    int firstLen = len / 2;
    int secondLen = len - firstLen;
    mergeSort(arr, firstLen, cmp);
    mergeSort(arr + firstLen, secondLen, cmp);
    T* c = new T[len];
    merge(arr, firstLen, arr + firstLen, secondLen, c, cmp);
    std::copy(c, c + len, arr);
    delete[] c;
}

struct Layer {
    int index;
    int pos;
    int width = 0;
};

void printArr(Layer* arr, int len) {
    for (int i = 0; i < len; i++) {
        std::cout << "(" << arr[i].index << "," << arr[i].pos << " "
                  << arr[i].width << ") ";
    }

    std::cout << std::endl;
}

class LayerComparator {
 public:
    LayerComparator() {}

    bool operator()(const Layer& l, const Layer& r) {
        return l.index < r.index;
    }
};

void task(std::istream& input, std::ostream& output) {
    int n = 0;
    input >> n;

    int len = n * 2;

    Layer* arr = new Layer[len];
    for (int i = 0; i < len; i++) {
        input >> arr[i].index;
        if (i % 2 == 0) {
            arr[i].pos = 0;
        } else {
            arr[i].pos = 1;
        }
    }

    mergeSort(arr, len, LayerComparator());

    int width = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i].pos == 0) {
            width++;
        } else {
            width--;
        }
        arr[i].width = width;
    }

    int res = 0;
    for (int i = 0; i < len - 1; i++) {
        if (arr[i].width == 1) {
            res += arr[i + 1].index - arr[i].index;
        }
    }

    output << res << std::endl;

    delete[] arr;
}

int main() { task(std::cin, std::cout); }
