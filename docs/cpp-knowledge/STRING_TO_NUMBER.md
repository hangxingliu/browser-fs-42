# String To Number  字符串转数字

## `std::atoi` and `std::stoi`

These two function are used for converting string to int.   
这两个函数用于转换字符串到整数

`std::stoi` Example:

``` cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string str = "NaN";
    try{
        cout << stoi(str) << endl;
    } catch(...) {
        cerr << "Invalid!" << endl;  
    }
    return 0;
}
```

`std::atoi` Example:

``` cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string str = "NaN";
    cout << atoi(str.c_str()) << endl; // Output: 0
    return 0;
}
```
