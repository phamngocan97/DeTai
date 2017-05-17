#pragma once

class AVL;
class QuesAndAns;
class AVLtree{
public:
	AVLtree();

	AVL *Node(QuesAndAns *Data);
	int Insert(AVL *&T, QuesAndAns *Data);
	int BalanceLeft(AVL *&T);
	int BalanceRight(AVL *&T);
	void LRRotate(AVL *&T);
	void RLRotate(AVL *&T);
	void LeftRotate(AVL *&T);
	void RightRotate(AVL *&T);

	void NLR(AVL *T);
	void NRL(AVL *T);
	void LNR(AVL *T);
	void RNL(AVL *T);
	void LRN(AVL *T);
	void RLN(AVL *T);

	~AVLtree();
};


class AVL {
public:
	QuesAndAns *val;
	int stt;//0 can bang
			//1 lech trai
			//-1 lech phai
	AVL *left;
	AVL *right;
};
class QuesAndAns {
	public:
		//string cauhoi, traloi[4];
		int id;
		char cauhoi[1000];
		char traloi[4][1000];
		int dapan;
};
