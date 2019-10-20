#include <iostream>
#include <algorithm>
#include <string>

template<typename T>
class Heap {
public:
    //Heap() = default;
    Heap() {};
    void Print() {
        for (int i = 0; i < size_; ++i) {
            std::cout << data_[i]<<' ';
        }
    };
    void Read(std::istream& is,size_t i);
    void Heapify() {
        for (int i = size_; i >= 0; --i) {
            ShiftDown(i);
        }
    };
    T Max() {
        return data_[0];
    };
    void DeleteMax() {
        data_[0] = data_[--size_];
        ShiftDown(0);
    };
    void Add(const T& elem) {
        if ( size_ == capacity_) {
            size_t newCapacity = capacity_ == 0 ? 1 : 2*capacity_;
            T* temp = new T[newCapacity];
            for (int i = 0; i < capacity_; ++i) {
                temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            capacity_ = newCapacity;
        }
        data_[size_++] = elem;
        ShiftUp(size_ - 1);
    }
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0 ;
private:
    int Left(int i) { return i*2 + 1;};
    int Right(int i) { return i*2 + 2;};
    int Parent(int i) { return (i-1)/2;};
    void ShiftDown(int i);
    void ShiftUp(int i);

};

template <typename T>
void Heap<T>::ShiftDown(int i) {
    int l = Left(i);
    int r = Right(i);
    int largest = -1;
    if ( l < size_ && data_[l] > data_[i]) {
        largest = l;
    }
    else largest = i;
    if ( r < size_ && data_[r] > data_[largest]) {
        largest = r;
    }
    if ( largest != i ) {
        std::swap(data_[i],data_[largest]);
        ShiftDown(largest);
    }
}

template <typename T>
void Heap<T>::ShiftUp(int i) {
    if (Parent(i) >= 0) {

        std::swap(data_[i],data_[Parent(i)]);
        i = Parent(i);
        if (i == 0)
            return;
        ShiftUp(i);
    }
}

template <typename T>
void Heap<T>::Read(std::istream &is,size_t i) {
    size_ = i;
    capacity_ = i;
    delete[] data_;
    data_ = new T[capacity_];
    for (int j = 0; j < size_; ++j) {
        is >> data_[j];
    }
}





int main() {
    Heap<int> h;
    size_t size;
    std::cin >> size;
    h.Read(std::cin,size);
    h.Print();
    std::cout<<std::endl;
    h.Heapify();
    h.Print();
   // std::cout << h.Max();
    std::cout<<std::endl;
    h.DeleteMax();
    h.Print();
    std::cout<<std::endl;
    int tmp;
    std::cin >> tmp;
    h.Add(tmp);
    h.Print();
    std::cout<<std::endl;
    return 0;
}