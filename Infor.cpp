#include "Infor.h"
#include<bits/stdc++.h>

using namespace std;
Infor::Infor()
{
}

Infor::Infor(int SoMonHoc, int SoLop){
	monHoc = new MonHoc[SoMonHoc];
	lop = new Lop[SoLop];
	for(int i=0;i<SoLop;i++) lop[i].soSv=0;
	_PmonHoc = 0;
	_Plop = 0;
	_SoMonHoc = SoMonHoc;
	_SoLop = SoLop;
}

Infor::~Infor()
{
	delete[] monHoc;
	delete[]lop;
}

int Infor::TestLop(int malop){
	for (int i = 0; i < _Plop; i++) {
		if (malop == lop[i].maLop) return i;
	}

	return -1;
}

int Infor::TestLop(string tenlop) {
	for (int i = 0; i < _Plop; i++) {
		if (tenlop == lop[i].tenLop) return i;
	}

	return -1;
}

int Infor::AddSv(SinhVien *sv,Lop *_lop){
	int flag;//vitri lop trong mang
	flag=TestLop(_lop->maLop);
	if(flag!=-1){//lop da co
		bool test=TestSV(lop[flag],sv.maSV);
		if(test){
			DSSV *temp=lop[flag].dssv;
			if(lop[flag].soSv==0){
				 DSSV *ds=new DSSV();
				ds->sv=sv;
				ds->next=NULL;
				temp=ds;
				 lop[flag].soSv++;
				 return 1;
			}
			else{
			while(temp->sv->maSV!=sv->maSV&&temp->next!=NULL) temp=temp->next;
				if(temp->sv->maSV!=sv.mssv){
					DSSV *ds=new DSSV();
					ds->sv=sv;
					ds->next=NULL;
					temp->next=ds;
					lop[flag].soSv++;
					return 1;
				}
				else{
					return -1;
				}
			}
		}
	}
	else{
		lop[_Plop]->dssv=new DSSV();
		lop[_Plop]->maLop=_lop->maLop;
		lop[_Plop]->tenLop=_lop->tenLop;
		
		DSSV *temp=lop[_Plop]->dssv;
		DSSV *ds=new DSSV();
		ds->sv=sv;
		ds->next=NULL;
		temp=ds;
		lop[_Plop].soSv++;
		
		_Plop++;
		return 1;
	}
}
bool Infor::TestSV(Lop lop,int mssv) {
	DSSV *temp = lop.dssv;
	while (temp != NULL) {
		if (temp->sv->maSV == mssv) return false;
	}
	return true;
}
SinhVien *SinhVien::Init() {
	SinhVien *temp = new SinhVien();
	string t;
	cout << "Nhap Ma Sinh Vien:  ";
	cin >> temp->maSV;
	cin.ignore(1);
	cout << "Nhap Ho: ";
	getline(cin, t);
	temp->Ho = t;
	cout << "Nhap Ten: ";
	getline(cin, t);
	temp->Ten = t;

	return temp;
}
