
#include <iostream>
#include <list>

using namespace std;

// khai bao ctdl cua 1 pt (1 nut) - 1 node trong dslk don, chua don thuc
struct Node
{
	int data;
	Node* pNext;
};

// khai bao kdl cua 1 danh sach lien ket
struct LinkedList
{
	Node* pHead;
	Node* pTail;
	LinkedList()
	{
		pHead = NULL;
		pTail = NULL;
	}
};

// thao tac co ban
void addTail(LinkedList &l, Node* pNew);
void addHead(LinkedList &l, Node* pNew);
void addAfter(LinkedList &l, Node* pNew, Node* q);
void deleteHead(LinkedList &l);
void deleteAfter(LinkedList &l, Node* pPre);
Node* search(LinkedList &l, int x);
void interchangeSort(LinkedList &l);
void selectionSort(LinkedList &l);

//Ung dung
void nhapDS(LinkedList &l);
void xuatDS(LinkedList l);
void themVaoViTriThuN(LinkedList &l, Node* pNew, int n);
void adAfterMax(LinkedList &l, Node* pNew);
int demX(LinkedList l, int x);
void deleteNode(LinkedList &l, int x);
void deleteAllNode(LinkedList &l, int x);

// sua de
void xoaSauSNT(LinkedList &l);
void themXSauY(LinkedList &l, int x, int y);
void suaSoChanDauTien(LinkedList &l, int x);
void timTrongL1KhongL2(LinkedList l1, LinkedList l2);

//chuong trinh chinh:
int main()
{
	// cau 2a
	LinkedList l1, l2;
	nhapDS(l1);
	xuatDS(l1);
	nhapDS(l2);
	xuatDS(l2);

	// cau 2b
	/*cout << "DS sau khi xoa sau snt dau tien: ";
	xoaSauSNT(l2);
	xuatDS(l2);

	int x;
	cout << "Nhap du lieu se thay the cho so chan dau tien: ";
	cin >> x;
	suaSoChanDauTien(l2, x);
	xuatDS(l2);*/

	/*int y, x;
	cout << "Nhap du lieu can them: ";
	cin >> x;
	cout << "Ban can them " << x << " sau pt nao: ";
	cin >> y;
	themXSauY(l2, x, y); 
	xuatDS(l2);*/

	//cau 2c
	cout << "==> Nhung pt co trong l1, khong co trong l2: ";
	timTrongL1KhongL2(l1, l2);

	//2d
	cout << endl;
	selectionSort(l2);
	xuatDS(l2);

	system("pause");
	return 0;
}

/*
* Them 1 pt vao dau ds
*/
void addHead(LinkedList &l, Node* pNew)
{
	if (l.pHead == NULL)
	{
		l.pHead = pNew;
		l.pTail = pNew;
	}
	else
	{
		pNew->pNext = l.pHead;
		l.pHead = pNew;
	}
}

/*
* Them 1 pt vao cuoi dslk
*/
void addTail(LinkedList &l, Node* pNew)
{
	if (l.pHead == NULL)
	{
		l.pHead = pNew;
		l.pTail = pNew;
	}
	else
	{
		l.pTail->pNext = pNew;
		l.pTail = pNew;
	}
}

/*
* Them 1 pt vao sau mot phan tu khac
*
* Tham so:
	l: dslk
	pNew: la con tro, tro vao pt can them
	q: la con tro dung truoc
* return;
*/
void addAfter(LinkedList &l, Node* pNew, Node* q) // 
{
	if (q != NULL && pNew != NULL)
	{
		pNew->pNext = q->pNext;
		q->pNext = pNew;
		if (q == l.pTail)
			l.pTail = pNew;
	}
}

//3. Them 1 pt bat ky vao sau so chan dau tien trong ds +0.5
// 1 3 2 7 5 4--> x = 100: 1 3 2 100 5 4
void themSauSoChan(LinkedList &l, Node* pNew)
{
	// tim so chan dau tien trong ds
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data % 2 == 0)
		{
			addAfter(l, pNew, p);
			break;
		}
	}
}

void nhapDS(LinkedList &l)
{
	int n;
	cout << "Nhap so phan tu cua dslk: ";
	cin >> n; // 

	for (int i = 1; i <= n; i++) //5 lan
	{
		// voi moi i: tao ra 1 nut roi gan no vao dslk
		//b1: tao 1 nut moi
		Node* pNew = new Node;
		cout << "Nhap du lieu cho nut moi: ";
		cin >> pNew->data;
		pNew->pNext = NULL;

		// b2: gan nut moi (do con tro pNew dang quan ly) nay vao dau dslk
		addHead(l, pNew);
		//addTail(l, pNew);
	}
}

void xuatDS(LinkedList l)
{

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		cout << p->data << " ";
	}
	cout << endl;
}

//1. hay them vao dau ds 1 pt co du lieu la tong gia tri cac phan tu trong ds: +0.5
void addSumHead(LinkedList &l)
{
	// tinh sum
	int tong = 0;
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		tong += p->data;
	}

	Node* pNew = new Node;
	pNew->data = tong;
	pNew->pNext = NULL;

	addHead(l, pNew);
}

//2. Them 1 pt vao sau phan tu lon nhat trong ds: 1 5 7 3, x = 100 --> 1 5 7 100 3
void adAfterMax(LinkedList &l, Node* pNew)
{
	// tim max
	Node* pMax = l.pHead;
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data > pMax->data)
			pMax = p;
	}
	// pMax dang chi vao pt co gia tri lon nhat
	addAfter(l, pNew, pMax);
}

