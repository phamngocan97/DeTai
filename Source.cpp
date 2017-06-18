#include<bits/stdc++.h>
#include <cstdlib>
#include<Windows.h>
#include<ctime>
#include<iomanip>
#include<thread>

#include"winbgim.h"
#include"Infor.h"
#include"AVLtree.h"

using namespace std;

typedef long long ll;
class SinhVien;
class DSSV;
class DSDiemThi;
class QuesAndAns;
class AVL;
enum {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};
enum {
    XOASV = 1,
    THEMSV = 2,
    SUASV = 3,
};
enum {
    /*	int c;
    while (1) {
    c = _getch();
    if (!isprint(c)) {// control key have 2 bytes
    c = _getch();
    cout << c << endl;
    //cout << "Control\n";
    }
    else { char key has 1 byte
    cout << "NO\n";
    }
    }
    */
    ENTER = 13,
    BACKSPACE = 8,
    TAB = 9,
    LEFT = 75,
    RIGHT = 77,
    UP = 72,
    DOWN = 80,
};

class Login {
	public:
		Login() {}

		Login(int rong, int dai) {
			this->dai = dai;
			this->rong = rong;
		}
		int dai, rong;
		int left, right, top, bottom;
};

class DSMON {
	public:
		DSMON(int n) {
			numSentence = n;
			Ques=new QuesAndAns*[200];
			for(int i=0; i<200; i++) {
				Ques[i]=new QuesAndAns();
			}
		}
		int GetCountMon() {
			return numSentence;
		}
		void Add(QuesAndAns *temp) {
			strcpy(Ques[numSentence]->cauhoi, temp->cauhoi);
			for (int i = 0; i < 4; i++) {
				strcpy(Ques[numSentence]->traloi[i], temp->traloi[i]);
			}
			Ques[numSentence]->dapan = temp->dapan;
			Ques[numSentence]->id = temp->id;
			numSentence++;
		}
		QuesAndAns **Ques;
	private:
		int numSentence;
};
class CircleClick {
	public:
		int bk, x, y;
};

int linex[] = { -1,0,1,1,1,0,-1 - 1 };
int liney[] = { -1,-1,-1,0,1,1,1,0 };


void InitRec(Login &log, int tamX, int tamY);
void InitRec(Login &log, int tamX, int tamY, int mau);
void InitCircle(CircleClick click, int mau);
bool IsClickRec(Login log, int x, int y);
bool IsClickCircle(CircleClick click, int x, int y);
void Swap(char *s1, char *s2);
void BFS(int x, int y, int x1, int y1, int R);

void DocFile();
void GhiFile();

void InitSoCau(Login &soCau, Login clock, int cauDaLam, int realQues);
void DrawLogin(Login &login, Login &id, Login &pass,Login &cancel);
int DangNhap(Login login, Login id, Login pass, Login cancel);
int TestId(string id, string pass);
void InitQuestion(int realQues,DSMON *ds);
void DrawTracNghiem(QuesAndAns Infor, CircleClick *click, int type);
void Write(char *s, int x, int y, int dai,int mauKhung);
void WriteColorWord(int x,int y,string s,int mau,int);

void ThemSINHVIEN(string lop, string malop, int type, int toadoX);
void HieuUngNhap(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS, int type = -1);
void HieuUngNhap1(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS, int type = -1);
void HieuUngNhaps(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS);
void HieuUngNhaps2(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar,int maxPerLine, int maxS);
void InDSDiem(string malop, string maMH, int maxInPage, int X);
void InDSLop(string malop, int maxInPage, int X);
int DeleteSV(string malop, int maxInPage, int X);
int SuaSinhVien(string malop, int maxInPage, int X);
void WindowSuaSV(string malop,string tenlop, SinhVien *sv, int toadoX);
void WindowGV();
void WindowThongBao(string s);
bool WindowThongBaoYN(string s);
void WindowBeforeThi();
void WindowAfterThi(QuesAndAns *CauHoi,CircleClick **click, int *chon,int n);
void WindowThemCauHoi();
int WindowChonMon();
bool WindowNhapTenLop(string &s);

void InitThread();
void CountDown(int time);

void LoadDSSV();
void DocCauHoi();


string currentId;
int currentLop;
float currentDiem;
int TIME = -1, SOCAU = -1;
int MON_HIEN_TAI=0;
const int SOMON =2, MAUCHU = BLACK,MAUNEN = COLOR(238,241,126),BUTTON = 10 | 0,WORDBUTTON = BLACK;
bool OVERTIME = false,stopThread = false;
bool isBack=false;

DSMON **dsmon;
Infor *inf;
AVL **CayCB;
AVLtree *TREE;

int IdArr[SOMON][1000];
int topClock,leftClock;
int main() {

	initwindow( 1200, 680);

	//------------------------------------------------------------//

	dsmon=new DSMON*[SOMON];
	CayCB=new AVL*[SOMON];
	for(int i=0; i<SOMON; i++) {
		CayCB[i]=NULL;
	}
	inf = new Infor(SOMON, 5);
	DocCauHoi();
	LoadDSSV();


//	DocFile();

	Login login, id, pass, cancel;
	int typeSign;

	setcolor(MAUCHU);
	while (1) {
		setbkcolor(MAUNEN);
		cleardevice();
		DrawLogin(login, id, pass,cancel);
		typeSign = DangNhap(login, id, pass,cancel);


		if(typeSign == -2) {
			break;
		}
		if (typeSign == -1) {
			WindowGV();
		}
		if (typeSign >= 0) {
			TIME=SOCAU=-1;

			isBack=false;
			WindowBeforeThi();
			if(isBack) continue;
			InitQuestion(SOCAU,dsmon[MON_HIEN_TAI]);
			//	InitThread();
			inf->UpdateDiem(inf->lop[typeSign]->maLop, currentId, inf->monHoc[MON_HIEN_TAI]->maMH, currentDiem);
		}
	}


	GhiFile();
	return 0;
}

void InitThread() {
	thread tracNghiem(InitQuestion,SOCAU,dsmon[MON_HIEN_TAI]);;
	//thread demnguoc(CountDown,TIME);
	tracNghiem.detach();
	//demnguoc.detach();
	if(tracNghiem.joinable()) {
		//tracNghiem = thread(InitQuestion,SOCAU,dsmon[MON_HIEN_TAI]);
		//tracNghiem.join();
	}
	//if(demnguoc.joinable()) demnguoc.join();
}

void InTime(int &phut,int &giay,int x,int y) {
	char MIN[4],SEC[3];
	MIN[3]=SEC[2]='\0';
	int m,s;
	m=phut,s=giay;
	for(int i=2; i>=0; i--) {
		MIN[i]=m%10 + '0';
		m/=10;
	}
	for(int i=1; i>=0; i--) {
		SEC[i]=s%10 + '0';
		s/=10;
	}
	Sleep(100);
	char in[15];
	memset(in,0,sizeof in);
	strcat(in,MIN);
	strcat(in," : ");
	strcat(in,SEC);
	outtextxy(x,y,in);
	if(giay>0) giay--;
	else {
		giay=59;
		phut--;
	}
}

void CountDown(int time) {
	OVERTIME = true;

	char MIN[4],SEC[3];
	MIN[3]=SEC[2]='\0';
	int phut,giay;
	phut=time;
	giay=0;
	stopThread = false;
	do {
		if(stopThread) return;
		if(giay>0) giay--;
		else {
			giay=59;
			phut--;
		}
		int m,s;
		m=phut,s=giay;
		for(int i=2; i>=0; i--) {
			MIN[i]=m%10 + '0';
			m/=10;
		}
		for(int i=1; i>=0; i--) {
			SEC[i]=s%10 + '0';
			s/=10;
		}
		Sleep(100);
		char in[15];
		memset(in,0,sizeof in);
		strcat(in,MIN);
		strcat(in," : ");
		strcat(in,SEC);
		outtextxy(leftClock+10,topClock+5,in);

	} while(phut!=0 || giay!=0);

	OVERTIME = false;
}

void DrawLogin(Login &login, Login &id, Login &pass,Login &cancel) {
	int disRong, disIdPass;
	disRong = 30;
	disIdPass = 30;

	cancel.dai = 90;
	cancel.rong = 30;

	login = Login(150, 400);

	id = Login(login.rong / 2 - disRong, login.dai / 2);
	pass = Login(login.rong / 2 - disRong, login.dai / 2);

	//setfillstyle(5, WHITE);

	InitRec(login, getmaxx() / 2, getmaxy() / 2,COLOR(135,221,231));
	InitRec(id, getmaxx() / 2, getmaxy() / 2 - id.rong / 2 - disIdPass / 2,MAUNEN);
	InitRec(pass, getmaxx() / 2, getmaxy() / 2 + id.rong / 2 + disIdPass / 2,MAUNEN);
	InitRec(cancel, getmaxx() - cancel.dai / 2 - 50, getmaxy() - cancel.rong / 2 - 50,BUTTON);
//	outtextxy(cancel.left + 20, cancel.top + 5, "Cancel");


	//floodfill(id.bottom - 5, id.right - 5, WHITE);
	//floodfill(pass.bottom - 1, pass.right - 1, WHITE);



	settextstyle(4, HORIZ_DIR, 3);
	outtextxy(login.left + 90, login.top - 40, "Dang Nhap");

	setbkcolor(COLOR(135,221,231));
	settextstyle(3, HORIZ_DIR, 1);
	outtextxy(login.left + 10, id.top + 15, "Tai Khoan");
	outtextxy(login.left + 10, pass.top + 15, "Mat Khau");


	WriteColorWord(cancel.left+10,cancel.top+5,"Thoat",WORDBUTTON,BUTTON);


	//outtextxy(cancel.left+10,cancel.top+5,"Thoat");
}

int DangNhap(Login login, Login id, Login pass, Login cancel) {
	int maxId = 12, maxPass = 24;
	int typeSign;
	bool signIn = false, taikhoan = false, matkhau = false;
	string tk = "", mk = "";
	int vtriIdx, vtriIdy, vtriPassx, vtriPassy;
	int disId, disPass;
	int moux = 0, mouy = 0;
	disId = 15;
	disPass = 8;

	vtriIdx = id.left + 1;
	vtriIdy = id.top + 5;
	vtriPassx = pass.left + 1;
	vtriPassy = pass.top + 5;

	while (!signIn) {
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			moux = mousex(), mouy = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(!taikhoan && !matkhau) {
			if(kbhit()) getch();
		}
		if(IsClickRec(cancel,moux,mouy)) {
			return -2;
		} else if (taikhoan || IsClickRec(id, moux, mouy)) {
			taikhoan = true;
			matkhau = false;
			char c;
			bool flag = false;
			bool outId = false;
			int xx=-1, yy=-1;
			while (!kbhit()) {
				if (ismouseclick(WM_LBUTTONDOWN)) {

					xx = mousex(), yy = mousey();
					if (!IsClickRec(id, xx, yy)) {
						moux = xx;
						mouy = yy;
						taikhoan=false;
						outId = true;
						break;
					}
					clearmouseclick(WM_LBUTTONDOWN);
				}
				if (flag) outtextxy(vtriIdx, vtriIdy, "|");
				else outtextxy(vtriIdx, vtriIdy, " ");
				flag = !flag;
				delay(400);

			}
			outtextxy(vtriIdx, vtriIdy, " ");
			if (!outId) {
				c = getch();
				if (c == ENTER) {
					typeSign = TestId(tk, mk);
					if (typeSign != -2) {
						signIn = true;
						currentId = tk;
						break;
					} else {
						outtextxy(login.left + 20, login.bottom + 50, "Sai ID/PassWord");
					}
				} else if ((ll)tk.size() > 0 && c == BACKSPACE) {
					//tk.pop_back();
					tk.erase(tk.size() - 1);
					vtriIdx -= disId;
					outtextxy(vtriIdx, vtriIdy, "    ");
				} else {
					if (c == BACKSPACE || (ll)tk.size() >= maxId) continue;
					if (!isprint(c)) {
						c = getch();
						continue;
					}
					tk = tk + c;
					outtextxy(vtriIdx, vtriIdy, &tk[tk.size() - 1]);
					vtriIdx += disId;
				}
			}
		}
		if (matkhau || IsClickRec(pass, moux, mouy)) {
			taikhoan = false;
			matkhau = true;
			char c;
			bool flag = false;
			bool outPass = false;
			while (!kbhit()) {
				if (ismouseclick(WM_LBUTTONDOWN)) {
					int xx, yy;
					xx = mousex(), yy = mousey();
					if (!IsClickRec(pass, xx, yy)) {
						moux = xx;
						mouy = yy;
						matkhau=false;
						outPass = true;
						break;
					}
					clearmouseclick(WM_LBUTTONDOWN);
				}
				if (flag) outtextxy(vtriPassx, vtriPassy, "|");
				else outtextxy(vtriPassx, vtriPassy, " ");
				flag = !flag;
				delay(400);
			}

			outtextxy(vtriPassx, vtriPassy, " ");
			if (!outPass) {
				c = getch();
				if (c == ENTER) {
					typeSign = TestId(tk, mk);
					if (typeSign != -2) {
						signIn = true;
						currentId = tk;
						break;
					} else {
						outtextxy(login.left + 20, login.bottom + 50, "Sai ID/PassWord");
					}
				}

				else if ((ll)mk.size() > 0 && c == BACKSPACE) {
					//mk.pop_back();
					mk.erase(mk.size() - 1);
					vtriPassx -= disPass;
					outtextxy(vtriPassx, vtriPassy, "    ");
				} else {
					if (c == BACKSPACE || (ll)mk.size() >= maxPass) continue;

					if (!isprint(c)) {
						c = getch();
						continue;
					}

					outtextxy(vtriPassx, vtriPassy, "*");
					vtriPassx += disPass;
					mk += c;
				}
			}
		}

	}

	return typeSign;
}
bool IsClickRec(Login log, int x, int y) {
	if (x <= log.right&&x >= log.left) {
		if (y <= log.bottom&&y >= log.top) return true;
	}
	return false;
}

bool IsClickCircle(CircleClick click, int x, int y) {
	if (((x - click.x)*(x - click.x) + (y - click.y)*(y - click.y)) <= click.bk*click.bk) {
		return true;
	}
	return false;
}
void InitRec(Login &log, int tamX, int tamY) {

	log.left = tamX - log.dai / 2;
	log.right = tamX + log.dai / 2;
	log.top = tamY - log.rong / 2;
	log.bottom = tamY + log.rong / 2;
	rectangle(log.left, log.top, log.right, log.bottom);

}

