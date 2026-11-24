#include<iostream>
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
	class Base_robot {
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
	};
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

		//2、赋值兼容性原则与对象切片(父类无法拥有子类自己的属性或者函数)
		//有与是public继承是 is-a的关系：子类对象可以隐式转换为父类类型：
		/*子类对象可以赋值给类对象（发生切片，丢失派生类特有成员）。
			子类指针 / 引用可以指向父类对象（多态的基础）。
			反向不成立：子类对象 / 指针不能隐式转换为子类类型*/
		//子类隐式退化为父类 向上转型；
		Base_robot robotB = Dance_robot(1);											//对象->对象：发生对象切片
		//std::cout << robotB.name;													//报错：robotB并没有name这个属性
		Base_robot* robotB1 = new Dance_robot(2);									//对象->指针：不会发生切片
		//std::cout << robotB1->name << std::endl;									//报错：robotB并没有name这个属性,但是可以通过这种方法，调用子类的对父类虚函数具体实现的函数
		Base_robot& robotB1 = robotD;												//对象->引用：不会发生切片
	}
}