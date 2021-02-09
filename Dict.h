// ensure this library description is only included once
#ifndef Dict_h
#define Dict_h

// include types & constants of Wiring core API
#include "Arduino.h"
// #include "Context.h"


// typedef void(*endpoint)();

// template class Dict<endpoint>;


template <class T> 
class  Dict
{
  public:


  Dict();
  ~Dict();
  void add(String, T);
  int Size();

  T * getValue(String);
  T * getValue(int);
  String * getKey(int);

  private:
  Dict(String, T);
  String Key;
  T Value;
  Dict<T> * Next = nullptr;


  int Size(int);
  Dict<T> * getDict(int,int);
  Dict<T> * getDict(String);
};




#endif
