#include "../../header.h"

template <typename T> class pimpl
{
private:
    unique_ptr<T> impl;
public:
    pimpl();
    ~pimpl();

    template <typename ...Args> pimpl (Args&& ...args);

    T* operator->();
    T& operator*();
};