void InitRec(Login &log, int tamX, int tamY, int mau) {
	log.left = tamX - log.dai / 2;
	log.right = tamX + log.dai / 2;
	log.top = tamY - log.rong / 2;
	log.bottom = tamY + log.rong / 2;

	int k = getcolor();
	setcolor(mau);
	rectangle(log.left, log.top, log.right, log.bottom);
	setfillstyle(12, mau);
	floodfill(tamX, tamY, mau);

	/*
	setfillstyle(12,mau);
	bar(log.left, log.top, log.right, log.bottom);
	*/

	setcolor(BLACK);
	setfillstyle(0, k);
	rectangle(log.left, log.top, log.right, log.bottom);
	setcolor(k);
}
void WriteColorWord(int x,int y,string s,int mauChu,int buttonColor) {
	setbkcolor(buttonColor);
	int k=getcolor();
	setcolor(mauChu);
	outtextxy(x,y,&s[0]);
	setcolor(k);
	setbkcolor(MAUNEN);
}
void InitCircle(CircleClick click, int mau) {
	int k = getcolor();

	if (mau == -1) {
		setcolor(MAUNEN);
		circle(click.x, click.y, click.bk);
		setfillstyle(12, MAUNEN);
		floodfill(click.x, click.y, MAUNEN);

		setcolor(BLACK);
		circle(click.x, click.y, click.bk);

	} else {
		setcolor(mau);
		circle(click.x, click.y, click.bk);
		setfillstyle(12, mau);
		floodfill(click.x, click.y, mau);
	}

	setcolor(k);
	setfillstyle(0, k);
}

int TestId(string id, string pass) {
	//cout<<id<<endl;
	//cout<<pass;
	if (id == "GV"&& pass == "GV") {
		return -1;
	} else {
		bool test = false;
		for (int i = 0; i < inf->GetSoLop(); i++) {
			//	cout<<inf->GetSoLop()<<" ";
			test = inf->TestSV(inf->lop[i], id);
			if (!test) {
				//	cout<<i;
				currentLop = i;
				return i;
			}

		}
	}
	return -2;
}

void InitSoCau(Login &soCau, Login clock, int cauDaLam, int realQues) {
	InitRec(soCau, getmaxx() - 30 - soCau.dai / 2, clock.bottom + soCau.rong / 2 + 10 + soCau.rong / 2);

	leftClock = clock.left;
	topClock = clock.top;

	char temp[1000], sumCau[1000];
	memset(temp, 0, sizeof temp);
	memset(sumCau, 0, sizeof sumCau);
	itoa(realQues, sumCau, 10);
	temp[0] = '/';
	strcat(temp, sumCau);
	outtextxy(soCau.right - soCau.dai / 2, soCau.top + soCau.rong / 2, &temp[0]);
	itoa(cauDaLam, temp, 10);
	outtextxy(soCau.left + 30, soCau.top + soCau.rong / 2, &temp[0]);
}
void DocCauHoi() {
	srand(time(0));
	fstream file;
	dsmon=new DSMON*[SOMON];

//	string tenFile[SOMON] = {"Ngon Ngu Lap Trinh C++.inp","Co So Du Lieu SQL.inp"};
	string tenFile[SOMON]= {"Ques.inp","SQLbin.txt"};
	string tenMon[SOMON]= {"Ngon ngu C++","Co so du lieu SQL"};
	string maMon[SOMON]= {"C++","SQL"};
	for(int i=0; i<SOMON; i++) {
		inf->AddMh(maMon[i],tenMon[i]);
		file.open((char*)tenFile[i].c_str(),ios::in|ios::binary);

		int n, k;
		file.read((char*)&n,sizeof(int));
		dsmon[i] = new DSMON(n);
		for(int j=0; j<n; j++) {
			file.read((char*)&k,sizeof(int));
			file.read(dsmon[i]->Ques[j]->cauhoi,k+1);

			for(int m=0; m<4; m++) {
				file.read((char*)&k,sizeof(int));
				file.read(dsmon[i]->Ques[j]->traloi[m],k+1);
				if(i==0) {
					//	cout<<dsmon[i]->Ques[j]->traloi[m]<<endl;
				}
			}
			file.read((char*)&k,sizeof(int));
			if(!(k<=4&&k>=1)) k=2;
			dsmon[i]->Ques[j]->dapan=k-1;

			QuesAndAns *temp=new QuesAndAns;
			strcpy(temp->cauhoi,dsmon[i]->Ques[j]->cauhoi);
			for(int m=0; m<4; m++) {
				strcpy(temp->traloi[m],dsmon[i]->Ques[j]->traloi[m]);
			}
			temp->dapan=dsmon[i]->Ques[j]->dapan;
			int k=rand()%1000;
			while(IdArr[i][k]!=0) {
				k=rand()%1000;
			}
			IdArr[i][k]++;
			temp->id=k;
			TREE->Insert(CayCB[i],temp);

		}
		file.close();
	}

}
void InitQuestion(int realQues, DSMON *dsm) {

	void *screen;
	int size = imagesize(0, 0, getmaxx(), getmaxy());
	screen = malloc(size);

	//inf->AddMh("ma", "ten");
	//fstream file;
	//file.open("Ques.inp", ios::in | ios::binary);

	int numQues = dsm->GetCountMon();
	//file.read((char*)&numQues, sizeof(int));

	if(realQues>numQues) {
		realQues=numQues;
	}


	CircleClick **click = new CircleClick*[numQues];
	QuesAndAns *CauHoi = new QuesAndAns[realQues];

	char **ques = new char*[numQues];
	for (int i = 0; i < numQues; i++) {
		ques[i] = new char[1000];
	}
	//string **ansSentence = new string*[numQues];
	char ***ansSentence = new char**[numQues];
	for (int i = 0; i < numQues; i++) {
		ansSentence[i] = new char*[4];
		for (int j = 0; j < 4; j++) {
			ansSentence[i][j] = new char[1000];
		}
	}

	for (int i = 0; i < numQues; i++) {
		click[i] = new CircleClick[4];
	}
	int *ans = new int[numQues];

	for (int i = 0; i < numQues; i++) {
		//	int k;
		//	file.read((char*)&k, sizeof(int));
		//	file.read(ques[i], k + 1);
		ques[i]=dsm->Ques[i]->cauhoi;
		for (int j = 0; j < 4; j++) {
			//file.read((char*)&k, sizeof(int));
			//file.read(ansSentence[i][j], k + 1);
			ansSentence[i][j]=dsm->Ques[i]->traloi[j];
		}

		//file.read((char*)&ans[i], sizeof(int));
		ans[i]=dsm->Ques[i]->dapan;
	}
	//file.read(reinterpret_cast<char*>(&s), sizeof(s));
	srand(time(0));
	for (int i = 1; i <= realQues; i++) {
		int k;
		if(i!=numQues) k = rand() % (numQues - i);
		else k=0;
		Swap(ques[k], ques[numQues - i]);
		//Swap(ansSentence[k], ansSentence[numQues - i]);
		for (int kk = 0; kk < 4; kk++) {
			Swap(ansSentence[k][kk], ansSentence[numQues - i][kk]);
		}
		swap(ans[k], ans[numQues - i]);

		//CauHoi[i - 1].cauhoi = ques[numQues - i];
		strcpy(CauHoi[i - 1].cauhoi, ques[numQues - i]);


		for (int kk = 0; kk < 4; kk++) {
			//CauHoi[i - 1].traloi[kk] = ansSentence[numQues - i][kk];
			strcpy(CauHoi[i - 1].traloi[kk], ansSentence[numQues - i][kk]);
		}

		CauHoi[i - 1].dapan = ans[numQues - i];
	}

	for (int i = 0; i < realQues; i++) {
		char c[100];
		itoa(i + 1, c, 10);
		strcat(c, "./  ");
		strcat(c, CauHoi[i].cauhoi);
		strcpy(CauHoi[i].cauhoi, c);
		/*
		for (int j = 0; j < 4; j++) {
			for (int k = strlen(CauHoi[i].traloi[j]) + 3; k >= 3; k--) {
				CauHoi[i].traloi[j][k] = CauHoi[i].traloi[j][k - 3];
			}
			CauHoi[i].traloi[j][0] = j + 'A';
			CauHoi[i].traloi[j][1] = '.';
			CauHoi[i].traloi[j][2] = ' ';

		}
		*/
	}

	Login next, previous, soCau, clock, ketThuc;
	next.dai = previous.dai = 90;
	next.rong = previous.rong = ketThuc.rong = 30;
	ketThuc.dai = 120;

	soCau.dai = 100;
	soCau.rong = 60;
	clock.dai = 100;
	clock.rong = 50;
	bool isClick;
	int *choose = new int[realQues];
	for (int i = 0; i < realQues; i++) {
		choose[i] = -1;
	}

	clearmouseclick(WM_LBUTTONDOWN);
	int i = 1, cauDaLam = 0;

	getimage(0, 0, getmaxx(), getmaxy(), screen);
	InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
	InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50);

	putimage(0, 0, screen, COPY_PUT);

	int phut=TIME,giay=0;
	float timeDelay=0;
	bool out=false;
	const float tDelay=0.02;
	while (1) {
		//	cout<<"K\n";
		//Sleep(0.00001);
		delay(0.00001);

		if (OVERTIME || out) {
			break;
		}
		isClick = false;
		cleardevice();
		//	cout<<"K1\n";

		InitRec(ketThuc, 40, getmaxy() - ketThuc.rong / 2 - 50,BUTTON);
		//outtextxy(ketThuc.left + 40, ketThuc.top + 5, "Ket Thuc");
		WriteColorWord(ketThuc.left + 40, ketThuc.top + 5, "Ket Thuc",WORDBUTTON,BUTTON);
		InitRec(clock, getmaxx() - 30 - clock.dai / 2, 30 + clock.rong / 2);
		InitSoCau(soCau, clock, cauDaLam, realQues);


		/////-------------------TIME--------------------
		timeDelay+=tDelay;
		if((int)timeDelay==(int)1) {

			timeDelay=0;
			InTime(phut,giay,clock.left+5,clock.top+5);
			if(giay==0 && phut==0) {
				OVERTIME=true;
				break;
			}
		}
		////-----------TIME-----------------------------

		DrawTracNghiem(CauHoi[i - 1], click[i - 1], choose[i - 1]);
		//	cout<<"K2\n";
		if (i < realQues) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50,BUTTON);
			//outtextxy(next.left + 20, next.top + 5, "NEXT");
			WriteColorWord(next.left + 20, next.top + 5, "NEXT",WORDBUTTON,BUTTON);
		}
		if (i > 1) {
			InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50,BUTTON);
			//outtextxy(previous.left + 20, previous.top + 5, "PREV");
			WriteColorWord(previous.left + 20, previous.top + 5, "PREV",WORDBUTTON,BUTTON);
		}

		while (1) {
			//		cout<<"K3\n";
//			Sleep(0.00001);
			//		cout<<"x\n";
			delay(0.00001);

			/////-------------------TIME--------------------
//			system("cls");
//			cout<<timeDelay<<" ____________";
			timeDelay+=tDelay;
			if((int)timeDelay==(int)1) {
				timeDelay=0;
				InTime(phut,giay,clock.left+5,clock.top+5);
				if(giay==0 && phut==0) {
					OVERTIME=true;
					break;
				}
			}
			////-----------TIME-----------------------------


			//		cout<<"xx\n";
			if (OVERTIME || out) {
				break;
			}
			//		cout<<"K4\n";
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (i < realQues&&IsClickRec(next, moux, mouy)) {
					//				cout<<"next\n";
					//isClick = true;
					i++;
					break;
				} else if (i > 1 && IsClickRec(previous, moux, mouy)) {
					//	isClick = true;
					i--;
					break;
				} else if (IsClickRec(ketThuc, moux, mouy)) {
					getimage(0, 0, getmaxx(), getmaxy(), screen);
					Login Big, yes, no;
					Big = Login(70, 230);
					yes = Login(30, 50);
					no = Login(30, 50);


					InitRec(Big, ketThuc.right + Big.dai / 2 + 30, getmaxy() - 30 - Big.rong / 2,RED);
					InitRec(yes, Big.left + 130, Big.top + 50,BUTTON);
					InitRec(no, yes.right + 20 + no.dai / 2, Big.top + 50,BUTTON);
					//outtextxy(Big.left + 20, Big.top + 5, "Ban co muon ket thuc?");
					//outtextxy(yes.left + 10, yes.top + 5, "Yes");
					//outtextxy(no.left + 10, no.top + 5, "No");
					WriteColorWord(Big.left + 20, Big.top + 5, "Ban co muon ket thuc?",WHITE,RED);
					WriteColorWord(yes.left + 10, yes.top + 5, "Yes",WORDBUTTON,BUTTON);
					WriteColorWord(no.left + 10, no.top + 5, "No",WORDBUTTON,BUTTON);
					bool clickNo = false;
					int  _moux = -1, _mouy = -1;
					while (1) {
						//Sleep(0.00001);
						delay(0.00001);

						/////-------------------TIME--------------------
						timeDelay+=tDelay;
						if((int)timeDelay==(int)1) {
							timeDelay=0;
							InTime(phut,giay,clock.left+5,clock.top+5);
							if(giay==0 && phut==0) {
								OVERTIME=true;
								break;
							}
						}
						////-----------TIME-----------------------------


						if (ismouseclick(WM_LBUTTONDOWN)) {
							_moux = mousex();
							_mouy = mousey();
							clearmouseclick(WM_LBUTTONDOWN);
						}
						if (IsClickRec(yes, _moux, _mouy)) {
							out = TRUE;
							stopThread = true;
//							cout<<"end\n";
							break;
						} else if (IsClickRec(no, _moux, _mouy)) {
							clickNo = true;
							break;
						}

					}
					if (clickNo) putimage(0, 0, screen, COPY_PUT);
				}
				bool chon = false;
				for (int j = 0; j < 4; j++) {
					if (IsClickCircle(click[i - 1][j], moux, mouy)) {
						chon = true;
						break;
					}
				}

				for (int j = 0; chon && j < 4; j++) {
					if (IsClickCircle(click[i - 1][j], moux, mouy)) {
						if (choose[i - 1] == -1) {
							cauDaLam++;
							//InitSoCau(soCau,clock,cauDaLam,realQues);
						}
						InitCircle(click[i - 1][j], BLACK);
						choose[i - 1] = j;

					} else {
						InitCircle(click[i - 1][j], -1);
						//choose[i] = 0;
					}
				}

			}
		}
		clearmouseclick(WM_LBUTTONDOWN);
	}

	int socaudung = 0;
	for (int i = 0; i < realQues; i++) {
		if (choose[i] == CauHoi[i].dapan) socaudung++;
	}
	if(socaudung==realQues) currentDiem=10.0;
	else currentDiem = (socaudung * 10) / ((float)realQues);
	char thongBao[100],cauDung[10],tongCau[10],cDiem[10];
	memset(thongBao,0,sizeof thongBao);
	memset(cauDung,0,sizeof cauDung);
	memset(tongCau,0,sizeof tongCau);
	memset(cDiem,0,sizeof cDiem);

	strcat(thongBao,"So cau: ");

	itoa(socaudung,cauDung,10);
	strcat(cauDung,"/");
	itoa(realQues,tongCau,10);
	strcat(cauDung,tongCau);

	strcat(thongBao,cauDung);
	strcat(thongBao,"   Diem: ");

