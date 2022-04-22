#include <assert.h>

#include <algorithm>
#include <iostream>
#include <iterator>

/*
Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение. Требуемое время работы:
O(m * log k), где k - позиция элементта B[m-1] в массиве A.. В процессе поиска
очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента
B[i-1]. n, k ≤ 10000.
*/

class CArray {
 public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    CArray(int bufferSize);
    CArray(const CArray& object);
    ~CArray() { delete[] buffer; }
    CArray& operator=(const CArray);
    int size() const { return realSize; }
    int operator[](int index) const;
    int& operator[](int index);
    void add(int element);
    void readFromStream(std::istream& input, int len);
    void writeToStream(std::ostream& output) const;

    int binarySearch(int firstElemIndex, int lastElemIndex, int elem);
    int exponentialSearch(int elem);
    CArray getIntersection(const CArray& other);

 private:
    const int kDefaultInitialSize = 10;
    int* buffer;
    int bufferSize;
    int realSize;
    void grow();
};

int& CArray::operator[](int index) {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

int CArray::operator[](int index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

void CArray::grow() {
    int newBufferSize = std::max(bufferSize * 2, CArray::kDefaultInitialSize);
    int* newBuffer = new int[newBufferSize];

    std::copy(buffer, buffer + realSize, newBuffer);

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

void CArray::add(int element) {
    if (realSize == bufferSize) grow();
    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

void CArray::readFromStream(std::istream& input, int len) {
    for (int i = 0; i < len; i++) {
        int curElem;
        input >> curElem;
        add(curElem);
    }
}

void CArray::writeToStream(std::ostream& output) const {
    for (int i = 0; i < realSize; i++) {
        output << buffer[i] << " ";
    }

    std::cout << std::endl;
}

int CArray::binarySearch(int firstElemIndex, int lastElemIndex, int element) {
    int first = firstElemIndex;
    int last = lastElemIndex + 1;

    while (first < last) {
        int mid = (first + last) / 2;

        if (buffer[mid] < element) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }

    return (first == lastElemIndex + 1 || buffer[first] != element) ? -1
                                                                    : first;
}

int CArray::exponentialSearch(int elem) {
    int i = 1;

    while (i < realSize && buffer[i] <= elem) {
        i = i * 2;
    }

    return binarySearch(i / 2, std::min(i, realSize - 1), elem);
}

CArray CArray::getIntersection(const CArray& other) {
    CArray newArray;

    for (int i = 0; i < other.size(); ++i) {
        int index = exponentialSearch(other[i]);
        if (index != -1) {
            newArray.add(buffer[index]);
        }
    }

    return newArray;
}

CArray::CArray(const CArray& object) {
    bufferSize = object.bufferSize;
    realSize = object.realSize;
    std::copy(object.buffer, object.buffer + object.realSize, buffer);
}

CArray& CArray::operator=(const CArray object) {
    bufferSize = object.bufferSize;
    realSize = object.realSize;
    std::copy(object.buffer, object.buffer + object.realSize, buffer);

    return *this;
}

int main() {
    CArray arr;
    CArray arr1;

    int len1 = 0;
    std::cin >> len1;
    int len2 = 0;
    std::cin >> len2;

    arr.readFromStream(std::cin, len1);
    arr1.readFromStream(std::cin, len2);

    CArray newArr = arr.getIntersection(arr1);
    newArr.writeToStream(std::cout);

    return 0;
}