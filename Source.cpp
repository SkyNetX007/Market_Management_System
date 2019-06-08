#include "Goods.h"
#include "Groups.h"
#include <conio.h>
#include "md5.cpp"

using namespace std;

string GetPasswd()
{
	string password;//真正的密码存放处
	char pw[32], ch;

	int i = 0;
	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b' && i > 0)
		{
			printf("\b \b");
			--i;
		}
		else if (ch != '\b')
		{
			pw[i++] = ch;
			printf("*");
		}
	}
	pw[i] = '\0';
	password = pw;//键盘输入的密码给密码存放处
	return password;
}

int Login(FILE* userList, ACCESS* currentUser)
{
	if (userList == NULL) {
		FILE* initList = fopen("/etc/shadow", "w+");
		fprintf(initList, "root:root\n");
		fclose(initList);
		return -1;
	}

	string psd;
	string tmpUser;
	string tmpPsd;
	cout << "Username: ";
	cin >> currentUser->ACCOUNT;
	bool UserExist = 0;
	while (!feof(userList)) {
		fscanf(userList, "%s:", tmpUser);
		fscanf(userList, "%s\n", tmpPsd);
		if (currentUser->ACCOUNT.compare(tmpUser) == 0)
		{
			UserExist = 1;
			break;
		}
	}
	if (!UserExist)
	{
		cout << "Invalid Username!" << endl;
		system("pause");
		return 0;
	}
	cout << "Password: ";
	psd = GetPasswd();
	if (encrypt(psd).compare(tmpPsd) == 0)
	{
		return 1;
	}
	else
	{
		cout<<"Invalid Password!" << endl;
		system("pause");
		return 0;
	}
}

int main()
{
	GoodsList* currentGoodsList = new GoodsList;
	LinkList* userList = new LinkList;
	ACCESS* currentUser = new ACCESS;

	FILE* Passwd = fopen("/etc/passwd", "r");
	if (Passwd == NULL) {
		FILE* initList = fopen("/etc/passwd", "w+");
		fprintf(initList, "root:x:0:root\n");
		fclose(initList);
		return -1;
	}
	else {
		ACCESS* tempUser = new ACCESS;
		int listlength = 0;
		while (!feof(Passwd)) {
			fscanf(Passwd, "%s:", tempUser->ACCOUNT);
			fscanf(Passwd, "x:%s:", tempUser->UID);
			fscanf(Passwd, "%s:", tempUser->COMMENT);
			userList->Insert(tempUser, listlength);
			listlength++;
		}
	}
	fclose(Passwd);

	currentGoodsList->ReadGoods(fopen("GoodsList.txt", "r+"));
	if (Login(fopen("/etc/shadow", "r"), currentUser) == 1)
	{
		Node* temp = userList->head;
		while (temp->next) {
			if (temp->val->ACCOUNT.compare(currentUser->ACCOUNT) == 0)
			{
				currentUser = temp->val;
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
	}
	else
	{
		cout << "Forced Logout";
		exit(0);
	}
	
	//currentUser -> Login();
	//currentUser -> Operations( currentGoodsList );
	//currentUser -> Logout();

	currentGoodsList->WriteGoods(fopen("GoodsList.txt", "w+"));
	return 0;
}