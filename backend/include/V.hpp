/**
 * @file V.hpp
 * @brief Custom vector implementation template class
 */

 #ifndef V_HPP
 #define V_HPP
 
 #include <cstddef>
 #include <stdexcept>
 #include <cstdlib>
 #include <new>
 #include <cstring>
 #include <iostream>
 #include <vector>
 
 /**
  * @class V
  * @brief Custom vector implementation with dynamic memory management
  * @tparam T The type of elements stored in the vector
  * 
  * This is a custom implementation of a dynamic array (vector) that provides
  * similar functionality to std::vector but with custom memory management.
  * It supports dynamic resizing, element access, and basic container operations.
  */
 template<typename T>
 class V {
 private:
	T* data;           ///< Pointer to the dynamically allocated array
	size_t size_;      ///< Current number of elements in the vector
	size_t capacity_;  ///< Current capacity of the allocated array
 
 public:
	/**
	 * @brief Default constructor
	 * 
	 * Creates an empty vector with no elements and no allocated memory.
	 */
	V() : data(nullptr), size_(0), capacity_(0) {}
	
	/**
	 * @brief Destructor
	 * 
	 * Frees the dynamically allocated memory.
	 */
	~V() { delete[] data; }
 
	/**
	 * @brief Copy constructor
	 * @param other The vector to copy from
	 * 
	 * Creates a new vector as a copy of the existing vector.
	 */
	V(const V& other) : size_(other.size_), capacity_(other.capacity_) {
	    data = new T[capacity_];
	    for (size_t i = 0; i < size_; i++) {
		   data[i] = other.data[i];
	    }
	}
	
	/**
	 * @brief Move constructor
	 * @param other The vector to move from
	 * 
	 * Creates a new vector by moving resources from another vector.
	 */
	V(V&& other) noexcept : data(other.data), size_(other.size_), capacity_(other.capacity_) {
	    other.data = nullptr;
	    other.size_ = 0;
	    other.capacity_ = 0;
	}
 
	/**
	 * @brief Copy assignment operator
	 * @param other The vector to assign from
	 * @return Reference to this vector
	 * 
	 * Assigns the contents of another vector to this vector.
	 */
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
 
	/**
	 * @brief Element access operator (non-const)
	 * @param index The index of the element to access
	 * @return Reference to the element at the specified index
	 * @throws std::out_of_range if index is out of bounds
	 */
	T& operator[](size_t index) {
	    if (index >= size_) {
		   throw std::out_of_range("Index out of bounds");
	    }
	    return data[index];
	}
 
	/**
	 * @brief Element access operator (const)
	 * @param index The index of the element to access
	 * @return Const reference to the element at the specified index
	 * @throws std::out_of_range if index is out of bounds
	 */
	const T& operator[](size_t index) const {
	    if (index >= size_) {
		   throw std::out_of_range("Index out of bounds");
	    }
	    return data[index];
	}
 
	// Iterator support
	/**
	 * @brief Get iterator to beginning
	 * @return Pointer to the first element
	 */
	T* begin() { return data; }
	
	/**
	 * @brief Get iterator to end
	 * @return Pointer to one past the last element
	 */
	T* end() { return data + size_; }
	
	/**
	 * @brief Get const iterator to beginning
	 * @return Const pointer to the first element
	 */
	const T* begin() const { return data; }
	
	/**
	 * @brief Get const iterator to end
	 * @return Const pointer to one past the last element
	 */
	const T* end() const { return data + size_; }
 
	// Capacity methods
	/**
	 * @brief Get the current size
	 * @return The number of elements in the vector
	 */
	size_t size() const { return size_; }
	
	/**
	 * @brief Get the current capacity
	 * @return The capacity of the allocated array
	 */
	size_t capacity() const { return capacity_; }
	
	/**
	 * @brief Check if the vector is empty
	 * @return True if the vector has no elements, false otherwise
	 */
	bool empty() const { return size_ == 0; }
 
	/**
	 * @brief Add an element to the end of the vector
	 * @param value The value to add
	 * 
	 * Adds a new element to the end of the vector, resizing if necessary.
	 */
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
 
	/**
	 * @brief Clear all elements from the vector
	 * 
	 * Removes all elements and frees the allocated memory.
	 */
	void clear() {
	    delete[] data;
	    data = nullptr;
	    size_ = 0;
	    capacity_ = 0;
	}
 };
 
 #endif