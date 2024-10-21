#include <bits/stdc++.h>

using namespace std;

/*
https://stackoverflow.com/questions/35792881/how-to-make-sure-an-object-will-really-be-moved-from
ADL https://stackoverflow.com/questions/45804068/move-constant-object-without-compiler-warning
https://stackoverflow.com/questions/62277859/is-there-any-compiler-flags-to-make-a-default-move-constructor-empty-the-moved
force_move  https://cplusplus.com/forum/general/232294/

https://pvs-studio.com/en/docs/warnings/v833/

https://gcc.gnu.org/bugzilla/show_bug.cgi?id=67906
*/


// Copy this line into your global header
// namespace std {
// template <class T>
// void move(const T& arg) = delete;  // ADL
// };

template <typename T>
decltype(auto) force_move(T&& value) {
  static_assert(!std::is_const_v<std::remove_reference_t<T>>,
                "Move can't be forced on const object.");
  return std::move(value);
}

int main() {
  // Compiled with Visual Studio 2017 version 15.3.1
  std::vector<std::string> v;

  std::string str1 = "string 1";
  v.push_back(std::move(str1));
  // Call push_back(T&&). The contents of str1 is moved into the vector.
  // This is less expensive, but str1 is now valid but unspecified.
  printf("str1=[%s] v.back=[%s]\n", str1.c_str(), v.back().c_str());

  const std::string str2 = "string 2";
  v.push_back(std::move(str2));
  // Call push_back(const T&). A copy of str2 is added into the vector.
  // str2 itself is unchanged.
  printf("str1=[%s] v.back=[%s]\n", str2.c_str(), v.back().c_str());

  return 0;
}