//	cout<"update\n";

	memset(cDiem, 0, sizeof cDiem);
	if(currentDiem==10.0) {
		cDiem[0]='1';
		cDiem[1]='0';
		cDiem[2]='\0';
	} else {
		int temp=currentDiem*100;
		for(int i=3; i>=0; i--) {
			if(i==1) {
				cDiem[i]='.';
				continue;
			} else {
				cDiem[i]=temp%10+'0';
				temp/=10;
			}
		}
		cDiem[4]='\0';
	}
	strcat(thongBao,cDiem);
	string ss(thongBao);
	WindowThongBao(ss);
	WindowAfterThi(CauHoi, click, choose, realQues);
	//file.close();
}

void DrawTracNghiem(QuesAndAns CauHoi, CircleClick *click, int type) {
	const int disToTop = 20; //khoang cach tu dong dau tien

	Login cauhoi, traloi[4];
	//CircleClick click[4];
	const int tamX = getmaxx() / 2;
	const int cDai = getmaxx() / 2 - 100;
	int crongQues = (int)(strlen(CauHoi.cauhoi)) / ((cDai-10)/12);
	crongQues+=1;
	crongQues *= 30;
	int tamY = disToTop + crongQues / 2;
	cauhoi.dai = cDai;
	cauhoi.rong = crongQues;
	cauhoi.dai +=20;

	InitRec(cauhoi, tamX, tamY,WHITE);
	Write(CauHoi.cauhoi, cauhoi.left + 5, cauhoi.top + 5, 55,WHITE);
	for (int i = 1; i <= 4; i++) {
		traloi[i - 1].dai = cDai;
		traloi[i - 1].rong = (int)(strlen(CauHoi.traloi[i - 1])) / ((cDai-10)/12);
		traloi[i-1].rong+=1;
		traloi[i-1].rong*=30;
		traloi[i-1].dai+=20;
		if (i == 1) {
			tamY = cauhoi.bottom + 30 + traloi[i - 1].rong / 2;
		} else {
			tamY = traloi[i - 2].bottom + 30 + traloi[i - 1].rong / 2;
		}
		InitRec(traloi[i - 1], tamX, tamY,WHITE);

		Write(CauHoi.traloi[i - 1], traloi[i - 1].left + 5, traloi[i - 1].top + 5,55,WHITE);
		click[i - 1].bk = 10;
		click[i - 1].y = tamY;
		click[i - 1].x = cauhoi.left - 30;

		//circle(click[i - 1].x, click[i - 1].y, click[i - 1].bk);

	}
	for (int i = 0; i < 4; i++) {
		if (type != i) {
			InitCircle(click[i], -1);
		} else {
			InitCircle(click[i], BLACK);
		}
	}

}

void Write(char *s, int x, int y, int dai,int mauKhung) {
	string ss;
	int vtriX, vtriY;
	vtriX = x;
	vtriY = y;
//	outtextxy(x, y, &s[0]);
//	return;
	/*
	for (int i = 0; i < strlen(s); i++) {
	//if (s[i] == '\0') return;
	if (vtriX + 5 >= dai*12 + x) {
		vtriX = x;
		vtriY += 30;
	}
	ss.push_back(s[i]);
	outtextxy(vtriX, vtriY, &ss[ss.size() - 1]);
	vtriX += 12;
	}
	*/
//		/*
	int maxInLine = dai;//55
	int line = strlen(s)/maxInLine;
	if(strlen(s)%maxInLine!=0) line++;

	for(int i=0; i<line; i++) {
		string s1;
		s1.resize(100);
		if(strlen(s)%maxInLine!=0 && i==line-1) {
			strncpy((char*)s1.c_str(),&s[i*maxInLine],strlen(s)%maxInLine);
		} else strncpy((char*)s1.c_str(),&s[i*maxInLine],maxInLine);
		cout<<s1<<endl;

		outtextxy(vtriX,vtriY,&s1[0]);
		WriteColorWord(vtriX,vtriY,&s1[0],MAUCHU,mauKhung);
		vtriY+=30;
	}
//	*/
}

void BFS(int x, int y, int x1, int y1, int R) {
	int *prevy = new int[getmaxy() + 1];
	int *prevx = new int[getmaxx() + 1];

	queue<int> qx;
	queue<int> qy;
	qx.push(x);
	qy.push(y);

	bool out = false;

	int ssize = 1, dem = 1;
	while (!qx.empty() && !out) {

		if (ssize == 0) {
			dem++;
			ssize = qx.size();
		}

		x = qx.front(), qx.pop();
		y = qy.front(), qy.pop();
		ssize--;

		for (int i = 0; i < 8; i++) {
			if ((x + linex[i] >= 0 && x + linex[i] <= getmaxx()) && (y + liney[i] >= 0 && y + liney[i] <= getmaxy())) {
				prevx[x + linex[i]] = x;
				prevy[y + liney[i]] = y;
				if (x + linex[i] == x1 && y + liney[i] == y1) {
					out = true;
					break;
				}
				qx.push(x + linex[i]);
				qy.push(y + liney[i]);
			}
		}
	}

	//Move
	stack<int> stx;
	stack<int> sty;


	int xt, yt;
	xt = x1, yt = y1;
	for (int i = 1; i <= dem; i++) {
		stx.push(xt);
		sty.push(yt);
		xt = prevx[xt];
		yt = prevy[yt];
	}
	for (int i = 1; i <= dem; i++) {
		//cleardevice();
		circle(stx.top(), sty.top(), R);
		stx.pop();
		sty.pop();
		Sleep(2000);
	}
}

void Swap(char *s1, char *s2) {
	char t[1000];
	strcpy(t, s1);
	strcpy(s1, s2);
	strcpy(s2, t);
}

void HieuUngNhap1(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS, int type) {
	char c;
	bool flag = false, out = false;
	while (!kbhit()) {

		if (ismouseclick(WM_LBUTTONDOWN)) {
			int xx, yy;
			xx = mousex(), yy = mousey();
			if (!IsClickRec(log, xx, yy)) {
				out = true;
				moux = mousex(), mouy = mousey();
				outtextxy(indexX, indexY, " ");
				clearmouseclick(WM_LBUTTONDOWN);
				return;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		if (flag) outtextxy(indexX, indexY, "|");
		else outtextxy(indexX, indexY, " ");

		flag = !flag;
		delay(400);
	}

	outtextxy(indexX, indexY, " ");
	if (out) return;

	c = getch();
	if ((ll)s.size() > 0 && c == BACKSPACE) {
		//mk.pop_back();
		s.erase(s.size() - 1);
		indexX -= disChar;
		outtextxy(indexX, indexY, "      ");
	} else {
		if (c == BACKSPACE || (ll)s.size() >= maxS) return;
		if (c == ENTER) return;
		if (!isprint(c)) {
			c = getch();
			return;
		}
		if(type!=3 && c== ' ') return;
		if (type == 1 && !(c <= '9'&&c >= '0')) return;
		if (type == 0 && !((c <= 'Z'&&c >= 'A') || (c <= 'z'&&c >= 'A'))) return;
		if(type==3) {
			if(c!=' ' && !((c <= 'Z'&&c >= 'A') || (c <= 'z'&&c >= 'A')))
				return;
		}

		s.push_back(c);
		outtextxy(indexX, indexY, &s[s.size() - 1]);
		indexX += disChar;
	}

}
void HieuUngNhap(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS, int type) {
	char c;
	bool flag = false, out = false;

	s.push_back(' ');
	s.push_back('|');
	while (!kbhit()) {

		if (ismouseclick(WM_LBUTTONDOWN)) {
			int xx, yy;
			xx = mousex(), yy = mousey();
			if (!IsClickRec(log, xx, yy)) {
				out = true;
				moux = mousex(), mouy = mousey();

				if(!flag) {
					s.erase(s.size() - 1);
					s.push_back(' ');
					outtextxy(indexX, indexY, &s[0]);
					s.erase(s.size() - 1);
					s.erase(s.size() - 1);
				}

				//outtextxy(indexX, indexY, " ");
				clearmouseclick(WM_LBUTTONDOWN);
				return;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		if (flag) {
			s.push_back(' ');
			s.push_back('|');
			outtextxy(indexX, indexY, &s[0]);
		} else {
			s.erase(s.size() - 1);
			s.push_back(' ');
			outtextxy(indexX, indexY, &s[0]);
			s.erase(s.size() - 1);
			s.erase(s.size() - 1);

		}

		flag = !flag;
		delay(400);
	}

	//outtextxy(indexX, indexY, " ");
	if(!flag) {
		s.erase(s.size() - 1);
		s.push_back(' ');
		outtextxy(indexX, indexY, &s[0]);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);
	}
	//outtextxy(indexX, indexY, &s[0]);
	if (out) return;

	c = getch();
	if ((ll)s.size() > 0 && c == BACKSPACE) {
		//mk.pop_back();

		s.erase(s.size() - 1);
		s.push_back(' ');
		s.push_back(' ');
		s.push_back(' ');
		s.push_back(' ');

		//indexX -= disChar;
		outtextxy(indexX, indexY, &s[0]);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);

		outtextxy(indexX, indexY, &s[0]);
	} else {
		if (c == BACKSPACE || (ll)s.size() >= maxS) return;
		if (c == ENTER) return;
		if (!isprint(c)) {
			c = getch();
			return;
		}
		if(type!=3 && c== ' ') return;
		if (type == 1 && !(c <= '9'&&c >= '0')) return;
		if (type == 0 && !((c <= 'Z'&&c >= 'A') || (c <= 'z'&&c >= 'A'))) return;
		if(type==3) {
			if(c!=' ' && !((c <= 'Z'&&c >= 'A') || (c <= 'z'&&c >= 'A')))
				return;
		}

		s.push_back(c);
		outtextxy(indexX, indexY, &s[0]);
		//indexX += disChar;
	}

}
void HieuUngNhaps(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS) {

	char c;
	bool flag = false, out = false;
	while (!kbhit()) {
//		if(indexY>=log.bottom-10) break;
		if (ismouseclick(WM_LBUTTONDOWN)) {
			int xx, yy;
			xx = mousex(), yy = mousey();
			if (!IsClickRec(log, xx, yy)) {
				out = true;
				moux = mousex(), mouy = mousey();
				outtextxy(indexX, indexY, " ");
				return;
			}
			clearmouseclick(WM_LBUTTONDOWN);

		}

		if (flag) outtextxy(indexX, indexY, "|");
		else outtextxy(indexX, indexY, " ");

		flag = !flag;
		delay(400);
	}

	outtextxy(indexX, indexY, " ");

	if (out) return;
	c=getch();
	if ( ((ll)s.size() > 0 && c == BACKSPACE)) {
		//mk.pop_back();
		s.erase(s.size() - 1);
		if(indexX==log.left+10) {
			indexY-=30;
			indexX=log.right-disChar -5;
		} else indexX -= disChar;
		outtextxy(indexX, indexY, "         ");
	} else {
		if (c == BACKSPACE || (ll)s.size() >= maxS) return;
		if (c == ENTER) return;
		if (!isprint(c)) {
			c = getch();
			return;
		}
		s.push_back(c);
		outtextxy(indexX, indexY, &s[s.size() - 1]);
		indexX += disChar;
		if(indexX + disChar + 5 >=log.right) {
			indexX=log.left+10;
			indexY+=30;
		}
	}


}
void HieuUngNhaps2(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar,int maxPerLine, int maxS) {

	char c;
	bool flag = false, out = false;
	s.push_back(' ');
	s.push_back('|');
	while (!kbhit()) {
//		if(indexY>=log.bottom-10) break;
		if (ismouseclick(WM_LBUTTONDOWN)) {
			int xx, yy;
			xx = mousex(), yy = mousey();
			if (!IsClickRec(log, xx, yy)) {
				out = true;
				moux = mousex(), mouy = mousey();
				//outtextxy(indexX, indexY, " ");
				if(!flag) {
					s.erase(s.size() - 1);
					s.push_back(' ');
						Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);
					s.erase(s.size() - 1);
					s.erase(s.size() - 1);
				}

				return;
			}
			clearmouseclick(WM_LBUTTONDOWN);

		}

		if (flag) {
			s.push_back(' ');
			s.push_back('|');
			Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);
		} else {
			s.erase(s.size() - 1);
			s.push_back(' ');
			Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);
			s.erase(s.size() - 1);
			s.erase(s.size() - 1);

		}

		flag = !flag;
		delay(400);
	}
	if(!flag) {
		s.erase(s.size() - 1);
		s.push_back(' ');
		Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);
	}
	//outtextxy(indexX, indexY, " ");

	if (out) return;
	c=getch();
	if ( ((ll)s.size() > 0 && c == BACKSPACE)) {
		//mk.pop_back();
				s.erase(s.size() - 1);
		s.push_back(' ');
		s.push_back(' ');
		s.push_back(' ');
		s.push_back(' ');

		//indexX -= disChar;
		Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);
		s.erase(s.size() - 1);

		Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);

	} else {
		if (c == BACKSPACE || (ll)s.size() >= maxS) return;
		if (c == ENTER) return;
		if (!isprint(c)) {
			c = getch();
			return;
		}
		s.push_back(c);
		Write((char*)s.c_str(),indexX,indexY,maxPerLine,MAUNEN);
		//indexX += disChar;
	}


}

