#include <iostream>
#include <cassert>

#include "matr.h"

int main()
{
  Matrix<int, 0> matrix;
  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 10; j++)
    {
      if (i == j)
      {
        matrix[i][j] = i;
      }
      if(i + j == 9) 
      {
        matrix[i][j] = j;
      }
    }
  }

  for (int i = 1; i < 9; ++i)
  {
    for (int j = 1; j < 9; j++)
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