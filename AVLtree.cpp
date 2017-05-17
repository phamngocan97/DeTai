#include "AVLtree.h"
#include<iostream>
#include<ctime>
using namespace std;



AVLtree::AVLtree()
{
}


AVLtree::~AVLtree()
{
}
#define LP -1
#define LT 1
#define CB 0

void AVLtree::NLR(AVL *T) {
	if (T != NULL) {
		cout << T->val->id << " ";
		NLR(T->left);
		NLR(T->right);
	}
}
void AVLtree::NRL(AVL *T) {
	if (T != NULL) {
		cout << T->val->id << " ";
		NRL(T->right);
		NRL(T->left);
	}
}

void AVLtree::LNR(AVL *T) {
	if (T != NULL) {
		LNR(T->left);
		cout << T->val->id << "(" << T->stt << ")  ";
		LNR(T->right);
	}
}
void AVLtree::RNL(AVL *T) {
	if (T != NULL) {
		RNL(T->right);
		cout << T->val->id << " ";
		RNL(T->left);
	}
}
void AVLtree::LRN(AVL *T) {
	if (T != NULL) {
		LRN(T->left);
		LRN(T->right);
		cout << T->val << " ";
	}
}
void AVLtree::RLN(AVL *T) {
	if (T != NULL) {
		RLN(T->right);
		RLN(T->left);
		cout << T->val << " ";
	}
}
AVL* AVLtree::Node(QuesAndAns *Data) {
	AVL *mem = new AVL;
	mem->left = NULL;
	mem->right = NULL;
	mem->val=new QuesAndAns;
	mem->val = Data;
	mem->stt = CB;
	return mem;
}
int AVLtree::Insert(AVL *&T, QuesAndAns *Data) {
	int stt;
	if (T == NULL) {
		T = Node(Data);
		if (T == NULL)
			return -1;//khong du bo nho tao cay
		else return 2; // them thanhcong tang chieu cao
	}
	else {
		if (T->val->id == Data->id)
			return 0;
		else if (T->val->id > Data->id) {
			stt = Insert(T->left, Data);
			if (stt < 2)
				return stt;
			switch (T->stt) {
			case LP: T->stt = CB; return 1;
			case LT: BalanceLeft(T); return 1;
			case CB: T->stt = LT;	return 2;
			}
		}
		else {
			stt = Insert(T->right, Data);
			if (stt < 2)
				return stt;
			switch (T->stt) {
			case LT: T->stt = CB; return 1;
			case CB: T->stt = LP; return 2;
			case LP: BalanceRight(T); return 1;
			}
		}
	}
}

void AVLtree::LeftRotate(AVL *&T) { //quay trai; mat can bang PP tai T;
	AVL *Q;
	Q = T->right;
	T->right = Q->left;
	Q->left = T;
	switch (Q->stt) {
	case LP:
		T->stt = CB;
		Q->stt = CB;
		break;
	case CB: //
		T->stt = LP;
		Q->stt = LT;
	}

	T = Q;
}
void AVLtree::RightRotate(AVL *&T) {//quay phai; mat can bang TT tai T;
	AVL *Q;
	Q = T->left;
	T->left = Q->right;
	Q->right = T;
	switch (Q->stt) {
	case CB://
		T->stt = LT;
		Q->stt = LP;
		break;
	case LT:
		T->stt = CB;
		Q->stt = CB;
	}

	T = Q;
}
void AVLtree::LRRotate(AVL *&T) {
	AVL *T1 = T->left;
	AVL *T2 = T1->right;
	T->left = T2->right;
	T2->right = T;
	T1->right = T2->left;
	T2->left = T1;
	switch (T2->stt) {
	case LT:   //T1->left!=NULL
		T->stt = LP;
		T1->stt = CB;
		break;
	case CB:
		T->stt = CB;
		T1->stt = CB;
		break;
	case LP:  //T1->left!=NULL
		T->stt = CB;
		T1->stt = LT;
		break;
	}
	T2->stt = CB;
	T = T2;
}
void AVLtree::RLRotate(AVL *&T) {
	AVL *T1, *T2;
	T1 = T->right;
	T2 = T1->left;
	T->right = T2->left;
	T2->left = T;
	T1->left = T2->right;
	T2->right = T1;
	switch (T2->stt) {
	case LT:  //T1->right!=NULL
		T->stt = CB;
		T1->stt = LP;
		break;
	case CB:
		T->stt = CB;
		T1->stt = CB;
		break;
	case LP:   //T1->right!=NULL
		T->stt = LT;
		T1->stt = CB;
		break;
	}
	T = T2;
}
int AVLtree::BalanceRight(AVL *&T) {
	AVL *T1 = T->right;
	switch (T1->stt) {
	case LT:
		RLRotate(T);
		return 2;
	case CB:
		LeftRotate(T);
		return 1;
	case LP:
		LeftRotate(T);
		return 2;
	}
}
int AVLtree::BalanceLeft(AVL *&T) {
	AVL *T1 = T->left;
	switch (T1->stt) {
	case LP:
		LRRotate(T);
		return 2;
	case CB:
		RightRotate(T);
		return 1;
	case LT:
		RightRotate(T);
		return 2;
	}
}
