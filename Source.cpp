/*
	Ho Ten: Tran Ngoc Truong
	Lop: CD18TT10
	MSSV: 18211TT0903
	CTDL va GT:Chuong 4 LinkedList
*/
//Khai bao thu vien:
#include <iostream>
#include <string>
using namespace std;
struct NODE
{
	int data;
	NODE* pNext;
};
struct  LinkedList
{
	NODE* pHead;
	NODE* pTail;
	LinkedList()
	{
		pHead = NULL;
		pTail = NULL;
	}
};
//Khai bao nguyen mau ham con:
void nhapDS(LinkedList& l);
void xuatDS(LinkedList l);
void tong(LinkedList l);
//cau1
void lietkeSNT(LinkedList l, int nN);
bool kiemTraSNT(int nN);
//cau2
void deleteHead(LinkedList& l);
//cau3
void deleteAfter(LinkedList& l, NODE* pPre);
void deleteNode(LinkedList& l, int x);
//cau4
void xoaPhanTuLapLai(LinkedList& l, int x);
//cau5
int count_X(LinkedList& L, int nX);
//cau6
NODE* Nth(LinkedList& l, int nN);
//cau7
NODE* doAdvance(LinkedList& l, int nVT);
int getSize(LinkedList& l);

//cau8
void chenPTU(LinkedList& l, int nX);
NODE* createNoDe(int nX);
//cau9
//cau10
//cauu11
//cau12a
//cau12b
//Chuong trinh chinh:
void main()
{
	int nN = 0;
	LinkedList l;
	nhapDS(l);
	xuatDS(l);
	tong(l);
	lietkeSNT(l, nN);
	cout<<endl;
	//cau2
	deleteHead(l);
	xuatDS(l);
	cout<<endl;
	//cau3
	int nK = 0;
	cout <<" Nhap phan tu can xoa:";
	cin >> nK;
	deleteNode(l,nK);
	xuatDS(l);
	cout<<endl;
	//cau4
	xoaPhanTuLapLai(l,nK);
	cout << "\nDS sau khi xoa: \n";
	xuatDS(l);
	cout<<endl;
	//cau5
	int nX = 0;
	cout << "Nhap nX= :";
	cin >> nX;
	cout << "So lan xuat hien cua" << nX << "la :" << count_X(l, nX) << endl;
	//cau6
	cout << "Nhap vao nN: ";
	cin >> nN;
	NODE* kq = Nth(l, nN);
	cout << "Cau 6: Ham Nth\n";
	if (kq != NULL)
		cout << "\tPhan tu thu " << nN << " co du lieu la: " << kq->data << endl;
	else
		cout << "\tKhong co phan tu trong danh sach!";
	// goi ham cau 7
	int nVT = 0;
	do
	{
		cout << "\nNhap nVT= ";
		cin >> nVT;
	} while (nVT < 1 || nVT > getSize(l));
	NODE * p = doAdvance(l, getSize(l) - nVT + 1);
	//cau8
	chenPTU(l, 5);
	cout << "\nDanh sach sau khi them: ";
	xuatDS(l);
	/*return 0;*/
	system("pause");
}
//Dinh nghia ham con:
void lietkeSNT(LinkedList l, int nN)
{
	int dem = 0;
	for (NODE* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (kiemTraSNT(p->data) == true)
		{
			cout << "  " << p->data;
		}
	}
}
bool kiemTraSNT(int nN)
{
	int demus = 0;
	for (int i = 1; i <= nN; i++)
	{
		if (nN % i == 0)
			demus++;
	}
	return demus == 2;
}
void tong(LinkedList l)
{
	int tong = 0;
	NODE* p = l.pHead;
	while (p != NULL)
	{
		tong += p->data;
		p = p->pNext;
	}
	cout << "Tong = " << tong << endl;
}
void nhapDS(LinkedList & l)
{
	int n;
	cout << "Nhap so luong phan tu cua danh sach: ";
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		NODE* pNew = new NODE;
		cout << "Nhap du lieu nut moi: ";
		cin >> pNew->data;
		pNew->pNext = NULL;
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
}
void xuatDS(LinkedList l)
{
	for (NODE* p = l.pHead; p != NULL; p = p->pNext)
	{
		cout << p->data << " ";
	}
	cout << endl;
}
//cau2
void deleteHead(LinkedList& l)
{
	if (l.pHead == NULL)
		return;
	NODE * p = l.pHead;
	l.pHead = p->pNext;
	delete p;
	if (l.pHead == NULL)
		l.pTail = NULL;
}

