#ifndef __GATE_SCENE_H_
#define __GATE_SCENE_H_


/*
 *	实现双向链表的九屏机制
 */


#include <iostream>
#include <string>

using namespace std;

// 双链表（对象）
class DoubleNode
{
public:
	DoubleNode(string key, int x, int y)
	{
		this->key = key;
		this->x = x;
		this->y = y;
		xPrev = xNext = NULL;
	};

	DoubleNode * xPrev;
	DoubleNode * xNext;

	DoubleNode * yPrev;
	DoubleNode * yNext;

	string key;
	int x; // 位置（x坐标）
	int y; // 位置（y坐标）

private:

};




// 地图/场景
class SceneNode
{
public:

	SceneNode()
	{
		this->_head = new DoubleNode("[head]", 0, 0); // 带头尾的双链表(可优化去掉头尾)
		this->_tail = new DoubleNode("[tail]", 0, 0);
		_head->xNext = _tail;
		_head->yNext = _tail;
		_tail->xPrev = _head;
		_tail->yPrev = _head;
	};

	// 对象加入(新增)
	DoubleNode * Add(string name, int x, int y)
	{

		DoubleNode * node = new DoubleNode(name, x, y);
		_add(node);
		return node;
	};

	// 对象离开(删除)
	void Leave(DoubleNode * node)
	{
		node->xPrev->xNext = node->xNext;
		node->xNext->xPrev = node->xPrev;
		node->yPrev->yNext = node->yNext;
		node->yNext->yPrev = node->yPrev;

		node->xPrev = NULL;
		node->xNext = NULL;
		node->yPrev = NULL;
		node->yNext = NULL;
	};

	// 对象移动
	void Move(DoubleNode * node, int x, int y)
	{
		Leave(node);
		node->x = x;
		node->y = y;
		_add(node);
	};

	// 获取范围内的AOI (参数为查找范围)
	void PrintAOI(DoubleNode * node, int xAreaLen, int yAreaLen)
	{
		cout << "Cur is: " << node->key << "（" << node->x << "," << node->y << ")" << endl;
		cout << "Print AOI:" << endl;

		// 往后找
		DoubleNode * cur = node->xNext;
		while (cur != _tail)
		{
			if ((cur->x - node->x) > xAreaLen)
			{
				break;
			}
			else
			{
				int inteval = 0;
				inteval = node->y - cur->y;
				if (inteval >= -yAreaLen && inteval <= yAreaLen)
				{
					cout << "\t" << cur->key << "(" << cur->x << "," << cur->y << ")" << endl;
				}
			}
			cur = cur->xNext;
		}

		// 往前找
		cur = node->xPrev;
		while (cur != _head)
		{
			if ((node->x - cur->x) > xAreaLen)
			{
				break;
			}
			else
			{
				int inteval = 0;
				inteval = node->y - cur->y;
				if (inteval >= -yAreaLen && inteval <= yAreaLen)
				{
					cout << "\t" << cur->key << "(" << cur->x << "," << cur->y << ")" << endl;
				}
			}
			cur = cur->xPrev;
		}
	};

	// 调试代码
	void PrintLink()  // 打印链表(从头开始)
	{
		// 打印x轴链表
		DoubleNode * cur = _head->xNext;
		while (cur != _tail)
		{
			cout << (cur->key) << "(" << (cur->x) << "," << (cur->y) << ") -> ";
			cur = cur->xNext;
		}
		cout << "end" << endl;

		// 打印y轴链表
		cur = _head->yNext;
		while (cur != _tail)
		{
			cout << (cur->key) << "(" << (cur->x) << "," << (cur->y) << ") -> ";
			cur = cur->yNext;
		}
		cout << "end" << endl;
	};

	// --------------------------------------------
	void test()
	{
		SceneNode scene = SceneNode();
		// 增加
		scene.Add("a", 1, 5);
		scene.Add("f", 6, 6);
		scene.Add("c", 3, 1);
		scene.Add("b", 2, 2);
		scene.Add("e", 5, 3);
		DoubleNode * node = scene.Add("d", 3, 3);

		scene.PrintLink();
		scene.PrintAOI(node, 2, 2);

		// 移动
		cout << endl << "[MOVE]" << endl;
		scene.Move(node, 4, 4);
		scene.PrintLink();
		scene.PrintAOI(node, 2, 2);

		// 删除
		cout << endl << "[LEAVE]" << endl;
		scene.Leave(node);
		scene.PrintLink();
	}

private:
	DoubleNode * _head;
	DoubleNode * _tail;

	void _add(DoubleNode * node)
	{
		// x轴处理
		DoubleNode * cur = _head->xNext;
		while (cur != NULL)
		{
			if ((cur->x > node->x) || cur == _tail) // 插入数据
			{
				node->xNext = cur;
				node->xPrev = cur->xPrev;
				cur->xPrev->xNext = node;
				cur->xPrev = node;
				break;
			}
			cur = cur->xNext;
		}

		// y轴处理
		cur = _head->yNext;
		while (cur != NULL)
		{
			if ((cur->y > node->y) || cur == _tail) // 插入数据
			{
				node->yNext = cur;
				node->yPrev = cur->yPrev;
				cur->yPrev->yNext = node;
				cur->yPrev = node;
				break;
			}
			cur = cur->yNext;
		}
	}
};



#endif

