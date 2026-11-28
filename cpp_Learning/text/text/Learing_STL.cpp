#include<iostream>
#include<queue>
#include<stack>
#include<deque>
#include<list>
#include<chrono>
#include<vector>
#include<forward_list>
#include<array>
class Text {
	std::string name;
	int age;
public:
	Text();
	Text(const std::string n,const int a ):name(n),age(a){}
};
namespace L_containerAdapter {
	//容器适配器，queue(队列)与statc(栈)
	void learnQueue() {
		//queue：是一种先进先出(FIFO)的数据结构，不提供迭代器
		//模板签名:template<class T, class Container = std::deque<T>> class queue;,底层容器默认为deque(双端队列)，也可以显式的指定为list(双端链表)
		//初始化
		std::queue<int> q;			//默认为deque
		std::queue<int, std::list<int>> q1;      //显式指定为list
		std::deque<int> d = { 1,3,4 };
		//从已有容器构造：拷贝或移动一个兼容的底层容器（如 deque、list）。注意类型必须与模板第二参数匹配。
		std::queue<int> q2(d);					//拷贝构造
		std::queue<int> q3(std::move(d));		//移动构造
		//从另一个同类型 queue 构造
		std::queue<int> q4(q);					//拷贝构造，同样可以使用move
		//迭代器范围初始哈
		//std::vector<int> vec{ 1,2,3,4,6,9 };
		//std::queue<int> q5(vec.begin(), vec.end());		//c++23支持
		q.push(100);										//队尾插入元素
		q.emplace(110);										
		//push与emplace的区别:push 与 emplace 的核心区别在于对象构造的时机与位置，这直接决定了是否存在额外的拷贝或移动开销,对于复杂对象尤为明显
		std::queue<Text> t1;
		auto start = std::chrono::steady_clock::now();
		int i =100000; //插入100000个测试用时
		for (int j = 0;j < i;++j) {
			t1.push(Text("A", 10));
		}
		auto end = std::chrono::steady_clock::now();
		//计算耗时单位毫秒使用push
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "push耗时: " << duration.count() << " ms\n";
		auto start1 = std::chrono::steady_clock::now();
		for (int j = 0;j < i;++j) {
			t1.emplace("B", 19);
		}
		auto end1 = std::chrono::steady_clock::now();
		//计算耗时单位毫秒使用emplace
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
		std::cout << "emplace耗时: " << duration1.count() << " ms\n"; //使用emplace要快于使用push。
		//由于先push在外部构造临时对象,再拷贝/移动到队列内部,而emplace直接在队列内部的存储位置上原地构造（in-place）
		q.push(120);
		q.push(130);
		q.push(140);
		std::cout << q.size() << std::endl; //获取队列长度
		int len = q.size();
		for (int j = 1;j <=len;j++) {				//由于queue没有迭代器所以用这种方法遍历。
			if (!q.empty()) {						//判读是否为空
				std::cout << q.front() << std::endl; //获取队首元素的值
				q.pop();							//队首元素出队，注意没有返回值。
			}
		}
		q.push(150);
		q.push(160);
		q.push(170);
		if(!q.empty())
		std::cout << q.back() << std::endl;			//获取队尾元素

	}
	void learnStack() {
		//Stack，是一种先进后出(LIFO)的数据结构，不提供迭代器
		//模板签名：template<class T, class Container = std::deque<T>> class stack;
		std::stack<int> s;															//底层容器默认为deque
		std::deque<int> d = { 1,2,3,4 };
		//从已有容器构造：拷贝或移动一个兼容的底层容器（如 deque、list）。注意类型必须与模板第二参数匹配。
		std::stack<int> s1(d);							//拷贝构造					
		std::list<int>  l = { 1,2,3,4 };
		std::stack<int, std::list<int>> s2(l);				//显式的指出底层容器为list
		std::stack<int, std::list<int> > s3(std::move(s2));				//移动构造
		//入栈
		s1.push(5);
		s1.emplace(6);									//这里push与emplace的区别与queue的区别一样
		//遍历
		int len = s1.size();							//获取长度
		for (int i = 0;i < len;i++) {
			if (!s1.empty()) {							//判定栈是否为空
				std::cout << s1.top() << std::endl;		//获取栈顶元素
				s1.pop();								//栈顶元素出栈
			}
			//出栈顺序6，5，4，3，2，1
		}
	}
}
namespace L_sequenceContainers {
	void learnVector() {
		//vector:是 STL 中最核心的动态数组容器，它封装了大小可变的数组，支持在尾部高效增删元素，并能在容量不足时自动重新分配内存。
		//vector数组的初始化
		std::vector<int> vec;		//默认构造空vector
		//指定vector数值的大小与元素的初始值
		std::vector<int> vec1(10);   //10个元素默认值为0
		std::vector<int> vec2(10, 1);//10个元素，默认值为1
		//初始化列表
		std::vector<int> vec3 = { 1,2,3,4,5,6 }; //或者可以省略=
		//拷贝构造
		std::vector<int> vec4(vec3);
		//移动构造
		std::vector<int> vec5(std::move(vec4));                  //vec5变为1，2，3，4，5，6，vec5变为空
		//迭代器范围构造
		std::vector<int> vec6(vec5.begin(), vec5.begin() + 2);   //vec6：1，2,(从vec5.begin(),向右2个元素，包括vec5.begin())
		for (auto& x : vec6) {									//由于vector提供迭代器因此，可以这样遍历
			std::cout << x << std::endl;
		}
		//常用的一些成员函数
		//size(),返回数组的长度
		std::cout << "数组的大小:" << vec6.size() << std::endl; //返回数组的大小
		//empty()，返回数组是否为空，空返回1，否则返回0
		if (!vec6.empty()) {									//判断数组是否为空
			std::cout << "数组非空" << std::endl;
		}
		else {
			std::cout << "数组为空" << std::endl;
		}
		//reserve()，预留vector数组的空间，非常重要，避免vector数组每一次添加新元素是由于空间不足，频繁的扩大容量，浪费时间
		//push_back(),尾插元素。
		//emplace_back(),尾插元素，与push_back()相比，省去临时对象的拷贝/移动，效率更高。
		//std::vector<Text> t1;
		//t1.reserve(100000);
		//std::vector<Text> t2;
		//auto start = std::chrono::steady_clock::now();
		//for (int i = 0;i < 100000;i++) {
		//	t1.push_back(Text("A", 18));
		//}
		//auto end = std::chrono::steady_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		//std::cout << "使用reserve，使用push_back()所消耗的时间:" << duration.count() << "ms" << std::endl;
		//auto start1 = std::chrono::steady_clock::now();
		//for (int i = 0;i < 100000;i++) {
		//	t2.push_back(Text("A", 18));
		//}
		//auto end1 = std::chrono::steady_clock::now();
		//auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
		//std::cout << "不使用reserve,使用push_back()所消耗的时间:" << duration1.count() << "ms" << std::endl;
		////clear()
		//t1.clear();									//销毁元素，size变为0，但是内存不释放
		//t2.clear();
		//std::vector<Text> t3;
		//auto start2 = std::chrono::steady_clock::now();
		//for (int i = 0;i < 100000;i++) {
		//	t1.emplace_back("A", 18);
		//}
		//auto end2 = std::chrono::steady_clock::now();
		//auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
		//std::cout << "使用reserve，使用emplace_back()所消耗的时间:" << duration2.count() << "ms" << std::endl;
		//auto start3 = std::chrono::steady_clock::now();
		//for (int i = 0;i < 100000;i++) {
		//	t3.emplace_back("A", 18);
		//}
		//auto end3 = std::chrono::steady_clock::now();
		//auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
		//std::cout << "不使用reserve，使用emplace_back()所消耗的时间:" << duration3.count() << "ms" << std::endl;
		//t3.clear();
		////capacity(),查看占用vector数组所占用的内存
		//std::cout << t1.capacity() << std::endl;
		//std::cout << t2.capacity() << std::endl;
		//std::cout << t3.capacity() << std::endl;
		////重新赋值空 vector
		//t1 = std::vector<Text>{};
		//t2 = std::vector<Text>{};
		//t3 = std::vector<Text>{};
		//std::cout << t1.capacity() << std::endl;
		//std::cout << t2.capacity() << std::endl;
		//std::cout << t3.capacity() << std::endl;
		// 
		//resize(),改变元素的个数若变大则填充默认值；若变小则删除多余元素。同时改变 size 和 capacity
		vec3.resize(8);						//默认值为0，resize(n,y)默认值为y
		for (auto x : vec3) {
			std::cout << x << " ";
		}
		std:: cout<< "\n";
		//pop_back(),删除末尾元素,无返回值
		vec3.pop_back();
		for (auto x : vec3) {
			std::cout << x << " ";
		}
		std::cout << "\n";
		//insert()，插入元素，利用迭代器。返回插入第一个元素的迭代,插入时一定注意维护迭代器
		auto it_start = vec3.begin();     //获取开始迭代器，指向第一个元素
		auto it_end = vec3.end();         //获取末尾迭代器，指向末尾元素的下一个位置
		//单值插入
		vec3.insert((it_start + 5), 100); //在it_start向右偏移5个元素的位置前插入包括it_start这个位置，100
		//多个同样的值插入
		it_start=vec3.insert(it_start, 5, 0);	//在it_start前插入5个零,让it_start重新指向首个元素
		//迭代器范围插入
		it_start=vec3.insert(it_start, vec6.begin(), vec6.end());	
		for (auto x : vec3) {
			std::cout << x << " ";
		}
		std::cout << "\n";
		//erase(),删除迭代器指向的元素，后面的元素会向前移动返回下一个有效的迭代器，一定要更新迭代器的指向，删除后原有迭代变为无效,再次调用是未定义行为
		// 确保 it_start 不是 end()，且后面至少有 1 个可删除元素
		vec3.erase(it_start + 1);
		for (auto x : vec3) {
			std::cout << x << " ";
		}
		std::cout << "\n";
		//访问
		// 迭代器
		std::cout << *it_start << std::endl;
		//除了通过迭代器访问，还可以像数组一样使用下标访问
		std::cout << vec3[0]<< std::endl;
		//ar()
		std::cout << vec3.at(0) << std::endl;
		//front() / back()	访问首尾元素,或更改队尾队首元素,返回引用
		int f = vec3.front();
		vec3.front()=1000;
		int b = vec3.back();
		vec3.back() = 1000;
		for (auto x : vec3) {
			std::cout << x << " ";
		}
		std::cout << "\n";
	}
}
int main() {
	{
		using namespace  L_containerAdapter;
		//learnQueue();
		//learnStack();
	}
	{
		using namespace  L_sequenceContainers;
		learnVector();

	}
}