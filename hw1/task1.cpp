/*
Если в числе содержится только один бит со значением 1, записать в выходной
поток OK. Иначе записать FAIL. Необходимо использование битовых операций.
Использование арифметических операций запрещено.
*/

#include <iostream>

bool onlyOneBit(unsigned int num) {
    int count = 0;
    while (num != 0) {
        if (num & 1) {
            count++;
            if (count > 1) {
                return false;
            }
        }
        num = num >> 1;
    }
    if (count == 1) {
        return true;
    }

    return false;
}

void taskOnlyOneBit(std::istream &input, std::ostream &output) {
    unsigned int num;
    input >> num;

    if (onlyOneBit(num)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
}

int main(int argc, const char *argv[]) {
    taskOnlyOneBit(std::cin, std::cout);
    return 0;
}