void ThemSINHVIEN(string tenlop, string malop, int type, int toadoX) {

	void *arrow;
	unsigned int size;

	size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
	arrow = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), arrow);
	cleardevice();
	//putimage(0,0,arrow,COPY_PUT);

	bool Trai = true;
	string Sma, Sho, Sten, Spassword;
	Login ma, ho, ten, password, apply, cancel;
	CircleClick nam, nu;

	ma.rong = ho.rong = ten.rong = password.rong = 40;
	ma.dai = 300;
	ho.dai = 130;
	ten.dai = 300;
	password.dai = 300;

	apply.dai = cancel.dai = 90;
	apply.rong = cancel.rong = 30;

	int tamX = toadoX + 80;

	InitRec(ma, tamX, ma.rong / 2 + 30);
	InitRec(ho, ma.left + ho.dai / 2, ma.bottom + 50);
	InitRec(ten, tamX, ho.bottom + 50);
	InitRec(password, tamX, ten.bottom + 50);

	outtextxy(ma.left - 130, ma.top + 5, "Ma Sinh Vien");
	outtextxy(ho.left - 130, ho.top + 5, "Ho");
	outtextxy(ten.left - 130, ten.top + 5, "Ten");
	outtextxy(password.left - 130, password.top + 5, "PassWord");

	InitRec(cancel, getmaxx() - cancel.dai / 2 - 50, getmaxy() - cancel.rong / 2 - 50,BUTTON);
	//outtextxy(cancel.left + 20, cancel.top + 5, "Cancel");
	WriteColorWord(cancel.left + 20, cancel.top + 5, "Cancel",WORDBUTTON,BUTTON);

	InitRec(apply, cancel.left - 50 - apply.rong / 2, getmaxy() - apply.rong / 2 - 50,BUTTON);
	//outtextxy(apply.left + 20, apply.top + 5, "Apply");
	WriteColorWord(apply.left + 20, apply.top + 5, "Apply",WORDBUTTON,BUTTON);

	nam.bk = nu.bk = 10;
	nam.y = nu.y = password.bottom + 30;
	nam.x = password.left + 40;
	nu.x = nam.x + nam.bk + 70;

	outtextxy(nam.x - nam.bk - 40, nam.y - 15, "Nam");
	outtextxy(nu.x - nu.bk - 30, nu.y - 15, "Nu");

	InitCircle(nam, BLACK);
	InitCircle(nu, -1);


	int moux = -1, mouy = -1;
	int indexXMa, indexXHo, indexXTen, indexXPass;
	int indexYMa, indexYHo, indexYTen, indexYPass;
	indexXHo = ho.left + 5;
	indexXMa = ma.left + 5;
	indexXTen = ten.left + 5;
	indexXPass = password.left + 5;

	indexYHo = ho.top + 10;
	indexYMa = ma.top + 10;
	indexYTen = ten.top + 10;
	indexYPass = password.top + 10;

	char c;
	if (type == THEMSV)
		while (1) {
			delay(0.00001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				outtextxy(password.left + 20, password.bottom + 60, "                               ");
				moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
			}
			if (IsClickRec(ma, moux, mouy)) {
				HieuUngNhap(ma, Sma, indexXMa, indexYMa, moux, mouy, 15, 15);
			} else if (IsClickRec(ho, moux, mouy)) {
				HieuUngNhap(ho, Sho, indexXHo, indexYHo, moux, mouy, 15, 6, 0);
			} else if (IsClickRec(ten, moux, mouy)) {
				HieuUngNhap(ten, Sten, indexXTen, indexYTen, moux, mouy, 15, 15, 3);
			} else if (IsClickRec(password, moux, mouy)) {
				HieuUngNhap(password, Spassword, indexXPass, indexYPass, moux, mouy, 15, 15);
			} else if (IsClickCircle(nam, moux, mouy) || IsClickCircle(nu, moux, mouy)) {
				if (IsClickCircle(nam, moux, mouy)) {
					InitCircle(nam, BLACK);
					InitCircle(nu, -1);
					Trai = true;
				} else if (IsClickCircle(nu, moux, mouy)) {
					InitCircle(nu, BLACK);
					InitCircle(nam, -1);
					Trai = false;
				}
				moux = -1, mouy = -1;
			} else if (IsClickRec(apply, moux, mouy)) {
				*inf->sv = SinhVien(Sma, Sho, Sten, Spassword, Trai);
				*inf->lopTemp = Lop(malop, tenlop);
				int isAdd = inf->AddSv(inf->sv, inf->lopTemp);

				outtextxy(password.left + 20, password.bottom + 60, "                                            ");
				if (isAdd == 1) {
					//outtextxy(password.left + 20, password.bottom + 60, "Them thanh cong");
					WindowThongBao("Them thanh cong");
				} else {
					//outtextxy(password.left + 20, password.bottom + 60, "Them that bai");
					WindowThongBao("Them that bai");
				}
				moux = -1;
				mouy = -1;
			} else if (IsClickRec(cancel, moux, mouy)) {

				putimage(0, 0, arrow, COPY_PUT);
				return;
			}
			if(kbhit()) getch();
			//cc
		}

}
void InDSDiem(string malop, string maMH, int maxInPage, int X) {
	void *arrow;
	unsigned int size;
	size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
	arrow = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), arrow);
	cleardevice();

	/////-----------------------------------------------------------------------/
	//////////////////////
	int indexLop = inf->TestLop(malop);
	int sosv = inf->lop[indexLop]->soSv;
	int indexMH = inf->TestMH(maMH);
	int index = 0;

	SinhVien **sv = new SinhVien*[sosv];
	for (int i = 0; i < sosv; i++) {
		sv[i] = new SinhVien();
	}
	DSSV *ds = inf->lop[indexLop]->dssv;
	while (ds != NULL) {
		sv[index] = ds->sv;
		ds = ds->next;
		index++;
	}

	Login next, previous, exit;
	next.dai = previous.dai = exit.dai = 90;
	next.rong = previous.rong = exit.rong = 30;

	index = 0;
	while (1) {
		delay(0.00001);
		cleardevice();
		if (index + maxInPage < sosv) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50,BUTTON);
			//outtextxy(next.left + 20, next.top + 5, "NEXT");
			WriteColorWord(next.left + 20, next.top + 5, "NEXT",WORDBUTTON,BUTTON);
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50,BUTTON);
			//outtextxy(previous.left + 20, previous.top + 5, "PREV");
			WriteColorWord(previous.left + 20, previous.top + 5, "PREV",WORDBUTTON,BUTTON);
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20,BUTTON);
		//outtextxy(exit.left + 10, exit.top + 5, "Thoat");
		WriteColorWord(exit.left + 10, exit.top + 5, "Thoat",WORDBUTTON,BUTTON);
		int indexY = 60;
		outtextxy(X, indexY - 40, "Ma SV");//400
		outtextxy(X + 350, indexY - 40, "Ho");//150
		outtextxy(X + 500, indexY - 40, "Ten");//400
		outtextxy(X + 950, indexY - 40, "Diem");//100

		line(0, indexY - 10, getmaxx(), indexY - 10);


		line(X + 320, 0, X + 320, indexY + 40*(maxInPage+1));
		line(X + 470, 0, X + 470, indexY + 40*(maxInPage+1));

		line(X + 920, 0, X + 920, indexY + 40*(maxInPage+1));
		line(0, indexY +40*(maxInPage + 1),getmaxx(),indexY + 40*(maxInPage+1));

		outtextxy(10,indexY +40*(maxInPage + 1) + 20,"Lop: ");
		outtextxy(70,indexY +40*(maxInPage + 1) + 20,&inf->lop[indexLop]->maLop[0]);
		outtextxy(10,indexY +40*(maxInPage + 1) + 70,"Mon: ");
		outtextxy(70,indexY +40*(maxInPage + 1) + 70,&inf->monHoc[indexMH]->tenMH[0]);

		char cDiem[10];
		for (int i = index; i < sosv && i < index + maxInPage; i++) {
			//	cout<<i<<endl;
			memset(cDiem, 0, sizeof cDiem);
//			itoa(sv[i]->diem[indexMH]->diemThi, cDiem, 10);
			if(sv[i]->diem[indexMH]->diemThi==10.0) {
				cDiem[0]='1';
				cDiem[1]='0';
				cDiem[2]='\0';
			} else {
				int temp=sv[i]->diem[indexMH]->diemThi*100;
//				cout<<temp<<endl;
				for(int i=3; i>=0; i--) {
					if(i==1) {
						cDiem[i]='.';
						continue;
					} else {
						cDiem[i]=temp%10+'0';
						temp/=10;
					}
				}
				cDiem[4]='\0';
			}
			outtextxy(X, indexY, &sv[i]->maSV[0]);
			outtextxy(X + 350, indexY, &sv[i]->Ho[0]);
			outtextxy(X + 500, indexY, &sv[i]->Ten[0]);
			if (sv[i]->diem[indexMH]->diemThi != -1) {
				outtextxy(X + 950, indexY, cDiem);
			} else {
				outtextxy(X + 950, indexY, "Chua Thi");
			}

			indexY += 40;
			//	if(i==sosv-2) cout<<"ccc";
		}
		while (1) {
			delay(0.00001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (index + maxInPage < sosv&&IsClickRec(next, moux, mouy)) {
					//isClick = true;
					index += maxInPage;
					break;
				} else if (index >= maxInPage && IsClickRec(previous, moux, mouy)) {
					//	isClick = true;
					index -= maxInPage;
					break;
				} else if (IsClickRec(exit, moux, mouy)) {
					putimage(0, 0, arrow, COPY_PUT);
					return;
				}


			}
		}
	}

}

void InDSLop(string malop, int maxInPage, int X) {
	void *arrow;
	unsigned int size;
	size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
	arrow = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), arrow);
	cleardevice();

	/////-----------------------------------------------------------------------/
	//////////////////////
	int indexLop = inf->TestLop(malop);
	int sosv = inf->lop[indexLop]->soSv;
	int index = 0;

	SinhVien **sv = new SinhVien*[sosv];
	for (int i = 0; i < sosv; i++) {
		sv[i] = new SinhVien();
	}
	DSSV *ds = inf->lop[indexLop]->dssv;
	while (ds != NULL) {
		sv[index] = ds->sv;
		ds = ds->next;
		index++;
	}

	Login next, previous, exit;
	next.dai = previous.dai = exit.dai = 90;
	next.rong = previous.rong = exit.rong = 30;

	index = 0;
	while (1) {
		delay(0.00001);
		cleardevice();
		if (index + maxInPage < sosv) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50,BUTTON);
			//outtextxy(next.left + 20, next.top + 5, "NEXT");
			WriteColorWord(next.left + 20, next.top + 5, "NEXT",WORDBUTTON,BUTTON);
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50,BUTTON);
			//outtextxy(previous.left + 20, previous.top + 5, "PREV");
			WriteColorWord(previous.left + 20, previous.top + 5, "PREV",WORDBUTTON,BUTTON);
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20,BUTTON);
		//outtextxy(exit.left + 10, exit.top + 5, "Thoat");
		WriteColorWord(exit.left + 10, exit.top + 5, "Thoat",WORDBUTTON,BUTTON);

		int indexY = 60;
		outtextxy(X, indexY - 40, "Ma SV");//400
		outtextxy(X + 350, indexY - 40, "Ho");//150
		outtextxy(X + 500, indexY - 40, "Ten");//400
		outtextxy(X + 950, indexY - 40, "Gioi Tinh");//100

		line(0, indexY - 10, getmaxx(), indexY - 10);


		line(X + 320, 0, X + 320, indexY + 40*(maxInPage+1));
		line(X + 470, 0, X + 470, indexY + 40*(maxInPage+1));

		line(X + 920, 0, X + 920, indexY + 40*(maxInPage+1));
		line(0, indexY +40*(maxInPage + 1),getmaxx(),indexY + 40*(maxInPage+1));

		outtextxy(10,indexY +40*(maxInPage + 1) + 20,"Lop: ");
		outtextxy(70,indexY +40*(maxInPage + 1) + 20,&inf->lop[indexLop]->maLop[0]);

		char cDiem[10];
		for (int i = index; i < sosv && i < index + maxInPage; i++) {
			//	cout<<i<<endl;
			outtextxy(X, indexY, &sv[i]->maSV[0]);
			outtextxy(X + 350, indexY, &sv[i]->Ho[0]);
			outtextxy(X + 500, indexY, &sv[i]->Ten[0]);
			if (sv[i]->Nam) {
				outtextxy(X + 950, indexY, "Nam");
			} else {
				outtextxy(X + 950, indexY, "Nu");
			}

			indexY += 40;
			//	if(i==sosv-2) cout<<"ccc";
		}
		while (1) {
			delay(0.00001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (index + maxInPage < sosv&&IsClickRec(next, moux, mouy)) {
					//isClick = true;
					index += maxInPage;
					break;
				} else if (index >= maxInPage && IsClickRec(previous, moux, mouy)) {
					//	isClick = true;
					index -= maxInPage;
					break;
				} else if (IsClickRec(exit, moux, mouy)) {
					putimage(0, 0, arrow, COPY_PUT);
					return;
				}


			}
		}
	}

}

int DeleteSV(string malop, int maxInPage, int X) {
	void *arrow;
	unsigned int size;
	size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
	arrow = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), arrow);
	cleardevice();

	/////-----------------------------------------------------------------------/
	//////////////////////
	int indexLop = inf->TestLop(malop);
	int sosv = inf->lop[indexLop]->soSv;
	int index = 0;

	SinhVien **sv = new SinhVien*[sosv];
	for (int i = 0; i < sosv; i++) {
		sv[i] = new SinhVien();
	}
	DSSV *ds = inf->lop[indexLop]->dssv;
	while (ds != NULL) {
		sv[index] = ds->sv;
		ds = ds->next;
		index++;
	}

	CircleClick *click = new CircleClick[sosv];
	int *mark = new int[sosv];
	for (int i = 0; i < sosv; i++) {
		mark[i] = -1;
		click[i].bk = 10;
		click[i].x = X - 40;
	}

	Login next, previous, exit, del;
	next.dai = previous.dai = exit.dai = del.dai = 90;
	next.rong = previous.rong = exit.rong = del.rong = 30;

	index = 0;
	int chon=0;
	while (1) {
		delay(0.00001);
		cleardevice();

		if (index + maxInPage < sosv) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50,BUTTON);
			//outtextxy(next.left + 20, next.top + 5, "NEXT");
			WriteColorWord(next.left + 20, next.top + 5, "NEXT",WORDBUTTON,BUTTON);
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50,BUTTON);
			//outtextxy(previous.left + 20, previous.top + 5, "PREV");
			WriteColorWord(previous.left + 20, previous.top + 5, "PREV",WORDBUTTON,BUTTON);
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20,BUTTON);
		//outtextxy(exit.left + 10, exit.top + 5, "Thoat");
		WriteColorWord(exit.left + 10, exit.top + 5, "Thoat",WORDBUTTON,BUTTON);
		InitRec(del, exit.left - del.dai / 2, exit.top + del.rong / 2,BUTTON);
		//outtextxy(fix.left + 10, fix.top + 5, "Sua");
		WriteColorWord(del.left + 10, del.top + 5, "Xoa",WORDBUTTON,BUTTON);



		int indexY = 60;
		outtextxy(X, indexY - 40, "Ma SV");//400
		outtextxy(X + 350, indexY - 40, "Ho");//150
		outtextxy(X + 500, indexY - 40, "Ten");//400
		outtextxy(X + 950, indexY - 40, "Gioi Tinh");//100

		line(0, indexY - 10, getmaxx(), indexY - 10);


		line(X + 320, 0, X + 320, indexY + 40*(maxInPage+1));
		line(X + 470, 0, X + 470, indexY + 40*(maxInPage+1));

		line(X + 920, 0, X + 920, indexY + 40*(maxInPage+1));
		line(0, indexY +40*(maxInPage + 1),getmaxx(),indexY + 40*(maxInPage+1));

		outtextxy(10,indexY +40*(maxInPage + 1) + 20,"Lop: ");
		outtextxy(70,indexY +40*(maxInPage + 1) + 20,&inf->lop[indexLop]->maLop[0]);

		for (int i = index; i < sosv && i < index + maxInPage; i++) {
			//	cout<<i<<endl;

			click[i].y = indexY + 5;
			InitCircle(click[i], mark[i]);

			outtextxy(X, indexY, &sv[i]->maSV[0]);
			outtextxy(X + 350, indexY, &sv[i]->Ho[0]);
			outtextxy(X + 500, indexY, &sv[i]->Ten[0]);
			if(sv[i]->Nam) {
				outtextxy(X + 950, indexY, "Nam");
			} else {
				outtextxy(X + 950, indexY, "Nu");
			}

			indexY += 40;
		}
		int moux = -1, mouy = -1;
		while (1) {
			delay(0.00001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
			}
			if (index + maxInPage < sosv&&IsClickRec(next, moux, mouy)) {
				index += maxInPage;
				break;
			} else if (index >= maxInPage && IsClickRec(previous, moux, mouy)) {
				index -= maxInPage;
				break;
			}

			else if (IsClickRec(exit, moux, mouy)) {
				return 0;
			} else if (IsClickRec(del, moux, mouy) && chon>0) {
				bool test;
				test = WindowThongBaoYN("Ban Co Muon Xoa Khong ?");
				if (test) {
					for (int t = 0; t < sosv; t++) {
						if (mark[t] != -1) {
							inf->DeleteSV(sv[t]->maSV);
						}
					}
					return 1;
				} else {
					moux = -1, mouy = -1;
					continue;
				}
			}
			for (int t = index; t < sosv && t < index + maxInPage; t++) {
				if (IsClickCircle(click[t], moux, mouy)) {
					if (mark[t] != -1) {
						mark[t] = -1;
						InitCircle(click[t], mark[t]);
						chon--;
					} else {
						chon++;
						mark[t] = BLACK;
						InitCircle(click[t], mark[t]);
					}
				}
			}//for
			moux = -1, mouy = -1;

		}
	}


}

