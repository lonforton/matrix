#include <map>
#include <utility>

template <typename T, T default_value>
class ElementHandler
{
public:
  void operator=(const T &value)
  {
    _matrix_map[_current_indexes] = value;

    if (_matrix_map.at(_current_indexes) == default_value)
    {
      _matrix_map.erase(_current_indexes);
    }
  }

  bool operator==(const T &value)
  {
    return this->getValue() == value;
  }

  bool operator!=(const ElementHandler<T, default_value> &rhs)
  {
    if (this->current_position != rhs.current_position)
    {
      this->current_position = 0;
      return true;
    }

    return false;
  }

  void setCurrentIndexes(int row_index, int column_index)
  {
    _current_indexes = std::make_pair(row_index, column_index);
  }

  T getValue()
  {
    if (_matrix_map.find(_current_indexes) == _matrix_map.end())
      return _default_value;

    return _matrix_map.at(_current_indexes);
  }

  int size() const
  {
    return _matrix_map.size();
  }

  auto begin()
  {
    return _matrix_map.begin();
  }

  auto end()
  {
    return _matrix_map.end();
  }

private:
  std::map<std::pair<int, int>, T> _matrix_map;
  std::pair<int, int> _current_indexes;
  T _default_value = default_value;
};

template <typename T, T default_value>
class RowsHandler
{
public:
  ElementHandler<T, default_value> &operator[](int column_index)
  {
    _column_index = column_index;
    _element_handler.setCurrentIndexes(_column_index, _row_index);
    return _element_handler;
  }

  void setCurrentRow(int row_index)
  {
    _row_index = row_index;
  }

  int size() const
  {
    return _element_handler.size();
  }

  T getValue()
  {
    return _element_handler.getValue();
  }

  auto begin()
  {
    return _element_handler.begin();
  }

  auto end()
  {
    return _element_handler.end();
  }

private:
  ElementHandler<T, default_value> _element_handler;
  int _column_index;
  int _row_index;
};

template <typename T, T default_value>
class Matrix
{
public:
  RowsHandler<T, default_value> &operator[](int row_index)
  {
    _rows_handler.setCurrentRow(row_index);
    return _rows_handler;
  }

  int size() const
  {
    return _rows_handler.size();
  }

  class iterator
  {
  public:
    using self_type = iterator;
    using value_type = std::tuple<T, T, T>;

    iterator(typename std::map<std::pair<int, int>, T>::iterator it) : _it(it) {}

    iterator &operator++() { ++_it;  return *this;  }
    value_type operator*() { return std::make_tuple(_it->first.first, _it->first.second, _it->second); }
    bool operator!=(const self_type &rhs) { return _it != rhs._it; }

  private:
    typename std::map<std::pair<int, int>, T>::iterator _it;
  };

  iterator begin()
  {
    return iterator(_rows_handler.begin());
  }

  iterator end()
  {
    return iterator(_rows_handler.end());
  }

private:
  RowsHandler<T, default_value> _rows_handler;
  int _column_index;
};

template <typename T, T default_value>
std::ostream &operator<<(std::ostream &out, ElementHandler<T, default_value> &element_handler)
{
  out << element_handler.getValue();
  return out;
}
