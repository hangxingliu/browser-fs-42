# Smart Pointer 智能指针

We can use smart pointers don’t need to explicitly call delete.   
使用智能指针可以避免显式的 delete 回收.

There are four type of smart pointers are provided from C++:
C++ 内置四种智能指针:

- **shared_ptr** (from C++11)
- **weak_ptr** (from C++11)
- **unique_ptr** (from C++11)
- **auto_ptr** (removed in C++17)

More details: <http://en.cppreference.com/w/cpp/memory>

## `std::shared_ptr`

`std::shared_ptr` share the ownship of object to several pointer. and it has a counter for reference(owners) counts.   
`std::shared_ptr` 让多个指针占有同一个对象. 它有个内部计数器来记录引用次数(占有者数量).

About `std::make_shared<Type>(...)` (it makes only one allocation but not 2 time, so faster than invoking constructor of `std::shared_ptr`):   
<https://stackoverflow.com/questions/18301511/stdshared-ptr-initialization-make-sharedfoo-vs-shared-ptrtnew-foo>   
(上面的 StackOverflow 是关于 `make_shared` 的, `make_shared` 比直接调用 `std::shared_ptr` 更快, 因为只分配一次内存.)

English: <http://en.cppreference.com/w/cpp/memory/shared_ptr>   
中文: <http://zh.cppreference.com/w/cpp/memory/shared_ptr>

#### `#use_count`, `#reset`

`use_count` is a field record how many `shared_ptr` managing the current object.   
(记录了目前有多少个 `shared_ptr` 管理着当前对象)

`reset` method could release ownship of managed object or replace managed object with another object.   
(释放当前 `shared_ptr` 管理的对象的管理权, (`use_count--;`), 或者替换成管理其他对象)

#### Example

``` cpp
#include <iostream>
#include <memory>
using namespace std;

class A {
public:
	int v;
	A(int v):v(v){}
	~A() { cout << "~A:" << v << endl; }
};

int main() {
	{ // scope 1
		shared_ptr<A> ptr(new A(100));
		cout << "use_count: " << ptr.use_count() << endl;
		{ // scope 2
			auto ptr2 = ptr;
			cout << "ptr2->v: " << ptr2->v << endl;
			cout << "use_count: " << ptr.use_count() << endl;
		}
		cout << "use_count: " << ptr.use_count() << endl;
	}
	printf("return 0;\n");
	return 0;
}
/* Output
	use_count: 1
	ptr2->v: 100
	use_count: 2
	use_count: 1
	~A:100
	return 0;
*/
```

---

**English version of following documents are coming soon ...**

## `std::weak_ptr`

`weak_ptr` 是一种智能指针("弱"引用). 必须从 `std::weak_ptr` 或 `std::shared_ptr` 构造 `weak_ptr`.

`weak_ptr` 被设计为配合 `shared_ptr` 工作的智能指针, 它并不能直接操作所管理的对象. 但是它能用来观察 `use_count`, `expired`, 所以创建一个 `weak_ptr` 并不会导致 `use_count++;`

如果需要从 `weak_ptr` 中获得 `shared_ptr` 以便操作管理对象, 这需要调用 `lock` 方法:

``` cpp
shared_ptr<int> a(new int(100)); // a.use_count() = 1
weak_ptr<int> b = a; // a.use_count() = b.use_count() = 1
auto c = b.lock(); // a.use_count() = b.use_count() = 2
cout << *(c.get()) << endl; // 100
```

## Return a `shared_ptr` managing `this` 

有时, 我们需要在类的内部返回一个 `this` 指针的 `shared_ptr` 时, 可以使用:   
`shared_from_this` (此时必须要让当前类 A 继承 `std::enable_shared_from_this<A>`)

**IMPORTANT!!** 如果某个类的实例并不是被 `shared_ptr` 管理的话, 类内部调用 `shared_from_this` 的行为未定义 (简单说就是会崩溃)

有时间的话, 请阅读: 
- <http://zh.cppreference.com/w/cpp/memory/enable_shared_from_this>
- <https://stackoverflow.com/questions/11711034/stdshared-ptr-of-this>

#### Example

Detailed example: [smart_pointer.cc](smart_pointer.cc)

Simple example:

``` cpp
#include <iostream>
#include <memory>
using namespace std;
class Cat: public enable_shared_from_this<Cat> { 
public: 
	shared_ptr<Cat> getPtr() { return shared_from_this(); }
	shared_ptr<Cat> getWrongPtr() { // 错误!!!!!!!!!
		return shared_ptr<Cat>(this);
	}
};
int main() {
	Cat* _cat = new Cat();
	shared_ptr<Cat> cat1(_cat);
	shared_ptr<Cat> cat2 = cat1->getPtr();
	cout << cat2.use_count() << endl; // output: 2

	// 错误!!!!!!
	shared_ptr<Cat> cat3 = cat1->getWrongPtr();
	cout << cat3.use_count() << endl; 
	// output: 1 (cat3 以为自己才是 _cat 的唯一管理者) 
	return 0;
}
```

## `unique_ptr` & `auto_ptr`

<https://stackoverflow.com/questions/3451099/stdauto-ptr-to-stdunique-ptr>

`auto_ptr` 已经被弃用了(`auto_ptr` 不能正确处理数组, 它会尝试 `delete` 而不是 `delete[]`).

`unique_ptr` 是通过指针占有并管理另一对象, 并在 `unique_ptr` 离开作用域时释放该对象的智能指针.

``` cpp
#include<memory>
#include<iostream>
using namespace std;
class A { public: int value = 0; };
int main() {
	A *_a = new A();
	_a->value = 100;
	{
		unique_ptr<A> a(_a);
		cout << a->value << endl;

		auto a2 = std::move(a);
		// cout << a->value << endl; // Segment fault
		cout << a2->value << endl;
	}
	cout << _a->value << endl; // 0
	return 0;
}

```
