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
	~Infor();

	MonHoc *monHoc;
	Lop *lop;
	DSSV *dssv;
	DSDiemThi *dsdiem;
	SinhVien *sv;
	
	int AddSv(SinhVien *sv,Lop *lop);
	int TestLop(int malop);
	int TestLop(string tenlop);
	bool TestSV(Lop lop, int mssv);
private:
	int _PmonHoc,_SoMonHoc;
	int _Plop,_SoLop;

};


class MonHoc {
public:
	int maMH;
	string tenMH;
};
class DSDiemThi {
public:
	int maMH,diem;
	DSDiemThi *next;
};
class SinhVien {
public:
	int maSV;
	string Ho,Ten,PassWord;
	bool gioiTinh;
	DSDiemThi *diem;
};
class DSSV {
public:
	SinhVien *sv;
	DSSV *next;
};
class Lop {
public:
	int maLop,soSv;
	string tenLop;
	DSSV *dssv;
};
