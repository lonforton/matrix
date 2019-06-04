#define BOOST_TEST_MODULE matrix_test_module

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include <random>

#include "matrix.h"

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

BOOST_AUTO_TEST_CASE(matrix_empty_test)
{
   Matrix<int, -1> matrix;
   BOOST_CHECK(matrix.size() == 0);  
}

BOOST_AUTO_TEST_CASE(matrix_empty_test_after_query)
{
   Matrix<int, -1> matrix;
   auto a = matrix[0][0];  
   BOOST_CHECK(matrix.size() == 0); 
   BOOST_CHECK(a == -1);
}

BOOST_AUTO_TEST_CASE(matrix_default_value_test)
{
   Matrix<int, -5> matrix;
   auto a = matrix[0][0];  
   BOOST_CHECK(matrix.size() == 0); 
   BOOST_CHECK(a == -5);
}

BOOST_AUTO_TEST_CASE(matrix_type_test)
{
    Matrix<long long, std::numeric_limits<long>::max() - 10> matrix;
    auto a = matrix[0][0];  
    BOOST_CHECK(matrix.size() == 0); 
    BOOST_CHECK(a == std::numeric_limits<long>::max() - 10);
}

BOOST_AUTO_TEST_CASE(matrix_fill_test)
{
  Matrix<int, -1> matrix;

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1, std::numeric_limits<int>::max() - 1);

  for (int i = 0; i < 100; ++i)
  {
    int row_roll = distribution(generator);
    int column_roll = distribution(generator);
    int value = distribution(generator);

    BOOST_CHECK(matrix[row_roll][column_roll] == -1);

    matrix[row_roll][column_roll] = value;

    BOOST_CHECK(matrix[row_roll][column_roll] == value);
  }
}

BOOST_AUTO_TEST_SUITE_END()