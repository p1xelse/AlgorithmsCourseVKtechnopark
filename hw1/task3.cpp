#include <iostream>

/*
Реализовать дек с динамическим зацикленным буфером.
Обрабатывать команды push * и pop *.
*/

#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

class Deque {
   public:
    Deque()
        : capacity(defaultInitSize),
          size(0),
          head(-1),
          tail(-1),
          buffer(nullptr) {}
    explicit Deque(int capacity);
    ~Deque() { delete[] buffer; }

    void pushBack(int a);
    int popFront();
    void pushFront(int a);
    int popBack();

    bool IsEmpty() const { return (head == tail) && (head == -1); }
    bool IsFull() const { return (size == capacity); }

   private:
    void grow();

    int *buffer;
    int capacity;
    int size;
    int head;
    int tail;

    static const int defaultInitSize = 5;
};

Deque::Deque(int size) : capacity(size), size(0), head(-1), tail(-1) {
    buffer = new int[capacity];
}

void Deque::grow() {
    capacity = capacity * 2;
    int *tmp = new int[capacity];
    int i = head;
    int j = 0;
    while (i != tail) {
        tmp[j] = buffer[i];
        i = (i + 1) % size;
        j++;
    }
    tmp[j] = buffer[i];

    head = 0;
    tail = size - 1;

    delete[] buffer;
    buffer = tmp;
}

void Deque::pushBack(int a) {
    if (IsFull()) {
        grow();
    }

    if (IsEmpty()) {
        head = tail = 0;
        buffer[head] = a;
        size++;
        return;
    }

    tail = (tail + 1) % capacity;
    buffer[tail] = a;
    size++;
}

void Deque::pushFront(int a) {
    if (IsFull()) {
        grow();
    }
    if (IsEmpty()) {
        head = tail = 0;
        buffer[tail] = a;
        size++;
        return;
    }

    head = (head - 1 + capacity) % capacity;
    buffer[head] = a;
    size++;
}

int Deque::popBack() {
    assert(IsEmpty() == false);
    int result = buffer[tail];

    if (head == tail) {
        head = tail = -1;
        size--;
        return result;
    }

    tail = (tail - 1 + capacity) % capacity;
    size--;
    return result;
}

int Deque::popFront() {
    assert(IsEmpty() == false);
    int result = buffer[head];

    if (head == tail) {
        head = tail = -1;
        size--;
        return result;
    }

    head = (head + 1) % capacity;
    size--;

    return result;
}

bool cmdHandler(Deque &dq, int cmd, int num) {
    if (dq.IsEmpty() && num == -1 && (cmd == 2 || cmd == 4)) {
        return true;

    } else if (dq.IsEmpty() && num != -1 && (cmd == 2 || cmd == 4)) {
        return false;
    }

    switch (cmd) {
        case 1:
            dq.pushFront(num);
            break;
        case 2:
            return dq.popFront() == num;
        case 3:
            dq.pushBack(num);
            break;
        case 4:
            return dq.popBack() == num;
    }

    return true;
}

void task(std::istream &input, std::ostream &output) {
    int len;
    input >> len;
    Deque dq(len);

    for (int i = 0; i < len; ++i) {
        int cmd, num;
        input >> cmd >> num;
        if (!cmdHandler(dq, cmd, num)) {
            output << "NO" << std::endl;
            return;
        }
    }

    output << "YES";
}

void test() {
    {
        std::stringstream input;
        input << "4 "
              << "1 21 "
              << "3 22 "
              << "1 24 "
              << "4 22 ";
        std::stringstream output;
        task(input, output);

        if (output.str() != std::string("YES"))
            std::cout << "FAIL TEST " << 0 << std::endl;
    }

    {
        std::stringstream input;
        input << "8 "
              << "1 1 "
              << "1 2 "
              << "1 3 "
              << "1 4 "
              << "2 4 "
              << "2 3 "
              << "2 2 "
              << "2 1 ";
        std::stringstream output;
        task(input, output);

        if (output.str() != std::string("YES"))
            std::cout << "FAIL TEST " << 1 << std::endl;
    }

    {
        std::stringstream input;
        input << "8 "
              << "1 1 "
              << "1 2 "
              << "1 3 "
              << "1 4 "
              << "4 1 "
              << "4 2 "
              << "4 3 "
              << "4 4 ";
        std::stringstream output;
        task(input, output);

        if (output.str() != std::string("YES"))
            std::cout << "FAIL TEST " << 2 << std::endl;
    }
}

int main(int argc, const char *argv[]) {
    task(std::cin, std::cout);
    return 0;
}
