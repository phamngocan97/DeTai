
#include<bits/stdc++.h>
#include<winbgim.h>
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

enum {
	ENTER =13,
	BACKSPACE =8,
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

int linex[] = { -1,0,1,1,1,0,-1 - 1 };
int liney[] = { -1,-1,-1,0,1,1,1,0 };

void BFS(int x, int y, int x1, int y1, int R);
void InitRec(Login &log, int tamX, int tamY);
void DrawLogin(Login &login, Login &id, Login &pass);
bool IsClickId(Login id, int x, int y);
bool IsClickPass(Login pass, int x, int y);
void DangNhap(Login id, Login pass);
bool TestId(string id, string pass);
int main() {
	int bg = 0, bm = 0;
	initgraph(&bg, &bm, " ");
	initwindow(1200, 550);
	//------------------------------------------------------------//

	Login login, id, pass;

	DrawLogin(login, id, pass);
	DangNhap(id, pass);

	cleardevice();
	circle(getmaxx() / 2, getmaxy() / 2, 50);
	while (!kbhit()) {
		
	}
	closegraph();

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
	outtextxy(login.left + 20, id.top + 15, "Tai Khoan");
	outtextxy(login.left + 20, pass.top + 15, "Mat Khau");
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

void DangNhap(Login id,Login pass) {
	bool signIn = false;
	string tk = "", mk = "";
	int vtriIdx, vtriIdy, vtriPassx, vtriPassy;
	vtriIdx = id.left + 1;
	vtriIdy = id.top + 5;
	vtriPassx = pass.left + 1;
	vtriPassy = pass.top + 5;

	while (!signIn) {
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
						if (TestId(tk, mk)) signIn = true;
						break;
					}
					else if (tk.size()>0&&c == BACKSPACE) {
						tk.pop_back();
						vtriIdx -= 10;
						outtextxy(vtriIdx, vtriIdy, "    ");
					}
					else {
						if (c == BACKSPACE) continue;
						tk = tk + c;
						outtextxy(vtriIdx, vtriIdy, &tk[tk.size() - 1]);
						vtriIdx += 10;
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
						if (TestId(tk, mk)) signIn = true;
						break;
					}

					else if (mk.size()>0 && c == BACKSPACE) {
						mk.pop_back();
						vtriIdx -= 10;
						outtextxy(vtriIdx, vtriIdy, "    ");
					}
					else {
						if (c == BACKSPACE) continue;
						outtextxy(vtriPassx, vtriPassy, "*");
						vtriPassx += 5;
						mk += c;
					}
				}
			}
		}
	}

}
bool TestId(string id, string pass) {
	if (id == "GVGV"&& pass == "123") {
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
