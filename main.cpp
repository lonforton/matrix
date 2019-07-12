#include <iostream>
#include <cassert>
#include <limits>

#include "matr.h"

int main()
{
  const int matrix_dimension = 10;

  Matrix<int, 0> matrix;
  for (int i = 0; i < matrix_dimension; ++i)
  {
    matrix[i][i] = i;
    matrix[matrix_dimension - i - 1][i] = matrix_dimension - i - 1;
  }

  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 10; j++)
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Occupied cells: " << matrix.size() << std::endl;   

  int x;
  int y;
  int v;
  for(auto c : matrix)
  {
    std::tie(x, y, v) = c;
    std::cout << x << " " << y << " " << v << std::endl;
  }

  return 0;
}