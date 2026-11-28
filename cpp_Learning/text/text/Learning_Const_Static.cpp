//#include<iostream>
//const int* add(int a,int b) {
//	int sum = a + b;
//	return &sum;
//}
//class Text {
//public:
//	const std::string name;
//	int age;
//	static int A;				//静态成员变量，声明
//	mutable int B=0;				//multable修饰非静态成员，使该成员可以在const修饰的成员函数中可以被修改
//	//Text()const				构造函数与析构函数不可以
//	Text();
//	Text(const std::string n, const int a) :name(n) ,age(a) {
//		//name=n;				//非法，不可在这里进行初始化
//	};
//	void print()const {			//承诺不修改非mutable修饰的成员
//		//age = 15;				//非法
//		//this->age = "zz";     //非法
//		B = 80;					//合法
//		A = 95;					//合法，也可以改变static修饰的成员
//		std::cout << name << " " << age << " " << A << " " << B << std::endl;
//	}
//	static void reSetInfo(Text& text) {	//类的成员静态函数
//		//this->name;					//非法，没有this指针，因此不能直接访问非静态成员变量或函数
//		A = 50;							//访问限制：只能访问静态成员变量和其他静态成员函数。若需操作对象，必须显式传入对象指针或引用作为参数
//		text.age = 90;
//		text.B = 60;
//		std::cout << "成员静态函数" << std::endl;
//	}
//};
//void Mcount() {
//	static int count = 0;		//仅仅初始化这一次。
//	//作用域：当前函数内部/代码区，外部不可见，
//	//生命周期：在静态存储区，程序结束时才释放
//	++count;
//	std::cout << count << std::endl;//每次调用这个函数都会加1
//}
//int Text::A = 90;
//int main() {
//	{
//
//		std::cout << "************************************************const****************************************" << std::endl;
//		//const：向编译器声明“不可变性”契约。
//		//1.普通变量
//		const int a = 10;     //a的值不可以在被修改
//		//a = 13;			  //报错，但是a仍然是一个变量，只是利用const修饰后编译器，拒绝了你的修改请求
//		//2.指针
//		int b = 20;
//		const int* p = &b;			//指针p的解类型为 const int，代表这p指向的内容不可以被修改
//		//*p = 15;					//报错，但是同样可以通过对指针p抹除限定符const，对指向的数据更改
//		int* q = const_cast<int*>(p);		//但是注意原始对象必须是非const修饰
//		*q = 30;
//		std::cout << b << std::endl;
//		int c = 40;
//		int* const p1 = &c;			//p1的解类型为int，代表p1的指向的内容可以用更改，但是p1的指向不可以被更改
//		*p1 = 50;
//		std::cout << c << std::endl;
//		//p1 = &a;				//报错
//		//引用
//		const int& r = a;			//创建只读别名，不可以通过r去修改a的值
//		//函数
//		//普通函数，只能放在返回值之前，表示返回值只读，常用于修饰返回是指针或者是引用的函数，防止通过调用者通过返回值修改数据
//		//*(add(a, b)) = 60;			//报错，不可以修改
//		//const int* p = add(a, b);
//		//成员函数，即可以放在前面，也可以放在后面，放在前面与普通函数的效果一样
//		Text text("zz", 18);
//		text.print();
//		//类成员变量
//		//必须在构造函数初始化列表中初始化，之后终身不可修改。
//	}
//	{
//		std::cout << "************************************************static****************************************" << std::endl;
//		//static:static 主要改变了对象的存储期（生命周期）和链接属性（可见性/共享性）
//		//函数内的局部静态变量
//		Mcount();
//		Mcount();
//		Mcount();
//		//类的静态成员变量
//		//存储位置：不属于任何对象实例，不占用对象内存大小
//		//定义规则：类内声明，类外定义
//		std::cout << Text::A << std::endl;		//使用类名调用
//		Text text1("xx",33);
//		text1.A = 100;							//使用对象名调用
//		Text text2("pp",44);
//		std::cout << text2.A<< std::endl;		//对text1中的A更改，text2中的也会发生变化，是因为静态成员变量，不属于任何实例
//		//类的成员静态函数
//		Text::reSetInfo(text1);					//调用方式：无需创建对象，直接通过 ClassName::func() 调用
//		text1.print();
//
//	}
//}