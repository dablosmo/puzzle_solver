#ifndef MY_LIST_H
#define MY_LIST_H
/**
    Copy your mylist.h file from PA2
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>

using namespace std;

template <typename T> class MyList
{
 private:
  int size_;
  int capacity_;
  T* data;
  T sample_;
 public:
  MyList();
  MyList(const MyList &rhs);
  MyList(int capacity);
  ~MyList();
  void push_back(T element);
  void push_front(T element);
  int size() const;
  int capacity() const;
  T* getdata() const;
  T& at(int location) const;
  void insert(int location, T element);
  bool remove(T val);
  void removevalue(T val);
  T pop(int loc);
  void poplocation(int loc);
  T& operator[](int location);
  void clear();
};

template <typename T> MyList<T>::MyList()
{
  size_ = 0;
  capacity_ = 1;
  data = new T[capacity_];
}

template <typename T> MyList<T>::MyList(const MyList &rhs)
{
  size_ = rhs.size();
  capacity_ = rhs.capacity();
  data = new T[capacity_];
  for (int i=0; i < size_; i++)
  {
    data[i] = (rhs.getdata())[i];
  }
}

template <typename T> MyList<T>::~MyList()
{
  delete[] data;
}

template <typename T> MyList<T>::MyList(int capacity)
{
  if((typeid(capacity).name()) != (typeid(capacity_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  size_ = 0;
  capacity_ = capacity;
  data = new T[capacity_];
}

///adds passed-in element to next available space in MyList
///double's MyList size if reaches size limit
template <typename T> void MyList<T>::push_back(T element)
{
  if((typeid(element).name()) != (typeid(sample_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if (size_ >= capacity_) ///no more space in MyList to hold additional elements
    {
      T *newdata = new T[capacity_*2];
      ///copy all old data over to new twice as large array
      for (int i=0; i<capacity_; i++)
	{
	  newdata[i] = data[i];
	}
      delete[] data; ///delete data from old small array
      data = newdata;
      capacity_ = capacity_*2;
    }
  data[size_] = element;
  size_++;
}

///adds passed-in element to front of MyList
///double's MyList size if reaches size limit
template <typename T> void MyList<T>::push_front(T element)
{
  if((typeid(element).name()) != (typeid(sample_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if (size_ >= capacity_) ///no more space in MyList to hold additional elements
    {
      T *newdata = new T[capacity_*2];
      ///copy all old data over to new twice as large array
      for (int i=0; i<capacity_; i++)
	{
	  newdata[i] = data[i];
	}
      delete[] data; ///delete data from old small array
      data = newdata;
      capacity_ = capacity_*2;
    }
  ///shift all elements in array to the right one space to make room at index 0
  for (int i=size_; i > 0; i--)
  {
    data[i] = data[i-1];
  }
  ///insert new value at index 0
  data[0] = element;
  size_++;
}

template <typename T> int MyList<T>::size() const
{
  return size_;
}

template <typename T> int MyList<T>::capacity() const
{
  return capacity_;
}

template <typename T> T* MyList<T>::getdata() const
{
  return data;
}

template <typename T> T& MyList<T>::at(int location) const
{
  if((typeid(location).name()) != (typeid(size_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if((location >= size_) || (location < 0))
    {
      throw out_of_range("Location out of scope");
    }
  return data[location];
}

///sets value at passed-in location to equal passed-in element
template <typename T> void MyList<T>::insert(int location, T element)
{
  if((typeid(location).name()) != (typeid(capacity_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if((typeid(element).name()) != (typeid(sample_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if((location >= size_) || (location < 0))
    {
      throw out_of_range("Location out of scope");
    }
  else if (location < capacity_)
    {
      data[location] = element;
      size_++;
    }
  else ///location is >= capacity_
    {
      cout << "Undefined Error" << endl;
    }
}

///searches through list and removes first instance of passed-in element
///returns true if element succesfully removed, false if element not found
template <typename T> bool MyList<T>::remove(T val)
{
  if((typeid(val).name()) != (typeid(sample_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  for (int i = 0; i < size_; i++)
    {
      if(data[i] == val)
	{
	  ///shift all elements beyond index i down one index
	  for (int j = i; j < (size_-1); j++)
	    {
	      data[j] = data[j+1];
	    }
	  size_--;
	  return true;
	}
    }
  return false;
}

///searches through list and removes first instance of passed-in element
template <typename T> void MyList<T>::removevalue(T val)
{
  if((typeid(val).name()) != (typeid(sample_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  for (int i = 0; i < size_; i++)
    {
      if(data[i] == val)
	{
	  ///shift all elements beyond index i down one index
	  for (int j = i; j < (size_-1); j++)
	    {
	      data[j] = data[j+1];
	    }
	  size_--;
	}
    }
}

///removes an element at given location and returns the element
template <typename T> T MyList<T>::pop(int loc)
{
  if((typeid(loc).name()) != (typeid(size_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if((loc >= size_) || (loc < 0))
    {
      throw out_of_range("Location out of scope");
    }
  ///save deleted element before deleting it in temporary variable
  T temp = data[loc];
  ///shift all elements beyond index i down one index
  for (int i = loc; i < (size_-1); i++)
    {
      data[i] = data[i+1];
    }
  size_--;
  return temp;
}

template <typename T> void MyList<T>::poplocation(int loc)
{
  if((typeid(loc).name()) != (typeid(size_).name()))
    {
      throw invalid_argument("Argument type mismatch");
    }
  if((loc >= size_) || (loc < 0))
    {
      throw out_of_range("Location out of scope");
    }
  ///shift all elements beyond index i down one index
  for (int i = loc; i < (size_-1); i++)
    {
      data[i] = data[i+1];
    }
  size_--;
}

template <typename T> T& MyList<T>::operator[](int location)
{
  return data[location];
}

template <typename T> void MyList<T>::clear()
{
  size_ = 0;
  capacity_ = 1;
  delete [] data;
  data = new T[capacity_];
}



#endif
