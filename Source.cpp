#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <set>
using namespace std;

struct FD//?????????????? ??????????? 
{
	vector<string> left;
	vector<string> right;
	FD(const vector<string>& _l, const vector<string>& _r) : left(_l), right(_r) {};
};

void ReadFile(string& name, vector<string>& X, vector<FD>& F);
void SX(const vector<string>& X, const vector<FD>& F, vector<string>& X_plus);
bool PRF(const FD& X_struct, const vector<FD>& F);
void NPOK(const vector<FD>& F, vector<FD>& G);

int main()
{
	SetConsoleCP(1251); //??????????? ???????
	SetConsoleOutputCP(1251);
	int tests = 6;
	for (int t = 0; t < tests; t++) {
		cout << "????: " << t + 1<<"\n";
		string file("Test"); //?????? ????? ????????? ??????
		file += to_string(t+1) + ".txt";

		vector<string> X;
		vector<FD> F;
		vector<FD> G;
		ReadFile(file, X, F);
		NPOK(F, G);
		cout << "???????????? ????????:\n";
		if (G.size() == 0)
			cout << "0\n";

		for (int i = 0; i < G.size(); i++)
		{
			if (G[i].left[0] == "")
				cout << "0";
			else {
				for (int j = 0; j < G[i].left.size(); j++)
					cout << G[i].left[j];
			}
			cout << "->";
			if (G[i].right[0] == "")
				cout << "0";
			else {
				for (int j = 0; j < G[i].right.size(); j++)
					cout << G[i].right[j];
			}
			cout << "\n";
		}
	}
	
	
	system("pause");
	return 0;
}

//??????? ? ?????????? ????? ?? ?????????
//??? ???? ????????? ????
void ReadFile(string& name, vector<string>& X, vector<FD>& F) {
	set<string> tX;
	ifstream In(name);
	if (!In) {
		cout << "???? ?? ??????!";
		exit(-1);
	}
	//?????? ????????
	char ch;
	string buff;
	getline(In, buff, '\n');
	for (int i = 0; i < buff.length(); i++) {
		if (buff[i] == ' ') {
			buff.erase(i, 1);
			i--;
		}
	}
	//???????? ? buff
	//????????? buff ?? ????????? ????????
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
		//????????? buff ?? ????????? ????????
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
			if (A == "0")
				A.clear();
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
		//????????? buff ?? ????????? ????????
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
			if (A == "0")
				A.clear();
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

void SX(const vector<string>& X, const vector<FD>& F, vector<string>& X_plus) {
	vector<string> OLD;
	vector<string> NEW = X;
	vector<string> Q;
	vector<string> A;
	vector<string> B;
	vector<string> C;
	while (NEW != OLD)
	{
		Q.clear();
		OLD = NEW;
		for (int i = 0; i < F.size(); i++)
		{
			A = NEW;
			B = F[i].left;
			C = F[i].right;
			sort(A.begin(), A.end());
			sort(B.begin(), B.end());
			sort(C.begin(), C.end());
			if (includes(A.begin(), A.end(), B.begin(), B.end()))//?????? ????????
			{
				Q.clear();
				set_union(A.begin(), A.end(), C.begin(), C.end(), back_inserter(Q));//??????????? ????????
				NEW = Q;
			}
		}
	}
	X_plus = NEW;
	X_plus.push_back("");
	set<string> XP(X_plus.begin(), X_plus.end());
	X_plus.clear();
	X_plus.assign(XP.begin(), XP.end());
}

bool PRF(const FD& X_struct, const vector<FD>& F)
{
	vector<string> X_plus;
	vector<string> X = X_struct.left;
	SX(X, F, X_plus);
	if (includes(X_plus.begin(), X_plus.end(), X_struct.right.begin(), X_struct.right.end()))//?????? ????????
		return true;
	else
		return false;
}

void NPOK(const vector<FD>& F, vector<FD>& G)
{
	G = F;
	vector<FD> G_minus;
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
