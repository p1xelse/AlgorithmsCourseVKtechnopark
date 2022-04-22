/*
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор
пользователя, посещаемость сайта). Напишите программу, которая выбирает K
пользователей, которые чаще других заходили на сайт, и выводит их в порядке
возрастания посещаемости. Количество заходов и идентификаторы пользователей не
повторяются.
*/

#include <assert.h>

#include <algorithm>
#include <iostream>

template <typename T>
class CArray {
 public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    explicit CArray(int bufferSize);
    CArray(const CArray& object);
    ~CArray() { delete[] buffer; }
    CArray& operator=(const CArray);
    int size() const { return realSize; }
    T operator[](int index) const;
    T& operator[](int index);
    void add(T element);
    void deleteLast();

 private:
    const int kDefaultInitialSize = 10;
    T* buffer;
    int bufferSize;
    int realSize;
    void grow();
};

template <typename T>
T& CArray<T>::operator[](int index) {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

template <typename T>
T CArray<T>::operator[](int index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

template <typename T>
void CArray<T>::grow() {
    int newBufferSize = std::max(bufferSize * 2, CArray::kDefaultInitialSize);
    T* newBuffer = new T[newBufferSize];

    std::copy(buffer, buffer + realSize, newBuffer);

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template <typename T>
void CArray<T>::add(T element) {
    if (realSize == bufferSize) {
        grow();
    }

    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

template <typename T>
CArray<T>::CArray(int capacity) : bufferSize(capacity), realSize(0) {
    buffer = new T[capacity];
}

template <typename T>
CArray<T>::CArray(const CArray& object) {
    bufferSize = object.bufferSize;
    realSize = object.realSize;
    std::copy(object.buffer, object.buffer + object.realSize, buffer);
}

template <typename T>
CArray<T>& CArray<T>::operator=(const CArray<T> object) {
    bufferSize = object.bufferSize;
    realSize = object.realSize;
    std::copy(object.buffer, object.buffer + object.realSize, buffer);

    return *this;
}

template <typename T>
void CArray<T>::deleteLast() {
    realSize--;
}

template <typename T, typename Comparator>
class MinHeap {
 public:
    MinHeap() = default;
    explicit MinHeap(int capacity;
    ~MinHeap() = default;

    int size();

    T extractMin();
    T getMin() { return arr[0]; }
    void insert(T key);

 private:
    CArray<T> arr;
    Comparator cmp;
    void siftDown(int i);
    void siftUp(int i);

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
};

template <typename T, typename Comparator>
MinHeap<T, Comparator>::MinHeap(int capacity) : arr(capacity) {}

template <typename T, typename Comparator>
void MinHeap<T, Comparator>::siftUp(int index) {
    while (index > 0) {
        if (!cmp(arr[index], arr[parent(index)])) return;
        std::swap(arr[index], arr[parent(index)]);
        index = parent(index);
    }
}

template <typename T, typename Comparator>
void MinHeap<T, Comparator>::insert(T element) {
    arr.add(element);
    siftUp(arr.size() - 1);
}

template <typename T, typename Comparator>
int MinHeap<T, Comparator>::size() {
    return arr.size();
}

template <typename T, typename Comparator>
void MinHeap<T, Comparator>::siftDown(int i) {
    int smallest = i;

    if (left(i) < arr.size() && cmp(arr[left(i)], arr[i])) {
        smallest = left(i);
    }

    if (right(i) < arr.size() && cmp(arr[right(i)], arr[smallest])) {
        smallest = right(i);
    }

    if (smallest != i) {
        std::swap(arr[i], arr[smallest]);
        siftDown(smallest);
    }
}

template <typename T, typename Comparator>
T MinHeap<T, Comparator>::extractMin() {
    assert(arr.size());
    T result = arr[0];

    arr[0] = arr[arr.size() - 1];
    arr.deleteLast();

    if (arr.size()) {
        siftDown(0);
    }

    return result;
}

struct Person {
    int id;
    int frequency;
};

class PersonComparator {
 public:
    bool operator()(const Person& l, const Person& r) {
        return l.frequency < r.frequency;
    }
};

void taskTopPersons(std::istream& input, std::ostream& output) {
    int N;
    int K;

    input >> N;
    input >> K;

    MinHeap<struct Person, PersonComparator> heap(K);

    for (int i = 0; i < N; i++) {
        Person curPerson;
        input >> curPerson.id;
        input >> curPerson.frequency;
        heap.insert(curPerson);

        if (heap.size() > K) {
            heap.extractMin();
        }
    }

    int sizeHeap = heap.size();

    for (int i = 0; i < sizeHeap; i++) {
        output << heap.extractMin().id << " ";
    }
    output << std::endl;
}

int main() {
    taskTopPersons(std::cin, std::cout);
    return 0;
}