int SuaSinhVien(string malop,string tenlop, int maxInPage, int X) {
	void *arrow;
	unsigned int size;
	size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
	arrow = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), arrow);
	cleardevice();

	/////-----------------------------------------------------------------------/
	//////////////////////
	int indexLop = inf->TestLop(malop);
	int sosv = inf->lop[indexLop]->soSv;
	int index = 0, choose=-1;

	SinhVien **sv = new SinhVien*[sosv];
	for (int i = 0; i < sosv; i++) {
		sv[i] = new SinhVien();
	}
	DSSV *ds = inf->lop[indexLop]->dssv;
	while (ds != NULL) {
		sv[index] = ds->sv;
		ds = ds->next;
		index++;
	}

	CircleClick *click = new CircleClick[sosv];
	for (int i = 0; i < sosv; i++) {
		click[i].bk = 10;
		click[i].x = X - 40;
	}

	Login next, previous, exit, fix;
	next.dai = previous.dai = exit.dai = fix.dai = 90;
	next.rong = previous.rong = exit.rong = fix.rong = 30;

	index = 0;
	int chon=0;
	while (1) {
		delay(0.00001);
		cleardevice();
		if (index + maxInPage < sosv) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50,BUTTON);
			//outtextxy(next.left + 20, next.top + 5, "NEXT");
			WriteColorWord(next.left + 20, next.top + 5, "NEXT",WORDBUTTON,BUTTON);
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50,BUTTON);
			//outtextxy(previous.left + 20, previous.top + 5, "PREV");
			WriteColorWord(previous.left + 20, previous.top + 5, "PREV",WORDBUTTON,BUTTON);
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20,BUTTON);
		//outtextxy(exit.left + 10, exit.top + 5, "Thoat");
		WriteColorWord(exit.left + 10, exit.top + 5, "Thoat",WORDBUTTON,BUTTON);
		InitRec(fix, exit.left - fix.dai / 2, exit.top + fix.rong / 2,BUTTON);
		//outtextxy(fix.left + 10, fix.top + 5, "Sua");
		WriteColorWord(fix.left + 10, fix.top + 5, "Sua",WORDBUTTON,BUTTON);

		int indexY = 60;
		outtextxy(X, indexY - 40, "Ma SV");//400
		outtextxy(X + 350, indexY - 40, "Ho");//150
		outtextxy(X + 500, indexY - 40, "Ten");//400
		outtextxy(X + 950, indexY - 40, "Gioi Tinh");//100

		line(0, indexY - 10, getmaxx(), indexY - 10);


		line(X + 320, 0, X + 320, indexY + 40*(maxInPage+1));
		line(X + 470, 0, X + 470, indexY + 40*(maxInPage+1));

		line(X + 920, 0, X + 920, indexY + 40*(maxInPage+1));
		line(0, indexY +40*(maxInPage + 1),getmaxx(),indexY + 40*(maxInPage+1));

		outtextxy(10,indexY +40*(maxInPage + 1) + 20,"Lop: ");
		outtextxy(70,indexY +40*(maxInPage + 1) + 20,&inf->lop[indexLop]->maLop[0]);

		for (int i = index; i < sosv && i < index + maxInPage; i++) {
			//	cout<<i<<endl;

			click[i].y = indexY + 5;
			if(choose==i) InitCircle(click[i], BLACK);
			else InitCircle(click[i],-1);

			outtextxy(X, indexY, &sv[i]->maSV[0]);
			outtextxy(X + 350, indexY, &sv[i]->Ho[0]);
			outtextxy(X + 500, indexY, &sv[i]->Ten[0]);
			if(sv[i]->Nam) {
				outtextxy(X + 950, indexY, "Nam");
			} else {
				outtextxy(X + 950, indexY, "Nu");
			}

			indexY += 40;
		}
		int moux = -1, mouy = -1;
		while (1) {
			delay(0.00001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
			}
			if (index + maxInPage < sosv&&IsClickRec(next, moux, mouy)) {
				index += maxInPage;
				break;
			} else if (index >= maxInPage && IsClickRec(previous, moux, mouy)) {
				index -= maxInPage;
				break;
			}

			else if (IsClickRec(exit, moux, mouy)) {
				//	putimage(0, 0, arrow, COPY_PUT);
				return 0;
			} else if (IsClickRec(fix, moux, mouy) && choose!=-1) {
				bool test;
				test = WindowThongBaoYN("Ban Co Muon Sua Khong ?");
				if (test) {
					for (int t = 0; t < sosv; t++) {
						if (t==choose) {
							//inf->DeleteSV(sv[t]->maSV);
							WindowSuaSV(malop,tenlop,sv[choose],600);
							break;
						}
					}
					return 1;
				} else {
					moux = -1, mouy = -1;
					continue;
				}
			}

			bool isClick=false;
			for (int t = index; t < sosv && t < index + maxInPage; t++) {
				if (IsClickCircle(click[t], moux, mouy)) {
					isClick=true;
					choose=t;
					break;
				}
			}//for
			if(isClick)
				for (int t = index; t < sosv && t < index + maxInPage; t++) {
					if(choose==t) {
						InitCircle(click[t],BLACK);
					} else {
						InitCircle(click[t],-1);
					}
				}//for

			moux = -1, mouy = -1;

		}
	}


}

void WindowSuaSV(string malop,string tenlop, SinhVien *sv, int toadoX) {

	cleardevice();
	//putimage(0,0,arrow,COPY_PUT);

	bool Trai = true;
	string Sma, Sho, Sten, Spassword,SLop,Smalop,Stenlop;
	Login ma, ho, ten, password, apply, cancel,maLop,tenLop;
	CircleClick nam, nu;

	maLop.dai = tenLop.dai = 220;
	maLop.rong = tenLop.rong = 60;

	ma.rong = ho.rong = ten.rong = password.rong = 40;
	ma.dai = 300;
	ho.dai = 130;
	ten.dai = 300;
	password.dai = 300;

	apply.dai = cancel.dai = 90;
	apply.rong = cancel.rong = 30;

	int tamX = toadoX + 80;

	InitRec(maLop, tamX - 30, maLop.rong / 2 + 10);
	outtextxy(maLop.left - 90, maLop.top + 5, "Ma Lop");
	InitRec(tenLop, maLop.right + tenLop.dai / 2 + 100, maLop.top + tenLop.rong / 2);
	outtextxy(maLop.right + 10, maLop.top + 5, "Ten Lop");


	InitRec(ma, tamX, maLop.bottom + ma.rong / 2 + 30);
	InitRec(ho, ma.left + ho.dai / 2, ma.bottom + 50);
	InitRec(ten, tamX, ho.bottom + 50);
	InitRec(password, tamX, ten.bottom + 50);

	outtextxy(10,10,"Lop: ");
	outtextxy(70,10,&malop[0]);
	outtextxy(10,50,"Ho: ");
	outtextxy(70,50,&sv->Ho[0]);
	outtextxy(10,100,"Ten: ");
	outtextxy(70,100,&sv->Ten[0]);
	outtextxy(10,150,"Gioi tinh: ");
	if(sv->Nam) outtextxy(85,150,"Nam");
	else outtextxy(85,150,"Nu");

	outtextxy(ma.left - 130, ma.top + 5, "Ma Sinh Vien");
	outtextxy(ho.left - 130, ho.top + 5, "Ho");
	outtextxy(ten.left - 130, ten.top + 5, "Ten");
	outtextxy(password.left - 130, password.top + 5, "PassWord");

	InitRec(cancel, getmaxx() - cancel.dai / 2 - 50, getmaxy() - cancel.rong / 2 - 50);
	outtextxy(cancel.left + 20, cancel.top + 5, "Cancel");

	InitRec(apply, cancel.left - 50 - apply.rong / 2, getmaxy() - apply.rong / 2 - 50);
	outtextxy(apply.left + 20, apply.top + 5, "Apply");

	nam.bk = nu.bk = 10;
	nam.y = nu.y = password.bottom + 30;
	nam.x = password.left + 40;
	nu.x = nam.x + nam.bk + 70;

	outtextxy(nam.x - nam.bk - 40, nam.y - 15, "Nam");
	outtextxy(nu.x - nu.bk - 30, nu.y - 15, "Nu");

	InitCircle(nam, BLACK);
	InitCircle(nu, -1);


	int moux = -1, mouy = -1;
	int indexXMa, indexXHo, indexXTen, indexXPass,indexXMalop,indexXTenlop;
	int indexYMa, indexYHo, indexYTen, indexYPass,indexYMalop,indexYTenlop;

	indexXMalop=maLop.left+5;
	indexXTenlop=tenLop.left+5;
	indexXHo = ho.left + 5;
	indexXMa = ma.left + 5;
	indexXTen = ten.left + 5;
	indexXPass = password.left + 5;

	indexYMalop=maLop.top+10;
	indexYTenlop=tenLop.top+10;
	indexYHo = ho.top + 10;
	indexYMa = ma.top + 10;
	indexYTen = ten.top + 10;
	indexYPass = password.top + 10;

	char c;
	while (1) {
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			//outtextxy(apply.left , apply.top -30, "                               ");
			moux = mousex(), mouy = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(IsClickRec(maLop,moux,mouy)) {
			HieuUngNhap(maLop,Smalop,indexXMalop,indexYMalop,moux,mouy,13,15);
		} else if(IsClickRec(tenLop,moux,mouy)) {
			HieuUngNhap(tenLop,Stenlop,indexXTenlop,indexYTenlop,moux,mouy,13,15);
		} else if (IsClickRec(ma, moux, mouy)) {
			HieuUngNhap(ma, Sma, indexXMa, indexYMa, moux, mouy, 15, 18);
		} else if (IsClickRec(ho, moux, mouy)) {
			HieuUngNhap(ho, Sho, indexXHo, indexYHo, moux, mouy, 15, 6, 0);
		} else if (IsClickRec(ten, moux, mouy)) {
			HieuUngNhap(ten, Sten, indexXTen, indexYTen, moux, mouy, 15, 18, 3);
		} else if (IsClickRec(password, moux, mouy)) {
			HieuUngNhap(password, Spassword, indexXPass, indexYPass, moux, mouy, 15, 18);
		} else if (IsClickCircle(nam, moux, mouy) || IsClickCircle(nu, moux, mouy)) {
			if (IsClickCircle(nam, moux, mouy) || Trai == false) {
				InitCircle(nam, BLACK);
				InitCircle(nu, -1);
				Trai = !Trai;
			} else if (IsClickCircle(nu, moux, mouy) || Trai == true) {
				InitCircle(nu, BLACK);
				InitCircle(nam, -1);
				Trai = !Trai;
			}
			moux = -1, mouy = -1;
		} else if (IsClickRec(apply, moux, mouy)) {
			bool test=true;
			if(Sma.size()!=0) {
				for(int i=0; i<inf->GetSoLop(); i++) {
					test=inf->TestSV(inf->lop[i],Sma);
					if(!test) {
						test=false;
						break;
					}
				}
			}

			if(test || (!test && Sma==sv->maSV)) {
				//string Sma, Sho, Sten, Spassword,SLop
				if(Sma.size()==0) Sma=sv->maSV;
				if(Sho.size()==0) Sho=sv->Ho;
				if(Sten.size()==0) Sten=sv->Ten;
				if(Spassword.size()==0) Spassword=sv->PassWord;
				if(Smalop.size()==0) Smalop=malop;
				if(Stenlop.size()==0) Stenlop=tenlop;

				if(Stenlop.size()==0) {
					int index=-1;
					index=inf->TestLop(Smalop);
					if(index!=-1) Stenlop=inf->lop[index]->tenLop;
				}

				float *diem = new float[SOMON];
				DSDiemThi **dsd=sv->diem;
				for(int i=0; i<SOMON; i++) {
					diem[i]=dsd[i]->diemThi;
				}
				inf->DeleteSV(sv->maSV);
				*inf->sv=SinhVien(Sma,Sho,Sten,Spassword,Trai);
				*inf->lopTemp = Lop(Smalop,Stenlop);

				int ad;
				ad = inf->AddSv(inf->sv,inf->lopTemp);

				if(ad!=-1)	{
					//outtextxy(apply.left , apply.top -30, " Sua Thanh Cong !");
					WindowThongBao("Sua Thanh Cong !");
				} else  {
					*inf->lopTemp = Lop(malop,tenlop);
					inf->AddSv(sv,inf->lopTemp);
					//outtextxy(apply.left , apply.top -30, " Sua That Bai !");
					WindowThongBao("Sua That Bai !");
				}

				for(int i=0; i<inf->GetSoLop(); i++) {
					DSSV *ds=inf->lop[i]->dssv;
					bool flag=false;
					while(ds!=NULL) {
						if(ds->sv->maSV==Sma) {
							flag=true;
							for(int j=0; j<SOMON; j++) {
								ds->sv->diem[j]->diemThi=diem[j];
							}
							break;
						}
						ds=ds->next;
					}
					if(flag) break;

				}

			} else {
				//outtextxy(apply.left , apply.top -30, "Trung MSSV! ");
				WindowThongBao("Trung MSSV !");
			}
			//outtextxy(apply.left , apply.top -30, "                                            ");

			moux = -1;
			mouy = -1;
		} else if (IsClickRec(cancel, moux, mouy)) {
			return;
		}
		//cc
		if(kbhit()) getch();
	}

}


