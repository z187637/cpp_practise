//// 函数指针、lambda、function学习
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<functional>
//class textClass {
//	std::string name;
//	int age;
//public:
//	void setInformation(const std::string n,const int a){
//		name = n;
//		age = a;
//	}
//	void getInformation() {
//		std::cout << name << " " << age << std::endl;
//	}
//};
//struct Accumulator {
//	int base;
//
//	// const 成员函数，不修改对象状态
//	int add_to(int x) const {
//		return base + x;
//	}
//};
//// 仿函数（函数对象）
//struct Multiplier {
//	int operator()(int a, int b) const { return a * b; }
//};
//int add(const int a, const int b) {
//	return a + b;
//}
//int mul(const int a, const int b) {
//	return a * b;
//}
////回调机制
//int compute(int a, int b,int (*operation)(int,int)) {
//	return operation(a, b);
//}
////2、函数指针作为返回值
//using OpFuns = int (*)(int, int);
//OpFuns selectFounction(char ch) {
//	if (ch == '+')return add;
//	if (ch == '*')return mul;
//	return nullptr;
//}
//int main() {
//	//函数指针：存放函数的起始地址
//	//格式 返回值类型 (*指针名称)(参数列表)
//	// 函数指针的类型，有返回值与参数列表共同决定
//	int (*addFunction)(int, int);
//	//addFunction = &add;								 //显式获取地址
//	addFunction = add;							        //隐式获取地址
//	std::cout <<"a+b=" << addFunction(1, 2) << std::endl;
//	using MFunction = int (*)(int, int);				//使用using(typedef) 给函数指针命名，代表接受返回值为 int，参数列表为两个int 类型的函数
//	MFunction mulFunction = mul;
//	std::cout << "a*b=" << mulFunction(2, 2) << std::endl;
//	//作用：1、回调机制，函数指针作为参数
//	std::cout << "回调加：" << compute(4, 3, addFunction)<< std::endl;
//	std::cout << "回调乘：" << compute(4, 3, mulFunction)<< std::endl;
//	//2、函数指针作为返回值
//	OpFuns accptFunction = selectFounction('+');
//	std::cout <<"作为返回值:" << accptFunction(4, 5) << std::endl;
//	//3、函数指针数组
//	int (*arrFunction[2])(int, int) = { add,mul };
//	std::cout << "arradd=" << arrFunction[0](2, 2) << std::endl;
//	std::cout << "arrmul=" << arrFunction[1](2, 3) << std::endl;
//	//4 成员函数指针
//	//声明并且初始化
//	void (textClass:: * setIn)(std::string, int) = &textClass::setInformation;
//	//通过对象调用
//	textClass m;
//	(m.*setIn)("zz", 18);
//	m.getInformation();
//	//通过指针调用
//	textClass* m1 = &m;
//	(m1->*setIn)("zx", 20);
//	m1->getInformation();
//	//lambda表达式[capture](parameters) mutable -> return_type { body }：解决了函数指针无法携带状态（上下文）的痛点,匿名函数
//	/*capture（捕获列表）：决定如何访问外部变量。
//		[]：不捕获任何变量。
//		[x]：按值捕获 x（拷贝副本）。
//		[&x]：按引用捕获 x（共享原变量）。
//		[=] / [&]：默认按值 / 引用捕获所有用到的外部变量。
//		[this]：在成员函数中捕获当前对象指针。*/
//	//作用1、一、最基础的形态：声明、立即调用、作为参数
//	//声明
//	auto compareM = [](int x, int y)->bool {
//		return x < y;
//		};
//	//调用
//	std::cout << compareM(7, 2) << std::endl;
//	// 立即调用
//	int n = [](int x, int y) { return x + y; }(5, 4);
//	std::cout << n << std::endl;
//	std::vector<int> vec{ 5,1,3,9,4,7,3,6,2,0,10 };
//	//参数
//	std::sort(vec.begin(), vec.end(), compareM);						//
//	for (const auto& i : vec) {
//		std::cout << i << " ";
//	}
//	std::cout << "\n";
//	int counter = 0;
//	std::string msg = "Hello";
//
//	// 作用2、捕获外部变量。引用捕获：能修改外部变量
//	auto byRef = [&counter, &msg]() {
//		counter++;
//		msg += " World";
//		};
//	byRef();
//	byRef();
//	std::cout << counter << ", " << msg << std::endl;   // 2, Hello World World
//
//	// 值捕获：拿到的是定义时的快照，外部改了也不影响它，内部修改会报错
//	int x = 10;
//	auto byVal = [x]() { return x; };
//	x = 100;
//	std::cout << byVal() << std::endl;                  // 仍输出 10
//	//默认情况下，按值捕获的变量在 Lambda 内部是 const 的，加 mutable 才能修改其副本，但是外部值仍旧不会被修改。
//	auto byVal1 = [x]()mutable { return x*10; };
//	std::cout << byVal1() << std::endl;
//	std::cout << x<< std::endl;
//	//特殊情况
//	int a = 0;
//	static int b = 0;                       // 静态存储期变量
//	auto f = [=]() mutable {
//		std::cout << "in lambda: " << ++a << ", " << ++b << std::endl;
//		};
//	f();                                    // in lambda: 1, 1
//	f();                                    // in lambda: 2, 2
//	std::cout << "in main: " << a << ", " << b << std::endl;  // in main: 0, 2,外部的静态变量被修改了
//	//function它的本质是一个“万能容器”，能够存储、复制和调用任何符合特定签名的可调用对象。
//	//std::function<返回类型(参数类型列表)> f
//	//1、普通函数、函数指针
//	std::function<int(int, int)> func = add;
//	//std::function<int(int, int)> func = addFunction;
//	std::cout << "func:" << func(1, 2) << std::endl;
//	// 2、包装带捕获的 Lambda（函数指针做不到这点！）
//	int offset = 10;
//	func = [offset](int a, int b) { return a + b + offset; };
//	std::cout << "lambda: " << func(3, 4) << "\n";
//	//3 仿函数
//	func = Multiplier{};
//	std::cout << "functor: " << func(3, 4) << "\n";
//	//4、包装成员函数指针（注意：需将对象作为第一个参数传入）
//	std::function<void( textClass&, std::string,int)> f_member = &textClass::setInformation;
//	f_member(m, "xxx", 36);
//	m.getInformation();
//	//5 配合 std::bind 绑定成员函数（更常用）
//	Accumulator acc{ 100 };
//
//	// std::bind 绑定成员函数的三要素：
//	//   1. &Accumulator::add_to  — 成员函数指针（必须显式取地址）
//	//   2. acc                   — 绑定的对象实例（按值拷贝；若需引用语义用 std::ref(acc)）
//	//   3. std::placeholders::_1 — 占位符，表示调用时传入的第一个参数对应 add_to 的 x
//	std::function<int(int)> f_bound = std::bind(&Accumulator::add_to, acc, std::placeholders::_1);
//
//	std::cout << "bound: " << f_bound(7) << "\n";  // 输出: bound: 107
//}