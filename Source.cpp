#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;

struct FD//Функциональная зависимость 
{
	string left;
	string right;
	FD(const string& _l, const string& _r) : left(_l), right(_r) {};
};

void ReadFile(string& name, vector<FD>& F);
void SX(const string& X, const vector<FD>& F, string& X_plus);
bool PRF(const FD& X_struct, const vector<FD>& F);
void NPOK(const vector<FD>& F, vector<FD>& G);
//вывод вектора функциональных зависимостей
void printFDV(vector<FD> &in) {
	if (in.size() == 0)
		cout << "0\n";
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i].left == "")
			cout << "0";
		else
			cout << in[i].left;
		cout << "->";
		if (in[i].right == "")
			cout << "0";
		else
			cout << in[i].right << endl;
	}
}

int main()
{
	SetConsoleCP(1251); //русификация консоли
	SetConsoleOutputCP(1251);
	int tests = 6; //число тестов
	for (int i = 0; i < tests; i++) {
		cout << "Тест" << i + 1 << '\n';
		string file("Test" + to_string(i + 1) + ".txt"); //откуда будем считывать данные
		vector<FD> F;
		vector<FD> G;
		ReadFile(file, F);
		NPOK(F, G);
		cout << "Неизбыточное покрытие:\n";
		printFDV(G);
		cout << "\n\n";
	}
	system("pause");
	return 0;
}

//функция к алгоритмам никак не относится
//она лишь считывает файл
void ReadFile(string& name, vector<FD>& F) {
	string X;
	ifstream In(name);
	if (!In) {
		cout << "Файл не найден!";
		exit(-1);
	}
	In >> X; //считываем множество атрибутов до \n
	X.shrink_to_fit();
	FD Func("", "");
	string input_1 = "";
	string input_2 = "";
	char ch = 0;
	cout << "Считал из файла:\n";
	while (!In.eof()) {
		input_1 = "";
		input_2 = "";
		ch = 0;
		while (true) {
			In >> ch;
			if (ch == '-')
				break;
			input_1 += ch;
			if (ch == '0' and In.eof()) {
				input_1.clear();
				break;
			}
		}
		if (input_1 == "")
			cout << '0';
		else
			cout << input_1 << '-';
		if (!In.eof()) {
			In >> ch;
			cout << ch;
			In >> input_2;
			cout << input_2;
		}
		else {
			input_2.clear();
			In >> ch;
		}
		if (input_1 == "0")
			input_1.clear();
		if (input_2 == "0")
			input_2.clear();

		F.push_back(FD(input_1, input_2));
		cout << "\n";
	}
	for (int i = 0; i < F.size(); i++) {
		F[i].left.shrink_to_fit();
		F[i].right.shrink_to_fit();
	}
	F.shrink_to_fit();
	cout << "\n";
}

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
	if (includes(X_plus.begin(), X_plus.end(), X_struct.right.begin(), X_struct.right.end()))//строка содержит
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
