#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<conio.h>

using namespace std;


class DS {
public:
	DS() {}
	string s;
	DS *next;

};

const int MAX = 11;

fstream file;

void Ghi();
void Doc();
void PerformDoc();
void PerformGhi();
void PerformDoc2();
int main() {
	PerformGhi();
	//PerformDoc();
	PerformDoc2();
	//Ghi();
	//system("cls");
	//Doc();

	string temp,k;
	DS *ds=new DS();
	DS *t = ds;

	for (int i = 0; i < 3; i++) {
		
		temp.resize(100);
		_itoa(100 + i, (char*)temp.c_str(), 10);
		t->s = temp;
		if (i < 3 - 1) {
			t->next = new DS();
			t = t->next;
		}

	}
	t = ds;
	return 0;
}
void PerformGhi() {
	fstream ghi;
	file.open("DSSVt.inp", ios::in);
	ghi.open("DSSVbin.inp", ios::out | ios::binary);

	int n;
	string s;
	getline(file, s);
	n = atoi(s.c_str());
	//file >> n;
	
	char c[100];
	ghi.write((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++) {
		file.getline(c, 100);
		int size = strlen(c);
		ghi.write((char*)&size, sizeof(int));
		ghi.write(c, size + 1);
	}
	for (int i = 0; i < n; i++) {
		file.getline(c, 100);
		int size = strlen(c);
		ghi.write((char*)&size, sizeof(int));
		ghi.write(c, size + 1);
	}
	for (int i = 0; i < n; i++) {
		file.getline(c, 100);
		int size = strlen(c);
		ghi.write((char*)&size, sizeof(int));
		ghi.write(c, size + 1);
	}

	file.close();
	ghi.close();


}
void PerformDoc2() {
	fstream file;
	file.open("DSSVbin.inp", ios::in | ios::binary);
	int n;
	file.read((char*)&n, sizeof(int));
	string *malop = new string[n];
	string *ho = new string[n];
	string *ten = new string[n];
	char c[100];
	string ss;
	
	for (int i = 0; i<n; i++) {
		int size;
		malop[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		malop[i] = c;
		cout << malop[i] << endl;
	}
	for (int i = 0; i<n; i++) {
		int size;
		ho[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		ho[i] = c;
		cout << ho[i] << endl;
	}
	for (int i = 0; i<n; i++) {
		int size;
		ten[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		ten[i] = c;
		cout << ten[i] << endl;
	}
	file.close();
}
void PerformDoc() {
	fstream doc;
	doc.open("DSSVbin.inp", ios::in | ios::binary);
	int n;
	char c[100];
	string s;
	doc.read((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++) {
		int k;
		doc.read((char*)&k, sizeof(int));
		doc.read(c, k + 1);
		string ss(c);
		cout << ss << endl;
	}
	for (int i = 0; i < n; i++) {
		int k;
		doc.read((char*)&k, sizeof(int));
		doc.read(c, k + 1);
		string ss(c);
		cout << ss << endl;
	}
	for (int i = 0; i < n; i++) {
		int k;
		doc.read((char*)&k, sizeof(int));
		doc.read(c, k + 1);
		string ss(c);
		cout << ss << endl;
	}
	doc.close();
}
void Ghi() {
	file.open("Input.inp", ios::out | ios::binary);

	char ques[MAX][1000];
	char dapan[MAX][4][1000];
	int ans[MAX];

	for (int i = 0; i<MAX; i++) {
		_itoa(i, ques[i], 10);
		ans[i] = i % 4;
		cout << strlen(ques[i]) << endl;
		for (int j = 0; j<4; j++) {
			_itoa(j + 100, dapan[i][j], 10);
		}
	}

	int n = MAX;
	file.write((char*)&n, sizeof(int));

	for (int i = 0; i < n; i++) {
		int len = strlen(ques[i]);
		file.write((char*)&len, sizeof(int));
		file.write(ques[i], strlen(ques[i]) + 1);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			int len = strlen(dapan[i][j]);
			file.write((char*)&len, sizeof(int));
			file.write(dapan[i][j], strlen(dapan[i][j]) + 1);
		}
	}
	for (int i = 0; i < n; i++) {
		file.write((char*)&ans[i], sizeof(int));
	}

	file.close();
}
void Doc() {
	//	cout<<"sdfghj";

	file.open("Input.inp", ios::in | ios::binary);

	int n;
	char ques[MAX][1000];
	char dapan[MAX][4][1000];
	int ans[MAX];

	file.read((char*)(&n), sizeof(int));

	for (int i = 0; i < n; i++) {
		int k;
		file.read((char*)&k, sizeof(int));
		file.read(ques[i], k + 1);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			int k;
			file.read((char*)&k, sizeof(int));
			file.read(dapan[i][j], k + 1);
		}
	}
	for (int i = 0; i < n; i++) {
		file.read((char*)(&ans[i]), sizeof(int));
	}

	for (int i = 0; i < MAX; i++) {
		for (int k = 0; k<strlen(ques[i]); k++) {
			cout << ques[i][k];
		}
		cout << endl;
		for (int j = 0; j <4; j++) {
			cout << j + 1 << ".  ";
			for (int k = 0; k<strlen(dapan[i][j]); k++) {
				cout << dapan[i][j][k];
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	file.close();
}
