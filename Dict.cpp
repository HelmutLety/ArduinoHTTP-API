
#include "Dict.h"
#include "Context.h"


template class Dict<String>;
template class Dict<void (*)(Context*)>;

void baafunction(char * function_name, void (*f)(String)){

}


template <typename T>
Dict<T>::~Dict()
{
  delete Next;
}
template <typename T>
Dict<T>::Dict()
{
  Dict("",T());
}
template <typename T>
Dict<T>::Dict(String key, T value)
{
  Key = key;
  Value = value;
}

template <typename T>
void Dict<T>::add(String key, T value)
{
  Dict<T> * nextValue = this;

  while(nextValue->Next)
  {
    nextValue = nextValue->Next;
  }

  nextValue->Next = new Dict<T>(key,value);
}
template <typename T>
int Dict<T>::Size()
{
  return Size(0);
}

template <typename T>
int Dict<T>::Size(int count)
{
  if (Next == nullptr)
  {
    return count;
  }
  return Next->Size(count + 1);
}

template <typename T>
T * Dict<T>::getValue(String par)
{
  if (Next == nullptr)
  {
    return NULL;
  }
  Dict<T> * val = Next->getDict(par);
  if (val == nullptr)
  {
    return NULL;
  }
  return &(val->Value);
}

template <typename T>
T * Dict<T>::getValue(int par)
{
  if (Next == nullptr)
  {
    return NULL;
  }
  Dict<T> * val = Next->getDict(0,par);
  if (val == nullptr)
  {
    return NULL;
  }
  return &(val->Value);
}

template <typename T>
String * Dict<T>::getKey(int par)
{
  if (Next == nullptr)
  {
    return NULL;
  }
  Dict<T> * val = Next->getDict(0,par);
  if (val == nullptr)
  {
    return NULL;
  }
  return &(val->Key);
}

template <typename T>
Dict<T> * Dict<T>::getDict(int count, int index)
{
  if (count == index)
  {
    return this;
  }
  if (Next == nullptr)
  {
    return NULL;
  }
  return Next->getDict(count + 1, index);
}

template <typename T>
Dict<T> * Dict<T>::getDict(String pKey)
{
  if (Key == pKey)
  {
    return this;
  }
  if (Next == nullptr)
  {
    return NULL;
  }
  return Next->getDict(pKey);
}