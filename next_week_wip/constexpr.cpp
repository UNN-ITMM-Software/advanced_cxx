#include <cstring>
namespace advcxx{
  using namespace std;
  constexpr unsigned int fib(size_t n){
    unsigned int a = 1, b = 1;
    for(size_t i = 0; i < n; ++i){
      unsigned int c = a + b;
      a = b;
      b = c;
    }
    return a;
  }
}

#include <cassert>
#include <iostream>
int main(){
  using namespace std;
  // C++17 have added more constexprness, we might be able to use ::std::array instead of C array
  int arr [] = {advcxx::fib(0), advcxx::fib(1), advcxx::fib(2), advcxx::fib(3)};
  /* g++ 5.4 -std=c++14 -O0 emits
     ...
        mov     DWORD PTR [rbp-16], 1
        mov     DWORD PTR [rbp-12], 1
        mov     DWORD PTR [rbp-8], 2
        mov     DWORD PTR [rbp-4], 3
     ...
   */
  size_t n; cin >> n;
  // Doesn't look very cxx-style
  assert(n < sizeof(arr) / sizeof(arr[0]));
  cout << arr[n] << endl;
  return 0;
}