bool WindowThongBaoYN(string s) {
	void *screen;
	int size = imagesize(0, 0, getmaxx(), getmaxy());
	screen = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), screen);

	cleardevice();

	int moux = -1, mouy = -1;
	Login ThongBao, Yes, No;
	ThongBao.dai = 300;
	ThongBao.rong = 100;
	Yes.dai = No.dai = 80;
	Yes.rong = No.rong = 30;
	InitRec(ThongBao, getmaxx() / 2, getmaxy() / 2,COLOR(234,132,198));
	InitRec(Yes, ThongBao.left + 70, ThongBao.bottom - Yes.rong - 10,BUTTON);
	InitRec(No, ThongBao.right - 70, ThongBao.bottom - Yes.rong - 10,BUTTON);

	//outtextxy(ThongBao.left + 10, ThongBao.top + 10, &s[0]);
	//outtextxy(Yes.left + 10, Yes.top + 5, "Yes");
	//outtextxy(No.left + 10, No.top + 5, "No");
	WriteColorWord(ThongBao.left + 10, ThongBao.top + 10, &s[0],WORDBUTTON,COLOR(234,132,198));
	WriteColorWord(Yes.left + 10, Yes.top + 5, "Yes",WORDBUTTON,BUTTON);
	WriteColorWord(No.left + 10, No.top + 5, "No",WORDBUTTON,BUTTON);

	int xx = -1, yy = -1;
	bool IsYes = false;
	while (1) {
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			xx = mousex(), yy = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if (IsClickRec(Yes, xx, yy)) {
			putimage(0, 0, screen, COPY_PUT);
			IsYes = true;
			break;
		} else if (IsClickRec(No, xx, yy)) {
			putimage(0, 0, screen, COPY_PUT);
			IsYes = false;
			break;
		}
	}

	putimage(0, 0, screen, COPY_PUT);
	return IsYes;
}

void WindowThongBao(string s) {
	void *screen;
	int size = imagesize(0, 0, getmaxx(), getmaxy());
	screen = malloc(size);
	getimage(0, 0, getmaxx(), getmaxy(), screen);
	cleardevice();

	int moux = -1, mouy = -1;
	Login ThongBao, Ok;
	ThongBao.dai = 300;
	ThongBao.rong = 100;
	Ok.dai = 50;
	Ok.rong = 30;
	InitRec(ThongBao, getmaxx() / 2, getmaxy() / 2,COLOR(234,132,198));
	InitRec(Ok, getmaxx() / 2, ThongBao.bottom - Ok.rong - 10,GREEN);
	//outtextxy(ThongBao.left + 10, ThongBao.top + 10, &s[0]);
	//outtextxy(Ok.left + 10, Ok.top + 5, "OK");
	WriteColorWord(ThongBao.left + 10, ThongBao.top + 10, &s[0],WORDBUTTON,COLOR(234,132,198));
	WriteColorWord(Ok.left + 10, Ok.top + 5, "OK",WORDBUTTON,GREEN);
	int xx = -1, yy = -1;
	while (1) {
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			xx = mousex(), yy = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if (IsClickRec(Ok, xx, yy)) {
			putimage(0, 0, screen, COPY_PUT);
			break;
		}
	}

	putimage(0, 0, screen, COPY_PUT);
}
void WindowBeforeThi() {
	cleardevice();
	string  socau = "", sophut = "";
	Login big, ok , Maxtime, Maxcau,back;
	big.dai=getmaxx()/4;
	big.rong=50*SOMON+20*SOMON;
	back.dai=ok.dai=80;
	back.rong=ok.rong=50;

	Maxcau.dai = Maxtime.dai = 90;
	Maxcau.rong = Maxtime.rong = 40;


	InitRec(big,getmaxx()/2,getmaxy()/2,13 | 0);
	InitRec(ok,getmaxx() - ok.dai/2 - 30,getmaxy() - ok.rong/2 -30,BUTTON);
	InitRec(back,ok.left-back.dai/2,ok.top+back.rong/2,BUTTON);

	InitRec(Maxcau, big.right + Maxcau.dai/2 + 140, big.top + Maxcau.rong/2);
	outtextxy(Maxcau.left - 70, Maxcau.top + 5, "So Cau");

	InitRec(Maxtime, big.right + Maxtime.dai/2  + 140, Maxcau.bottom + 30);
	outtextxy(Maxtime.left - 90, Maxtime.top + 5, "Thoi Gian");

	//outtextxy(ok.left+5,ok.top + 7,"OK");
	//outtextxy(back.left+5,back.top+7,"BACK");
	WriteColorWord(ok.left+5,ok.top + 7,"OK",WORDBUTTON,BUTTON);
	WriteColorWord(back.left+5,back.top+7,"BACK",WORDBUTTON,BUTTON);

	CircleClick *click = new CircleClick[SOMON];
	for(int i=0; i<SOMON; i++) {
		click[i].bk=10;
		click[i].x=big.left+10;
	}
	int indexY=big.top+20;
	for(int i=0; i<SOMON; i++) {
		click[i].y=indexY + 12;
		//outtextxy(big.left+30,indexY,&inf->monHoc[i]->tenMH[0]);
		WriteColorWord(big.left+30,indexY,&inf->monHoc[i]->tenMH[0],MAUCHU,13 | 0);
		indexY+=30;
	}

	for(int i=0; i<SOMON; i++) {
		if(i==MON_HIEN_TAI) {
			InitCircle(click[i],BLACK);
		} else InitCircle(click[i],-1);
	}
	int indexXCau,indexYCau,indexXTime,indexYTime;
	indexXCau = Maxcau.left + 5;
	indexYCau = Maxcau.top + 5;
	indexXTime = Maxtime.left + 5;
	indexYTime = Maxtime.top + 5;
	int disChar = 15;

	int moux=-1,mouy=-1;
	int chon=MON_HIEN_TAI;
	bool isClick=false;

	while(1) {
		delay(0.000001);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			moux=mousex(),mouy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(IsClickRec(ok,moux,mouy)) {
			if(TIME<=0 || SOCAU<=0) {
				WindowThongBao("Thoi gian/So cau khong hop le");
			} else {
				MON_HIEN_TAI = chon;

				DSSV *ds = inf->lop[currentLop]->dssv;
				while(ds->sv->maSV!=currentId) ds=ds->next;
				if(ds->sv->diem[MON_HIEN_TAI]->diemThi != (float)-1) {
					WindowThongBao("Da Thi Mon Nay !");
					moux=mouy=-1;
					continue;
				}

				return;
			}
			moux=mouy=-1;
			continue;
		} else if(IsClickRec(back,moux,mouy)) {
			isBack=true;
			return;
		} else if (IsClickRec(Maxcau, moux, mouy)) {
			HieuUngNhap1(Maxcau, socau, indexXCau, indexYCau, moux, mouy, 15, 3, 1);
			if (socau.size() != 0) {
				int temp;
				temp = atoi((char*)socau.c_str());
				SOCAU=temp;
				if(SOCAU >dsmon[chon]->GetCountMon()) {
					while((ll)socau.size()>0) {
						socau.erase(socau.size() - 1);
						indexXCau -= 15;
						outtextxy(indexXCau, indexYCau, "      ");
					}
					char tt[10];
					itoa(dsmon[chon]->GetCountMon(),tt,10);
					for(ll ii=0; ii<(ll)strlen(tt); ii++) {
						socau.push_back(tt[ii]);
						outtextxy(indexXCau, indexYCau, &socau[socau.size() - 1]);
						indexXCau += 15;
					}
					SOCAU = dsmon[chon]->GetCountMon();
				}

			}
			continue;
		} else if (IsClickRec(Maxtime, moux, mouy)) {
			HieuUngNhap1(Maxtime, sophut, indexXTime, indexYTime, moux, mouy, 15, 3, 1);
			if (sophut.size() != 0) {
				int temp;
				temp = atoi((char*)sophut.c_str());
				if(temp>0) TIME=temp;
			}
			continue;
		}
		for(int i=0; i<SOMON; i++) {
			if(IsClickCircle(click[i],moux,mouy)) {
				isClick=true;
				chon=i;
				////////BOSUNG----------------------------------
				if (socau.size() != 0) {
					int temp;
					temp = atoi((char*)socau.c_str());
					SOCAU=temp;
					if(SOCAU >dsmon[chon]->GetCountMon()) {
						while((ll)socau.size()>0) {
							socau.erase(socau.size() - 1);
							indexXCau -= 15;
							outtextxy(indexXCau, indexYCau, "      ");
						}
						char tt[10];
						itoa(dsmon[chon]->GetCountMon(),tt,10);
						for(ll ii=0; ii<(ll)strlen(tt); ii++) {
							socau.push_back(tt[ii]);
							outtextxy(indexXCau, indexYCau, &socau[socau.size() - 1]);
							indexXCau += 15;
						}
						SOCAU = dsmon[chon]->GetCountMon();
					}

				}
				//--------------------------BOSUNG
				break;
			}
		}
		if(isClick) {
			isClick=true;
			for(int i=0; i<SOMON; i++) {
				if(chon==i) InitCircle(click[i],BLACK);
				else InitCircle(click[i],-1);
			}
			moux=mouy=-1;
		}
		if(kbhit()) getch();
	}

}
void WindowAfterThi(QuesAndAns *CauHoi,CircleClick **click, int *chon,int n) {
	void *screen;
	int size = imagesize(0,0,getmaxx(),getmaxy());
	screen = malloc(size);
	cleardevice();

	Login next, previous, ketThuc;

	next.dai = previous.dai = 90;
	next.rong = previous.rong = ketThuc.rong = 30;
	ketThuc.dai = 120;

	InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
	InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50);

	int i=1;

	bool out=false;
	while(1) {
		delay(0.00001);
		cleardevice();

		InitRec(ketThuc, 40, getmaxy() - ketThuc.rong / 2 - 50,BUTTON);
		//outtextxy(ketThuc.left + 40, ketThuc.top + 5, "Ket Thuc");
		WriteColorWord(ketThuc.left + 40, ketThuc.top + 5, "Ket Thuc",WORDBUTTON,BUTTON);

		DrawTracNghiem(CauHoi[i - 1], click[i - 1], chon[i - 1]);
		if(chon[i - 1] != CauHoi[i-1].dapan) {
			CircleClick temp;
			int ans=CauHoi[i-1].dapan;
			temp.bk=click[i-1][ans].bk;
			temp.x=click[i-1][ans].x;
			temp.y=click[i-1][ans].y;
			InitCircle(temp,RED);
		}
		if (i < n) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50,BUTTON);
			//outtextxy(next.left + 20, next.top + 5, "NEXT");
			WriteColorWord(next.left + 20, next.top + 5, "NEXT",WORDBUTTON,BUTTON);
		}
		if (i > 1) {
			InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50,BUTTON);
			//outtextxy(previous.left + 20, previous.top + 5, "PREV");
			WriteColorWord(previous.left + 20, previous.top + 5, "PREV",WORDBUTTON,BUTTON);
		}
		while(1) {
			delay(0.000001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (i < n&&IsClickRec(next, moux, mouy)) {
					//isClick = true;
					i++;
					break;
				} else if (i > 1 && IsClickRec(previous, moux, mouy)) {
					//	isClick = true;
					i--;
					break;
				} else if (IsClickRec(ketThuc, moux, mouy)) {
					getimage(0, 0, getmaxx(), getmaxy(), screen);
					Login Big, yes, no;
					Big = Login(70, 230);
					yes = Login(30, 50);
					no = Login(30, 50);


					InitRec(Big, ketThuc.right + Big.dai / 2 + 30, getmaxy() - 30 - Big.rong / 2,RED);
					InitRec(yes, Big.left + 130, Big.top + 50,BUTTON);
					InitRec(no, yes.right + 20 + no.dai / 2, Big.top + 50,BUTTON);
					//	outtextxy(Big.left + 20, Big.top + 5, "Ban co muon ket thuc?");
					//	outtextxy(yes.left + 10, yes.top + 5, "Yes");
					//	outtextxy(no.left + 10, no.top + 5, "No");
					WriteColorWord(Big.left + 20, Big.top + 5, "Ban co muon ket thuc?",WHITE,RED);
					WriteColorWord(yes.left + 10, yes.top + 5, "Yes",WORDBUTTON,BUTTON);
					WriteColorWord(no.left + 10, no.top + 5, "No",WORDBUTTON,BUTTON);
					bool clickNo = false;
					int  _moux = -1, _mouy = -1;
					while (1) {
						delay(0.00001);
						if (ismouseclick(WM_LBUTTONDOWN)) {
							_moux = mousex();
							_mouy = mousey();
							clearmouseclick(WM_LBUTTONDOWN);
						}
						if (IsClickRec(yes, _moux, _mouy)) {
							out = TRUE;
							return;
							break;
						} else if (IsClickRec(no, _moux, _mouy)) {
							clickNo = true;
							break;
						}
					}
					if (clickNo) putimage(0, 0, screen, COPY_PUT);
				}

			}

		}
	}

}
bool WindowNhapTenLop(string &s) {
	s.clear();
	string s1;
	Login tenLop,ok,back;
	tenLop.dai = 220;
	tenLop.rong = 60;

	ok.dai=back.dai=90;
	ok.rong=back.rong=30;

	void *screen;
	int size = imagesize(0,0,getmaxx(),getmaxy());
	screen = malloc(size);
	getimage(0,0,getmaxx(),getmaxy(),screen);

	cleardevice();

	InitRec(tenLop,getmaxx()/2,getmaxy()/2);
	InitRec(ok,getmaxx()-ok.dai/2-30,getmaxy() - ok.rong/2-30,BUTTON);
	InitRec(back,ok.left-back.dai/2,ok.top+back.rong/2,BUTTON);

	outtextxy(tenLop.left-90,tenLop.top+5,"Ten Lop ");
	//outtextxy(ok.left+10,ok.top+5,"OK");
	//outtextxy(back.left+10,back.top+5,"Back");
	WriteColorWord(ok.left+10,ok.top+5,"OK",WORDBUTTON,BUTTON);
	WriteColorWord(back.left+10,back.top+5,"Back",WORDBUTTON,BUTTON);

	int disChar = 15,maxS=10;
	int moux=-1,mouy=-1;
	int indexXTenLop,indexYTenLop;
	indexXTenLop = tenLop.left + 10;
	indexYTenLop = tenLop.top + tenLop.rong / 2 - 10;

	while(1) {
		delay(0.00001);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			moux=mousex();
			mouy=mousey();
		}
		if(IsClickRec(tenLop,moux,mouy)) {
			HieuUngNhap(tenLop, s1, indexXTenLop, indexYTenLop, moux, mouy, disChar, maxS, 2);
		} else if(IsClickRec(back,moux,mouy)) {
			putimage(0,0,screen,COPY_PUT);
			return false;
		} else if(IsClickRec(ok,moux,mouy)) {
			for(int i=0; i<s1.size(); i++) {
				s.push_back(s1[i]);
			}
			return true;
		}
		if(kbhit()) getch();
	}

}
void WindowGV() {
	cleardevice();
	Login maLop, tenLop;
	Login choose,inDs, inDsLop,inDsDiem, SV, themSv, xoaSv, suaSv, NhapMon, Maxtime, Maxcau, exit;
	Login tha;
	int tamX;

	string currentMaLop = "", currentTenLop = "", socau = "", sophut = "";
	const string SinDs = "In danh sach";
	const string SinDsLop = "Danh sach lop";
	const string SinDsDiem = "Danh sach diem";
	const string SinhVien = "Sinh vien";
	const string addMh = "Them cau hoi";
	const string addCauHoi = "Them cau hoi";
	const string ThemSV = "Them sinh vien";
	const string XoaSV = "Xoa sinh vien";
	const string SuaSV = "Sua sinh vien";

	maLop.dai = tenLop.dai = 220;
	maLop.rong = tenLop.rong = 60;
	Maxcau.dai = Maxtime.dai = 90;
	Maxcau.rong = Maxtime.rong = 40;
	exit.dai = 90;
	exit.rong = 30;

	choose.dai = inDsLop.dai = inDs.dai = inDsDiem.dai = SV.dai = NhapMon.dai = themSv.dai = xoaSv.dai = suaSv.dai = 200;
	choose.rong = 50;
	inDsLop.rong = inDs.rong = inDsDiem.rong = SV.rong = NhapMon.rong = themSv.rong = xoaSv.rong = suaSv.rong = 50;

	//tha.dai=30;
	//tha.rong=choose.rong;
	//-----------------------------------------------------------------------------------


	tamX = 30 + choose.dai / 2;
	InitRec(maLop, tamX + 50, maLop.rong / 2 + 10);
	outtextxy(maLop.left - 70, maLop.top + 5, "Ma Lop");
//	InitRec(tenLop, maLop.right + tenLop.dai / 2 + 100, maLop.top + tenLop.rong / 2);
//	outtextxy(maLop.right + 10, maLop.top + 5, "Ten Lop");

	InitRec(choose, tamX, maLop.bottom + 60);
	int dis = inDsLop.rong / 2;
	int tamY = choose.bottom + 20;
	tamY += dis;
	InitRec(inDs, tamX, tamY, COLOR(67,116,231));
	//outtextxy(inDs.left + 20, inDs.top + 10, &SinDs[0]);
	WriteColorWord(inDs.left + 20, inDs.top + 10, &SinDs[0],WHITE,COLOR(67,116,231));


	tamY = dis + inDs.bottom;
	InitRec(SV, tamX, tamY , COLOR(67,116,231));
	//outtextxy(SV.left + 20, SV.top + 10, &SinhVien[0]);
	WriteColorWord(SV.left + 20, SV.top + 10, &SinhVien[0],WHITE,COLOR(67,116,231));

	tamY = dis + SV.bottom;
	InitRec(NhapMon, tamX, tamY,COLOR(67,116,231));
	//outtextxy(NhapMon.left + 20, NhapMon.top + 10, &addMh[0]);
	WriteColorWord(NhapMon.left + 20, NhapMon.top + 10, &addMh[0],WHITE,COLOR(67,116,231));

//	InitRec(Maxcau, tamX + 40, NhapMon.bottom + 30);
//	outtextxy(Maxcau.left - 70, Maxcau.top + 5, "So Cau");

//	InitRec(Maxtime, tamX + 40, Maxcau.bottom + 30);
//	outtextxy(Maxtime.left - 90, Maxtime.top + 5, "Thoi Gian");

	InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 40,BUTTON);
	//outtextxy(exit.left + 5, exit.top + 5, "Thoat");
	WriteColorWord(exit.left + 5, exit.top + 5, "Thoat",WORDBUTTON,BUTTON);

	//------------------------------------------------------------------

	int maxS = 10;
	int moux = -1, mouy = -1;
	int indexXMaLop, indexXTenLop;
	int indexYMaLop, indexYTenLop;
	indexXMaLop = maLop.left + 10;
	indexXTenLop = tenLop.left + 10;
	indexYMaLop = maLop.top + maLop.rong / 2 - 10;
	indexYTenLop = tenLop.top + tenLop.rong / 2 - 10;

	int indexXCau, indexYCau, indexXTime, indexYTime;

	indexXCau = Maxcau.left + 5;
	indexYCau = Maxcau.top + 5;
	indexXTime = Maxtime.left + 5;
	indexYTime = Maxtime.top + 5;
	int disChar = 15;
	bool nhap = false, clickTha = false;
	char c;

	void *screen;
	int size;
	size = imagesize(0, 0, getmaxx(), getmaxy());
	screen = malloc(size);

	while (1) {
		delay(0.000001);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			moux = mousex();
			mouy = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if (IsClickRec(maLop, moux, mouy)) {
			HieuUngNhap(maLop, currentMaLop, indexXMaLop, indexYMaLop, moux, mouy, disChar, maxS, 2);
		} else if (IsClickRec(exit, moux, mouy)) {
			return;
		} else { //cc

			int chooseX = choose.left + 10, chooseY = choose.top + 20;
			string xoa = "                                      ";
			if (IsClickRec(inDs, moux, mouy)) {
				//		outtextxy(0,10,"  ");
				//		outtextxy(0,10,"1");
				if (currentMaLop == "") {
					WindowThongBao("Chua Nhap Lop!");
					moux = -1, mouy = -1;
					continue;
				}
				if(inf->TestLop(currentMaLop) == -1) {
					WindowThongBao("Lop Khong Ton Tai!");
					moux=-1,mouy=-1;
					continue;
				}

				getimage(0, 0, getmaxx(), getmaxy(), screen);

				outtextxy(exit.left - 15, exit.top - 25, "                                                        ");
				outtextxy(chooseX, chooseY, &xoa[0]);
				outtextxy(chooseX, chooseY, &SinDs[0]);

				InitRec(inDsLop, inDs.right + inDsLop.dai / 2, inDs.top + inDsLop.rong / 2, COLOR(67,116,231));
				InitRec(inDsDiem, inDsLop.right + inDsDiem.dai / 2, inDsLop.top + inDsDiem.rong / 2, COLOR(67,116,231));

				//outtextxy(inDsLop.left + 10, inDsLop.top + 5, &SinDsLop[0]);
				//outtextxy(inDsDiem.left + 10, inDsDiem.top + 5, &SinDsDiem[0]);
				WriteColorWord(inDsLop.left + 10, inDsLop.top + 5, &SinDsLop[0],WHITE,COLOR(67,116,231));
				WriteColorWord(inDsDiem.left + 10, inDsDiem.top + 5, &SinDsDiem[0],WHITE,COLOR(67,116,231));

				int xx = -1, yy = -1;
				while (1) {
					delay(0.0001);
					if (ismouseclick(WM_LBUTTONDOWN)) {
						xx = mousex(), yy = mousey();
						clearmouseclick(WM_LBUTTONDOWN);

						if (IsClickRec(inDsDiem, xx, yy)) {
							cleardevice();
							int mon = WindowChonMon();
							InDSDiem(currentMaLop, inf->monHoc[mon]->maMH, 10, 100);
							xx = -1, yy = -1;
							break;
						} else if (IsClickRec(inDsLop, xx, yy)) {
							InDSLop(currentMaLop,10,100);
							xx = -1, yy = -1;
							break;
						} else { //click ra ngoai
							//clearmouseclick(WM_LBUTTONDOWN);
							break;
						}
					}
				}
				moux = -1, mouy = -1;
				putimage(0, 0, screen, COPY_PUT);

			} else if (IsClickRec(SV, moux, mouy)) {
				if (currentMaLop == "") {
					WindowThongBao("Chua Nhap Lop!");
					moux = -1, mouy = -1;
					continue;
				}

				getimage(0, 0, getmaxx(), getmaxy(), screen);

				outtextxy(exit.left - 15, exit.top - 25, "                                                        ");
				outtextxy(chooseX, chooseY, &xoa[0]);
				outtextxy(chooseX, chooseY, &SinhVien[0]);

				InitRec(themSv, SV.right + themSv.dai / 2, SV.top + SV.rong / 2,COLOR(67,116,231));
				InitRec(xoaSv, themSv.right + xoaSv.dai / 2, themSv.top + xoaSv.rong / 2,COLOR(67,116,231));
				InitRec(suaSv, xoaSv.right + suaSv.dai / 2, xoaSv.top + suaSv.rong / 2, COLOR(67,116,231));

				outtextxy(themSv.left + 10, themSv.top + 5, &ThemSV[0]);
				outtextxy(xoaSv.left + 10, xoaSv.top + 5, &XoaSV[0]);
				outtextxy(suaSv.left + 10, suaSv.top + 5, &SuaSV[0]);

				WriteColorWord(themSv.left + 10, themSv.top + 5, &ThemSV[0],WHITE,COLOR(67,116,231));
				WriteColorWord(xoaSv.left + 10, xoaSv.top + 5, &XoaSV[0],WHITE,COLOR(67,116,231));
				WriteColorWord(suaSv.left + 10, suaSv.top + 5, &SuaSV[0],WHITE,COLOR(67,116,231));

				int xx = -1, yy = -1;
				while (1) {
					delay(0.0001);
					if (ismouseclick(WM_LBUTTONDOWN)) {
						xx = mousex(), yy = mousey();
						clearmouseclick(WM_LBUTTONDOWN);

						if (IsClickRec(themSv, xx, yy)) {
							int temp = inf->TestLop(currentMaLop);
							if(temp==-1) {
								bool flag=WindowNhapTenLop(currentTenLop);
								if(!flag) { //back
									xx=-1,yy=-1;
									break;
								}
							} else currentTenLop = inf->lop[temp]->tenLop;
							ThemSINHVIEN(currentTenLop, currentMaLop, THEMSV, SV.right + 400);
							xx = -1, yy = -1;
							break;
						} else if (IsClickRec(xoaSv, xx, yy)) {
							if (inf->TestLop(currentMaLop) == -1) {
								putimage(0, 0, screen, COPY_PUT);
								WindowThongBao("Lop Khong Ton Tai !");
								moux = -1, mouy = -1;
								break;
							}
							int type = 0;

							while (1) {
								type = DeleteSV(currentMaLop, 10, 100);
								if (type == 0) break;
							}
							xx = -1, yy = -1;
							break;
						}


						else if (IsClickRec(suaSv, xx, yy)) {
							if (inf->TestLop(currentMaLop) == -1) {
								putimage(0, 0, screen, COPY_PUT);
								WindowThongBao("Lop Khong Ton Tai !");
								moux = -1, mouy = -1;
								break;
							}
							int type = 0;

							while (1) {
								type = SuaSinhVien(currentMaLop,currentTenLop, 10,100);
								if (type == 0) break;
							}
							xx = -1, yy = -1;
							break;

						} else { //click ra ngoai
							//clearmouseclick(WM_LBUTTONDOWN);
							break;
						}
					}
				}
				moux = -1, mouy = -1;
				putimage(0, 0, screen, COPY_PUT);

			} else if (IsClickRec(NhapMon, moux, mouy)) {
				//		outtextxy(0,10,"  ");
				//		outtextxy(0,10,"3");
				outtextxy(exit.left - 15, exit.top - 25, "                                                        ");
				outtextxy(chooseX, chooseY, &xoa[0]);
				outtextxy(chooseX, chooseY, &addMh[0]);
				WindowThemCauHoi();
			}
			moux = -1, mouy = -1;
		}

		if(kbhit()) getch();
	}

}

