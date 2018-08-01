#ifndef TUPLE_VECTORS_H
#define TUPLE_VECTORS_H

#include <vector>
#include <type_traits>
#include <iostream>
#include <cstdlib>

// Initialize a vector with random data
template<typename T>
void initialize_vector(std::vector<T>& v, const size_t column_length, const size_t column_range)
{
 v.resize(column_length);
 std::generate(v.begin(), v.end(), [column_range](){return std::rand() % column_range;});
}

//compile time recursion to initialize a tuple of vectors
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
initialize_tuple(std::tuple<std::vector<Tp>...>& t, size_t column_length, size_t column_range)
{
 //bottom of compile-time recursion
 //purposely empty...
}
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
initialize_tuple(std::tuple<std::vector<Tp>...>& t, size_t column_length, size_t column_range)
{
  // Initialize the current vector
 initialize_vector(std::get<I>(t), column_length, column_range);

 //recurse to next vector in tuple
 initialize_tuple<I + 1, Tp...>(t, column_length, column_range);
}


// Prints a vector 
template<typename T>
void print_vector(std::vector<T>& v)
{
 std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, ", "));
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
print_tuple(std::tuple<std::vector<Tp>...>& t)
{
 //bottom of compile-time recursion
 //purposely empty...
}

//compile time recursion to print a tuple of vectors
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
print_tuple(std::tuple<std::vector<Tp>...>& t)
{
 // print the current vector:
 print_vector(std::get<I>(t));
 std::cout << std::endl;

 //recurse to next vector in tuple
 print_tuple<I + 1, Tp...>(t);
}



// compile time recursion to compute the element wise equality of two rows 
// in two tuples of vectors
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == (sizeof...(Tp)), bool>::type
rows_equal(const std::tuple<std::vector<Tp>...>& left, const std::tuple<std::vector<Tp>...>& right, const size_t left_index, const size_t right_index)
{
    // bottom of recursion
    // If we reach this point, we know the ve
    return true;
}
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), bool>::type
rows_equal(const std::tuple<std::vector<Tp>...>& left, const std::tuple<std::vector<Tp>...>& right, const size_t left_index, const size_t right_index)
{
    if(std::get<I>(left)[left_index] == std::get<I>(right)[right_index]){
        return rows_equal<I + 1, Tp...>(left, right, left_index, right_index);
    }
    else
        return false;
}

#endif
