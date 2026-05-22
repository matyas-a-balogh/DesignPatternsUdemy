#include "pimpl.h"

template<typename T>
pimpl<T>::pimpl() : impl{new T{}}
{

}

template<typename T>
pimpl<T>::~pimpl()
{
    // it will happen automatically
}

template<typename T>
template<typename... Args>

// fwd const
pimpl<T>::pimpl(Args &&... args)
  :impl{ new T{forward<Args>(args)... }}
{
}

template<typename T>
T *pimpl<T>::operator->()
{
  return impl.get();
}

template<typename T>
T &pimpl<T>::operator*()
{
  return *impl.get();
}