int WindowChonMon() {
	int monHienTai=0;
////--------------------------------------------------------------------------------------------
	Login big, ok , Maxtime, Maxcau;
	big.dai=getmaxx()/4;
	big.rong=50*SOMON+20*SOMON;
	ok.dai=80;
	ok.rong=30;

	Maxcau.dai = Maxtime.dai = 90;
	Maxcau.rong = Maxtime.rong = 40;


	InitRec(big,getmaxx()/2,getmaxy()/2,13 | 0);
	InitRec(ok,big.right-ok.dai/2,big.bottom+ok.rong/2,BUTTON);

	//outtextxy(ok.left+5,ok.top+5,"Ok");
	WriteColorWord(ok.left+5,ok.top+5,"Ok",WORDBUTTON,BUTTON);

	CircleClick *clk = new CircleClick[SOMON];
	for(int i=0; i<SOMON; i++) {
		clk[i].bk=10;
		clk[i].x=big.left+10;
	}
	int indexY=big.top+20;
	for(int i=0; i<SOMON; i++) {
		clk[i].y=indexY + 12;
		//outtextxy(big.left+30,indexY,&inf->monHoc[i]->tenMH[0]);
		WriteColorWord(big.left+30,indexY,&inf->monHoc[i]->tenMH[0],WORDBUTTON,13 | 0);
		indexY+=30;
	}

	for(int i=0; i<SOMON; i++) {
		if(i==monHienTai) {
			InitCircle(clk[i],BLACK);
		} else InitCircle(clk[i],-1);
	}
	int xx=-1,yy=-1;
	while(1) {
		delay(0.00001);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			xx=mousex(),yy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
			bool chon=false;
			for(int i=0; i<SOMON; i++) {
				if(IsClickCircle(clk[i],xx,yy)) {
					monHienTai=i;
					chon=true;
					break;
				}
			}
			if(chon) {
				for(int i=0; i<SOMON; i++) {
					if(monHienTai==i) {
						InitCircle(clk[i],BLACK);
					} else InitCircle(clk[i],-1);
				}
			}

			if(IsClickRec(ok,xx,yy)) {
				break;
			}
		}
	}
	return monHienTai;
}

