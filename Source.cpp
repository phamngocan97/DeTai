//#include"graphics.h"
#include"winbgim.h"
#include"Infor.h"
#include"AVLtree.h"

using namespace std;

typedef long long ll;
class SinhVien;
class DSSV;
class DSDiemThi;
class QuesAndAns;
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
			Ques=new QuesAndAns*[n];
			for(int i=0; i<n; i++) {
				Ques[i]=new QuesAndAns();
			}
		}
		int GetCountMon() {
			return numSentence;
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


void InitSoCau(Login &soCau, Login clock, int cauDaLam, int realQues);
void DrawLogin(Login &login, Login &id, Login &pass);
int DangNhap(Login login, Login id, Login pass);
int TestId(string id, string pass);
void InitQuestion(int realQues,DSMON *ds);
void DrawTracNghiem(QuesAndAns Infor, CircleClick *click, int type);
void Write(char *s, int x, int y, int dai);

void ThemSINHVIEN(string lop, string malop, int type, int toadoX);
void HieuUngNhap(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS, int type = -1);
void HieuUngNhaps(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS);
void InDS(string malop, string maMH, int maxInPage, int X);
int DeleteSV(string malop, int maxInPage, int X);
int SuaSinhVien(string malop, int maxInPage, int X);
void WindowSuaSV(string malop,string tenlop, SinhVien *sv, int toadoX);
void WindowGV();
void WindowThongBao(string s);
bool WindowThongBaoYN(string s);
void WindowBeforeThi();
void WindowThemCauHoi();

void LoadDSSV();
void DocCauHoi();

Infor *inf;
string currentId;
float currentDiem;
int TIME = -1, SOCAU = -1;
int MON_HIEN_TAI=1;
const int SOMON =2;
bool OVERTIME = false;

DSMON **dsmon;
int main() {


	//initgraph(&bg, &bm, " ");
	initwindow(1200, 680);
	//------------------------------------------------------------//

	inf = new Infor(SOMON, 2);
	DocCauHoi();

	Login login, id, pass;
	int typeSign;

	//InitQuestion();
	LoadDSSV();
//	inf->AddMh("a", "b");
	while (1) {
		cleardevice();
		DrawLogin(login, id, pass);
		typeSign = DangNhap(login, id, pass);
		
		cout<<typeSign<<endl;
		
		if (typeSign == -1) {
			WindowGV();
		}
		if (typeSign >= 0) {
			//cout<<"sdfg";
			TIME=SOCAU=-1;
			WindowBeforeThi();
			InitQuestion(SOCAU,dsmon[MON_HIEN_TAI]);
			inf->UpdateDiem(inf->lop[typeSign]->maLop, currentId, inf->monHoc[MON_HIEN_TAI]->maMH, currentDiem);
		}
	}


	while (!kbhit()) {

	}
	//closegraph();

	return 0;
}


void DrawLogin(Login &login, Login &id, Login &pass) {
	int disRong, disIdPass;
	disRong = 30;
	disIdPass = 30;
	login = Login(150, 400);

	id = Login(login.rong / 2 - disRong, login.dai / 2);
	pass = Login(login.rong / 2 - disRong, login.dai / 2);

	//setfillstyle(5, WHITE);

	InitRec(login, getmaxx() / 2, getmaxy() / 2);
	InitRec(id, getmaxx() / 2, getmaxy() / 2 - id.rong / 2 - disIdPass / 2);
	InitRec(pass, getmaxx() / 2, getmaxy() / 2 + id.rong / 2 + disIdPass / 2);


	//floodfill(id.bottom - 5, id.right - 5, WHITE);
	//floodfill(pass.bottom - 1, pass.right - 1, WHITE);


	settextstyle(4, HORIZ_DIR, 3);
	outtextxy(login.left + 90, login.top - 40, "Dang Nhap");

	settextstyle(3, HORIZ_DIR, 1);
	outtextxy(login.left + 10, id.top + 15, "Tai Khoan");
	outtextxy(login.left + 10, pass.top + 15, "Mat Khau");
}

int DangNhap(Login login, Login id, Login pass) {
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
		if (taikhoan || IsClickRec(id, moux, mouy)) {
			taikhoan = true;
			matkhau = false;
			char c;
			bool flag = false;
			bool outId = false;
			while (!kbhit()) {
				if (ismouseclick(WM_LBUTTONDOWN)) {
					int xx, yy;
					xx = mousex(), yy = mousey();
					if (IsClickRec(pass, xx, yy)) {
						moux = xx;
						mouy = yy;
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
						outtextxy(login.bottom + 20, login.left + 50, "Sai ID/PassWord");
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
					if (IsClickRec(id, xx, yy)) {
						moux = xx;
						mouy = yy;
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

	setcolor(k);
	setfillstyle(0, k);

}

void InitCircle(CircleClick click, int mau) {
	int k = getcolor();

	if (mau == -1) {
		setcolor(BLACK);
		circle(click.x, click.y, click.bk);
		setfillstyle(12, BLACK);
		floodfill(click.x, click.y, BLACK);

		setcolor(WHITE);
		circle(click.x, click.y, click.bk);

	} else {
		//	setcolor(WHITE);
		circle(click.x, click.y, click.bk);
		setfillstyle(12, WHITE);
		floodfill(click.x, click.y, WHITE);
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

				return i;
			}

		}
	}
	return -2;
}

void InitSoCau(Login &soCau, Login clock, int cauDaLam, int realQues) {
	InitRec(soCau, getmaxx() - 30 - soCau.dai / 2, clock.bottom + soCau.rong / 2 + 10 + soCau.rong / 2);
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
	fstream file;
	dsmon=new DSMON*[SOMON];
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
			}
			file.read((char*)&k,sizeof(int));
			dsmon[i]->Ques[j]->dapan=k;
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

	bool out=false;
	while (1) {
		delay(0.00001);
		if (OVERTIME || out){
			 break;
		}
		isClick = false;
		cleardevice();

		DrawTracNghiem(CauHoi[i - 1], click[i - 1], choose[i - 1]);

		InitRec(clock, getmaxx() - 30 - clock.dai / 2, 30 + clock.rong / 2);
		InitSoCau(soCau, clock, cauDaLam, realQues);

		if (i < realQues) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
			outtextxy(next.left + 20, next.top + 5, "NEXT");
		}
		if (i > 1) {
			InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50);
			outtextxy(previous.left + 20, previous.top + 5, "PREV");
		}
		InitRec(ketThuc, 40, getmaxy() - ketThuc.rong / 2 - 50);
		outtextxy(ketThuc.left + 40, ketThuc.top + 5, "Ket Thuc");
		
		while (1) {
			delay(0.00001);
			if (OVERTIME || out){
				break;	
			} 
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (i < realQues&&IsClickRec(next, moux, mouy)) {
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


					InitRec(Big, ketThuc.right + Big.dai / 2 + 30, getmaxy() - 30 - Big.rong / 2);
					InitRec(yes, Big.left + 130, Big.top + 50);
					InitRec(no, yes.right + 20 + no.dai / 2, Big.top + 50);
					outtextxy(Big.left + 20, Big.top + 5, "Ban co muon ket thuc?");
					outtextxy(yes.left + 10, yes.top + 5, "Yes");
					outtextxy(no.left + 10, no.top + 5, "No");
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
						InitCircle(click[i - 1][j], 1);
						choose[i - 1] = j + 1;

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
	currentDiem = (socaudung * 10) / ((float)realQues);
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

	InitRec(cauhoi, tamX, tamY);
	Write(CauHoi.cauhoi, cauhoi.left + 5, cauhoi.top + 5, (cDai-10)/12);
	for (int i = 1; i <= 4; i++) {
		traloi[i - 1].dai = cDai;
		traloi[i - 1].rong = (int)(strlen(CauHoi.traloi[i - 1])) / ((cDai-10)/12);
		traloi[i-1].rong+=1;
		traloi[i-1].rong*=30;

		if (i == 1) {
			tamY = cauhoi.bottom + 30 + traloi[i - 1].rong / 2;
		} else {
			tamY = traloi[i - 2].bottom + 30 + traloi[i - 1].rong / 2;
		}
		InitRec(traloi[i - 1], tamX, tamY);

		Write(CauHoi.traloi[i - 1], traloi[i - 1].left + 5, traloi[i - 1].top + 5, (cDai-10)/12);
		click[i - 1].bk = 10;
		click[i - 1].y = tamY;
		click[i - 1].x = cauhoi.left - 30;

		//circle(click[i - 1].x, click[i - 1].y, click[i - 1].bk);

	}
	for (int i = 1; i <= 4; i++) {
		if (type != i) {
			InitCircle(click[i - 1], -1);
		} else {
			InitCircle(click[i - 1], 1);
		}
	}

}

void Write(char *s, int x, int y, int dai) {
	string ss;
	int vtriX, vtriY;
	vtriX = x;
	vtriY = y;
//	outtextxy(x, y, &s[0]);
//	return;
	//	/*
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

void HieuUngNhap(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS, int type) {
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
void HieuUngNhaps(Login log, string &s, int &indexX, int &indexY, int &moux, int &mouy, int disChar, int maxS){
	
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
	c = getch();
	if ( ((ll)s.size() > 0 && c == BACKSPACE)) {
		//mk.pop_back();
		s.erase(s.size() - 1);
		if(indexX==log.left+10){
			indexY-=30;
			indexX=log.right-disChar -5;
		}
		else indexX -= disChar;
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
		if(indexX + disChar + 5 >=log.right){
			indexX=log.left+10;
			indexY+=30;
		}
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

	InitCircle(nam, WHITE);
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
				HieuUngNhap(ma, Sma, indexXMa, indexYMa, moux, mouy, 15, 18);
			} else if (IsClickRec(ho, moux, mouy)) {
				HieuUngNhap(ho, Sho, indexXHo, indexYHo, moux, mouy, 15, 6, 0);
			} else if (IsClickRec(ten, moux, mouy)) {
				HieuUngNhap(ten, Sten, indexXTen, indexYTen, moux, mouy, 15, 18, 3);
			} else if (IsClickRec(password, moux, mouy)) {
				HieuUngNhap(password, Spassword, indexXPass, indexYPass, moux, mouy, 15, 18);
			} else if (IsClickCircle(nam, moux, mouy) || IsClickCircle(nu, moux, mouy)) {
				if (IsClickCircle(nam, moux, mouy) || Trai == false) {
					InitCircle(nam, WHITE);
					InitCircle(nu, -1);
					Trai = !Trai;
				} else if (IsClickCircle(nu, moux, mouy) || Trai == true) {
					InitCircle(nu, WHITE);
					InitCircle(nam, -1);
					Trai = !Trai;
				}
				moux = -1, mouy = -1;
			} else if (IsClickRec(apply, moux, mouy)) {
				*inf->sv = SinhVien(Sma, Sho, Sten, Spassword, Trai);
				*inf->lopTemp = Lop(malop, tenlop);
				int isAdd = inf->AddSv(inf->sv, inf->lopTemp);

				outtextxy(password.left + 20, password.bottom + 60, "                                            ");
				if (isAdd == 1) {
					outtextxy(password.left + 20, password.bottom + 60, "Them thanh cong");
				} else {
					outtextxy(password.left + 20, password.bottom + 60, "Them that bai");
				}
				moux = -1;
				mouy = -1;
			} else if (IsClickRec(cancel, moux, mouy)) {

				putimage(0, 0, arrow, COPY_PUT);
				return;
			}
			//cc
		}

}
void InDS(string malop, string maMH, int maxInPage, int X) {
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
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
			outtextxy(next.left + 20, next.top + 5, "NEXT");
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50);
			outtextxy(previous.left + 20, previous.top + 5, "PREV");
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20);
		outtextxy(exit.left + 10, exit.top + 5, "Thoat");
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

		char cDiem[10];
		for (int i = index; i < sosv && i < index + maxInPage; i++) {
			//	cout<<i<<endl;
			memset(cDiem, 0, sizeof cDiem);
			itoa(sv[i]->diem[indexMH]->diemThi, cDiem, 10);

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
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
			outtextxy(next.left + 20, next.top + 5, "NEXT");
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50);
			outtextxy(previous.left + 20, previous.top + 5, "PREV");
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20);
		outtextxy(exit.left + 10, exit.top + 5, "Thoat");
		InitRec(del, exit.left - del.dai / 2, exit.top + del.rong / 2);
		outtextxy(del.left + 10, del.top + 5, "Xoa");

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
						mark[t] = 1;
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
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
			outtextxy(next.left + 20, next.top + 5, "NEXT");
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - previous.dai / 2, getmaxy() - previous.rong - 50);
			outtextxy(previous.left + 20, previous.top + 5, "PREV");
		}
		InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 20);
		outtextxy(exit.left + 10, exit.top + 5, "Thoat");
		InitRec(fix, exit.left - fix.dai / 2, exit.top + fix.rong / 2);
		outtextxy(fix.left + 10, fix.top + 5, "Sua");

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


		for (int i = index; i < sosv && i < index + maxInPage; i++) {
			//	cout<<i<<endl;

			click[i].y = indexY + 5;
			if(choose==i) InitCircle(click[i], 1);
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
						InitCircle(click[t],1);
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

	InitCircle(nam, WHITE);
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
				InitCircle(nam, WHITE);
				InitCircle(nu, -1);
				Trai = !Trai;
			} else if (IsClickCircle(nu, moux, mouy) || Trai == true) {
				InitCircle(nu, WHITE);
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
				for(int i=0;i<SOMON;i++){
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
				}
				else  {
					*inf->lopTemp = Lop(malop,tenlop);
					inf->AddSv(sv,inf->lopTemp);
					//outtextxy(apply.left , apply.top -30, " Sua That Bai !");
					WindowThongBao("Sua That Bai !");
				}
				
				for(int i=0;i<inf->GetSoLop();i++){
					DSSV *ds=inf->lop[i]->dssv;
					bool flag=false;
					while(ds!=NULL){
						if(ds->sv->maSV==Sma){
							flag=true;
							for(int j=0;j<SOMON;j++){
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
	InitRec(ThongBao, getmaxx() / 2, getmaxy() / 2);
	InitRec(Yes, ThongBao.left + 70, ThongBao.bottom - Yes.rong - 10);
	InitRec(No, ThongBao.right - 70, ThongBao.bottom - Yes.rong - 10);

	outtextxy(ThongBao.left + 10, ThongBao.top + 10, &s[0]);
	outtextxy(Yes.left + 10, Yes.top + 5, "Yes");
	outtextxy(No.left + 10, No.top + 5, "No");
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
	InitRec(ThongBao, getmaxx() / 2, getmaxy() / 2);
	InitRec(Ok, getmaxx() / 2, ThongBao.bottom - Ok.rong - 20);
	outtextxy(ThongBao.left + 10, ThongBao.top + 10, &s[0]);
	outtextxy(Ok.left + 10, Ok.top + 5, "OK");
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
	Login big, ok , Maxtime, Maxcau;
	big.dai=getmaxx()/4;
	big.rong=50*SOMON+20*SOMON;
	ok.dai=80;
	ok.rong=50;

	Maxcau.dai = Maxtime.dai = 90;
	Maxcau.rong = Maxtime.rong = 40;


	InitRec(big,getmaxx()/2,getmaxy()/2);
	InitRec(ok,getmaxx() - ok.dai/2 - 30,getmaxy() - ok.rong/2 -30);

	InitRec(Maxcau, big.right + Maxcau.dai/2 + 140, big.top + Maxcau.rong/2);
	outtextxy(Maxcau.left - 70, Maxcau.top + 5, "So Cau");

	InitRec(Maxtime, big.right + Maxtime.dai/2  + 140, Maxcau.bottom + 30);
	outtextxy(Maxtime.left - 90, Maxtime.top + 5, "Thoi Gian");

	outtextxy(ok.left+5,ok.top + 7,"OK");

	CircleClick *click = new CircleClick[SOMON];
	for(int i=0; i<SOMON; i++) {
		click[i].bk=10;
		click[i].x=big.left+10;
	}
	int indexY=big.top+20;
	for(int i=0; i<SOMON; i++) {
		click[i].y=indexY + 5;
		outtextxy(big.left+30,indexY,&inf->monHoc[i]->tenMH[0]);
		indexY+=30;
	}

	for(int i=0; i<SOMON; i++) {
		if(i==MON_HIEN_TAI) {
			InitCircle(click[i],WHITE);
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
			} else return;
			moux=mouy=-1;
			continue;
		} else if (IsClickRec(Maxcau, moux, mouy)) {
			HieuUngNhap(Maxcau, socau, indexXCau, indexYCau, moux, mouy, 15, 3, 1);
			if (socau.size() != 0) {
				int temp;
				temp = atoi((char*)socau.c_str());
				if(temp>0) SOCAU=temp;
			}
			continue;
		} else if (IsClickRec(Maxtime, moux, mouy)) {
			HieuUngNhap(Maxtime, sophut, indexXTime, indexYTime, moux, mouy, 15, 3, 1);
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
				break;
			}
		}
		if(isClick) {
			isClick=true;
			for(int i=0; i<SOMON; i++) {
				if(chon==i) InitCircle(click[i],WHITE);
				else InitCircle(click[i],-1);
			}
			moux=mouy=-1;
		}

	}

}
void WindowGV() {
	cleardevice();
	Login maLop, tenLop;
	Login choose, inDsLop, SV, themSv, xoaSv, suaSv, NhapMon, Maxtime, Maxcau, exit;
	Login tha;
	int tamX;

	string currentMaLop = "", currentTenLop = "", socau = "", sophut = "";
	const string inDs = "In danh sach";
	const string SinhVien = "Sinh vien";
	const string addMh = "Them mon hoc";
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

	choose.dai = inDsLop.dai = SV.dai = NhapMon.dai = themSv.dai = xoaSv.dai = suaSv.dai = 200;
	choose.rong = 50;
	inDsLop.rong = SV.rong = NhapMon.rong = themSv.rong = xoaSv.rong = suaSv.rong = 50;

	//tha.dai=30;
	//tha.rong=choose.rong;
	//-----------------------------------------------------------------------------------


	tamX = 30 + choose.dai / 2;
	InitRec(maLop, tamX + 50, maLop.rong / 2 + 10);
	outtextxy(maLop.left - 70, maLop.top + 5, "Ma Lop");
	InitRec(tenLop, maLop.right + tenLop.dai / 2 + 100, maLop.top + tenLop.rong / 2);
	outtextxy(maLop.right + 10, maLop.top + 5, "Ten Lop");

	InitRec(choose, tamX, maLop.bottom + 60);
	int dis = inDsLop.rong / 2;
	int tamY = choose.bottom + 20;
	tamY += dis;
	InitRec(inDsLop, tamX, tamY);
	outtextxy(inDsLop.left + 20, inDsLop.top + 10, &inDs[0]);


	tamY = dis + inDsLop.bottom;
	InitRec(SV, tamX, tamY);
	outtextxy(SV.left + 20, SV.top + 10, &SinhVien[0]);

	tamY = dis + SV.bottom;
	InitRec(NhapMon, tamX, tamY);
	outtextxy(NhapMon.left + 20, NhapMon.top + 10, &addMh[0]);

//	InitRec(Maxcau, tamX + 40, NhapMon.bottom + 30);
//	outtextxy(Maxcau.left - 70, Maxcau.top + 5, "So Cau");

//	InitRec(Maxtime, tamX + 40, Maxcau.bottom + 30);
//	outtextxy(Maxtime.left - 90, Maxtime.top + 5, "Thoi Gian");

	InitRec(exit, getmaxx() - exit.dai - 50, getmaxy() - exit.rong - 40);
	outtextxy(exit.left + 5, exit.top + 5, "Thoat");
	//------------------------------------------------------------------

	int maxS = 13;
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
		} else if (IsClickRec(tenLop, moux, mouy)) {
			HieuUngNhap(tenLop, currentTenLop, indexXTenLop, indexYTenLop, moux, mouy, disChar, maxS, 2);
		} else if (IsClickRec(exit, moux, mouy)) {
			return;
		} else { //cc

			int chooseX = choose.left + 10, chooseY = choose.top + 20;
			string xoa = "                                      ";
			if (IsClickRec(inDsLop, moux, mouy)) {
				//		outtextxy(0,10,"  ");
				//		outtextxy(0,10,"1");
				outtextxy(exit.left - 15, exit.top - 25, "                                                        ");
				outtextxy(chooseX, chooseY, &xoa[0]);
				outtextxy(chooseX, chooseY, &inDs[0]);


				if (inf->TestLop(currentMaLop) != -1) {
					InDS(currentMaLop, inf->monHoc[0]->maMH, 10, 100);
				} else { // khong co lop
					WindowThongBao("Lop khong ton tai");
				}
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

				InitRec(themSv, SV.right + themSv.dai / 2, SV.top + SV.rong / 2);
				InitRec(xoaSv, themSv.right + xoaSv.dai / 2, themSv.top + xoaSv.rong / 2);
				InitRec(suaSv, xoaSv.right + suaSv.dai / 2, xoaSv.top + suaSv.rong / 2);

				outtextxy(themSv.left + 10, themSv.top + 5, &ThemSV[0]);
				outtextxy(xoaSv.left + 10, xoaSv.top + 5, &XoaSV[0]);
				outtextxy(suaSv.left + 10, suaSv.top + 5, &SuaSV[0]);

				int xx = -1, yy = -1;
				while (1) {
					delay(0.0001);
					if (ismouseclick(WM_LBUTTONDOWN)) {
						xx = mousex(), yy = mousey();
						clearmouseclick(WM_LBUTTONDOWN);

						if (IsClickRec(themSv, xx, yy)) {
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


	}

}

void WindowThemCauHoi(){
	
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


	InitRec(big,getmaxx()/2,getmaxy()/2);
	InitRec(ok,big.right-ok.dai/2,big.bottom+ok.rong/2);
	outtextxy(ok.left+5,ok.top+5,"Ok");
	
	CircleClick *clk = new CircleClick[SOMON];
	for(int i=0; i<SOMON; i++) {
		clk[i].bk=10;
		clk[i].x=big.left+10;
	}
	int indexY=big.top+20;
	for(int i=0; i<SOMON; i++) {
		clk[i].y=indexY + 5;
		outtextxy(big.left+30,indexY,&inf->monHoc[i]->tenMH[0]);
		indexY+=30;
	}

	for(int i=0; i<SOMON; i++) {
		if(i==MON_HIEN_TAI) {
			InitCircle(clk[i],WHITE);
		} else InitCircle(clk[i],-1);
	}
	int xx=-1,yy=-1;
	while(1){
		delay(0.00001);
		if(ismouseclick(WM_LBUTTONDOWN)){
			xx=mousex(),yy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
			bool chon=false;
			for(int i=0;i<SOMON;i++){
				if(IsClickCircle(clk[i],xx,yy)){
					monHienTai=i;
					chon=true;
					break;
				}
			}
			if(chon){
				for(int i=0;i<SOMON;i++){
					if(monHienTai==i){
						InitCircle(clk[i],WHITE);
					}
					else InitCircle(clk[i],-1);
				}
			}
			
			if(IsClickRec(ok,xx,yy)){
				break;
			}
		}
	}

	cleardevice();
	/////////------------------------------------------------------------------//////
	
	string Scauhoi="",SdapanA="",SdapanB="",SdapanC="",SdapanD="";
	Login cauHoi,dapanA,dapanB,dapanC,dapanD,them,cancel;
	CircleClick click[4];
	
	for(int i=0;i<4;i++){
		click[i].bk=15;
	}
		
	cauHoi.dai = dapanA.dai = dapanB.dai = dapanC.dai = dapanD.dai = getmaxx()/2-100;
	cauHoi.rong = dapanA.rong = dapanB.rong = dapanC.rong = dapanD.rong = 30*3 + 10;//30:kcach  3: so dong toi da
	them.dai = cancel.dai = 80;
	them.rong = cancel.rong =50;
	
	const int maxS = (cauHoi.dai -10)/25 *3 + 10;
	
	InitRec(cauHoi,getmaxx()/2,cauHoi.rong/2 + 50);
	
	InitRec(dapanA,getmaxx()/2,cauHoi.bottom+dapanA.rong/2+30);
	InitRec(dapanB,getmaxx()/2,dapanA.bottom+dapanB.rong/2+20);
	InitRec(dapanC,getmaxx()/2,dapanB.bottom+dapanC.rong/2+20);
	InitRec(dapanD,getmaxx()/2,dapanC.bottom+dapanD.rong/2+20);
	
	InitRec(cancel,getmaxx()-cancel.dai/2-30,getmaxy()-cancel.rong/2-30);
	InitRec(them,cancel.left-them.dai/2,cancel.top+them.rong/2);
	outtextxy(them.left+10,them.top+5,"Them");
	outtextxy(cancel.left+10,cancel.top+5,"Huy bo");
	
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
	for(int i=0;i<4;i++){
		InitCircle(click[i],-1);
	}
	while(1){
		delay(0.000001);
		if(ismouseclick(WM_LBUTTONDOWN)){
			moux=mousex();
			mouy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(IsClickRec(cauHoi,moux,mouy)){
			HieuUngNhaps(cauHoi,Scauhoi,indexXQues,indexYQues,moux,mouy,disChar,maxS);
		}
		else if(IsClickRec(dapanA,moux,mouy)){
			cout<<"a"<<endl;
			HieuUngNhaps(dapanA,SdapanA,indexXA,indexYA,moux,mouy,disChar,maxS);
		}
		else if(IsClickRec(dapanB,moux,mouy)){
			cout<<"b"<<endl;
			HieuUngNhaps(dapanB,SdapanB,indexXB,indexYB,moux,mouy,disChar,maxS);
		}
		else if(IsClickRec(dapanC,moux,mouy)){
			cout<<"c"<<endl;
			HieuUngNhaps(dapanC,SdapanC,indexXC,indexYC,moux,mouy,disChar,maxS);
		}
		else if(IsClickRec(dapanD,moux,mouy)){
			cout<<"d"<<endl;
			HieuUngNhaps(dapanD,SdapanD,indexXD,indexYD,moux,mouy,disChar,maxS);
		}
		bool isclick = false;
		for(int i=0;i<4;i++){
			if(IsClickCircle(click[i],moux,mouy)){
				isclick = true;
				dapan=i;
				moux=-1,mouy=-1;
				break;
			}
		}
		if(isclick){
			for(int i=0;i<4;i++){
				if(dapan == i){
					InitCircle(click[i],WHITE);
				}
				else{
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
		*inf->lopTemp = Lop("CC", "CNTT");
		inf->AddSv(inf->sv, inf->lopTemp);
	}
}
