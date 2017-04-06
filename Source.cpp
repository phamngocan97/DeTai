
#include<bits/stdc++.h>
#include"winbgim.h"
/*
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int BROWN = 6;
const int LIGHTGRAY = 7;
const int DARKGRAY = 8;
const int LIGHTBLUE = 9;
const int LIGHTGREEN = 10;
const int LIGHTCYAN = 11;
const int LIGHTRED = 12;
const int LIGHTMAGENTA = 13;
const int YELLOW = 14;
const int WHITE = 15;
*/
/*
enum fill_styles
{
EMPTY_FILL,
SOLID_FILL,
LINE_FILL,
LTSLASH_FILL,
SLASH_FILL,
BKSLASH_FILL,
LTBKSLASH_FILL,
HATCH_FILL,
XHATCH_FILL,
INTERLEAVE_FILL,
WIDE_DOT_FILL,
CLOSE_DOT_FILL,
USER_FILL
};
*/
using namespace std;

typedef long long ll;
enum {
	ENTER = 13,
	BACKSPACE = 8,
	TAB = 9,
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
class QuesAndAns {
public:
	string cauhoi, traloi;
	int dapan;
};

int linex[] = { -1,0,1,1,1,0,-1 - 1 };
int liney[] = { -1,-1,-1,0,1,1,1,0 };

void Swap(string&, string&);
void BFS(int x, int y, int x1, int y1, int R);
void InitRec(Login &log, int tamX, int tamY);
void DrawLogin(Login &login, Login &id, Login &pass);
bool IsClickId(Login id, int x, int y);
bool IsClickPass(Login pass, int x, int y);
void DangNhap(Login login, Login id, Login pass);
int TestId(string id, string pass);
void InitQuestion();
void DrawTracNghiem(QuesAndAns Infor);
int main() {
	int bg = 0, bm = 0;
	//initgraph(&bg, &bm, " ");
	initwindow(1200, 550);
	//------------------------------------------------------------//

	Login login, id, pass;

	DrawLogin(login, id, pass);
	DangNhap(login, id, pass);

	cleardevice();
	circle(getmaxx() / 2, getmaxy() / 2, 50);
	InitQuestion();
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
bool IsClickId(Login id, int x, int y) {
	if (x <= id.right&&x >= id.left) {
		if (y <= id.bottom&&y >= id.top) return true;
	}
	return false;
}
bool IsClickPass(Login pass, int x, int y) {
	if (x <= pass.right&&x >= pass.left) {
		if (y <= pass.bottom&&y >= pass.top) return true;
	}
	return false;
}

void DangNhap(Login login, Login id, Login pass) {
	bool signIn = false;
	string tk = "", mk = "";
	int vtriIdx, vtriIdy, vtriPassx, vtriPassy;
	int disId, disPass;
	disId = 15;
	disPass = 5;

	vtriIdx = id.left + 1;
	vtriIdy = id.top + 5;
	vtriPassx = pass.left + 1;
	vtriPassy = pass.top + 5;

	while (!signIn) {
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)) {

			if (IsClickId(id, mousex(), mousey())) {
				char c;
				bool flag = false;
				bool outId = false;
				while (!kbhit()) {
					if (IsClickPass(pass, mousex(), mousey())) {
						outId = true;
						break;
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
						if (TestId(tk, mk)) {
							signIn = true;
							break;
						}
						else {
							outtextxy(login.bottom + 20, login.left + 50, "Sai ID/PassWord");
						}
					}
					else if ((ll)tk.size()>0 && c == BACKSPACE) {
						//tk.pop_back();
						tk.erase(tk.size() - 1);
						vtriIdx -= disId;
						outtextxy(vtriIdx, vtriIdy, "    ");
					}
					else {
						if (c == BACKSPACE) continue;
						tk = tk + c;
						outtextxy(vtriIdx, vtriIdy, &tk[tk.size() - 1]);
						vtriIdx += disId;
					}
				}
			}
			if (IsClickPass(pass, mousex(), mousey())) {
				char c;
				bool flag = false;
				bool outPass = false;
				while (!kbhit()) {
					if (IsClickId(id, mousex(), mousey())) {
						outPass = true;
						break;
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
						if (TestId(tk, mk)) {
							signIn = true;
							break;
						}
						else {
							outtextxy(login.left + 20, login.bottom + 50, "Sai ID/PassWord");
						}
					}

					else if ((ll)mk.size()>0 && c == BACKSPACE) {
						//mk.pop_back();
						mk.erase(mk.size() - 1);
						vtriPassx -= disPass;
						outtextxy(vtriPassx, vtriPassy, " ");
					}
					else {
						if (c == BACKSPACE) continue;
						outtextxy(vtriPassx, vtriPassy, "*");
						vtriPassx += disPass;
						mk += c;
					}
				}
			}
		}
	}

}
int TestId(string id, string pass) {
	if (id == "GV"&& pass == "GV") {
		return 1;
	}
	return 0;
}