void WindowThemCauHoi() {

	void *screen;
	int size = imagesize(0,0,getmaxx(),getmaxy());
	screen = malloc(size);
	getimage(0,0,getmaxx(),getmaxy(),screen);
	cleardevice();

	int monHienTai=0;
////--------------------------------------------------------------------------------------------
	Login big, ok , Maxtime, Maxcau;
	big.dai=getmaxx()/4;
	big.rong=50*SOMON+20*SOMON;
	ok.dai=80;
	ok.rong=30;

	Maxcau.dai = Maxtime.dai = 90;
	Maxcau.rong = Maxtime.rong = 40;


	InitRec(big,getmaxx()/2,getmaxy()/2,13 | 0);
	InitRec(ok,big.right-ok.dai/2,big.bottom+ok.rong/2,BUTTON);
	//outtextxy(ok.left+5,ok.top+5,"Ok");
	WriteColorWord(ok.left+5,ok.top+5,"Ok",WORDBUTTON,BUTTON);

	CircleClick *clk = new CircleClick[SOMON];
	for(int i=0; i<SOMON; i++) {
		clk[i].bk=10;
		clk[i].x=big.left+10;
	}
	int indexY=big.top+20;
	for(int i=0; i<SOMON; i++) {
		clk[i].y=indexY + 15;
		outtextxy(big.left+30,indexY,&inf->monHoc[i]->tenMH[0]);
		WriteColorWord(big.left+30,indexY,&inf->monHoc[i]->tenMH[0],WORDBUTTON,13 | 0);
		indexY+=30;
	}

	for(int i=0; i<SOMON; i++) {
		if(i==monHienTai) {
			InitCircle(clk[i],BLACK);
		} else InitCircle(clk[i],-1);
	}
	int xx=-1,yy=-1;
	while(1) {
		delay(0.00001);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			xx=mousex(),yy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
			bool chon=false;
			for(int i=0; i<SOMON; i++) {
				if(IsClickCircle(clk[i],xx,yy)) {
					monHienTai=i;
					chon=true;
					break;
				}
			}
			if(chon) {
				for(int i=0; i<SOMON; i++) {
					if(monHienTai==i) {
						InitCircle(clk[i],BLACK);
					} else InitCircle(clk[i],-1);
				}
			}

			if(IsClickRec(ok,xx,yy)) {
				break;
			}
		}
	}

	cleardevice();
	/////////------------------------------------------------------------------//////

	string Scauhoi="",SdapanA="",SdapanB="",SdapanC="",SdapanD="";
	Login cauHoi,dapanA,dapanB,dapanC,dapanD,them,cancel;
	CircleClick click[4];

	for(int i=0; i<4; i++) {
		click[i].bk=15;
	}

	cauHoi.dai = dapanA.dai = dapanB.dai = dapanC.dai = dapanD.dai = getmaxx()/2-100;
	cauHoi.rong = dapanA.rong = dapanB.rong = dapanC.rong = dapanD.rong = 30*3 + 10;//30:kcach  3: so dong toi da
	them.dai = cancel.dai = 80;
	them.rong = cancel.rong =50;

	

	InitRec(cauHoi,getmaxx()/2,cauHoi.rong/2 + 50);

	InitRec(dapanA,getmaxx()/2,cauHoi.bottom+dapanA.rong/2+30);
	InitRec(dapanB,getmaxx()/2,dapanA.bottom+dapanB.rong/2+20);
	InitRec(dapanC,getmaxx()/2,dapanB.bottom+dapanC.rong/2+20);
	InitRec(dapanD,getmaxx()/2,dapanC.bottom+dapanD.rong/2+20);

	InitRec(cancel,getmaxx()-cancel.dai/2-30,getmaxy()-cancel.rong/2-30,BUTTON);
	InitRec(them,cancel.left-them.dai/2,cancel.top+them.rong/2,BUTTON);
	//outtextxy(them.left+10,them.top+5,"Them");
	//outtextxy(cancel.left+10,cancel.top+5,"Huy bo");
	WriteColorWord(them.left+10,them.top+5,"Them",WORDBUTTON,BUTTON);
	WriteColorWord(cancel.left+10,cancel.top+5,"Huy bo",WORDBUTTON,BUTTON);

	outtextxy(cauHoi.left-100,cauHoi.top+10,"Cau Hoi");
	outtextxy(dapanA.left-40,dapanA.top+10,"A");
	click[0].x = dapanA.left-60;
	click[0].y = dapanA.top+15;

	outtextxy(dapanB.left-40,dapanB.top+10,"B");
	click[1].x = dapanB.left-60;
	click[1].y = dapanB.top+15;

	outtextxy(dapanC.left-40,dapanC.top+10,"C");
	click[2].x = dapanC.left-60;
	click[2].y = dapanC.top+15;

	outtextxy(dapanD.left-40,dapanD.top+10,"D");
	click[3].x = dapanD.left-60;
	click[3].y = dapanD.top+15;

	int indexXQues,indexXA,indexXB,indexXC,indexXD,indexYQues,indexYA,indexYB,indexYC,indexYD;

	indexXQues = cauHoi.left+10;
	indexXA = dapanA.left+10;
	indexXB = dapanC.left+10;
	indexXC = dapanC.left+10;
	indexXD = dapanD.left+10;

	indexYQues = cauHoi.top+10;
	indexYA = dapanA.top+10;
	indexYB = dapanB.top+10;
	indexYC = dapanC.top+10;
	indexYD = dapanD.top+10;

	int moux=-1,mouy=-1;
	int disChar=20;
	int dapan = -1;
	int maxPerLine = 26;
	//const int maxS = (cauHoi.dai -10)/25 *3 + 10;
	const int maxS = 26*3-2;
	for(int i=0; i<4; i++) {
		InitCircle(click[i],-1);
	}
	while(1) {
		delay(0.000001);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			moux=mousex();
			mouy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(IsClickRec(cancel,moux,mouy)) {
			bool out = WindowThongBaoYN("Ban co muon thoat ?");
			if(out) {
				putimage(0,0,screen,COPY_PUT);
				return;
			} else {
				moux=-1;
				mouy=-1;
				continue;
			}
		} else if(IsClickRec(them,moux,mouy)) {
			if(dapan != -1 && Scauhoi.size()>0 && SdapanA.size()>0 && SdapanB.size()>0 && SdapanC.size()>0 && SdapanD.size()>0) {
				int k;
				srand(time(0));
				do {
					k=rand()%1000;
				} while(IdArr[monHienTai][k]!=0);
				IdArr[monHienTai][k]++;
				QuesAndAns *temp=new QuesAndAns;
				temp->dapan=dapan;
				temp->id=k;
				strcpy(temp->cauhoi,(char*)Scauhoi.c_str());
				strcpy(temp->traloi[0],(char*)SdapanA.c_str());
				strcpy(temp->traloi[1],(char*)SdapanB.c_str());
				strcpy(temp->traloi[2],(char*)SdapanC.c_str());
				strcpy(temp->traloi[3],(char*)SdapanD.c_str());

				TREE->Insert(CayCB[monHienTai],temp);
				dsmon[monHienTai]->Add(temp);
//				cout<<inf->monHoc[monHienTai]->tenMH<<"  "<<dsmon[monHienTai]->GetCountMon()<<endl;
//				cout<<dsmon[monHienTai]->Ques[dsmon[monHienTai]->GetCountMon()-1]->traloi[2]<<endl;
				WindowThongBao("Them Thanh Cong! ");
				putimage(0,0,screen,COPY_PUT);
				return;

			} else {
				WindowThongBao("Ban chua nhap du! ");
				moux=-1;
				mouy=-1;
				continue;
			}
		} else if(IsClickRec(cauHoi,moux,mouy)) {
			HieuUngNhaps2(cauHoi,Scauhoi,indexXQues,indexYQues,moux,mouy,disChar,maxPerLine,maxS);
		} else if(IsClickRec(dapanA,moux,mouy)) {
			//	cout<<"a"<<endl;
			HieuUngNhaps2(dapanA,SdapanA,indexXA,indexYA,moux,mouy,disChar,maxPerLine,maxS);
		} else if(IsClickRec(dapanB,moux,mouy)) {
			//	cout<<"b"<<endl;
			HieuUngNhaps2(dapanB,SdapanB,indexXB,indexYB,moux,mouy,disChar,maxPerLine,maxS);
		} else if(IsClickRec(dapanC,moux,mouy)) {
			//	cout<<"c"<<endl;
			HieuUngNhaps2(dapanC,SdapanC,indexXC,indexYC,moux,mouy,disChar,maxPerLine,maxS);
		} else if(IsClickRec(dapanD,moux,mouy)) {
			//	cout<<"d"<<endl;
			HieuUngNhaps2(dapanD,SdapanD,indexXD,indexYD,moux,mouy,disChar,maxPerLine,maxS);
		} else if(kbhit()) getch();
		bool isclick = false;
		for(int i=0; i<4; i++) {
			if(IsClickCircle(click[i],moux,mouy)) {
				isclick = true;
				dapan=i;
				moux=-1,mouy=-1;
				break;
			}
		}
		if(isclick) {
			for(int i=0; i<4; i++) {
				if(dapan == i) {
					InitCircle(click[i],BLACK);
				} else {
					InitCircle(click[i],-1);
				}
			}
		}

	}
}
void LoadDSSV() {

	fstream file;
	file.open("DSSVbin.inp", ios::in | ios::binary);
	int n;
	file.read((char*)&n, sizeof(int));
	string *masv = new string[n];
	string *ho = new string[n];
	string *ten = new string[n];
	char c[100];
	string ss;

	for (int i = 0; i < n; i++) {
		int size;
		masv[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		masv[i] = c;
		//cout << masv[i] << endl;
	}
	for (int i = 0; i < n; i++) {
		int size;
		ho[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		ho[i] = c;
		//	cout << ho[i] << endl;
	}
	for (int i = 0; i < n; i++) {
		int size;
		ten[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		ten[i] = c;
		//	cout << ten[i] << endl;
	}
	file.close();


	for (int i = 0; i < n; i++) {
		*inf->sv = SinhVien(masv[i], ho[i], ten[i], masv[i], true);
		*inf->lopTemp = Lop("CN2", "CNTT");
		inf->AddSv(inf->sv, inf->lopTemp);
	}
}

void GhiFile() {
	fstream file;
	string tenFile[SOMON] = {"Ngon Ngu Lap Trinh C++.inp","Co So Du Lieu SQL.inp"};
	/////---------Cau Hoi----------////////////
	for(int i=0; i<SOMON; i++) {
		file.open(tenFile[i].c_str(),ios::out|ios::binary);
		int n=dsmon[i]->GetCountMon();
		file.write((char*)&n,sizeof(int));
		for(int j=0; j<n; j++) {
			int k=strlen(dsmon[i]->Ques[j]->cauhoi);

			file.write((char*)&k,sizeof(int));
			file.write(dsmon[i]->Ques[j]->cauhoi,k+1);

			//	cout<<dsmon[i]->Ques[j]->cauhoi<<endl;

			for(int m=0; m<4; m++) {
				k=strlen(dsmon[i]->Ques[j]->traloi[m]);
				file.write((char*)&k,sizeof(int));
				file.write(dsmon[i]->Ques[j]->traloi[m],k+1);

			}
			k=dsmon[i]->Ques[j]->dapan;
			cout<<k<<endl;
			k++;
			file.write((char*)&k,sizeof(int));
		}


		file.close();
	}
	///-----End Cau Hoi----------///////////

////////--------DSSV------/////////////////
	file.open("DSSV2",ios::out|ios::binary);
	int temp=inf->GetSoLop();
	file.write((char*)&temp,sizeof(int));

	char tenLop[100],maLop[100],ho[100],ten[100],pass[100],maSV[100];
	for(int i=0; i<inf->GetSoLop(); i++) {

		bool nam=false;
		int k;
		memset(tenLop,0,sizeof tenLop);
		memset(maLop,0,sizeof maLop);
		strcpy(tenLop,inf->lop[i]->tenLop.c_str());
		strcpy(maLop,inf->lop[i]->maLop.c_str());

		k=inf->lop[i]->soSv;
		file.write((char*)&k,sizeof(int));

		k=strlen(maLop);
		file.write((char*)&k,sizeof(int));
		file.write(maLop,strlen(maLop)+1);

		k=strlen(tenLop);
		file.write((char*)&k,sizeof(int));
		file.write(tenLop,strlen(tenLop)+1);

		DSSV *ds=inf->lop[i]->dssv;
		while(ds!=NULL) {
			memset(ho,0,sizeof ho);
			memset(ten,0,sizeof ten);
			memset(pass,0,sizeof pass);
			memset(maSV,0,sizeof maSV);

			strcpy(ho,ds->sv->Ho.c_str());
			strcpy(ten,ds->sv->Ten.c_str());
			strcpy(pass,ds->sv->PassWord.c_str());
			strcpy(maSV,ds->sv->maSV.c_str());
			nam=ds->sv->Nam;


			k=strlen(maSV);
			file.write((char*)&k,sizeof(int));
			file.write(maSV,strlen(maSV)+1);

			k=strlen(ho);
			file.write((char*)&k,sizeof(int));
			file.write(ho,strlen(ho)+1);

			k=strlen(ten);
			file.write((char*)&k,sizeof(int));
			file.write(ten,strlen(ten)+1);

			k=strlen(pass);
			file.write((char*)&k,sizeof(int));
			file.write(pass,strlen(pass)+1);

			if(nam) k=1;
			else k=0;
			file.write((char*)&k,sizeof(int));
			for(int j=0; j<SOMON; j++) {
				float diem = ds->sv->diem[j]->diemThi;
				file.write((char*)&diem,sizeof(float));
			}

			ds=ds->next;
		}
	}

	file.close();
	//////----------END DSSV-------////////////
}
void DocFile() {
	fstream file;

	DocCauHoi();

	file.open("DSSV2",ios::in|ios::binary);
	int soLop;
	file.read((char*)&soLop,sizeof(int));

	char tenLop[100],maLop[100],ho[100],ten[100],pass[100],maSV[100];
	bool nam=false;
	string *StenLop,*SmaLop;
	StenLop=new string[soLop];
	SmaLop=new string[soLop];


	for(int i=0; i<soLop; i++) {

		StenLop[i].resize(100);
		SmaLop[i].resize(100);

		memset(tenLop,0,sizeof tenLop);
		memset(maLop,0,sizeof maLop);
		int k,soSv;
		file.read((char*)&soSv,sizeof(int));

		file.read((char*)&k,sizeof(int));
		file.read(maLop,k+1);

		file.read((char*)&k,sizeof(int));
		file.read(tenLop,k+1);


		StenLop[i] = tenLop;
		SmaLop[i] = maLop;

		string *Sma=new string[soSv];
		string *Sten=new string[soSv];
		string *Sho=new string[soSv];
		string *Spass=new string[soSv];

		for(int j=0; j<soSv; j++) {
			memset(ho,0,sizeof ho);
			memset(ten,0,sizeof ten);
			memset(pass,0,sizeof pass);
			memset(maSV,0,sizeof maSV);
			Sma[j].resize(100);
			Sho[j].resize(100);
			Sten[j].resize(100);
			Spass[j].resize(100);

			file.read((char*)&k,sizeof(int));
			file.read(maSV,k+1);
			file.read((char*)&k,sizeof(int));
			file.read(ho,k+1);
			file.read((char*)&k,sizeof(int));
			file.read(ten,k+1);
			file.read((char*)&k,sizeof(int));
			file.read(pass,k+1);


			Sma[j]=maSV;
			Sho[j]=ho;
			Sten[j]=ten;
			Spass[j]=pass;

			file.read((char*)&k,sizeof(int));
			if(k==1) nam=true;
			else nam=false;

			*inf->sv = SinhVien(Sma[j],Sho[j],Sten[j],Spass[j],nam);
			*inf->lopTemp=Lop(SmaLop[i],StenLop[i]);
			inf->AddSv(inf->sv,inf->lopTemp);

			float diem;
			for(int indexMon=0; indexMon<SOMON; indexMon++) {
				file.read((char*)&diem,sizeof(float));
				inf->UpdateDiem(SmaLop[i],Sma[j],inf->monHoc[indexMon]->maMH,diem);

//				cout<<SmaLop[i]<<" "<<Sma[j]<<" "<<inf->monHoc[j]->maMH<<" "<<diem<<endl;
			}

		}
	}

	file.close();
}
