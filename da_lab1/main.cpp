
#include <iostream>
//#include "vector.h"
#include <algorithm>




template<typename T>
class TVector {
public:
    TVector() = default;

    T* begin() {
        return Data;
    }

    T* end() {
        return Data + SizeVector;
    }

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

struct sort_class{
    bool operator() (KV i,KV j){
        return (i.key < j.key);
    }
} sort_object;




const int COUNT_CONST = 65;


TVector<KV> Counting(const TVector<KV> &v, int max) {
    if (v.Size() == 0) {
        return {};
    }
    TVector<KV> tmp(v.Size());
    TVector<int> a(max + 1);
    for (size_t i = 0; i < max + 1; ++i) {
        a[i] = 0;
    }
    for (size_t i = 0; i < v.Size(); ++i) {
        a[v[i].key]++;
    }
    for (int i = 1; i < max + 1; ++i) {
        a[i] += a[i - 1];
    }
    for (int i = v.Size() - 1; i >= 0; --i) {
        int temp_int = v[i].key;
        tmp[a[v[i].key] - 1] = v[i];
        a[temp_int] -= 1;
    }
    return tmp;

}

void Filling(char *c) {
    for (size_t i = 0; i < COUNT_CONST; ++i) {
        c[i] = '\0';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    TVector<KV> input_vector;
    KV lol;
    Filling(lol.value);
    int max_key = -1;
    while (std::cin >> lol) {
        input_vector.Push_back(lol);
        if (lol.key > max_key) {
            max_key = lol.key;
        }
        Filling(lol.value);
    }
    std::sort(input_vector.begin(),input_vector.end(), sort_object);
    //TVector<KV> res = Counting(input_vector, max_key);
    for (size_t i = 0; i < input_vector.Size(); ++i) {
        std::cout << input_vector[i] << std::endl;
    }
    return 0;
}