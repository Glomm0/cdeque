
 #include <iostream>
#include <algorithm>
#include <exception>

template <typename T>
class cdeque_iterator {
private:
   T *_data;
   int _reserved;
   int _offset;
   int _pos;
public:
   cdeque_iterator(T* __data,int __reserved,int __offset,int __pos) :
      _data(__data), _reserved(__reserved), _offset(__offset), _pos(__pos) {}
   typedef std::random_access_iterator_tag iterator_category;
   typedef T value_type;
   typedef int difference_type;
   typedef T& reference;
   typedef T* pointer;
   cdeque_iterator<T>& operator++() {
      _pos++;
      return *this;
   }
   cdeque_iterator<T>& operator--() {
      _pos--;
      return *this;
   }
   T& operator*() {return _data[(_offset+_pos)%_reserved];}

   friend bool operator==(const cdeque_iterator<T> &a,const cdeque_iterator<T> &b) {
      if (a._pos==b._pos)
        return true;
      else
        return false;
   }
   friend bool operator!=(const cdeque_iterator<T> &a,const cdeque_iterator<T> &b) {
         if (a._pos==b._pos)
        return false;
      else
        return true;
   }
   friend bool operator<(const cdeque_iterator<T> &a,const cdeque_iterator<T> &b) {
         if (a._pos<b._pos)
        return true;
      else
        return false;
   }
   cdeque_iterator& operator+=(int k) {
       _pos=_pos+k;
       return *this;
   }
   friend cdeque_iterator operator+(const cdeque_iterator<T> &a, int k) {
      cdeque_iterator<T> other(a);
      return other+=k;
   }
   friend cdeque_iterator operator-(const cdeque_iterator<T> &a, int k) {
      cdeque_iterator<T> other(a);
      return other+=-k;
   }
   friend int operator-(const cdeque_iterator<T> &a,const cdeque_iterator<T> &b) {
       return a._pos-b._pos;
   }
};



template <typename T>
class cdeque {
private:
   int _reserved;
   int _size;
   int _offset;
   T* _data;
   void reallocate(int __reserve);
public:
   cdeque(int _reserve) {
      if (_reserve<1)
         throw std::length_error("reserve must be >0");
      _reserved=_reserve;
      _size=0;
      _offset=0;
      _data=new T [_reserved];
   }
   ~cdeque() {
      delete[] _data;
   }
   int size() {
      return _size;
   }
   T& operator[](int i) {
      return _data[(_offset+i)%_reserved];
   }
   T& front() {
      return _data[_offset];
   }
   T& back() {
      return _data[(_offset+_size-1)%_reserved];
   }
   void push_back(const T &x) {
      if (_size+1==_reserved)
         reallocate(2*_reserved);
       _data[(_offset+_size)%_reserved]=x;
       _size++;
   }
   void push_front(const T &x) {
      if (_size+1==_reserved)
         reallocate(2*_reserved);
      _size++;
      if (_offset==0)
      {
          _offset=_reserved-1;
          _data[_offset]=x;
      }
        else
        {
         _offset--;
        _data[_offset]=x;
        }
   }

   void pop_back(){
          _size--;
   }
   void pop_front() {
       if (_offset==_reserved-1)
       {
         _offset=0;

       }
       else
        _offset++;
      _size--;

   }

     cdeque_iterator<T> begin() {
    return  cdeque_iterator<T>(_data,_reserved,_offset,0);
   }


    cdeque_iterator<T> end() {
    return cdeque_iterator<T>( _data,_reserved,_offset,_size);
   }

};
template <typename T>
void cdeque<T>::reallocate(int __reserve) {
  T* data2=new T[__reserve];
  for (int i=0;i<_size;i++)
  {
      data2[i]=_data[(_offset+i)%_reserved];
  }
    _offset=0;
    _reserved=__reserve;
    delete []_data;
    _data=data2;

}

int main() {
  cdeque<int> d(1);
  for (int j=1;j<10;j++) {
     d.push_back(j);
     for (int i=0;i<d.size();i++)
        std::cout<<d[i]<<' ';
     std::cout<<std::endl;
  }
  for (int j=0;j<10;j++) {
     for (int i=0;i<d.size();i++)
        std::cout<<d[i]<<' ';
     std::cout<<std::endl;
     int x=d.front();
     d.pop_front();
     d.push_back(x);
  }
  for (int j=0;j<11;j++) {
     for (int i=0;i<d.size();i++)
        std::cout<<d[i]<<' ';
     std::cout<<std::endl;
     int x=d.back();
     d.pop_back();
     d.push_front(x);
  }

cdeque<int> e(1);
  e.push_back(12);
  e.push_back(155);
    e.push_back(-5);
      e.push_back(77);

  std::sort(e.begin(),e.end());
  for (int i=0;i<e.size();i++)
     std::cout<<e[i]<<' ';
  std::cout<<std::endl;
}