/*
* Xoa 1 phan tu dung sau pPre
*/
void deleteAfter(LinkedList& l, NODE* pPre)
{
	if (pPre != NULL && pPre->pNext != NULL) // neu pPre ton tai, va sau pPre cung ton tai (tuc ton tai phan tu can xoa)
	{
		NODE* p = pPre->pNext;
		pPre->pNext = p->pNext;
		delete p;
		if (pPre->pNext == NULL)
			l.pTail = pPre;
	}
}
/*
* Xoa 1 phan tu co du lieu la x bat ky
*/
//cau3
void deleteNode(LinkedList& l, int x) // 3 5  4 5 , x = 4
{
	if (x == l.pHead->data)
		deleteHead(l);
	else // x nam tu pt thu 2 tro di, tim pt dung truoc no
	{
		for (NODE* pPre = l.pHead; pPre != NULL; pPre = pPre->pNext)
		{
			if (pPre->pNext->data == x)
			{
				deleteAfter(l, pPre);
				break;
			}
		}
	}
}
//cau 4
void xoaPhanTuLapLai(LinkedList& l, int x)
{
	NODE* pPre = l.pHead;
	while (pPre != NULL && pPre->data == x)
	{
		pPre = pPre->pNext;
		deleteHead(l);
	}
	for (; pPre != NULL;)
	{
		if (pPre->pNext != NULL && pPre->pNext->data == x)
			deleteAfter(l, pPre);
		else
		{
			pPre = pPre->pNext;
		}
	}
}

//cau5
int count_X(LinkedList& L, int nX)
{
	int nCount = 0;
	for (NODE* p = L.pHead; p != NULL; p = p->pNext)
	{
		if (p->data == nX)
		{
			nCount++;
		}
	}
	return nCount;
}
//cau6
NODE* Nth(LinkedList& l, int nN)
{
	int nVT = 0;
	for (NODE* p = l.pHead; p != NULL; p = p->pNext)
	{
		nVT++;
		if (nVT == nN)
		{
			return p;
		}
	}
	return NULL;
}
//cau7
NODE* doAdvance(LinkedList& l, int nVT)
{
	if (nVT<1 || nVT>getSize(l))
		return NULL;
	NODE* p = l.pHead;
	int i = 1;
	while (i < nVT && p != NULL)
	{
		p = p->pNext;
		i++;
	}
	return p;
}
int getSize(LinkedList& l)
{
	int size = 0;
	for (NODE* p=l.pHead; p != NULL; p = p->pNext)
	{
		size++;
	}
	return size;
}

//cau8
void chenPTU(LinkedList& l, int nX)
{
	NODE* pNew = createNoDe(nX);
	if (nX < l.pHead->data) // nX vao dau danh sach
	{
		pNew->pNext = l.pHead;
		l.pHead = pNew;
	}
	else if (nX >= l.pTail->data) //nX vao cuoi danh sach
	{
		l.pTail->pNext = pNew;
		l.pTail = pNew;
	}
	else
	{
		NODE* p = l.pHead;
		while (p != NULL && p->pNext != NULL)
		{
			if (nX <= p->pNext->data)
			{
				pNew->pNext = p->pNext;
				p->pNext = pNew;
				break;
			}
			p = p->pNext;
		}
	}
}
NODE* createNoDe(int nX)
{
	NODE* p = new NODE;
	if (p == NULL)
	{
		exit(1);
	}
	p->data = nX;
	p->pNext = NULL;
}