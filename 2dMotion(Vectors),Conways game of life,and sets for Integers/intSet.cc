// intSet.cc
#include "intSet.h"

void intSet::resize() {
    capacity *= 2;
    int* new_data = new int[capacity];
    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
}

intSet::intSet() : data(new int[4]), size(0), capacity(4) {}

intSet::intSet(const intSet& is) : size(is.size), capacity(is.capacity) {
    data = new int[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = is.data[i];
    }
}

intSet::intSet(intSet&& is) : data(is.data), size(is.size), capacity(is.capacity) {
    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;
}

intSet::~intSet() {
    delete[] data;
}

intSet& intSet::operator=(const intSet& is) {
    if (this != &is) {
        delete[] data;
        size = is.size;
        capacity = is.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = is.data[i];
        }
    }
    return *this;
}

intSet& intSet::operator=(intSet&& is) {
    if (this != &is) {
        delete[] data;
        data = is.data;
        size = is.size;
        capacity = is.capacity;
        is.data = nullptr;
        is.size = 0;
        is.capacity = 0;
    }
    return *this;
}

intSet intSet::operator|(const intSet &other) const {
    intSet result(*this);
    for (int i = 0; i < other.size; ++i) {
        result.add(other.data[i]);
    }
    return result;
}

intSet intSet::operator&(const intSet &other) const {
    intSet result;
    for (int i = 0; i < size; ++i) {
        if (other.contains(data[i])) {
            result.add(data[i]);
        }
    }
    return result;
}

bool intSet::operator==(const intSet &other) const {
    if (size != other.size) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        if (!other.contains(data[i])) {
            return false;
        }
    }
    return true;
}

bool intSet::isSubset(const intSet &s) const {
    for (int i = 0; i < size; ++i) {
        if (!s.contains(data[i])) {
            return false;
        }
    }
    return true;
}

bool intSet::contains(int e) const {
    for (int i = 0; i < size; ++i) {
        if (data[i] == e) {
            return true;
        }
    }
    return false;
}

void intSet::add(int e) {
    if (contains(e)) {
        return;
    }
    if (size == capacity) {
        resize();
    }
    data[size++] = e;
}

void intSet::remove(int e) {
    for (int i = 0; i < size; ++i) {
        if (data[i] == e) {
            for (int j = i; j < size - 1; ++j) {
                data[j] = data[j + 1];
            }
            --size;
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const intSet& is) {
    
    out << "(";
    int* sortedElements = new int[is.size];
    for (int i = 0; i < is.size; ++i) {
        sortedElements[i] = is.data[i];
    }
    for (int i = 0; i < is.size - 1; ++i) {
        for (int j = 0; j < is.size - i - 1; ++j) {
            if (sortedElements[j] > sortedElements[j + 1]) {
                int temp = sortedElements[j];
                sortedElements[j] = sortedElements[j + 1];
                sortedElements[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < is.size; ++i) {
        out << sortedElements[i];
        if (i < is.size - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}