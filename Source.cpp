//#include"graphics.h"
#include"winbgim.h"
#include"Infor.h"
using namespace std;

typedef long long ll;
class SinhVien;
class DSSV;
class DSDiemThi;
enum{
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
enum{
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
	DOWN =80,
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
	//string cauhoi, traloi[4];
	char cauhoi[1000];
	char traloi[4][1000];
	int dapan;
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

void InitSoCau(Login &soCau,Login clock,int cauDaLam,int realQues);
void DrawLogin(Login &login, Login &id, Login &pass);
int DangNhap(Login login, Login id, Login pass);
int TestId(string id, string pass);
void InitQuestion(int realQues);
void DrawTracNghiem(QuesAndAns Infor, CircleClick *click,int type);
void Write(char *s, int x, int y, int dai);

void ProcessGV(string lop,string malop,int type,int toadoX);
void HieuUngNhap(Login log,string &s,int &indexX,int &indexY,int &moux,int &mouy,int disChar, int maxS,int type=-1);
void InDS(string malop,string maMH,int maxInPage,int X);
void WindowGV();

void LoadDSSV();

Infor *inf;
string currentId;
float currentDiem;
int TIME=45,SOCAU=20;
bool OVERTIME=false;
int main() {
	inf=new Infor(2,2);	
	int bg = 0, bm = 0;
	//initgraph(&bg, &bm, " ");
	initwindow(1200, 550);
	//------------------------------------------------------------//

	
	
	Login login, id, pass;
	int typeSign;

	//InitQuestion();	
	LoadDSSV();
	while(1){
		cleardevice();
		DrawLogin(login, id, pass);
		typeSign = DangNhap(login, id, pass);

		if(typeSign==-1){
			WindowGV();
		}
		if(typeSign>=0){
			//cout<<"sdfg";
			InitQuestion(SOCAU);	
			inf->UpdateDiem(inf->lop[typeSign]->maLop,currentId,"a",currentDiem);
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
	int maxId=12,maxPass=24;
	int typeSign;
	bool signIn = false,taikhoan=false,matkhau=false;
	string tk = "", mk = "";
	int vtriIdx, vtriIdy, vtriPassx, vtriPassy;
	int disId, disPass;
	int moux=0,mouy=0;
	disId = 15;
	disPass = 8;

	vtriIdx = id.left + 1;
	vtriIdy = id.top + 5;
	vtriPassx = pass.left + 1;
	vtriPassy = pass.top + 5;

	while (!signIn) {
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)) {
			moux=mousex(),mouy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
			if (taikhoan || IsClickRec(id, moux, mouy)) {
				taikhoan=true;
				matkhau=false;
				char c;
				bool flag = false;
				bool outId = false;
				while (!kbhit()) {
					if(ismouseclick(WM_LBUTTONDOWN)){
						int xx,yy;
						xx=mousex(),yy=mousey();
						if(IsClickRec(pass,xx,yy)){
							moux=xx;
							mouy=yy;
							outId=true;
							break;
						}
						clearmouseclick(WM_LBUTTONDOWN)	;
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
						typeSign=TestId(tk,mk);
						if (typeSign!=-2) {
							signIn = true;	
							currentId=tk;						
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
						if (c == BACKSPACE || (ll)tk.size()>=maxId) continue;
						if(!isprint(c)){
							c=getch();
							continue;
						}
						tk = tk + c;
						outtextxy(vtriIdx, vtriIdy, &tk[tk.size() - 1]);
						vtriIdx += disId;
					}
				}
			}
			if (matkhau || IsClickRec(pass, moux, mouy) ){
				taikhoan=false;
				matkhau=true;
				char c;
				bool flag = false;
				bool outPass = false;
				while (!kbhit()) {
					if(ismouseclick(WM_LBUTTONDOWN)){
						int xx,yy;
						xx=mousex(),yy=mousey();
						if(IsClickRec(id,xx,yy)){
							moux=xx;
							mouy=yy;
							outPass=true;
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
						typeSign=TestId(tk,mk);
						if (typeSign!=-2) {
							signIn = true;
							currentId=tk;
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
						outtextxy(vtriPassx, vtriPassy, "    ");
					}
					else {
						if (c == BACKSPACE || (ll)mk.size()>=maxPass) continue;
								
						if(!isprint(c)){
							c=getch();
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

	}
	else {
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
	}
	else{
		bool test=false;
		for(int i=0;i<inf->GetSoLop();i++){
		//	cout<<inf->GetSoLop()<<" ";
			test=inf->TestSV(inf->lop[i],id);
			if(!test){
			//	cout<<i;
			
				return i;	
			}
			
		}
	}
	return -2;
}

void InitSoCau(Login &soCau,Login clock,int cauDaLam,int realQues){
	InitRec(soCau,getmaxx()-30-soCau.dai/2,clock.bottom+soCau.rong/2+10+soCau.rong/2);
	char temp[1000],sumCau[1000];
	memset(temp,0,sizeof temp);
	memset(sumCau,0,sizeof sumCau);
	itoa(realQues,sumCau,10);
	temp[0]='/';
	strcat(temp,sumCau);
	outtextxy(soCau.right-soCau.dai/2,soCau.top+soCau.rong/2,&temp[0]);
	itoa(cauDaLam,temp,10);
	outtextxy(soCau.left+30,soCau.top+soCau.rong/2,&temp[0]);
}

void InitQuestion(int realQues) {
	void *screen;
	int size=imagesize(0,0,getmaxx(),getmaxy());
	screen=malloc(size);
	
	inf->AddMh("ma","ten");
	fstream file;
	file.open("Ques.inp", ios::in | ios::binary);
	
	int numQues;
	file.read((char*)&numQues, sizeof(int));

	CircleClick **click = new CircleClick*[numQues];
	QuesAndAns CauHoi[20];
	
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
		int k;
		file.read((char*)&k, sizeof(int));
		file.read(ques[i], k + 1);
	}
	for (int i = 0; i < numQues; i++) {
		for (int j = 0; j < 4; j++) {
			int k;
			file.read((char*)&k, sizeof(int));
			file.read(ansSentence[i][j], k + 1);
		}
	}
	for (int i = 0; i < numQues; i++) {
		file.read((char*)&ans[i], sizeof(int));
	}
	//file.read(reinterpret_cast<char*>(&s), sizeof(s));
	srand(time(0));
	for (int i = 1; i <= realQues; i++) {
		int k = rand() % (numQues - i);
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
	
	for(int i=0;i<realQues;i++){
		char c[100];
		itoa(i+1,c,10);
		strcat(c,"./  ");
		strcat(c,CauHoi[i].cauhoi);
		strcpy(CauHoi[i].cauhoi,c);
		for(int j=0;j<4;j++){
			for(int k=strlen(CauHoi[i].traloi[j])+3;k>=3;k--){
				CauHoi[i].traloi[j][k]=CauHoi[i].traloi[j][k-3];
			}
			CauHoi[i].traloi[j][0]=j+'A';
			CauHoi[i].traloi[j][1]='.';
			CauHoi[i].traloi[j][2]=' ';
			
		}
	}
	Login next, previous ,soCau,clock,ketThuc;
	next.dai = previous.dai = 90;
	next.rong = previous.rong =ketThuc.rong= 30;
	ketThuc.dai=120;
	
	soCau.dai=100;
	soCau.rong=60;
	clock.dai=100;
	clock.rong=50;
	bool isClick;
	int *choose = new int[realQues];
	for(int i=0;i<realQues;i++){
		choose[i]=-1;
	}

	clearmouseclick(WM_LBUTTONDOWN);
	int i=1,cauDaLam=0;
	
	getimage(0,0,getmaxx(),getmaxy(),screen);
	InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
	InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50);
	putimage(0,0,screen,COPY_PUT);
	
	while(1) {
		delay(0.00001);
		if(OVERTIME) break;
		isClick = false;
		cleardevice();
		
		DrawTracNghiem(CauHoi[i - 1], click[i - 1],choose[i-1]);
		
		InitRec(clock,getmaxx()-30-clock.dai/2,30+clock.rong/2);
		InitSoCau(soCau,clock,cauDaLam,realQues);

		if (i < realQues) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
			outtextxy(next.left + 20, next.top + 5, "NEXT");
		}
		if (i > 1) {
			InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50);
			outtextxy(previous.left + 20, previous.top + 5, "PREV");
		}
		InitRec(ketThuc,40,getmaxy()-ketThuc.rong/2-50);
		outtextxy(ketThuc.left+40,ketThuc.top+5,"Ket Thuc");
		
		while (1) {
			delay(0.00001);
			if(OVERTIME) break;
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (i<realQues&&IsClickRec(next, moux, mouy)) {
					//isClick = true;
					i++;
					break;
				}
				else if (i>1 && IsClickRec(previous, moux, mouy)) {
				//	isClick = true;
					i--;
					break;
				}
				else if(IsClickRec(ketThuc,moux,mouy)){
					getimage(0,0,getmaxx(),getmaxy(),screen);
					Login Big,yes,no;
					Big = Login(70,230);
					yes=Login(30,50);
					no=Login(30,50);
					
					
					InitRec(Big,ketThuc.right+Big.dai/2+30,getmaxy()-30-Big.rong/2);
					InitRec(yes,Big.left+130,Big.top+50);
					InitRec(no,yes.right+20+no.dai/2,Big.top+50);
					outtextxy(Big.left+20,Big.top+5,"Ban co muon ket thuc?");
					outtextxy(yes.left+10,yes.top+5,"Yes");
					outtextxy(no.left+10,no.top+5,"No");
					bool clickNo=false;
					int  _moux=-1,_mouy=-1;
					while(1){
						delay(0.00001);
						if(ismouseclick(WM_LBUTTONDOWN)){
							_moux=mousex();
							_mouy=mousey();
							clearmouseclick(WM_LBUTTONDOWN);
						}
						if(IsClickRec(yes,_moux,_mouy)){
							OVERTIME=TRUE;
							break;
						}
						else if(IsClickRec(no,_moux,_mouy)){
							clickNo=true;
							break;
						}
					}
					if(clickNo) putimage(0,0,screen,COPY_PUT);
				}
				bool chon=false;
				for(int j=0;j<4;j++){
					if (IsClickCircle(click[i - 1][j], moux, mouy)) {
						chon=true;
						break;
					}
				}
				
				for (int j = 0;chon && j < 4; j++) {
					if (IsClickCircle(click[i - 1][j], moux, mouy)) {
							if(choose[i-1]==-1){
								cauDaLam++;
								//InitSoCau(soCau,clock,cauDaLam,realQues);
							}
							InitCircle(click[i - 1][j], 1);
							choose[i-1] = j+1;
							
					}
					else {
						InitCircle(click[i - 1][j], -1);
						//choose[i] = 0;
					}
				}
				
			}
		}
		clearmouseclick(WM_LBUTTONDOWN);
	}
	
	int socaudung=0;
	for(int i=0;i<realQues;i++){
		if(choose[i]==CauHoi[i].dapan) socaudung++;
	}
	currentDiem=(socaudung*10)/((float)realQues);
	file.close();
}

void DrawTracNghiem(QuesAndAns CauHoi, CircleClick *click,int type) {
	const int disToTop = 100;
	
	Login cauhoi, traloi[4];
	//CircleClick click[4];
	const int tamX = getmaxx() / 2;
	const int cDai = getmaxx() / 2 - 100;
	int crongQues = (int)(strlen(CauHoi.cauhoi)) * 5 / cDai;
	crongQues += 3;
	crongQues *= 15;
	int tamY = disToTop + crongQues / 2;
	cauhoi.dai = cDai;
	cauhoi.rong = crongQues;

	InitRec(cauhoi, tamX, tamY);
	Write(CauHoi.cauhoi, cauhoi.left + 5, cauhoi.top + 5, cDai);
	for (int i = 1; i <= 4; i++) {
		traloi[i - 1].dai = cDai;
		traloi[i - 1].rong = (strlen(CauHoi.traloi[i - 1])) * 5 / cDai;
		traloi[i - 1].rong += 3;
		traloi[i - 1].rong *= 10;
		if (i == 1) {
			tamY = cauhoi.bottom + 30 + traloi[i - 1].rong / 2;
		}
		else {
			tamY = traloi[i - 2].bottom + 30 + traloi[i - 1].rong / 2;
		}
		InitRec(traloi[i - 1], tamX, tamY);

		Write(CauHoi.traloi[i - 1], traloi[i - 1].left + 5, traloi[i - 1].top + 5, cDai);
		click[i - 1].bk = 10;
		click[i - 1].y = tamY;
		click[i - 1].x = cauhoi.left - 30;
		
		//circle(click[i - 1].x, click[i - 1].y, click[i - 1].bk);
		
	}
	for (int i = 1; i <= 4; i++) {
		if (type != i){
		 InitCircle(click[i - 1], -1);
		}
		else{
		 InitCircle(click[i - 1], 1);
		}
	}

}

void Write(char *s, int x, int y, int dai) {
	string ss;
	int vtriX, vtriY;
	vtriX = x;
	vtriY = y;
	outtextxy(x, y, &s[0]);
	return;
//	/*
	for (int i = 0; i < strlen(s); i++) {
	//if (s[i] == '\0') return;
	if (vtriX + 5 >= dai) {
	vtriX = x;
	vtriY += 10;
	}
	ss.push_back(s[i]);
	outtextxy(vtriX, vtriY, &ss[ss.size()-1]);
	vtriX += 10;
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

void HieuUngNhap(Login log,string &s,int &indexX,int &indexY,int &moux,int &mouy,int disChar,int maxS,int type){
		char c;
		bool flag=false,out=false;
			while (!kbhit()) {			
				if(ismouseclick(WM_LBUTTONDOWN)){
						int xx,yy;
						xx=mousex(),yy=mousey();
						if(!IsClickRec(log,xx,yy)){
							out=true;
							moux=mousex(),mouy=mousey();
							break;
						}
						clearmouseclick(WM_LBUTTONDOWN)	;
					}
				
				if (flag) outtextxy(indexX, indexY, "|");
				else outtextxy(indexX, indexY, " ");
				
				flag = !flag;
				delay(400);
			}
			
			outtextxy(indexX, indexY, " ");
			if(out) return;
			c=getch();	
			if ((ll)s.size()>0 && c == BACKSPACE) {
				//mk.pop_back();
				s.erase(s.size() - 1);
				indexX -= disChar;
				outtextxy(indexX, indexY, "      ");
			}
			else {
				if(c==BACKSPACE || (ll)s.size()>=maxS) return;
				if(c==ENTER) return;
				if(!isprint(c)){
					c=getch();
					return;
				}
				if(type==1 && !(c<='9'&&c>='0')) return;
				if(type==0 && !((c<='Z'&&c>='A')||(c<='z'&&c>='A')) ) return;
				s.push_back(c);
				outtextxy(indexX,indexY,&s[s.size()-1]);
				indexX+=disChar;
			}
	
}

void ProcessGV(string tenlop,string malop,int type,int toadoX){
	
  void *arrow;
  unsigned int size;	   
   
   size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
   arrow = malloc(size);
   getimage(0, 0, getmaxx(), getmaxy(),arrow);
   cleardevice();
   //putimage(0,0,arrow,COPY_PUT);
	
	bool Trai=true;
	string Sma,Sho,Sten,Spassword;
	Login ma,ho,ten,password,apply,cancel;
	CircleClick nam,nu;

	ma.rong=ho.rong=ten.rong=password.rong=40;
	ma.dai=300;
	ho.dai=100;
	ten.dai=300;
	password.dai=300;
	
	apply.dai=cancel.dai=90;
	apply.rong=cancel.rong=30;
	
	int tamX=toadoX+80;
	
	InitRec(ma,tamX,ma.rong/2+30);
	InitRec(ho,ma.left+ho.dai/2,ma.bottom+50);
	InitRec(ten,tamX,ho.bottom+50);
	InitRec(password,tamX,ten.bottom+50);
	
	outtextxy(ma.left-130,ma.top+5,"Ma Sinh Vien");
	outtextxy(ho.left-130,ho.top+5,"Ho");
	outtextxy(ten.left-130,ten.top+5,"Ten");
	outtextxy(password.left-130,password.top+5,"PassWord");

	InitRec(cancel,getmaxx()-cancel.dai/2-50,getmaxy()-cancel.rong/2-50);
	outtextxy(cancel.left+20,cancel.top+5,"Cancel");
	
	InitRec(apply,cancel.left-50-apply.rong/2,getmaxy()-apply.rong/2-50);
	outtextxy(apply.left+20,apply.top+5,"Apply");
	
	nam.bk=nu.bk=10;
	nam.y=nu.y=password.bottom+30;
	nam.x=password.left+40;
	nu.x=nam.x+nam.bk+70;
	
	outtextxy(nam.x-nam.bk-40,nam.y-15,"Nam");
	outtextxy(nu.x-nu.bk-30,nu.y-15,"Nu");
	
	InitCircle(nam,WHITE);
	InitCircle(nu,-1);
	

	int moux=-1,mouy=-1;
	int indexXMa,indexXHo,indexXTen,indexXPass;
	int indexYMa,indexYHo,indexYTen,indexYPass;
	indexXHo=ho.left+5;
	indexXMa=ma.left+5;
	indexXTen=ten.left+5;
	indexXPass=password.left+5;
	
	indexYHo=ho.top+10;
	indexYMa=ma.top+10;
	indexYTen=ten.top+10;
	indexYPass=password.top+10;
	
	
	
	
	char c;	
	if(type==THEMSV);
	while(1){
		delay(0.00001);
		if(ismouseclick(WM_LBUTTONDOWN)){
			moux=mousex(),mouy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(IsClickRec(ma,moux,mouy)){
			HieuUngNhap(ma,Sma,indexXMa,indexYMa,moux,mouy,15,18);
		}
		else if(IsClickRec(ho,moux,mouy)){
			HieuUngNhap(ho,Sho,indexXHo,indexYHo,moux,mouy,15,6,0);
		}
		else if(IsClickRec(ten,moux,mouy)){
			HieuUngNhap(ten,Sten,indexXTen,indexYTen,moux,mouy,15,18,0);
		}
		else if(IsClickRec(password,moux,mouy)){
			HieuUngNhap(password,Spassword,indexXPass,indexYPass,moux,mouy,15,18);
		}
		else if(IsClickCircle(nam,moux,mouy)||IsClickCircle(nu,moux,mouy)){
				if(IsClickCircle(nam,moux,mouy)||Trai==false){
					InitCircle(nam,WHITE);
					InitCircle(nu,-1);
					Trai=!Trai;
				}
				else if(IsClickCircle(nu,moux,mouy)||Trai==true){
					InitCircle(nu,WHITE);
					InitCircle(nam,-1);
					Trai=!Trai;
				}
				moux=-1,mouy=-1;
		}
		else if(IsClickRec(apply,moux,mouy)){
			*inf->sv= SinhVien(Sma,Sho,Sten,Spassword,Trai);
			*inf->lopTemp = Lop(malop,tenlop);
			int isAdd=inf->AddSv(inf->sv,inf->lopTemp);
			
			outtextxy(password.left+20,password.bottom+60,"                                            ");
			if(isAdd==1){
				outtextxy(password.left+20,password.bottom+60,"Them thanh cong");
			}
			else{
				outtextxy(password.left+20,password.bottom+60,"Them that bai");
			}
			moux=-1;
			mouy=-1;
		}
		else if(IsClickRec(cancel,moux,mouy)){

			putimage(0,0,arrow,COPY_PUT);
			return;
		}
		//cc
	}
	
}
void InDS(string malop,string maMH,int maxInPage,int X){
	void *arrow;
   unsigned int size;	      
   size = imagesize(0, 0, getmaxx(), getmaxy());//trai-tren: 0-0....phai-duoi: maxx,maxy
   arrow = malloc(size);
   getimage(0, 0, getmaxx(), getmaxy(),arrow);
   cleardevice();
   
   /////-----------------------------------------------------------------------/
   //////////////////////
	int indexLop=inf->TestLop(malop);
	int sosv=inf->lop[indexLop]->soSv;
	int indexMH=inf->TestMH(maMH);
	int index=0;
	
	SinhVien **sv=new SinhVien*[sosv];
	for(int i=0;i<sosv;i++){
		sv[i]=new SinhVien();
	}
	DSSV *ds=inf->lop[indexLop]->dssv;
	while(ds!=NULL){
		sv[index]=ds->sv;
		ds=ds->next;
		index++;
	}
	
	Login next, previous,exit;
	next.dai = previous.dai = exit.dai = 90;
	next.rong = previous.rong = exit.rong = 30;
	
	index=0;
	while(1) {
		delay(0.00001);
		cleardevice();
		if (index + maxInPage < sosv) {
			InitRec(next, getmaxx() - next.dai - 50, getmaxy() - next.rong - 50);
			outtextxy(next.left + 20, next.top + 5, "NEXT");
		}
		if (index >= maxInPage) {
			InitRec(previous, next.left - 50 - previous.rong / 2, getmaxy() - previous.rong - 50);
			outtextxy(previous.left + 20, previous.top + 5, "PREV");
		}
		InitRec(exit,getmaxx()-exit.dai-50,getmaxy()-exit.rong-20);
		outtextxy(exit.left+10,exit.top+5,"Thoat");
		int indexY=60;
		outtextxy(X,indexY-40,"Ma SV");
		outtextxy(X+200,indexY-40,"Ho");
		outtextxy(X+400,indexY-40,"Ten");
		outtextxy(X+630,indexY-40,"Diem");
		
		line(0,indexY-10,X+700,indexY-10);		

		line(X+170,0,X+170,getmaxy());
		line(X+370,0,X+370,getmaxy());
		
		line(X+600,0,X+600,getmaxy());
		line(X+700,0,X+700,getmaxy());
		
		char cDiem[10];
		for(int i=index;i<sosv && i<index+maxInPage;i++){
		//	cout<<i<<endl;
			memset(cDiem,0,sizeof cDiem);
			itoa(sv[i]->diem[indexMH]->diemThi,cDiem,10);
			
			outtextxy(X,indexY,&sv[i]->maSV[0]);
			outtextxy(X+200,indexY,&sv[i]->Ho[0]);
			outtextxy(X+400,indexY,&sv[i]->Ten[0]);
			outtextxy(X+630,indexY,cDiem);
			indexY+=40;
		//	if(i==sosv-2) cout<<"ccc";
		}
		while(1){
		delay(0.00001);
			if (ismouseclick(WM_LBUTTONDOWN)) {
				int moux = mousex(), mouy = mousey();
				clearmouseclick(WM_LBUTTONDOWN);
				//outtextxy(mousex(), mousey(), "x");
				if (index + maxInPage<sosv&&IsClickRec(next, moux, mouy)) {
					//isClick = true;
					index+=maxInPage;
					break;
				}
				else if (index>=maxInPage && IsClickRec(previous, moux, mouy)) {
				//	isClick = true;
					index-=maxInPage;
					break;
				}
				else if(IsClickRec(exit,moux,mouy)){
					putimage(0,0,arrow,COPY_PUT);
					return;					
				}
				
	
			}
		}
	}

}
void WindowGV(){
	cleardevice();
	Login maLop,tenLop;
	Login choose,inDsLop,nhapSv,NhapMon,Maxtime,Maxcau,exit;
	Login tha;
	int tamX;
	
	string currentMaLop="",currentTenLop="",socau="",sophut="";
	const string inDs="In danh sach";
	const string addSv="Them sinh vien";
	const string addMh="Them mon hoc";
	const string addCauHoi="Them cau hoi";
	
	maLop.dai=tenLop.dai=220;
	maLop.rong=tenLop.rong=60;
	Maxcau.dai=Maxtime.dai=90;
	Maxcau.rong=Maxtime.rong=40;
	exit.dai=90;
	exit.rong=30;
	
	choose.dai=inDsLop.dai=nhapSv.dai=NhapMon.dai=200;
	choose.rong=50;
	inDsLop.rong=nhapSv.rong=NhapMon.rong=50;
	
	//tha.dai=30;
	//tha.rong=choose.rong;
//-----------------------------------------------------------------------------------	
	
	
	tamX=30+choose.dai/2;
	InitRec(maLop,tamX+50,maLop.rong/2+10);	
	outtextxy(maLop.left-70,maLop.top+5,"Ma Lop");
	InitRec(tenLop,maLop.right+tenLop.dai/2+100,maLop.top+tenLop.rong/2);
	outtextxy(maLop.right+10,maLop.top+5,"Ten Lop");
	
	InitRec(choose,tamX,maLop.bottom+60);	
	//InitRec(tha,choose.right+tha.dai/2,choose.top+tha.rong/2);
	int dis=inDsLop.rong/2;
	int tamY=choose.bottom+20;
	tamY+=dis;				
	InitRec(inDsLop,tamX,tamY);
	outtextxy(inDsLop.left+20,inDsLop.top+10,&inDs[0]);
	
			
	tamY=dis+inDsLop.bottom;
	InitRec(nhapSv,tamX,tamY);
	outtextxy(nhapSv.left+20,nhapSv.top+10,&addSv[0]);
			
	tamY=dis+nhapSv.bottom;
	InitRec(NhapMon,tamX,tamY);
	outtextxy(NhapMon.left+20,NhapMon.top+10,&addMh[0]);
	
	InitRec(Maxcau,tamX+40,NhapMon.bottom+30);
	outtextxy(Maxcau.left-70,Maxcau.top+5,"So Cau");
	
	InitRec(Maxtime,tamX+40,Maxcau.bottom+30);
	outtextxy(Maxtime.left-90,Maxtime.top+5,"Thoi Gian");
	
	InitRec(exit,getmaxx()-exit.dai-50,getmaxy()-exit.rong-40);
	outtextxy(exit.left+5,exit.top+5,"Thoat");
//------------------------------------------------------------------
	
	int maxS=13;
	int moux =-1,mouy=-1;
	int indexXMaLop,indexXTenLop;
	int indexYMaLop,indexYTenLop;
	indexXMaLop=maLop.left+10;	
	indexXTenLop=tenLop.left+10;
	indexYMaLop=maLop.top+maLop.rong/2-10;
	indexYTenLop=tenLop.top+tenLop.rong/2-10;
	
	int indexXCau,indexYCau,indexXTime,indexYTime;
	
	indexXCau=Maxcau.left+5;
	indexYCau=Maxcau.top+5;
	indexXTime=Maxtime.left+5;
	indexYTime=Maxtime.top+5;
	int disChar=15;
	bool nhap=false,clickTha=false;
	char c;
	

	while(1){
		delay(0.000001);
		if(ismouseclick(WM_LBUTTONDOWN)){
			moux=mousex();
			mouy=mousey();
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(IsClickRec(maLop,moux,mouy)){
			HieuUngNhap(maLop,currentMaLop,indexXMaLop,indexYMaLop,moux,mouy,disChar,maxS,2);
		}
		else if(IsClickRec(tenLop,moux,mouy)){
			HieuUngNhap(tenLop,currentTenLop,indexXTenLop,indexYTenLop,moux,mouy,disChar,maxS,2);
		}
		else if(IsClickRec(Maxcau,moux,mouy)){
			outtextxy(exit.left-15,exit.top-25,"                                                        ");
			HieuUngNhap(Maxcau,socau,indexXCau,indexYCau,moux,mouy,15,3,1);
			
			if(socau.size()!=0)
				SOCAU=atoi((char*)socau.c_str());
		}
		else if(IsClickRec(Maxtime,moux,mouy)){
			outtextxy(exit.left-15,exit.top-25,"                                                        ");
			HieuUngNhap(Maxtime,sophut,indexXTime,indexYTime,moux,mouy,15,3,1);
			
			if(sophut.size()!=0)
				TIME=atoi((char*)sophut.c_str());
		}
		else if(IsClickRec(exit,moux,mouy)){
			return ;
			/*
			if(TIME==-1||SOCAU==-1){
				outtextxy(exit.left-15,exit.top-25,"Nhap Thoi gian/So cau");
			}
			else{
				return;
			}
			moux=-1,mouy=-1;
			*/
		}
		else{//cc
			
			int chooseX=choose.left+10,chooseY=choose.top+20;
			string xoa="                                      ";
			if(IsClickRec(inDsLop,moux,mouy)){
		//		outtextxy(0,10,"  ");
		//		outtextxy(0,10,"1");
				outtextxy(exit.left-15,exit.top-25,"                                                        ");
				outtextxy(chooseX,chooseY,&xoa[0]);
				outtextxy(chooseX,chooseY,&inDs[0]);
				//void InDS(string malop,string maMH,int maxInPage,int X)
				if(inf->TestLop(currentMaLop)!=-1){
					InDS(currentMaLop,inf->monHoc[0]->maMH,10,100);
				}
			}
			else if(IsClickRec(nhapSv,moux,mouy)){
		//		outtextxy(0,10,"  ");
		//		outtextxy(0,10,"2");
				outtextxy(exit.left-15,exit.top-25,"                                                        ");	
				outtextxy(chooseX,chooseY,&xoa[0]);
				outtextxy(chooseX,chooseY,&addSv[0]);
				
				ProcessGV(currentMaLop,currentTenLop,2,nhapSv.right+400);
			
			}
			else if(IsClickRec(NhapMon,moux,mouy)){
		//		outtextxy(0,10,"  ");
		//		outtextxy(0,10,"3");
				outtextxy(exit.left-15,exit.top-25,"                                                        ");
				outtextxy(chooseX,chooseY,&xoa[0]);
				outtextxy(chooseX,chooseY,&addMh[0]);
			}
			moux=-1,mouy=-1;
		}
		
	
	}
	
}
void LoadDSSV(){
	inf->AddMh("a","b");
		fstream file;
	file.open("DSSVbin.inp", ios::in | ios::binary);
	int n;
	file.read((char*)&n, sizeof(int));
	string *masv = new string[n];
	string *ho = new string[n];
	string *ten = new string[n];
	char c[100];
	string ss;
	
	for (int i = 0; i<n; i++) {
		int size;
		masv[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		masv[i] = c;
		//cout << masv[i] << endl;
	}
	for (int i = 0; i<n; i++) {
		int size;
		ho[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		ho[i] = c;
	//	cout << ho[i] << endl;
	}
	for (int i = 0; i<n; i++) {
		int size;
		ten[i].resize(100);
		file.read((char*)&size, sizeof(int));
		file.read(c, size + 1);
		ten[i] = c;
	//	cout << ten[i] << endl;
	}
	file.close();


			for(int i=0;i<n;i++)	{
				*inf->sv=SinhVien(masv[i],ho[i],ten[i],masv[i],true);
				*inf->lopTemp=Lop("CC","CNTT");
				inf->AddSv(inf->sv,inf->lopTemp);
			}
}
