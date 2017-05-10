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

bool Infor::TestSV(Lop *lop, string mssv) {
	DSSV *temp = lop->dssv;
	while (temp != NULL) {
		if (temp->sv->maSV == mssv) return false;
		temp = temp->next;
	}
	return true;
}
int Infor::AddSv(SinhVien *sinhvien, Lop *_lop) {
	if (sinhvien->maSV.size() == 0 || sinhvien->Ho.size() == 0 || sinhvien->Ten.size() == 0 || sinhvien->PassWord.size() == 0) {
		return -1;
	}
	if (_lop->maLop.size() == 0 || _lop->tenLop.size() == 0) {
		return -1;
	}
	for (int i = 0; i < _Plop; i++) {
		if (!TestSV(lop[i], sinhvien->maSV)) {
			cout << "daco";
			return -1;
		}
	}
	int flag;//vitri lop trong mang
	flag = TestLop(_lop->maLop);
	if (flag != -1 && lop[flag]->soSv != 0) {//lop da co		

		DSSV *temp = this->lop[flag]->dssv;
		DSSV *prev = NULL;

		if (temp != NULL) {
			while (temp->next != NULL) {
				if (temp->sv->Ten != sinhvien->Ten) {
					if (temp->sv->Ten < sinhvien->Ten) {
						prev = temp;
						temp = temp->next;
					}
					else break;
				}
				else {
					if (temp->sv->Ho < sinhvien->Ho) {
						prev = temp;
						temp = temp->next;
					}
					else break;
				}
			}
		}

		if (temp->sv->maSV != sinhvien->maSV) {
			SinhVien *svTemp = new SinhVien(sinhvien);

			if (prev == NULL) {
				bool truoc = true;
				if (this->lop[flag]->soSv == 1) {
					if (temp->sv->Ten != sinhvien->Ten) {
						if (temp->sv->Ten < sinhvien->Ten) truoc = false;
					}
					else {
						if (temp->sv->Ho < sinhvien->Ho) truoc = false;
					}
				}
				if (truoc) {
					DSSV *dstemp = new DSSV();
					dstemp->sv = svTemp;

					dstemp->next = temp;
					this->lop[flag]->dssv = dstemp;
					temp = this->lop[flag]->dssv;
				}
				else {
					temp->next = new DSSV();
					temp->next->sv = svTemp;
					temp->next->next = NULL;
					temp = temp->next;
				}
			}
			else {
				bool truoc = true;
				if (temp->next == NULL) {
					if (temp->sv->Ten != sinhvien->Ten) {
						if (temp->sv->Ten < sinhvien->Ten) truoc = false;
					}
					else {
						if (temp->sv->Ho < sinhvien->Ho) truoc = false;
					}
				}
				if (temp->next == NULL && !truoc) {
					temp->next = new DSSV();
					temp->next->sv = svTemp;
					temp->next->next = NULL;
					temp = temp->next;
				}
				else {
					DSSV *dstemp = new DSSV();
					dstemp->sv = svTemp;

					DSSV *currentnext = prev->next;
					dstemp->next = currentnext;
					prev->next = dstemp;
					temp = prev->next;
				}
				

			}
			temp->sv->diem = new DSDiemThi*[this->_SoMonHoc];
			for (int i = 0; i < this->_SoMonHoc; i++) {
				temp->sv->diem[i] = new DSDiemThi();
				temp->sv->diem[i]->diemThi = -1;
			}


			this->lop[flag]->soSv++;
			return 1;
		}
	}
	else {
		lop[_Plop]->dssv = new DSSV();
		if (flag = -1) {
			lop[_Plop]->maLop = _lop->maLop;
			lop[_Plop]->tenLop = _lop->tenLop;
		}

		DSSV *temp = lop[_Plop]->dssv;
		SinhVien *svT = new SinhVien(sv);
		temp->sv = svT;
		temp->next = NULL;
		temp->sv->diem = new DSDiemThi*[this->_SoMonHoc];
		for (int i = 0; i < this->_SoMonHoc; i++) {
			temp->sv->diem[i] = new DSDiemThi();
			temp->sv->diem[i]->diemThi = -1;
		}

		lop[_Plop]->soSv++;
		if (flag == -1) _Plop++;

		return 1;
	}
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
