#pragma once
#include <iostream>

template<typename T>
class TVector {
public:
    TVector() = default;

    TVector(size_t size) {
        Data = new T[size];
        SizeVector = size;
        Capacity = size;
    }

    TVector(const TVector &o) {
        Data = new T[o.SizeVector];
        SizeVector = o.SizeVector;
        Capacity = o.SizeVector;
        for (size_t i = 0; i < SizeVector;++i) {
            Data[i] = o.Data[i];
        }
    }

    ~TVector() {
        delete[] Data;
    }

    T &operator[](size_t number) {
        return Data[number];
    }

    const T &operator[](size_t number) const {
        return Data[number];
    }

    void Push_back(const T &elem) {
        if (SizeVector == Capacity) {
            size_t new_cap = Capacity == 0 ? 1 : Capacity * 2;
            T *temp = new T[new_cap];
            for (size_t i = 0; i < SizeVector;++i) {
                temp[i] = Data[i];
            }
            delete[] Data;
            Data = temp;
            Capacity = new_cap;
        }
        Data[SizeVector] = elem;
        SizeVector++;
    }

    TVector &operator=(const TVector &o) {
        if (o.SizeVector <= Capacity) {
            for (size_t i = 0; i < o.SizeVector;++i) {
                Data[i] = o.Data[i];
            }
            SizeVector = o.SizeVector;
        } else {
            delete[] Data;
            Data = new T[o.SizeVector];
            SizeVector = o.SizeVector;
            Capacity = o.SizeVector;
            for (size_t i = 0; i < o.SizeVector;++i) {
                Data[i] = o.Data[i];
            }
        }

        return *this;
    }

    size_t Size() const {
        return SizeVector;
    }

private:
    T *Data = nullptr;
    size_t SizeVector = 0;
    size_t Capacity = 0;
};

struct KV {
    unsigned short key;
    char value[65];
};

std::istream &operator>>(std::istream &is, KV &elem) {
    is >> elem.key >> elem.value;
    return is;
}

std::ostream &operator<<(std::ostream &is, KV &elem) {
    is << elem.key << '\t' << elem.value;
    return is;
}

