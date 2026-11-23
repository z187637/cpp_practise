////智能指针：裸指针new后忘记delete、中途抛出异常导致没有delete、多处重复释放
////智能指针用RALL思想一次解决：对象析构自动释放资源，不需要手动管理。      
//#include<iostream>
//#include<memory>				//提供智能指针与内存管理的相关工具
//#include<chrono>				//计算代码运行时间
//#include<vector>
//class Myclass {
//private:
//	std::string name;
//public:
//	Myclass(const std::string n) :name(n) {
//		std::cout << "1我是一个构造函数:" << name << std::endl;
//	}
//	~Myclass() {
//		std::cout << "1我是一个析构函数:" <<name<< std::endl;
//	}
//	void setName(const std::string& n) {
//		name = n;
//	}
//};
//struct Child; // 前向声明
//struct Parent {
//	std::shared_ptr<Child> child; // 拥有子节点（强引用）
//
//	~Parent() { std::cout << "Parent destroyed\n"; }
//};
//struct Child {
//	std::weak_ptr<Parent> parent; // 仅观察父节点（弱引用，不阻止销毁）
//
//	~Child() { std::cout << "Child destroyed\n"; }
//};
//class Text {
//public:
//	Text() { std::cout << "默认构造\n"; }
//	Text(const Text&) { std::cout << "拷贝构造\n"; };
//	Text(Text&&) { std::cout << "移动构造\n"; }
//};
//int main() {
//	Myclass* compare_class=new Myclass("compare_class");									//不会自动调用析构函数
//	{	//unique_ptr独占所有权，不可拷贝，可以移动，零额外开销，默认首选方案
//		std::unique_ptr<Myclass> Uclass1 = std::make_unique<Myclass>("Uclass1");			//离开作用域后自动调用析构函数释放内存
//		//不可以拷贝，只能移动
//		//auto class2 = class1;				//编译错误
//		auto Uclass2 = std::move(Uclass1);	//所有权转让给class2 ，class1变为空
//		Uclass2->setName("Uclass2");
//		if (Uclass1 == nullptr) {
//			std::cout << "Uclass1为空" << std::endl;
//		}
//		//shared_ptr共享所有权，多个指针共同拥有一个对象，内部用引用计数记录，技术归零才释放
//		auto Sclass1 = std::make_shared<Myclass>("Sclass1");
//		auto Sclass2 = Sclass1;
//		auto Sclass3 = Sclass1;
//		//Sclass3.reset();	//重置Sclass的指向				
//		std::cout << Sclass1.use_count() << std::endl;		//查看计数：3
//		//shared_prt的Bug：两个对象间通过shared_ptr相互引用，导致计数永远是>=1,导致指针无法释放，造成资源泄露
//		
//		//std::cout << Sclass1.use_count() << std::endl;		//查看计数：3
//		//weak_ptr弱指针不拥有对象，不增加引用计数,有效解决shared_ptr的bug
//		std::weak_ptr<Myclass> Wclass1 = Sclass1;
//		std::cout << Sclass1.use_count() << std::endl;		//查看计数仍是：3
//		if (auto p = Wclass1.lock()) {						//尝试获取 share_ptr
//			std::cout << "Sclass1还活着" << std::endl;
//		}
//		else {
//			std::cout << "Sclass1已经释放" << std::endl;
//		}
//		//解决share_ptr的bug
//		auto parent = std::make_shared<Parent>();
//		auto child = std::make_shared<Child>();
//
//		// 建立双向关联
//		parent->child = child;
//		child->parent = parent; // weak_ptr 从 shared_ptr 构造，不增加引用计数
//
//		// 安全访问父节点
//		if (auto locked_parent = child->parent.lock()) {
//			std::cout << "Child can access parent\n";
//		}
//		else {
//			std::cout << "Parent already destroyed\n";
//		}
//	}
//		{
//			//移动语义
//			/*move()函数：本身并不移动任何数据，它仅仅是一个类型转换函数。
//			std::move 的唯一作用是将传入的参数（通常是左值）强制转换为右值引用（rvalue reference）*/
//			/*左值：通常是指一个变量的地址一般可以&取地址，右值一般是没有名字指字面变量的大小*/
//			//右值引用，只能绑定右值，不可以绑定左值，除非使用move();
//			int a = 42;
//			//int&& b = a;		//编译错误，a具有左值
//			int&& b = 42;		//正确，42是右值
//			int c = std::move(a);	//使用move()函数，强制变为右值引用
//			std::cout << c<< std::endl;
//			//拷贝与移动的对比
//			//1、拷贝所用的时间
//			std::vector<int> vec1(1000000, 1);
//			auto start = std::chrono::high_resolution_clock::now();
//			std::vector<int> vec2 = vec1;
//			auto end = std::chrono::high_resolution_clock::now();
//			auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
//			std::cout << "耗时："<<duration.count()<<"μs" << std::endl;
//			std::cout << "vec1:size" << vec1.size() << " vec2:size" << vec1.size() << std::endl;
//			//移动所用的时间
//			auto start1 = std::chrono::high_resolution_clock::now();
//			std::vector<int> vec3 = std::move(vec1);
//			auto end1 = std::chrono::high_resolution_clock::now();
//			auto duration1 = std::chrono::duration_cast<std::chrono::microseconds> (end1 - start1);
//			std::cout << "耗时：" << duration1.count() << "μs" << std::endl;	
//			std::cout << "vec1:size" << vec1.size() << " vec2:size" << vec3.size() << std::endl;		//移动的速度大约是拷贝速度的10000倍
//			Text text;
//			Text text1 = text;						//拷贝构造
//			Text text2 = std::move(text);			//移动构造
//
//		}
//	std::cin.get();  
//	delete compare_class;					//如果不显式调用delete compare_class不会被释放
//}
