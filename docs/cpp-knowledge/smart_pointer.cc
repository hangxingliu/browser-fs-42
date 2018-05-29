#include <iostream>
#include <memory>
#include <list>

using namespace std;

class A;
class B;

class B {
public:
	long val;
	shared_ptr<A> parent;
};

class A : public enable_shared_from_this<A> {
public:
	long val = 0;
	weak_ptr<B> child;
	void addChild(shared_ptr<B> child) {
		this->child = child;
		child->parent = shared_from_this();
	}
};

int main() {
	auto _b = new B();
	_b->val = 1024;
	{
		shared_ptr<A> a(new A());
		shared_ptr<B> b(_b);
		a->val = 100;
		a->addChild(b);

		cout << "b.use_count: " << b.use_count() << endl; // 1
		weak_ptr<B> child = a->child; // 因为 weak_ptr 不占有数据, 只是观测 use_count 和 expired
		cout << "b.use_count: " << child.use_count() << endl; // 所以这儿还是 1

		shared_ptr<B> childPtr = child.lock(); // weak_ptr.lock 后就创建一个 shared_ptr
		cout << "a.val: " << childPtr->parent->val << endl;
		cout << "b.use_count: " << b.use_count() << endl; // 所以这儿 + 1 = 2

		childPtr.reset(); // 清除这个占用, use_count - 1
		cout << "b.use_count: " << b.use_count() << endl; // 1
	}
	cout << _b->val << endl; // 0: 由于使用了智能智能, 所以出了上面那个作用域后, _b 已经被 free 掉了
	return 0;
}
