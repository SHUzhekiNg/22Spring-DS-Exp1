#include "Assistance.h"					// ʵ�ó��������
#include "ChildSiblingTree.h"			// �����ֵܱ�ʾ����

int main(void)
{
    try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
		int n = 8;
		ChildSiblingTree<char> t(items, parents, n);
		cout << "��:" << endl;
		DisplayTWithConcaveShape(t);
		cout << endl;
		system("PAUSE");				// ���ÿ⺯��system()

		cout << "�ȸ��������:";
		t.PreRootOrder(Write);
		cout << endl;
		cout << "����������:";
		t.PostRootOrder(Write);
		cout << endl;
		cout << "��α�����:";
		t.LevelOrder(Write);
		cout << endl;
		cout << "����:";
		cout << t.Height();
		cout << endl;
		cout << "���Ķ�:";
		cout << t.Degree();
		cout << endl;
		char e;
		t.GetElem(t.GetRoot(), e);
		cout << "���" << e << "�Ķ�:" << t.NodeDegree(t.GetRoot()); 
		cout << endl;
		system("PAUSE");				// ���ÿ⺯��system()
		
		ChildSiblingTree<char> t1(t);
		cout << "���ƹ�����:" << endl;
//		DisplayTWithConcaveShape<char>(t1);
		DisplayTWithConcaveShape(t1);
		cout << endl;
		system("PAUSE");				// ���ÿ⺯��system()

		t1 = t;
		cout << "��ֵ������ع�����:" << endl;
//		DisplayTWithConcaveShape<char>(t1);
		DisplayTWithConcaveShape(t1);
		cout << endl;
		system("PAUSE");				// ���ÿ⺯��system()

		e = 'A';
		ChildSiblingTree<char> t2(e);	// ������eΪ������

		ChildSiblingTreeNode<char> *cur = t2.GetRoot();
		e = 'B';
		t2.InsertChild(cur, 1, e);

		e = 'C';
		t2.InsertChild(cur, 2, e);

		cout << "��:" << endl;
		DisplayTWithConcaveShape(t2);
		cout << endl;
		ChildSiblingTreeNode<char> *f, *c;
		f = t2.GetRoot();
		c = t2.FirstChild(f);
		f = t2.Parent(c);
		cout << c->data << "˫����:" << f->data;
		cout << endl;
		system("PAUSE");				// ���ÿ⺯��system()

		cur = t2.GetRoot();
		t2.DeleteChild(cur, 2);					
		cout << "ɾ�����ڶ���������:" << endl;
		DisplayTWithConcaveShape(t2);
		cout << endl;
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}

