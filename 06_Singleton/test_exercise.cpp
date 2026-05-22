#include <functional>
using namespace std;

struct SingletonTester
{
  template <typename T>
  bool is_singleton(function<T*()> factory)
  {
    T* obj1 = factory();
    T* obj2 = factory();

    if(obj1 == obj2) return true;
    else return false;
  }
};
