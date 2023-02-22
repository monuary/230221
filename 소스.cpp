#include<iostream>
#include<cstring>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu();		//�޴����
void MakeAccount();		//���°����� ���� �Լ�
void DepositMoney();	//�Ա�
void WithdrawMoney();	//���
void ShowAllAccInfo();	//�ܾ���ȸ

enum{MAKE=1,DEPOSIT,WITHDRAW,INQUIRE,EXIT};	//1���� ���ʴ�� �ö󰣴�.

class Account
{
	int accID;		//���¹�ȣ
	int balance;	//�ܾ�
	char* cusName;	//���̸�
public:
	Account(int ID, int money, char* name) :accID(ID), balance(money)
	{
		cusName = new char[strlen(name) + 1];	//++�� ���� �ڿ��� �� �� �ִ�.
		strcpy(cusName, name);
	}
	int GetAccID() { return accID; }
	void Deposit(int money) { balance += money; }
	int Withdraw(int money)	//��ݾ� ��ȯ, ���� �� 0 ��ȯ
	{
		if (balance < money)return 0;
		balance -= money;
		return money;
	}
	void ShowAccInfo()
	{
		cout << "����ID: " << accID << endl;
		cout << "�̸�: " << cusName << endl;
		cout << "�ܾ�: " << balance << endl;
	}
	~Account() { delete[]cusName; }
};

Account* accArr[100];	//Account������ ���� �迭
int accNum = 0;			//����� Account ��

int main()
{
	int choice;

	while (1)
	{
		ShowMenu();
		cout << "����: "; cin >> choice; cout << endl;

		switch (choice)
		{
		case MAKE:MakeAccount(); break;			//break�� ���� �ݺ��� ����. ���� �ݺ��� ���� ���۵ȴ�.
		case DEPOSIT:DepositMoney(); break;
		case WITHDRAW:WithdrawMoney(); break;
		case INQUIRE:ShowAllAccInfo(); break;
		case EXIT:for (int i = 0; i < accNum; i++)delete accArr[i]; return 0;
		default:cout << "Illegal selection.." << endl;	//1~5�� �ƴ� ���� �Է� ��
		}
	}
	return 0;
}

void ShowMenu()
{
	cout << "-----Menu-----" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}
void MakeAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[���°���]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�̸�: "; cin >> name;
	cout << "�Աݾ�: "; cin >> balance; cout << endl;

	accArr[accNum++] = new Account(id, balance, name);
}
void DepositMoney()
{
	int money;
	int id;
	cout << "[�Ա�]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�Աݾ�: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->Deposit(money);
			cout << "�ԱݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}
void WithdrawMoney()
{
	int money;
	int id;
	cout << "[���]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "��ݾ�: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "�ܾ׺���" << endl << endl;
				return;
			}
			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}
void ShowAllAccInfo()
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		cout << endl;
	}
}