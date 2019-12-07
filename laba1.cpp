#include <iostream>
#include <cstdlib>

struct KValue {
    char keys[9];
    unsigned long long value;
};

class TVector {
    int size;
    int capacity;
    KValue* vectorData;
public:
    TVector() {
        size = 0;
        capacity = 0;
        vectorData = new KValue[2];
    }
    TVector(int var) {
        size = var;
        capacity = var;
        vectorData = new KValue[var];
    }
    TVector(int k, KValue* m) {
        size = k;
        capacity = k;
        vectorData = new KValue[k];
        if (k != 0) {
            for (size_t j = 0; j < k; j++) {
                vectorData[j] = m[j];
            }
        }
    }

    KValue& operator[] (int k) {
        return vectorData[k];
    }

    int VectorSize() {
        return size;
    }

    void NewSize() {
        if (capacity == 0) {
            capacity = 1;
        }
        capacity *= 2;
        KValue* temporary = new KValue[capacity];
        for (int j = 0; j < size; j++) {
            temporary[j] = vectorData[j];
        }
        delete [] vectorData;
        vectorData = temporary;
    }

    void PushBack(KValue element) {
        if (size == capacity) {
            NewSize();
        }
        vectorData[size++] = element;
    }
    ~TVector() {
        delete [] vectorData;
    }
};

void RadixSorting(TVector &vector) {
    int digitsC[10] = {};
    int charsC[26] = {};
    TVector temp(vector.VectorSize());
    for (int i = 8; i != 0; i--) {
        if (vector[0].keys[i - 1] == ' ') {
            continue;
        }
        if (vector[0].keys[i - 1] >= '0' && vector[0].keys[i - 1] <= '9') {
            int j = 0;
            int n = 0;
            for (j = 0; j < vector.VectorSize(); j++) {
                digitsC[vector[j].keys[i - 1] - '0'] += 1;
            }
            for (n = 1; n < 10; n++) {
                digitsC[n] += digitsC[n - 1];
            }
            for (j = vector.VectorSize(); j != 0; j--) {
                --digitsC[vector[j - 1].keys[i - 1] - '0'];
                temp[digitsC[vector[j - 1].keys[i - 1] - '0']] = vector[j - 1];
            }
        } else {
            int j = 0;
            int n = 0;
            for (j = 0; j < vector.VectorSize(); j++) {
                charsC[vector[j].keys[i - 1] - 'A'] += 1;
            }
            for (n = 1; n < 26; n++) {
                charsC[n] += charsC[n - 1];
            }
            for (j = vector.VectorSize(); j != 0; j--) {
                --charsC[vector[j - 1].keys[i - 1] - 'A'];
                temp[charsC[vector[j - 1].keys[i - 1] - 'A']] = vector[j - 1];
            }
        }
        for (int k = 0; k < 10; k++) {
            digitsC[k] = 0;
        }
        for (int k = 0; k < 26; k++) {
            charsC[k] = 0;
        }
        for (int m = 0; m < vector.VectorSize(); m++) {
            vector[m] = temp[m];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    TVector dataVector;
    KValue element;

    char string[64] = {};
    char number[32] = {};
    while (true) {
        string[0] = '\0';
        std::cin.getline(string, 64);
        if (std::cin.eof()) {
            break;
        }
        if (std::cin.fail() || (string[0] < 'A')) {
            continue;
        }
        int k = 0;
        int j = 0;
        for (k = 0; k < 8; k++) {
            element.keys[k] = string[k];
        }
        element.keys[8] = '\0';
        while (!(string[k] >= '0' && string[k] <= '9')) {
            k++;
        }
        while (string[k] >= '0' && string[k] <= '9') {
            number[j++] = string[k++];
        }
        element.value = std::strtoull(number, NULL, 10);
        dataVector.PushBack(element);
        for (j = 0; j < 32; j++) {
            number[j] = 0;
        }
        for (k = 0; k < 64; k++) {
            string[k] = 0;
        }
    }
    if (dataVector.VectorSize() != 0) {
        RadixSorting(dataVector);
    }
    for (int j = 0; j < dataVector.VectorSize(); j++) {
        std::cout << dataVector[j].keys << " " << dataVector[j].value << std::endl;
    }
    return 0;
}
