#pragma once
#include <string>
#include <iostream>
using namespace std;

class ACCESS
{
public:
	int UID = {0};
	string ACCOUNT = {0};
	string COMMENT = {0};
	virtual string *GetType();
	int DisplayUserList();

	//string Type;
	friend int AccountSave();

protected:
	virtual int UserAdd();
	virtual int UserDel();
	virtual int UserMod();
};

class Admin : protected ACCESS
{
public:
	string Type = "admin";
	virtual string* GetType() { return &Type; }

private:
	string PASSWORD = {0};

	friend int PasswdSave();
};

class User : protected ACCESS
{
public:
	string Type = "user";
	virtual string* GetType() { return &Type; }

private:
	string PASSWORD = {0};

	friend int PasswdSave();
};

class Guest : protected ACCESS
{
public:
	string Type = "guest";
	virtual string* GetType() { return &Type; }

private:
	string PASSWORD = {0};

	friend int PasswdSave();
};

class Node
{
public:
	ACCESS *val;
	Node *next;
	Node(ACCESS *val) : val(val), next(NULL) {}
	Node() {}
};

class LinkList
{
public:
	//构造函数
	LinkList();
	//在链表头部插入结点
	void InsertHead(ACCESS *val);
	//插入结点
	void Insert(ACCESS *val, int pos);
	//删除结点
	void Remove(ACCESS *val);
	void Remove(int pos);
	//得到链表长度
	int Length();
	//查找结点位置
	int Find(ACCESS *val, bool s_mode);
	//全文搜索
	void Search(LinkList *list);
	//打印链表
	void Print();

	Node *head;
	int length;
	friend int SaveFile(LinkList list);
};

//构造函数
LinkList::LinkList()
{
	head = new Node;
	length = 0;
}

//得到链表长度
int LinkList::Length()
{
	return length;
}

//在链表头部插入结点
void LinkList::InsertHead(ACCESS *val)
{
	Insert(val, 0);
}

void LinkList::Insert(ACCESS *val, int pos)
{
	if (pos < 0)
	{
		cout << "Pos must be greater than zero!" << endl;
		return;
	}
	int index = 1;
	Node *temp = head;
	Node *node = new Node(val);
	if (pos == 0)
	{
		Node temphead = *head;
		Insert(head->val, 1);
		head->next->next = temphead.next;
		head->val = val;
		length++;
		return;
	}
	while (temp != NULL && index < pos)
	{
		temp = temp->next;
		index++;
	}
	if (temp == NULL)
	{
		cout << "Insert failed" << endl;
		return;
	}
	node->next = temp->next;
	temp->next = node;
	length++;
}

//删除结点
void LinkList::Remove(ACCESS *val)
{
	int pos = Find(val, 0);
	if (pos == -1)
	{
		cout << "Delete failed!" << endl;
		return;
	}
	if (pos == 1)
	{
		Node *tempnode = head->next;
		*head = *head->next;
		delete tempnode;
		length--;
		return;
	}
	int index = 2;
	Node *temp = head;
	while (index < pos)
	{
		temp = temp->next;
		index++;
	}
	Node *tempnode = temp->next;
	temp->next = temp->next->next;
	delete tempnode;
	length--;
	cout << "Remove Complete" << endl;
}

void LinkList::Remove(int pos)
{
	if (pos == -1)
	{
		cout << "Delete failed!" << endl;
		return;
	}
	if (pos == 1)
	{
		Node *tempnode = head->next;
		*head = *head->next;
		delete tempnode;
		length--;
		return;
	}
	int index = 2;
	Node *temp = head;
	while (index < pos)
	{
		temp = temp->next;
		index++;
	}
	Node *tempnode = temp->next;
	temp->next = temp->next->next;
	delete tempnode;
	length--;
}

int LinkList::Find(ACCESS *val, bool s_mode)
{
	Node *temp = head;
	int index = 1;
	while (temp != NULL)
	{
		if (s_mode)
		{

			if (temp->val->ACCOUNT.compare(val->ACCOUNT) == 0 || temp->val->UID == val->UID)
			{
				return index;
			}
			temp = temp->next;
			index++;
		}
		else
		{
			if (temp->val->ACCOUNT.compare(val->ACCOUNT) == 0 && temp->val->UID == val->UID)
			{
				return index;
			}
			temp = temp->next;
			index++;
		}
	}
	return -1; //不存在返回-1
}

void LinkList::Print()
{
	if (head == NULL)
	{
		cout << "LinkList is empty!" << endl;
		return;
	}
	Node *temp = head;
	cout << "UID"
		 << "\t"
		 << "ACCOUNT"
		 << "\t"
		 << "TYPE"
		 << "\t"
		 << "PASSWD"
		 << "\t"
		 << "COMMENT" << endl;
	while (temp != NULL)
	{
		cout << temp->val->UID << "\t" << temp->val->ACCOUNT << "\t" << *temp->val->GetType() << "\t"
			 << "x"
			 << "\t" << temp->val->COMMENT << endl;
		temp = temp->next;
	}
	cout << endl;
}
