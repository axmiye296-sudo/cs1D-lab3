#ifndef V_HPP
#define V_HPP

#include <cstddef>
#include <stdexcept>
#include <cstdlib>
#include <new>
#include <cstring>
#include <iostream>
#include <vector>

template<typename T>
class V {
	private:
		T* data;
		size_t size_;
		size_t capacity_;

	public:
		V() : data(nullptr), size_(0), capacity_(0) {}
 		~V() { delete[] data; }

		V(const V& other) : size_(other.size_), capacity_(other.capacity_) {
        		data = new T[capacity_];
        		for (size_t i = 0; i < size_; i++) {
            			data[i] = other.data[i];
        		}
    		}
		V(V&& other) noexcept : data(other.data), size_(other.size_), capacity_(other.capacity_) {
			other.data = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;
		}

		V& operator=(const V& other) {
			if (this != &other) {
				delete[] data;
				size_ = other.size_;
				capacity_ = other.capacity_;
				data = new T[capacity_];
				for (size_t i = 0; i < size_; i++) {
					data[i] = other.data[i];
				}
			}
			return *this;
		}

		T& operator[](size_t index) {
        		if (index >= size_) {
            		throw std::out_of_range("Index out of bounds");
        		}
        		return data[index];
    		}

    		const T& operator[](size_t index) const {
        		if (index >= size_) {
            		throw std::out_of_range("Index out of bounds");
        		}
        		return data[index];
    		}

    		T* begin() { return data; }
    		T* end() { return data + size_; }
    		const T* begin() const { return data; }
    		const T* end() const { return data + size_; }

    		size_t size() const { return size_; }
    		size_t capacity() const { return capacity_; }
    		bool empty() const { return size_ == 0; }

		void push_back(const T& value) {
			if(size_ == capacity_) {
				size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
				T* new_data = new T[new_capacity];
				for (size_t i = 0; i < size_; i++) {
					new_data[i] = data[i];
				}

				delete[] data;
				data = new_data;
				capacity_ = new_capacity;
			}
			data[size_] = value;
			size_++;
		}

		void clear() {
			delete[] data;
			data = nullptr;
			size_ = 0;
			capacity_ = 0;
		}

};

#endif