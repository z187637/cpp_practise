#include<iostream>
#include<algorithm>
#include<vector>
namespace L_Encapsulation{
	//封装 ：封装是指将数据（属性）和操作数据的方法（行为）捆绑在一起，并对外隐藏内部实现细节，仅通过公开的接口与外界交互。
	//c++通过public、protected与private实现封装
	class Myperson {
		friend std::string Myfriend(const Myperson& M);			//友元函数，访问其私有与受保护的属性
		friend class MyParent;										//友元类
	private:													//私有的：只有类自身与友元类可以访问的属性或者方法,隐藏内部状态
		std::string name;
		int age;
		double score;
		std::string hobby;
	public:														//公共的：任何代码都可访问其成员
		explicit Myperson(const std::string n,int a,double s ,const std::string h):name(n),age(a),score(s),hobby(h){}						//explicit 声明 禁止隐式转换与隐式构造
		void setName(const std::string name) {																//const修饰变量，表示这是一个常量，值无法被修改
			this->name = name;																				//this指针是一个隐藏的函数参数，指向调用改函数的对象，此处是消除歧义
		}
		void setAge(const int age) {
			this->age = age;
		}
		void setScore(const double score) {
			this->score = score;
		}
		std::string getName() const{																		//const修饰函数，表示不修改非静态变量的值
			return this->name;
		}
		int getAge() {
			return this->age;
		}
		double getScore() {
			return this->score;
		}
		void setHobby(const std::string hobby) {
			this->hobby;
		}
	protected:																								//受保护的：成员可被类自身、友元及派生类访问，用于支持继承体系内的受控共享
		
		std::string setHobby()const {
			return this->hobby;
		}
	};
	std::string Myfriend(const Myperson& M) {																//友元函数
		return M.hobby;
	}
	class MyParent {
		/*
		私有属性......
		*/
		Myperson M;
	public:
		static int sonCount;																			//静态属性sonCount:记录子女数量
																										//属于类本身，而不是但一个的实例化对象，无论对象有多少份，静态对象只有一份
																										// 不可用this指针，在类中声明，来类外初始化。
		//friend class Myperson;
	public:
		MyParent(const Myperson& m):M(m){}
		void buyGift() {
			 std::cout << "送给你最喜欢的：" << M.hobby << std::endl;
		}
		static void eat() {
			//this->M.getName();																		//报错，没有this指针
			//std::cout << M.getName() << std::endl;														//报错只能访问静态变量		
			std::cout << "吃饭了" << std::endl;
		}
	};
	 int MyParent::sonCount = 1;																		//静态属性的初始化
}
namespace L_Inherotance {
	//继承 它允许一个类（派生类/子类）基于另一个类（基类/父类）来构建。，子类会继承派生类中的数据成员、普通函数。
	// 不会继承构造、析构函数与赋值预算符重载的函数。
	class Base_robot {														//类的默认访问权限是private
	private:
		std::string function_1 = "唱歌";
		std::string function_2 = "聊天";
		std::string function_3 = "设置提醒";
		int number;
	public:
		
		Base_robot(int n) :number(n) {
			std::cout << "我是Base_robot的构造函数" << std::endl;
		}
		~Base_robot() {
			std::cout << "我是Base_robot的析构函数" << std::endl;
		}
		void setFunction3(const std::string& f) {
			function_3 = f;
		}
		std::string getFunction_3() {
			return  function_3;
		}
		virtual void Myfunction() {
			std::cout << "我来陪你聊天" << std::endl;
		}
	};
	class Dance_robot :public Base_robot{											//public继承：is-a的关系基类的 public/protected 成员在派生类中保持原有访问级别。																					
																					//继承方式决定了基类成员在派生类中的最高访问权限。
																					// 无论使用哪种继承方式，基类的 private 成员在派生类中始终不可直接访问（但会被继承并占用内存）。

