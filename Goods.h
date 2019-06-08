#pragma once
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct Goods
{
	string name = "Undefined";
	string ID = "0";
	string type = "0";
	double price = -1;
	double discount = 0;
	int num = 0;
	Goods *next = nullptr;

	void Swap(Goods *_goods2);
	void PrintInfo(); //按照一定格式输出商品信息，防止名字太长导致错位
	void SetInfo(string _name, string _ID, string _type, double _price, double _discount, int _num);
};

struct GoodsList //_No从0开始
{
	Goods *head = new Goods;

	void InsertNewGoods(Goods *_newGoods, int _No = -1);
	void ManualAdd();
	void DeleteGoods(int _No);
	Goods *Content(int _No);
	void PrintContent(int _No);
	void SwapGoods(int _No1, int _No2);
	void ReadGoods(FILE *list);
	void WriteGoods(FILE *list);

	void Sort(double priceMode);
	void Sort(string stringMode);
};