void InitRec(Login &log, int tamX, int tamY) {

	log.left = tamX - log.dai / 2;
	log.right = tamX + log.dai / 2;
	log.top = tamY - log.rong / 2;
	log.bottom = tamY + log.rong / 2;
	rectangle(log.left, log.top, log.right, log.bottom);

}

void InitQuestion() {
	fstream file;
	file.open("Ques.inp", ios::in | ios::binary);

	int numQues, realQues;
	realQues = 20;
	file.read((char*)&numQues, sizeof(int));

	QuesAndAns Infor[20];
	string *ques = new string[numQues];
	string *ansSentence = new string[numQues];
	int *ans = new int[numQues];

	for (int i = 0; i < numQues; i++) {
		file.read((char*)&ques[i], sizeof(string));
	}
	for (int i = 0; i < numQues; i++) {
		file.read((char*)&ansSentence[i], sizeof(string));
	}
	for (int i = 0; i < numQues; i++) {
		file.read((char*)&ans[i], sizeof(int));
	}
	//file.read(reinterpret_cast<char*>(&s), sizeof(s));
	srand(time(0));
	for (int i = 1; i <= realQues; i++) {
		int k = rand() % (numQues - i);
		Swap(ques[k], ques[numQues - i]);
		Swap(ansSentence[k], ansSentence[numQues - i]);
		swap(ans[k], ans[numQues - i]);

		Infor[i - 1].cauhoi = ques[numQues - i];

		Infor[i - 1].traloi.resize(4);
		Infor[i - 1].traloi = ansSentence[numQues - i];

		Infor[i - 1].cauhoi = ques[numQues - i];
	}

	for (int i = 1; i <= realQues; i++) {
		cleardevice();
		DrawTracNghiem(Infor[i - 1]);
		while (!kbhit()) delay(0.001);
	}
}
void DrawTracNghiem(QuesAndAns Infor) {
	const int disToTop = 100;
	Login cauhoi,traloi[4];
	const int tamX = getmaxx() / 2;
	const int cDai = getmaxx() / 4;
	int crongQues = (int)Infor.cauhoi.length() * 5 / cDai + 10;
	int tamY = disToTop + crongQues / 2;
	cauhoi.dai = cDai;
	cauhoi.rong = crongQues;
	
	InitRec(cauhoi, tamX, tamY);

	for (int i = 1; i <= 4; i++) {
		traloi[i-1].dai = cDai;
		traloi[i-1].rong = (int)Infor.traloi.length() * 5 / cDai + 10;

		if (i == 1) {
			tamY = cauhoi.bottom + 30 + traloi[i - 1].rong / 2;
		}
		else {
			tamY = traloi[i - 2].bottom + 30 + traloi[i - 1].rong / 2;
		}
		InitRec(traloi[i - 1], tamX, tamY);
	}

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
void Swap(string &s1, string &s2) {
	string s = s1;
	s1 = s2;
	s2 = s;
}
