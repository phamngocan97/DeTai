#include<bits/stdc++.h>
#include "Infor.h"

using namespace std;
Infor::Infor()
{
}

Infor::Infor(int SoMonHoc, int SoLop) {
	monHoc = new MonHoc[SoMonHoc];
	lop = new Lop*[SoLop];
	for (int i = 0; i < SoLop; i++) {
		lop[i] = new Lop();
		lop[i]->soSv = 0;
	}
	lopTemp=new Lop();
	sv = new SinhVien();
	_PmonHoc = 0;
	_Plop = 0;
	_SoMonHoc = SoMonHoc;
	_SoLop = SoLop;
}

int Infor::TestLop(string malop) {
	for (int i = 0; i < _Plop; i++) {
		if (malop == lop[i]->maLop) return i;
	}

	return -1;
}


int Infor::AddSv(SinhVien *sv, Lop *_lop) {
	int flag;//vitri lop trong mang
	flag = TestLop(_lop->maLop);
	if (flag != -1) {//lop da co
		bool test = TestSV(this->lop[flag], sv->maSV);
		if (test) {//chua co sv nay
			DSSV *temp = this->lop[flag]->dssv;
			while (temp->sv->maSV != sv->maSV && temp->next != NULL) temp = temp->next;
			if (temp->sv->maSV != sv->maSV) {
				SinhVien *svTemp = new SinhVien(sv);
				temp->next = new DSSV();
				temp->next->sv = svTemp;
				temp->next->next = NULL;
				this->lop[flag]->soSv++;
				return 1;
			}			
		}
		else {
				return -1;
			}
	}
	else {
		lop[_Plop]->dssv = new DSSV();
		lop[_Plop]->maLop = _lop->maLop;
		lop[_Plop]->tenLop = _lop->tenLop;

		DSSV *temp = lop[_Plop]->dssv;
		SinhVien *svT = new SinhVien(sv);
		temp->sv = svT;
		temp->next = NULL;
		lop[_Plop]->soSv++;

		_Plop++;
		return 1;
	}
}
bool Infor::TestSV(Lop *lop, string mssv) {
	DSSV *temp = lop->dssv;
	while (temp != NULL) {
		if (temp->sv->maSV == mssv) return false;
		temp = temp->next;
	}
	return true;
}


Infor::~Infor()
{
	delete[] monHoc;
	delete[]lop;
}
