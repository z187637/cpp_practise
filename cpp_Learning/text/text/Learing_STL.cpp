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

	}

}
int main() {
	{
		using namespace  L_containerAdapter;
		//learnQueue();
		learnStack();
	}
}