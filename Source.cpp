#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <set>
using namespace std;

struct FD//Функциональная зависимость 
{
	vector<string> left;
	vector<string> right;
	FD(const vector<string>& _l, const vector<string>& _r) : left(_l), right(_r) {};
};

void ReadFile(string& name, vector<string>& X, vector<FD>& F);
void SX(const string& X, const vector<FD>& F, string& X_plus);
bool PRF(const FD& X_struct, const vector<FD>& F);
void NPOK(const vector<FD>& F, vector<FD>& G);

int main()
{
	SetConsoleCP(1251); //русификация консоли
	SetConsoleOutputCP(1251);

	string file("Input.txt"); //откуда будем считывать данные
	vector<string> X;
	vector<FD> F;
	vector<FD> G;
	ReadFile(file, X, F);
	//NPOK(F, G);
	if (G.size() == 0)
		cout << "0\n";
	/*
	for (int i = 0; i < G.size(); i++)
	{
		if (G[i].left[0] == "")
			cout << "0";
		else
			cout << G[i].left;
		cout << "->";
		if (G[i].right == "")
			cout << "0";
		else
			cout << G[i].right << endl;
	}
	*/
	system("pause");
	return 0;
}

//функция к алгоритмам никак не относится
//она лишь считывает файл
void ReadFile(string& name, vector<string>& X, vector<FD>& F) {
	set<string> tX;
	ifstream In(name);
	if (!In) {
		cout << "Файл не найден!";
		exit(-1);
	}
	//читаем атрибуты
	char ch;
	string buff;
	getline(In, buff, '\n');
	for (int i = 0; i < buff.length(); i++) {
		if (buff[i] == ' ') {
			buff.erase(i, 1);
			i--;
		}
	}
	//атрибуты в buff
	//разбиваем buff на отдельные атрибуты
	string A;
	int len = buff.length();
	int j = 0;
	while (j < len) {
		A += buff[j];
		while (j < len - 1)
			if (buff[j + 1] >= '0' && buff[j + 1] <= '9') {
				j++;
				A += buff[j];
			}
			else {
				break;
			}

		tX.insert(A);
		A.clear();
		j++;
	}
	X.assign(tX.begin(), tX.end());
	int currentF = 0;
	while (!In.eof()) {

		buff.clear();
		getline(In, buff, '-');
		for (int i = 0; i < buff.length(); i++) {
			if (buff[i] == ' ') {
				buff.erase(i, 1);
				i--;
			}
		}
		//разбиваем buff на отдельные атрибуты
		string A;
		set<string> FLeft;
		int len = buff.length();
		int j = 0;
		while (j < len) {
			A += buff[j];
			while (j < len - 1)
				if (buff[j + 1] >= '0' && buff[j + 1] <= '9') {
					j++;
					A += buff[j];
				}
				else {
					break;
				}
			FLeft.insert(A);
			A.clear();
			j++;
		}
		In.get(ch);
		buff.clear();
		getline(In, buff, '\n');
		for (int i = 0; i < buff.length(); i++) {
			if (buff[i] == ' ') {
				buff.erase(i, 1);
				i--;
			}
		}
		//разбиваем buff на отдельные атрибуты
		A.clear();
		set<string> FRight;
		len = buff.length();
		j = 0;
		while (j < len) {
			A += buff[j];
			while (j < len - 1)
				if (buff[j + 1] >= '0' && buff[j + 1] <= '9') {
					j++;
					A += buff[j];
				}
				else {
					break;
				}
			FRight.insert(A);
			A.clear();
			j++;
		}
		vector<string> left;
		vector<string> right;
		left.assign(FLeft.begin(), FLeft.end());
		right.assign(FRight.begin(), FRight.end());
		F.push_back(FD(left, right));
	}
}
/*
void SX(const string& X, const vector<FD>& F, string& X_plus) {
	string OLD = "";
	string NEW = X;
	string Q = "";
	string A;
	string B;
	string C;
	int k = 0;
	while (NEW != OLD)
	{
		Q = "";
		k++;
		OLD = NEW;
		for (int i = 0; i < F.size(); i++)
		{
			A = NEW;
			B = F[i].left;
			C = F[i].right;
			sort(A.begin(), A.end());
			sort(B.begin(), B.end());
			sort(C.begin(), C.end());
			if (includes(A.begin(), A.end(), B.begin(), B.end()))//строка содержит
			{
				Q.clear();
				set_union(A.begin(), A.end(), C.begin(), C.end(), std::back_inserter(Q));//объединение множеств
				NEW = Q;
			}
		}
	}
	X_plus = NEW;
}

bool PRF(const FD& X_struct, const vector<FD>& F)
{
	string X_plus;
	string X = X_struct.left;
	SX(X, F, X_plus);
	if (std::includes(X_plus.begin(), X_plus.end(), X_struct.right.begin(), X_struct.right.end()))//строка содержит
		return true;
	else
		return false;
}

void NPOK(const vector<FD>& F, vector<FD>& G)
{
	G = F;
	vector<FD> G_minus = F;
	for (int i = 0; i < F.size(); i++)
	{
		G_minus = G;
		int k = 0;
		while (true)
		{
			if (k < G_minus.size())
			{
				if (F[i].left == G_minus[k].left && F[i].right == G_minus[k].right)
					G_minus.erase(G_minus.begin() + k);
				else
					k++;
			}
			else
				break;
		}
		if (PRF(F[i], G_minus))
			G = G_minus;
	}
}
*/