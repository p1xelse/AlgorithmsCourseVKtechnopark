/*
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше
1000000. Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include <cassert>
#include <iostream>
#include <ctype.h>

class ByteNumber {
 private:
    int64_t number;

 public:
    ByteNumber() = default;
    static const int ByteCount = 8;
    explicit ByteNumber(int number) : number(number) {}
    int64_t getNumber() const { return number; }
    void setNumber(int64_t num) { number = num; }
    int operator[](int numByte) { return (number >> (8 * numByte)) & 0xFF; }
};

void LSDByteSort(ByteNumber *arr, size_t n, int byteNum) {
    assert(arr != nullptr);
    assert(n > 0);

    int minVal = arr[0][byteNum];
    int maxVal = arr[0][byteNum];

    for (int i = 1; i < n; i++) {
        minVal = std::min(minVal, arr[i][byteNum]);
        maxVal = std::max(maxVal, arr[i][byteNum]);
    }

    int countBufSize = maxVal - minVal + 1;
    int *countBuf = new int[countBufSize]();

    for (int i = 0; i < n; i++) {
        countBuf[arr[i][byteNum] - minVal]++;
    }

    for (int i = 1; i < countBufSize; i++) {
        countBuf[i] += countBuf[i - 1];
    }

    ByteNumber *tmpBuf = new ByteNumber[n];

    for (int i = n - 1; i >= 0; i--) {
        int countBufPos = arr[i][byteNum] - minVal;
        countBuf[countBufPos]--;
        tmpBuf[countBuf[countBufPos]] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = tmpBuf[i];
    }

    delete[] countBuf;
    delete[] tmpBuf;
}

void LSDSort(int64_t *arr, int len) {
    ByteNumber *newArr = new ByteNumber[len];

    for (int i = 0; i < len; i++) {
        newArr[i].setNumber(arr[i]);
    }

    for (int i = 0; i < ByteNumber::ByteCount; i++) {
        LSDByteSort(newArr, len, i);
    }

    for (int i = 0; i < len; i++) {
        arr[i] = newArr[i].getNumber();
    }

    delete[] newArr;
}

void printArr(int64_t *arr, int len, std::ostream &output) {
    for (int i = 0; i < len; i++) {
        output << arr[i] << " ";
    }

    output << std::endl;
}

void task(std::istream &input, std::ostream &output) {
    int n = 0;
    input >> n;

    int64_t *arr = new int64_t[n];
    for (int i = 0; i < n; i++) {
        input >> arr[i];
    }

    LSDSort(arr, n);
    printArr(arr, n, output);

    delete[] arr;
}

int main() {
    task(std::cin, std::cout);
    return 0;
}
