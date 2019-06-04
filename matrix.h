#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

template <typename T>
class MatrixElem
{
public:  

  T returnValue() const
  {
    if (matrix_map.find(_row_index) == matrix_map.end())
      return _default_value;

    auto column_map = matrix_map.at(_row_index);
    if (column_map.find(_column_index) == column_map.end())
      return _default_value;

    if (column_map.at(_column_index) == _default_value)
    {
      column_map.erase(_column_index);
      return _default_value;
    }

    return column_map.at(_column_index);

    return _default_value;
  }

  void operator=(const T &value)   
  {
    matrix_map[_row_index][_column_index] = value;
  }

  bool operator==(const T &value)
  {
    return this->returnValue() == value;
  }

  void setElementIndexes(int row_index, int column_index)
  {
    _row_index = row_index;
    _column_index = column_index;
  }

  void setDefaultValue(T default_value)
  {
    _default_value = default_value;
  }

  size_t getMatrixSize()
  {
    std::vector<int> rows_sizes;
    rows_sizes.reserve(matrix_map.size());
    std::transform(matrix_map.begin(), matrix_map.end(), std::back_inserter(rows_sizes),
                   [](const typename std::map<int, std::map<int, T>>::value_type &pair) { return pair.second.size(); });
    size_t matrix_size = std::accumulate(rows_sizes.begin(), rows_sizes.end(), 0);

    return matrix_size;
  }

private:
  std::map<int, std::map<int, T>> matrix_map;
  int _row_index = 0;
  int _column_index = 0;
  T _default_value;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const MatrixElem<T> &matrix_elem)
{
  out << matrix_elem.returnValue();
  return out;
}

template <typename T>
class RowsHandler
{
public:
  MatrixElem<T> &operator[](int column_index)
  {
    _matrix_elem.setElementIndexes(_row_index, column_index);
    _matrix_elem.setDefaultValue(_default_value);
    return _matrix_elem;
  }

  void setRowIndex(int row_index)
  {
    _row_index = row_index;
  }

  void setDefaultValue(T default_value)
  {
    _default_value = default_value;
  }

  size_t size()
  {
    return _matrix_elem.getMatrixSize();
  }

private:
  MatrixElem<T> _matrix_elem;
  int _row_index;
  T _default_value;
};

template <typename T, T default_value>
class Matrix
{
public:

  size_t size()
  {
    return _rows_handler.size();
  }

  RowsHandler<T> &operator[](int row_index)
  {
    _rows_handler.setRowIndex(row_index);
    _rows_handler.setDefaultValue(default_value);
    return _rows_handler;
  }

private:
  RowsHandler<T> _rows_handler;
};
