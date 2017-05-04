#include<bits/stdc++.h>
#include "Infor.h"

using namespace std;
Infor::Infor()
{
}

Infor::Infor(int SoMonHoc, int SoLop) {
	monHoc = new MonHoc*[SoMonHoc];
	lop = new Lop*[SoLop];
	for (int i = 0; i < SoLop; i++) {
		lop[i] = new Lop();
		lop[i]->soSv = 0;
	}
	for(int i=0;i<SoMonHoc;i++){
		monHoc[i]=new MonHoc();
	}
	lopTemp=new Lop();
	sv = new SinhVien();
	_PmonHoc = 0;
	_Plop = 0;
	_SoMonHoc = SoMonHoc;
	_SoLop = SoLop;
}
int Infor::GetSoLop(){
	return this->_Plop;
};

int Infor::GetSoMon(){
		return this->_PmonHoc;
};
int Infor::TestLop(string malop) {
	for (int i = 0; i < _Plop; i++) {
		if (malop == lop[i]->maLop) return i;
	}

	return -1;
}


int Infor::AddSv(SinhVien *sinhvien, Lop *_lop) {
	if(sinhvien->maSV.size()==0||sinhvien->Ho.size()==0||sinhvien->Ten.size()==0||sinhvien->PassWord.size()==0){
			return -1;
	}
	if(_lop->maLop.size()==0||_lop->tenLop.size()==0){
		return -1;
	}
	int flag;//vitri lop trong mang
	flag = TestLop(_lop->maLop);
	if (flag != -1) {//lop da co
		bool test = TestSV(this->lop[flag], sinhvien->maSV);
		if (test) {//chua co sv nay
			DSSV *temp = this->lop[flag]->dssv;
			if(temp!=NULL)
				while (temp->sv->maSV != sinhvien->maSV && temp->next != NULL) temp = temp->next;
			if (temp->sv->maSV != sinhvien->maSV) {
				SinhVien *svTemp = new SinhVien(sinhvien);
				temp->next = new DSSV();
				temp->next->sv = svTemp;
				temp->next->next = NULL;
				temp=temp->next;
				
				temp->sv->diem=new DSDiemThi*[this->_SoMonHoc];
				for(int i=0;i<this->_SoMonHoc;i++){
					temp->sv->diem[i]=new DSDiemThi();
					temp->sv->diem[i]->diemThi=-1;
				}
				
				
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
		temp->sv->diem=new DSDiemThi*[this->_SoMonHoc];
		for(int i=0;i<this->_SoMonHoc;i++){
			temp->sv->diem[i]=new DSDiemThi();
			temp->sv->diem[i]->diemThi=-1;
		}
		
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


int Infor::UpdateDiem(string malop,string masv,string mamh,float diem){
	int indexLop=TestLop(malop);
	if(indexLop!=-1){
		DSSV *temp=this->lop[indexLop]->dssv;
		while(temp!=NULL && temp->sv->maSV!=masv) temp=temp->next;
		if(temp==NULL) return -1; // khong co sinh vien nay
		else{
			//DSDiemThi *dsdiem=temp->sv->diem;
			//while(dsdiem!=NULL && dsdiem->mh->maMH!=mamh) dsdiem=dsdiem->next;
			int k=-1;
			for(int i=0;i<_PmonHoc;i++) {
				if(monHoc[i]->maMH==mamh) {
					k=i;
					break;
				}
			}
			if(k==-1) return -1;//ko co mon hoc nay
			else{
				for(int i=0;i<_Plop;i++){
					DSSV *ds=lop[i]->dssv;
					while(ds!=NULL){
						if(ds->sv->maSV==masv){
							ds->sv->diem[k]->diemThi=diem;
						
							return 1;			
						}
						ds=ds->next;
					}
				}
				
			}
		}
	}
	else {
		return -1;//ko co lop nay
	}
	
}

int Infor::AddMh(string ma,string ten){
	for(int i=0;i<_PmonHoc;i++){
		if(monHoc[i]->maMH==ma) return -1;
	}
	monHoc[_PmonHoc]->maMH=ma;
	monHoc[_PmonHoc]->tenMH=ten;
	
	_PmonHoc++;
	return 1;
}
int Infor::TestMH(string ma){
	for(int i=0;i<_PmonHoc;i++){
		if(monHoc[i]->maMH==ma) return  i;
	}
	return -1;
}

int Infor::DeleteSV(string mssv){
	int indexLop=-1;
	for(int i=0;i<_Plop;i++){
		if(!TestSV(lop[i],mssv)){
			indexLop=i;
		}
	}
	if(indexLop==-1) return -1;
	
	DSSV *ds=lop[indexLop]->dssv;
	if(ds->sv->maSV==mssv){
		lop[indexLop]->dssv=lop[indexLop]->dssv->next;
		delete ds;
		lop[indexLop]->soSv--;
	}
	else{
		DSSV *prev,*del,*temp;
		temp=lop[indexLop]->dssv;
		while(1){
			if(temp->next->sv->maSV==mssv){
				prev=temp;
				temp=temp->next->next;
				break;
			}
			prev=temp;
			temp=temp->next;			
		}
		del=prev->next;
		prev->next=temp;
		delete del;
		lop[indexLop]->soSv--;
	}
	return 1;
}
Infor::~Infor()
{
	delete[] monHoc;
	delete[]lop;
}
