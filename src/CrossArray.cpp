#include "../include/CrossArray.hpp"

namespace sjtu {

CrossArray::CrossArray(int lines) {
    max_lines = lines;
    current_lines = 0;
    arrays = new int*[max_lines];
    sizes = new int[max_lines];
    
    // Initialize all pointers to nullptr and sizes to 0
    for (int i = 0; i < max_lines; i++) {
        arrays[i] = nullptr;
        sizes[i] = 0;
    }
}

CrossArray::CrossArray(const CrossArray & o) {
    // Copy basic properties
    max_lines = o.max_lines;
    current_lines = o.current_lines;
    
    // Allocate memory for arrays and sizes
    arrays = new int*[max_lines];
    sizes = new int[max_lines];
    
    // Copy each array
    for (int i = 0; i < current_lines; i++) {
        sizes[i] = o.sizes[i];
        if (sizes[i] > 0) {
            arrays[i] = new int[sizes[i]];
            for (int j = 0; j < sizes[i]; j++) {
                arrays[i][j] = o.arrays[i][j];
            }
        } else {
            arrays[i] = nullptr;
        }
    }
    
    // Initialize remaining arrays to nullptr
    for (int i = current_lines; i < max_lines; i++) {
        arrays[i] = nullptr;
        sizes[i] = 0;
    }
}

CrossArray::~CrossArray() {
    // Delete each allocated array
    for (int i = 0; i < max_lines; i++) {
        delete[] arrays[i];
    }
    
    // Delete the arrays and sizes pointers
    delete[] arrays;
    delete[] sizes;
}

bool CrossArray::InsertArrays(const int * Input, int size) {
    // Check if we can insert another array
    if (current_lines >= max_lines) {
        return false;
    }
    
    // Allocate memory for the new array
    arrays[current_lines] = new int[size];
    sizes[current_lines] = size;
    
    // Copy the input data
    for (int i = 0; i < size; i++) {
        arrays[current_lines][i] = Input[i];
    }
    
    // Increment the count of current lines
    current_lines++;
    
    return true;
}

void CrossArray::AppendArrays(const int * Input, int Line, int size) {
    // Calculate new size
    int new_size = sizes[Line] + size;
    
    // Allocate new array with the combined size
    int* new_array = new int[new_size];
    
    // Copy existing elements
    for (int i = 0; i < sizes[Line]; i++) {
        new_array[i] = arrays[Line][i];
    }
    
    // Copy new elements
    for (int i = 0; i < size; i++) {
        new_array[sizes[Line] + i] = Input[i];
    }
    
    // Delete old array and update pointer
    delete[] arrays[Line];
    arrays[Line] = new_array;
    sizes[Line] = new_size;
}

CrossArray& CrossArray::WhichGreater(CrossArray & o) {
    // Calculate total number of elements in this object
    int this_count = 0;
    for (int i = 0; i < current_lines; i++) {
        this_count += sizes[i];
    }
    
    // Calculate total number of elements in o
    int o_count = 0;
    for (int i = 0; i < o.current_lines; i++) {
        o_count += o.sizes[i];
    }
    
    // Return the one with more elements, or this if equal
    if (this_count >= o_count) {
        return *this;
    } else {
        return o;
    }
}

bool CrossArray::IsSame(const CrossArray & o) {
    // Check if both objects point to the same memory location
    return this == &o;
}

void CrossArray::DoubleCrossLength() {
    // Create new arrays with double the capacity
    int new_max_lines = max_lines * 2;
    int** new_arrays = new int*[new_max_lines];
    int* new_sizes = new int[new_max_lines];
    
    // Copy existing data
    for (int i = 0; i < max_lines; i++) {
        new_arrays[i] = arrays[i];
        new_sizes[i] = sizes[i];
    }
    
    // Initialize new positions to nullptr
    for (int i = max_lines; i < new_max_lines; i++) {
        new_arrays[i] = nullptr;
        new_sizes[i] = 0;
    }
    
    // Update member variables
    delete[] arrays;
    delete[] sizes;
    arrays = new_arrays;
    sizes = new_sizes;
    max_lines = new_max_lines;
}

const int* CrossArray::AtArray(int i) {
    // Return the pointer to the i-th array
    return arrays[i];
}

int& CrossArray::At(int i, int j) {
    // Return reference to the j-th element of the i-th array
    return arrays[i][j];
}

}