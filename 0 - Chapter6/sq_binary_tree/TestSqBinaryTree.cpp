#include "Assistance.h"					// ���������
#include "SqBinaryTree.h"				// ˳��洢��������

int main(void)
{
	int p, c, l, r;
	char e, cElem, pElem, lElem, rElem;
	
	e = 'A';
	SqBinaryTree<char> bt(e,20);		// ����������
	
	e = 'B';
	p = bt.GetRoot();
	bt.InsertLeftChild(p, e);		// ��������

	e = 'C';
	bt.InsertRightChild(p, e);	// �����Һ���
		
	p = bt.LeftChild(p);
	e = 'D';
	bt.InsertLeftChild(p, e);	// �����Һ���

	p = bt.GetRoot();
	p = bt.RightChild(p);
	e = 'E';
	bt.InsertLeftChild(p, e);		// ��������
	e = 'F';
	bt.InsertRightChild(p, e);	// �����Һ���

	c = bt.LeftChild(p);
	bt.GetElem(p, pElem);
	bt.GetElem(c, cElem);
	cout << cElem << "˫����" << pElem << endl;
	p = bt.GetRoot();	// ��
	bt.GetElem(p, pElem);
	l = bt.LeftChild(p);			// ����
	bt.GetElem(l, lElem);
	r = bt.RightSibling(l);		    // �Һ���
	bt.GetElem(r, rElem);

	cout << pElem << "������" << lElem;
	cout << ", �Һ�����" << rElem << endl;
	cout << "�������ĸ���" << bt.Height() << endl;

	cout << "ԭ��:" << endl;
	DisplayBTWithTreeShape<char>(bt);
	cout << endl;
	system("PAUSE");				// ���ÿ⺯��system()
		
	SqBinaryTree<char> btNew(bt);	// ���ƹ�������
	cout << "���ƹ�������:" << endl;
	DisplayBTWithTreeShape<char>(btNew);
	cout << endl;
	system("PAUSE");			

	btNew = bt;						// ��ֵ��������
	cout << "��ֵ��������:" << endl;
	DisplayBTWithTreeShape<char>(btNew);
	cout << endl;
	system("PAUSE");	

	cout << "�����:" << bt.NodeCount();
	cout << endl;
	system("PAUSE");		

	cout << "�������:" << endl;
	bt.PreOrder(Write<char>);
	cout<<endl;
	system("PAUSE");		

	cout << "�������:" << endl;
	bt.InOrder(Write<char>);
	cout<<endl;
	system("PAUSE");	

	cout << "�������:" << endl;
	bt.PostOrder(Write<char>);
	cout<<endl;
	system("PAUSE");	

	cout << "��α���:" << endl;
	bt.LevelOrder(Write<char>);
	cout<<endl;
	system("PAUSE");	

	p = bt.GetRoot();
	bt.DeleteRightChild(p);					
	cout << "ɾ��������������:" << endl;
	DisplayBTWithTreeShape<char>(bt);
	cout << endl;
	system("PAUSE");				// ���ÿ⺯��system()

	char pre[]={'A','B','D','E','G','H','C','F','I'};		// ��������
	char in[]={'D','B','G','E','H','A','C','F','I'};		// ��������
	int n = 9, size=15;						// ������
	SqBinaryTree<char> preInbt;
	preInbt = CreateBinaryTree(pre, in, n, size);// ���������
		
	cout << "��pre[]={'A','B','D','E','G','H','C','F','I'},in[]={'D','B','G','E','H','A','C','F','I'}���������:" << endl;
	DisplayBTWithTreeShape<char>(preInbt);
	cout << endl;

	system("PAUSE");
	return 0;
}

