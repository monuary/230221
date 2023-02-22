#include<iostream>
#include<cstring>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu();		//메뉴출력
void MakeAccount();		//계좌개설을 위한 함수
void DepositMoney();	//입금
void WithdrawMoney();	//출금
void ShowAllAccInfo();	//잔액조회

enum{MAKE=1,DEPOSIT,WITHDRAW,INQUIRE,EXIT};	//1부터 차례대로 올라간다.

class Account
{
	int accID;		//계좌번호
	int balance;	//잔액
	char* cusName;	//고객이름
public:
	Account(int ID, int money, char* name) :accID(ID), balance(money)
	{
		cusName = new char[strlen(name) + 1];	//++은 변수 뒤에만 쓸 수 있다.
		strcpy(cusName, name);
	}
	int GetAccID() { return accID; }
	void Deposit(int money) { balance += money; }
	int Withdraw(int money)	//출금액 반환, 부족 시 0 반환
	{
		if (balance < money)return 0;
		balance -= money;
		return money;
	}
	void ShowAccInfo()
	{
		cout << "계좌ID: " << accID << endl;
		cout << "이름: " << cusName << endl;
		cout << "잔액: " << balance << endl;
	}
	~Account() { delete[]cusName; }
};

Account* accArr[100];	//Account저장을 위한 배열
int accNum = 0;			//저장된 Account 수

int main()
{
	int choice;

	while (1)
	{
		ShowMenu();
		cout << "선택: "; cin >> choice; cout << endl;

		switch (choice)
		{
		case MAKE:MakeAccount(); break;			//break는 현재 반복을 종료. 따라서 반복이 새로 시작된다.
		case DEPOSIT:DepositMoney(); break;
		case WITHDRAW:WithdrawMoney(); break;
		case INQUIRE:ShowAllAccInfo(); break;
		case EXIT:for (int i = 0; i < accNum; i++)delete accArr[i]; return 0;
		default:cout << "Illegal selection.." << endl;	//1~5이 아닌 숫자 입력 시
		}
	}
	return 0;
}

void ShowMenu()
{
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}
void MakeAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout << "[계좌개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이름: "; cin >> name;
	cout << "입금액: "; cin >> balance; cout << endl;

	accArr[accNum++] = new Account(id, balance, name);
}
void DepositMoney()
{
	int money;
	int id;
	cout << "[입금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "입금액: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->Deposit(money);
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl << endl;
}
void WithdrawMoney()
{
	int money;
	int id;
	cout << "[출금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "출금액: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "잔액부족" << endl << endl;
				return;
			}
			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl << endl;
}
void ShowAllAccInfo()
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		cout << endl;
	}
}