// 4. Them 1 phan tu bat ky vao vi tri thu n (tinh tu dau ds) cua dslk: 4 6 8 7 5, n = 4, x =100 --> 4 6 100 8 7 5 // +1 diem
void themVaoViTriThuN(LinkedList &l, Node* pNew, int n)
{
	int dem = 1;
	if (n == 1)
		addHead(l, pNew);
	else
	{
		for (Node* p = l.pHead; p != NULL; p = p->pNext)
		{
			if (dem + 1 == n)
			{
				addAfter(l, pNew, p);
				break;
			}
			dem++;
		}
	}

}

// Bai 5
int demX(LinkedList l, int x)
{
	int dem = 0;
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data == x)
			dem++;
	}

	return dem;
}

void deleteHead(LinkedList &l)
{
	if (l.pHead == NULL)
		return;
	Node* p = l.pHead;
	l.pHead = p->pNext;
	delete p;
	if (l.pHead == NULL)
		l.pTail = NULL;
}


/*
* Xoa 1 phan tu dung sau pPre
*/
void deleteAfter(LinkedList &l, Node* pPre) // 1 2 3 5 6, 
{
	if (pPre != NULL && pPre->pNext != NULL)
	{
		Node* p = pPre->pNext; // p chi vao pt can xoa
		pPre->pNext = p->pNext;
		delete p;

		if (pPre->pNext == NULL)
			l.pTail = pPre;
	}
}

/*
* Xoa 1 phan tu co du lieu la x bat ky: +0.5: 5 6 4 6 2, x = 6
*/
void deleteNode(LinkedList &l, int x)
{
	if (l.pHead == NULL)
		return;

	if (x == l.pHead->data)
		deleteHead(l);
	else // x nam tu pt thu 2 tro di
	{
		// tim pt dung truoc x
		for (Node* pPre = l.pHead; pPre != NULL; pPre = pPre->pNext) 
		{
			if (pPre->pNext != NULL && pPre->pNext->data == x)
			{
				deleteAfter(l, pPre);
				break;
			}
		}
	}

}


/*
* Xoa tat ca pt co du lieu la x // +1:  1 6 5 6 6 6, x = 6
*/
void deleteAllNode(LinkedList &l, int x)
{
	// xoa tat ca x o dau ds
	Node* p = l.pHead;
	while (p != NULL && p->data == x)
	{
		p = p->pNext;
		deleteHead(l);
		//p = l.pHead;
	}

	// xoa tat ca pt co du lieu la x, tu vi tri thu 2
	while (p != NULL)
	{
		// dung p truoc pt co du lieu la x
		if (p->pNext != NULL && p->pNext->data == x)//// 5 6 2
		{
			deleteAfter(l, p);
			
		}
		else
			p = p->pNext;
	}
}

/*
* xoa 1 phan tu sau pt lon nhat
*/

/*
* xoa 1 pt sau so nguyen to dau tien + 0.5
*/


//2.	Xóa k phần tử ở đầu danh sách (k nhập từ bàn phím)//5
void deleteKNode(LinkedList &l, int k)
{
	//int spt = sizeList(l);
	// check k
	// chay vong lap k lan, moi lan goi deleteHead
}

Node* search(LinkedList &l, int x)
{
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data == x)
			return p;
	}
	return NULL;
}

/*
* SX ds tang dan
*/
void interchangeSort(LinkedList &l)
{
	for (Node* p = l.pHead; p != l.pTail; p = p->pNext)
	{
		for (Node* t = p->pNext; t != NULL; t = t->pNext)
		{
			if (t->data < p->data)
			{
				swap(t->data, p->data);
			}
		}
	}
}

/*
* sx giam dan
*/
void selectionSort(LinkedList &l)
{
	for (Node* p = l.pHead; p != l.pTail; p = p->pNext)
	{
		// tim Max
		Node* pMax = p;
		for (Node* t = p->pNext; t != NULL; t = t->pNext)
		{
			if (t->data > pMax->data)
				pMax = t;
		}
		//pMax dang chi vao pt co gtri lon nhat cua day bat dau la p
		swap(p->data, pMax->data);
	}
}

/*
* KTRa snt
*/
bool kiemTraSNT(int x)
{
	if (x <= 1)
		return false;
	for (int i = 2; i < x; i++)
	{
		if (x % i == 0)
			return false;
	}

	return true;
}

/*
* xoa sau snt dau tien
*/
void xoaSauSNT(LinkedList &l)
{
	// tim snt dau tien
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (kiemTraSNT(p->data) == true)
		{
			deleteAfter(l, p);
		}
	}
}

void suaSoChanDauTien(LinkedList &l, int x)
{
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data % 2 == 0)
		{
			p->data = x;
			break;
		}
	}
}

/*
* Them x vao sau y
*/
void themXSauY(LinkedList &l, int x, int y) // y 6 y 5 y
{
	// Tim y
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data == y)
		{
			//tao nut moi can them (nut co du lieu la x)
			Node* pNew = new Node;
			pNew->data = x;
			pNew->pNext = NULL;

			addAfter(l, pNew, p);
			//break;
		}
	}
}

void timTrongL1KhongL2(LinkedList l1, LinkedList l2)
{
	for (Node* p = l1.pHead; p != NULL; p = p->pNext)
	{
		// voi moi pt trong l1, tim trong l2
		if (search(l2, p->data) == NULL)
			cout << p->data << " ";
	}
}