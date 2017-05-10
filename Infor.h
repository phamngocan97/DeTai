#pragma once
#include<bits/stdc++.h>
using namespace std;

class MonHoc;
class DSDiemThi;
class SinhVien;
class DSSV;
class Lop;

class Infor
{
public:
	Infor();
	Infor(int, int);
	

	MonHoc **monHoc;
	Lop **lop;
	Lop *lopTemp;
	SinhVien *sv;
	
	int AddSv(SinhVien *sinhvien,Lop *lop);
	int AddMh(string ma,string ten);
	int TestLop(string malop);
	bool TestSV(Lop *lop, string mssv);
	int TestMH(string ma);
	int UpdateDiem(string malop,string masv,string mamh,float diem);
	int GetSoLop();
	int GetSoMon();
	int DeleteSV(string mssv);
	~Infor();
private:
	int _PmonHoc,_SoMonHoc;
	int _Plop,_SoLop;
};


class MonHoc {
public:
	string maMH;
	string tenMH;
};
class DSDiemThi {
public:
	MonHoc *mh;
	float diemThi;
	DSDiemThi *next;
};
class SinhVien {
public:
	SinhVien() {};
	SinhVien(SinhVien *sv) {
		this->maSV = sv->maSV;
		this->Ho = sv->Ho;
		this->Ten = sv->Ten;
		this->PassWord = sv->PassWord;
		this->Nam = sv->Nam;
	}
	SinhVien(string ma,string ho,string ten,string pass,bool nam){
		this->maSV=ma;
		this->Ho=ho;
		this->Ten=ten;
		this->PassWord=pass;
		this->Nam=nam;
	}
	string maSV;
	string Ho,Ten,PassWord;
	bool Nam;
	DSDiemThi **diem;
};
class DSSV {
public:
	SinhVien *sv;
	DSSV *next;
};
class Lop {
public:
	Lop(){};
	Lop(string ma,string ten){
		this->maLop=ma;
		this->tenLop=ten;
	}
	
	string maLop;
	int soSv;
	string tenLop;
	DSSV *dssv;
};
