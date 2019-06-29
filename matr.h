#include <map>
#include <utility>

template <typename T, T default_value>
class ElementHandler
{
public:
  void operator=(const T &value)
  {
    _matrix_map[_current_indexes] = value;

    if(_matrix_map.at(_current_indexes) == default_value)
    {
      _matrix_map.erase(_current_indexes);
    }

    current_it = _matrix_map.begin();
  }

  bool operator==(const T &value)
  {
    return this->getValue() == value;
  }

  bool operator!=(const ElementHandler<T, default_value> &rhs)
  {
    if(this->current_position != rhs.current_position)
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
    if(_matrix_map.find(_current_indexes) == _matrix_map.end())  
      return _default_value;

    return _matrix_map.at(_current_indexes);
  }

  int size() const
  {
    return _matrix_map.size();
  }

  void goNextElem()
  {
    ++current_it;
    ++current_position;
  }

  void goEndState()
  {
    current_position = _matrix_map.size();
  }

  std::tuple<T, T, T> getIndexesValueTuple()
  {
    return std::make_tuple(current_it->first.first, current_it->first.second, current_it->second);
  }

  void update()
  {
    first = current_it->first;
    second = current_it->second;
  }

    std::pair<int, int> first;
    T second;

  private:
    std::map<std::pair<int, int>, T> _matrix_map;
    std::pair<int, int> _current_indexes;
    int _default_value = default_value;
    typename std::map<std::pair<int, int>, T>::iterator current_it;
    int current_position = 0;
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

  std::tuple<T, T, T> getIndexesValueTuple()
  {
    return _element_handler.getIndexesValueTuple();
  }

   ElementHandler<T, default_value> getPairValue() 
  {
    _element_handler.update();
    return _element_handler;
  }

  void goNextElem()
  {
    return _element_handler.goNextElem();
  }

  void goEndState()
  {
    _element_handler.goEndState();
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
    using reference = std::pair<std::pair<int, int>, T>&;
    using pointer = std::pair<std::pair<int, int>, T>*;
    using iterator_category = std::forward_iterator_tag;

    iterator(RowsHandler<T, default_value>* rows_it_handler) : _rows_it_handler(rows_it_handler){};
 
    iterator &operator++() {  _rows_it_handler->goNextElem(); return *this;}
    self_type operator++(__attribute__((unused)) int junk) { self_type i = *this;  _rows_it_handler->goNextElem(); return i; }
    value_type operator*() { return _rows_it_handler->getIndexesValueTuple(); }
    bool operator!=(const self_type& rhs) { 
      return _rows_it_handler->getPairValue() != rhs.getRowsHandler()->getPairValue();
    }

    RowsHandler<T, default_value>* getRowsHandler() const
    {
      return _rows_it_handler;
    }

    private:
      RowsHandler<T, default_value> *_rows_it_handler;
  };

  iterator begin()
  {
    return iterator(&_rows_handler);
  }

  iterator end()
  {
    RowsHandler<T, default_value>* rows_handler = new RowsHandler<T, default_value>(_rows_handler);
    rows_handler->goEndState();
    return iterator(rows_handler);
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