		std::string functonDance = "跳舞";
	public:
		std::string name="HD_R";
	public:
		void changeFunction() {
			//function_3 = "演奏乐器";												//报错，基类的private永远不可以访问.需要基类提供public方法,通过公有接口间接操作
			setFunction3("演奏乐器");
		}
		Dance_robot(int n):Base_robot(n) {
			std::cout << "我是Dance_robot的构造函数" << std::endl;
		}
		~Dance_robot() {
			std::cout << "我是Dance_robot的析构函数" << std::endl;
		}
		void Myfunction() override {
		std::cout << "我会跳舞" << std::endl;
		}
	};
	class A {
	public:
		int a;
		
	};
	class B:virtual public A {								//虚继承
	public:
		int b;
		
	};
	class C :virtual public A {										
	public:
		int c;
		
	};
	class D:public B,public C{
		int d;
		
	};

}
namespace L_Polymorphism {
	//多态（Polymorphism）的核心定义是“同一接口，多种实现”，即使用统一的方式处理不同类型的数据。
	//依据检索材料，C++ 多态按绑定时机分为静态多态和动态多态两大类，二者在机制、开销和应用场景上完全不同。
	//一、静态多态(编译时多态)：函数调用地址在编译阶段确定（早绑定），无运行时开销。
	//1、函数的重载：同一作用域内同名函数，编译器根据参数类型/数量选择版本，返回值并不能作为重载的标准
	void add(int a, int b) {
		std::cout << a + b << std::endl;
	}
	void add(double a, double b) {
		std::cout << a + b << std::endl;
	}
	void add(double a, double b,double c) {
		std::cout << a + b+c << std::endl;
	}
	//2、运算符重载：可重载几乎所有运算符；但不可创建新运算符，不可改变优先级/结合性/操作数个数
	//不可重载的运算符：.、.*、：：、？：、sizeof
	class stone {								
	public:
		int wight;
		stone(int w) :wight(w) {};
		
		stone operator+(const stone& s) {			//重载"+"是两个石头类相加，"+"为双目运算符，左侧操作数默认就是调用该函数的对象本身（即 *this），因此此处仅仅需要传入一个右侧的参数，但是左侧的操作数必须时类的对象
			return stone(this->wight + s.wight);     //临时变量，此处绝对不可以返回引用类型，返回一个局部临时变量(作用域结束会自动销毁)会造成，悬空引用						
		}
		friend stone operator-(int a, const stone& s);	//如果左侧操作数并不是一个类对象，如是一个int+stone，必须将 operator+ 重载为非成员函数（通常声明为 friend），此时左右操作数都作为显式参数传入。
		//重载前置自增
		stone& operator++() {
			++wight;				//先自增
			return *this;			//在返回
		}
		//重置后置自增
		stone operator++(int) {			//使用哑元进行区分前置与后置版本
			stone s = *this;		//先存
			wight++;				//再自增
			return s;				//返回
		}
	};
	stone operator-(const stone& s,int a) {
		return stone( s.wight-a);
	}
	//3、模板(template)
	//函数模板，不需要显式指出T的类型，编译器会自动推导,仅支持全部特化
	template<typename T>
	T Mmin(T a, T b) {				//通用实行
		return a > b ? b: a;
	}
	//函数模板的全特化
	template<>
	int Mmin<int>(int a, int b) {	//int的特用模板
		/*
		独特的逻辑实现
		*/
		std::cout << "int的特用模板" << std::endl;
		return a > b ? b : a;
	}
	//类模板，需要显式指出T的类型，支持全特化与偏特化
	template<typename T>					//通用模板
	class Box {
	public:
		void print() { std::cout << "Generic\n"; }
	};
	template<>
	class Box<int> {					//全特化模板
	public:
		void print() { std::cout << "Specialized for int\n"; }
	};
	//偏特化

	template<typename T,typename U>			//通用模板
	class Mpair {
		void print() { std::cout << "MPair:Generic\n"; }
	};
	template<typename U>					//偏特化1第一个参数为int
	class Mpair<int, U> {
		void print() { std::cout << "MPair:Specialized first is 'int'\n"; }
	};
	template<typename T>					//偏特化2第二个参数为int
	class Mpair<T ,int> {
		void print() { std::cout << "MPair: Specialized second is 'int'\n"; }
	};
	template<typename T>					//3两个参数一样
	class Mpair<T, T> {
		void print() { std::cout << "MPair:Specialized  common\n"; }
	};
	
	template<typename T, typename U>
	class Mpair<T*, U> {						//4指针
		void print() { std::cout << "MPair:Specialized  P\n"; }
	};
	//运行时多态
	//主要是通过虚函数来实现
	/*三个必要条件
		1、有继承关系
		2、子类重写（override）父类的虚函数
		3、通过父类指针或引用调用虚函数*/
		// 1. 基类：声明虚函数 + 虚析构
	class Animal {
	public:
		virtual void makeSound() const {
			std::cout << "Animal sound" << std::endl;
		}
		virtual ~Animal() = default;  // ✅ 必须为虚析构，防止内存泄漏
	};

	// 2. 派生类：使用 override 重写虚函数
	class Dog : public Animal {
	public:
		void makeSound() const override {  // ✅ override 确保真正构成重写
			std::cout << "Woof!" << std::endl;
		}
	};

	class Cat : public Animal {
	public:
		void makeSound() const override {
			std::cout << "Meow!" << std::endl;
		}
	};

