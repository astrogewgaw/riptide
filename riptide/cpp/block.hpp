#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstddef> // size_t
#include <type_traits>
#include "kernels.hpp"


namespace riptide {

/* Wraps a pointer that stores a contiguous two-dimensional array */
template <typename T>
class BlockTemplate {

public:
    T* const data;
    const size_t rows;
    const size_t cols;

public:
    BlockTemplate(T* ptr, size_t rows, size_t cols)
        : data(ptr), rows(rows), cols(cols)
        {}

    size_t head_size() const 
        {return rows >> 1;}

    T* rowptr(size_t irow) const 
        {return data + irow * cols;}

    BlockTemplate head() const 
        {return BlockTemplate(data, head_size(), cols);}

    BlockTemplate tail() const 
        {
        const size_t h = head_size();
        return BlockTemplate(rowptr(h), rows - h, cols);
        }
    
    BlockTemplate<std::add_const_t<T>> const_view() const
        {
        return BlockTemplate<std::add_const_t<T>>(data, rows, cols);
        }

}; // class BlockTemplate

/* Wraps a float pointer that stores a contiguous two-dimensional array */
typedef BlockTemplate<float> Block; 

/* Wraps a const float pointer that stores a contiguous two-dimensional array */
typedef BlockTemplate<const float> ConstBlock;

} // namespace riptide

#endif // BLOCK_HPP