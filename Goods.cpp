#pragma warning(disable : 4996)
#include "Goods.h"

#define NAME_LENGTH 14
#define PAGE_MAX 6

void Goods::PrintInfo() //以一定格式输出商品信息，保证不会因为商品名字太长导致错位（但是会很多行）
{
	int subs = name.length() / NAME_LENGTH;
	for (int i = 0; i < subs; i++)
	{
		cout << name.substr(i * NAME_LENGTH, NAME_LENGTH) << "\n";
	}
	if (name.length() < 8)
		cout << name << "\t\t";
	else
		cout << name.substr(subs * NAME_LENGTH) << "\t";

	cout << setprecision(2) << setiosflags(ios::fixed);
	cout << price << "\t\t";
	cout << discount * 100 << "%\t\t";
	cout << price * (1 - discount) << "\t\t";
	cout << num << "\n\n";
}

void Goods::SetInfo(string _name, string _ID, string _type, double _price, double _discount, int _num)
{
	name = _name, ID = _ID, type = _type;
	price = _price, discount = _discount;
	num = _num;
}

void GoodsList::InsertNewGoods(Goods *_newGoods, int _No)
{
	Goods *temp = nullptr;
	int currentLength = 0;
	for (temp = head; temp->next && currentLength != _No; temp = temp->next, currentLength++)
		;
	if (temp->price == -1)
		temp = _newGoods;
	else
	{
		_newGoods->next = temp->next;
		temp->next = _newGoods;
	}
}

void GoodsList::ManualAdd()
{
	char tempName[50] = "\0", tempID[50] = "\0", tempType[50] = "\0";
	double tempPrice = 0;
	int tempNum = 0;
	Goods *temp = nullptr;
	printf("Insert new goods' name: ");
	scanf("%s", tempName);
	printf("\t\t\t ID: ");
	scanf("%s", tempID);
	printf("\t\t\t type: ");
	scanf("%s", tempType);
	printf("\t\t\t original price: ");
	scanf("%lf", &tempPrice);
	printf("\t\t\t number in storage: ");
	scanf("%d", &tempNum);
	temp = Content(-1);
	temp->SetInfo(tempName, tempID, tempType, tempPrice, 0, tempNum);
	temp->next = new Goods;
}

Goods *GoodsList::Content(int _No)
{
	Goods *temp = head;
	for (int i = 0; i != _No && temp->next; temp = temp->next, i++)
		;
	return temp;
}

void GoodsList::PrintContent(int _No) //_No == -1 -> PrintAll
{
	if (_No == -1)
	{
		cout << "Name\t\t"
			 << "Original_Price\t"
			 << "Discount_Rate\t"
			 << "Current_Price\t"
			 << "Storage" << endl;
		for (int i = 0; i <= 60; i++, printf("-"))
			;
		cout << "\n"
			 << endl;
		for (Goods *temp = head; temp->next; temp = temp->next)
			temp->PrintInfo();
	}
	else
	{
		Content(_No)->PrintInfo();
	}
}

void GoodsList::DeleteGoods(int _No)
{
	if (_No == 0)
	{
		Goods *temp = head;
		head = head->next;
		delete (temp);
	}
	else
	{
		Goods *temp = Content(_No);
		Content(_No - 1)->next = temp->next;
		delete (temp);
	}
}

void GoodsList::SwapGoods(int _No1, int _No2)
{
	Goods temp = *Content(_No1);
	Goods *No1Next = temp.next;
	Goods *No2Next = Content(_No2)->next;

	*Content(_No1) = *Content(_No2);
	Content(_No1)->next = No1Next;

	*Content(_No2) = temp;
	Content(_No2)->next = No2Next;
}

void GoodsList::ReadGoods(FILE *list)
{
	Goods *temp = Content(-1);
	char tempName[50] = "\0", tempID[50] = "\0", tempType[50] = "\0";
	double tempPrice = 0, tempDiscount;
	int tempNum;
	while (1)
	{
		fscanf(list, "%s%s%s", tempName, tempID, tempType);
		fscanf(list, "%lf%lf%d", &tempPrice, &tempDiscount, &tempNum);
		temp->SetInfo(tempName, tempID, tempType, tempPrice, tempDiscount, tempNum);
		if (tempPrice == -1 || feof(list))
			break;
		temp->next = new Goods, temp = temp->next;
	}
	fclose(list);
}

void GoodsList::WriteGoods(FILE *list)
{
	Goods *temp = head;
	for (; temp; temp = temp->next)
	{
		fprintf(list, "%s %s %s", temp->name.c_str(), temp->ID.c_str(), temp->type.c_str());
		fprintf(list, "\n%lf %lf %d\n", temp->price, temp->discount, temp->num);
	}
	fclose(list);
}

void GoodsList::Sort(double priceMode)
{
	Goods *temp = nullptr;
	for (int complete = 1; complete != 1; complete = 1)
	{
		temp = head;
		while (temp->next)
		{
			if ((temp->price - temp->next->price) * priceMode > 0)
			{
				temp->Swap(temp->next);
				complete = 0;
			}
			temp = temp->next;
		}
	}
}

void GoodsList::Sort(string stringMode)
{
	int mode = (stringMode[0] == '-' ? -1 : 1);
	string toCompare1 = "\0", toCompare2 = "\0";
	Goods *temp = nullptr;
	for (int complete = 1; complete != 1; complete = 1)
	{
		temp = head;
		while (temp->next)
		{
			if (stringMode == "name" || stringMode == "-name")
				toCompare1 = temp->name, toCompare2 = temp->next->name;
			else if (stringMode == "type" || stringMode == "-type")
				toCompare1 = temp->type, toCompare2 = temp->next->type;
			else if (stringMode == "ID" || stringMode == "-ID")
				toCompare1 = temp->ID, toCompare2 = temp->next->ID;
			else
				return;

			if (toCompare1.compare(toCompare2) * mode > 0)
			{
				temp->Swap(temp->next);
				complete = 0;
			}
			temp = temp->next;
		}
	}
}