	// 3. 统一接口：通过基类引用处理所有派生类型
	void processAnimal(const Animal& animal) {
		animal.makeSound();  // 运行时根据实际对象类型决定调用哪个版本
	}
}
int main() {
	{
		//using L_Encapsulation::Myperson;																	//仅仅使用这一个类，
		using namespace L_Encapsulation;																	//使用该命名空间的所有东西
		//Mytext text = { "zz", 18, 85.0 };																	//企图隐式调用构造函数，报错
		Myperson text = Myperson("zz", 18, 85.0, "篮球");
		//double tscore = text.score;												       					//报错，因为score被private修饰为对象的私有属性
		double tscore = text.getScore();																	//通过public修饰的函数经行获取数据。
		std::cout << "score:" << tscore << std::endl;
		//std::string thobby = text.setHobby();																//报错，不可以访问 被protected修饰的函数
		std::string thobby = Myfriend(text);																//使用友元函数访问，protected或private属性
		std::cout << "hobby：" << thobby << std::endl;
		MyParent p(text); // 创建一个对象
		p.buyGift();																						//友元类访问
		//静态属性访问
		std::cout << MyParent::sonCount << std::endl;;
		//静态函数
		MyParent::eat();
	}
	{
		using namespace L_Inherotance;
		//1、继承后的基类与子类的构造与析构顺序;
		Dance_robot robotD(1);	//构造：先基类在子类，析构：顺序相反

		//2、赋值兼容性原则与对象切片
		//有与是public继承是 is-a的关系：子类对象可以隐式转换为父类类型：
		/*子类对象可以赋值给类对象（发生切片，丢失派生类特有成员）。
			子类指针 / 引用可以指向父类对象（多态的基础）。
			反向不成立：子类对象 / 指针不能隐式转换为子类类型*/
			//子类隐式退化为父类 向上转型；
			//对象切片是指：当派生类对象按值赋值或初始化给基类对象时，编译器只复制其中的基类子对象部分，派生类特有的成员数据和方法被"切掉"丢弃，最终得到一个纯粹的基类对象
		Base_robot robotB = Dance_robot(1);											//对象->对象：发生对象切片
		//std::cout << robotB.name;													//报错：robotB并没有name这个属性
		Base_robot* robotB1 = new Dance_robot(2);									//对象->指针：不会发生切片
		//std::cout << robotB1->name << std::endl;									//报错：robotB1指向的地方有name这个属性,，但是由于robotB1->name这个行为是静态绑定，因此不允许rotorB1访问name这个属性
		robotB1->Myfunction();														//但是可以通过这种方法，可以实现通过基类的指针调用派生类的虚函数
		Base_robot& robotB2 = robotD;												//对象->引用：不会发生切片
		robotB2.Myfunction();														//同样可以实现通过基类的指针调用派生类的虚函数
		//菱形继承与虚继承
		//菱形继承，会导致数据冗余、内存浪费与成员访问的二义性
		//D继承B与C，B与C继承A，形成菱形继承
		//内存浪费;
		D dClass;
		std::cout << sizeof(dClass) << std::endl;								//大小为20，本应为16,但是由于有两份A的数据所以多了一个int的大小，由于对直接虚继承类公共基类插入了 虚基类指针所以占用内存变多了
		//数据访问的二义性
		dClass.a = 10;															//报错，编译器不明白a是来自哪里，使用虚继承后报错消失
		//解决办法公共基类使用虚继承
	}
	{
		std::cout << "********************************************L_Polymorphism******************************************" << std::endl;
		using namespace L_Polymorphism;
		//函数重载
		add(5, 6);
		add(8.1, 9.75);
		add(8.1, 9.75, -7.2);
		//运算符重载
		stone s(5);
		stone s1(20);
		stone s2 = s + s1;
		std::cout << s2.wight << std::endl;				//新石头的中量为25
		stone s3 = s - 2;
		std::cout << s3.wight << std::endl;				//新石头重量为2;
		//std::cout << (++s).wight << std::endl;		//输出为6
		std::cout << (s++).wight << std::endl;			//输出为5	
		//函数模板
		std::cout << Mmin(9, 3) << std::endl;
		std::cout << Mmin(9.6, 3.9) << std::endl;
		Box<double> b;									//显式指出T的类型
		b.print();
		Box<int> b1;
		b1.print();
		Mpair<int, double> p;
		// 4. 基类指针/引用指向不同派生类对象
		std::vector<std::unique_ptr<Animal>> animals;
		animals.push_back(std::make_unique<Dog>());
		animals.push_back(std::make_unique<Cat>());
		animals.push_back(std::make_unique<Animal>());

		for (const auto& a : animals) {
			a->makeSound();       // 动态绑定
			processAnimal(*a);    // 引用传递同样触发多态
		}
	}
}