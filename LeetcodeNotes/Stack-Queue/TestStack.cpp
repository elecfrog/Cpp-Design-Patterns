#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <list>

using namespace std;

/*

    - C++中stack 是容器么？
    - 我们使用的stack是属于哪个版本的STL？
    - 我们使用的STL中stack是如何实现的？
    - stack 提供迭代器来遍历stack空间么？

    以STL中栈往往不被归类为容器，而被归类为container adapter（容器适配器）
    Stack的内部结构，栈的底层实现可以是vector，deque，list 都是可以的， 主要就是数组和链表的底层实现。

    我们常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的底层结构。

    deque是一个双向队列，只要封住一段，只开通另一端就可以实现栈的逻辑了。

 */
int main()
{
    cout << "Hello!" << endl;

    stack<int, vector<int>> third; // 使用vector为底层容器的栈
    queue<int, list<int>> third; // 定义以list为底层容器的队列
}