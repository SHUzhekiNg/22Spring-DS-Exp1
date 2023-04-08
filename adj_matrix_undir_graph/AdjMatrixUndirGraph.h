#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__

#include <windows.h>

void print(int n) {
    if (n == -1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), abs(n));
    }
    return;
}

// ����ͼ���ڽӾ�����
template<class ElemType>
class AdjMatrixUndirGraph {
protected:
// �ڽӾ�������ݳ�Ա:
    int vexNum, vexMaxNum, arcNum;            // ������Ŀ������Ķ��������Ŀ�ͱ���
    int **arcs;                                // ��ű���Ϣ�ڽӾ���
    ElemType *vertexes;                        // ��Ŷ�����Ϣ������
    mutable Status *tag;                    // ��־����
    int dfs(int v1, int v2);

    int dfs_1(int v1, int v2, int flag = 0);

public:
// �ڽӾ������͵ķ�������:
    AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);

    // ������es[]Ϊ����,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
    AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);

    // ��������Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
    ~AdjMatrixUndirGraph();                    // ��������
    void Clear();                          // ���ͼ
    bool IsEmpty();                 // �ж�����ͼ�Ƿ�Ϊ��
    int GetOrder(ElemType &d) const;// �󶥵�����
    Status GetElem(int v, ElemType &d) const;// �󶥵��Ԫ��ֵ
    Status SetElem(int v, const ElemType &d);// ���ö����Ԫ��ֵ
    int GetVexNum() const;                    // ���ض������
    int GetArcNum() const;                    // ���ر���
    int FirstAdjVex(int v) const;        // ���ض���v�ĵ�һ���ڽӵ�
    int NextAdjVex(int v1, int v2) const;         // ���ض���v1�������v2����һ���ڽӵ�
    void InsertVex(const ElemType &d);             // ����Ԫ��ֵΪd�Ķ���
    void InsertArc(int v1, int v2, int W);                 // ���붥��Ϊv1��v2�ı�
    void DeleteVex(const ElemType &d);             // ɾ��Ԫ��ֵΪd�Ķ���
    void DeleteArc(int v1, int v2);                 // ɾ������Ϊv1��v2�ı�
    Status GetTag(int v) const;                     // ���ض���v�ı�־
    void SetTag(int v, Status val) const;       // ���ö���v�ı�־Ϊval
    AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g);    // ���ƹ��캯��
    AdjMatrixUndirGraph<ElemType> &operator=(const AdjMatrixUndirGraph<ElemType> &g);

    // ��ֵ�������
    void Display();                             // ��ʾ�ڽӾ�������ͼ
    int CountOutDegree(ElemType &e);

    int CountInDegree(ElemType &e);

    int ShortestPath_Floued(ElemType &e1, ElemType &e2);

    int ShortestPath_DJ(ElemType &e1, ElemType &e2);

    int ShortestPath_dfs(ElemType &e1, ElemType &e2);

    int ShortestPath_dfs_1(ElemType &e1, ElemType &e2, int flag = 0);

    int limitedPath_dfs(ElemType &e1, ElemType &e2, int limits);

};

// ����ͼ���ڽӾ������ʵ�ֲ���
template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::CountOutDegree(ElemType &e) {
    int v1 = 0;
    for (; v1 < vexNum; v1++) {
        if (vertexes[v1] == e) break;
    }
    if (v1 == vexNum) {
        throw Error("��ѯ�ڵ㲻����!");
    }
    int s = 0;
    for (int i = 0; i < vexNum; ++i) {
        if (arcs[v1][i] != -1) s++;
    }
    return s;
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::CountInDegree(ElemType &e) {
    int v1 = 0;
    for (; v1 < vexNum; v1++) {
        if (vertexes[v1] == e) break;
    }
    if (v1 == vexNum) {
        throw Error("��ѯ�ڵ㲻����!");
    }
    int s = 0;
    for (int i = 0; i < vexNum; ++i) {
        if (arcs[i][v1] != -1) s++;
    }
    return s;
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::ShortestPath_Floued(ElemType &e1, ElemType &e2) {
    int v1 = -1, v2 = -1;
    for (int i = 0; i < vexNum; ++i) {
        if (vertexes[i] == e1) v1 = i;
        if (vertexes[i] == e2) v2 = i;
    }
    if (v1 == -1 || v2 == -1) {
        throw Error("����Ķ��㲻ȫ���ڣ�");
    }
    int sp[vexNum][vexNum];
    for (int i = 0; i < vexNum; ++i) {
        for (int j = 0; j < vexNum; ++j) {
            sp[i][j] = (arcs[i][j] == -1 ? DEFAULT_INFINITY : arcs[i][j]);
        }
    }
    for (int mid = 0; mid < vexNum; ++mid) {
        for (int start = 0; start < vexNum; ++start) {
            for (int end = 0; end < vexNum; end++) {
                if (sp[start][end] > sp[start][mid] + sp[mid][end]) {
                    sp[start][end] = sp[start][mid] + sp[mid][end];
                }
            }
        }
    }
    return sp[v1][v2];
    /*
    int pathlen = arcs[v1][v2] == -1 ? DEFAULT_INFINITY : arcs[v1][v2];
    for (int mid = 0; mid < vexNum; mid++) {
        if (mid == v1 || mid == v2) {
            int d = arcs[v1][v2] == -1 ? DEFAULT_INFINITY : arcs[v1][v2];
            pathlen = pathlen < d ? pathlen : d;
        } else {
            int front = arcs[v1][mid] == -1 ? DEFAULT_INFINITY : arcs[v1][mid];
            int rear = arcs[mid][v2] == -1 ? DEFAULT_INFINITY : arcs[mid][v2];
            pathlen = pathlen < (front + rear) ? pathlen : (front + rear);
        }
    }
    return pathlen;*/
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::ShortestPath_DJ(ElemType &e1, ElemType &e2) {
    int v1 = -1, v2 = -1;
    for (int i = 0; i < vexNum; ++i) {
        if (vertexes[i] == e1) v1 = i;
        if (vertexes[i] == e2) v2 = i;
    }
    if (v1 == -1 || v2 == -1) {
        throw Error("����Ķ��㲻ȫ���ڣ�");
    }
    int dis[vexNum];
    int visited[vexNum];
    int to_visit;
    for (int i = 0; i < vexNum; ++i) {
        if (i == v1) dis[i] = 0;
        else dis[i] = DEFAULT_INFINITY;
        visited[i] = 0;
    }
    for (int visited_num = 0; visited_num < vexNum; visited_num++) {
        int mindis = DEFAULT_INFINITY;
        for (int i = 0; i < vexNum; ++i) {
            if (visited[i] == 0) {
                to_visit = mindis < dis[i] ? to_visit : i;
                mindis = mindis < dis[i] ? mindis : dis[i];
            }
        }
        for (int i = 0; i < vexNum; ++i) {
            if (arcs[to_visit][i] != -1 && visited[i] == 0) {
                dis[i] = (dis[to_visit] + arcs[to_visit][i]) < dis[i] ? (dis[to_visit] + arcs[to_visit][i]) : dis[i];
            }
        }
        visited[to_visit] = 1;
    }
    return dis[v2];
    /*
    int dis[vexNum];
    int white_point[vexNum];
    int new_white_point_i, white_point_num = 1;
    for (int i = 0; i < vexNum; ++i) {
        if (i == v1) {
            dis[i] = 0;
            white_point[i] = 1;
            new_white_point_i = i;
        } else {
            dis[i] = DEFAULT_INFINITY;
            white_point[i] = 0;
        }
    }
    while (true) {
        for (int i = 0; i < vexNum; ++i) {
            if (arcs[new_white_point_i][i] == -1) {
                continue;
            } else if (white_point[i] == 0) {
                int d = dis[new_white_point_i] + arcs[new_white_point_i][i];
                dis[i] = dis[i] < d ? dis[i] : d;
            }
        }
        int min_white_point_data = DEFAULT_INFINITY;
        for (int i = 0; i < vexNum; ++i) {
            if (white_point[i] == 1) {
                continue;
            } else {
                new_white_point_i = dis[i] < min_white_point_data ? i : new_white_point_i;
                min_white_point_data = dis[i] < min_white_point_data ? dis[i] : min_white_point_data;
            }
        }
        white_point[new_white_point_i] = 1;
        white_point_num++;
        if (white_point_num == vexNum - 1) {
            break;
        }
    }
    /*for (int i = 0; i < vexNum; ++i) {
        cout << dis[i] << " ";
    }
    cout << endl;
    return dis[v2];*/
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::ShortestPath_dfs(ElemType &e1, ElemType &e2) {
    int v1 = -1, v2 = -1;
    for (int i = 0; i < vexNum; ++i) {
        if (vertexes[i] == e1) v1 = i;
        if (vertexes[i] == e2) v2 = i;
    }
    if (v1 == -1 || v2 == -1) {
        throw Error("����Ķ��㲻ȫ���ڣ�");
    }

    for (int i = 0; i < GetVexNum(); i++) {
        if (i != v1) SetTag(v1, UNVISITED);
        else SetTag(v1, VISITED);
    }
    return dfs(v1, v2);
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::ShortestPath_dfs_1(ElemType &e1, ElemType &e2, int flag) {
    int v1 = -1, v2 = -1;
    for (int i = 0; i < vexNum; ++i) {
        if (vertexes[i] == e1) v1 = i;
        if (vertexes[i] == e2) v2 = i;
    }
    if (v1 == -1 || v2 == -1) {
        throw Error("����Ķ��㲻ȫ���ڣ�");
    }

    for (int i = 0; i < GetVexNum(); i++) {
        if (i != v1) SetTag(v1, UNVISITED);
        else SetTag(v1, VISITED);
    }

    return dfs_1(v1, v2, flag);
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::dfs(int v1, int v2) {
    int pathlen = DEFAULT_INFINITY;
    if (v1 == v2) return 0;

    for (int i = 0; i < GetVexNum(); i++) {
        int k = DEFAULT_INFINITY;

        if (GetTag(i) == UNVISITED && arcs[v1][i] != -1) {
            SetTag(i, VISITED);
            k = arcs[v1][i] + dfs(i, v2);
            SetTag(i, UNVISITED);
        }
        pathlen = min(pathlen, k);
    }
    for (int i = 0; i < GetVexNum(); i++) {
        SetTag(v1, UNVISITED);
    }
    return pathlen;
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::dfs_1(int v1, int v2, int flag) {
    int pathlen = DEFAULT_INFINITY;
    int secondpathlen = DEFAULT_INFINITY;
    if (v1 == v2) return 0;

    for (int i = 0; i < GetVexNum(); i++) {
        int k = DEFAULT_INFINITY;

        if (GetTag(i) == UNVISITED && arcs[v1][i] != -1) {
            SetTag(i, VISITED);
            k = arcs[v1][i] + dfs_1(i, v2, 1);
            SetTag(i, UNVISITED);
        }
        pathlen = min(pathlen, k);
        if (k > pathlen) secondpathlen = min(secondpathlen, k);
    }
    for (int i = 0; i < GetVexNum(); i++) {
        SetTag(v1, UNVISITED);
    }

    if (flag == 0 && secondpathlen == DEFAULT_INFINITY)
        cout << "�޴ζ�·!" << endl;
    else if (flag == 0 && secondpathlen != DEFAULT_INFINITY)
        cout << "�ζ�·��" << secondpathlen << endl;

    return pathlen;
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::limitedPath_dfs(ElemType &e1, ElemType &e2, int limits) {
    int v1 = -1, v2 = -1;
    for (int i = 0; i < vexNum; ++i) {
        if (vertexes[i] == e1) v1 = i;
        if (vertexes[i] == e2) v2 = i;
    }

    if (v1 == -1 || v2 == -1) {
        throw Error("����Ķ��㲻ȫ���ڣ�");
    }
    struct Edge {
        int a, b, c;
    } edges[arcNum + 5];

    int num = 0;
    for (int i = 0; i < GetVexNum(); i++)
        for (int j = 0; j < GetVexNum(); j++) {
            if (arcs[i][j] != -1) {
                edges[num++] = {i, j, arcs[i][j]};
            }
        }

    int dist[GetVexNum() + 5];
    memset(dist, DEFAULT_INFINITY, sizeof(dist));
    int last[GetVexNum() + 5];
    memset(last, DEFAULT_INFINITY, sizeof(last));
    dist[v1] = 0;

    for (int i = 0; i < limits; i++) {
        memcpy(last, dist, sizeof dist);
        for (int j = 0; j < arcNum; j++) {
            auto e = edges[j];
            dist[e.b] = min(dist[e.b], last[e.a] + e.c);
        }
    }
    return dist[v2];
}

template<class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum)
// �����������������Ԫ��Ϊes[],�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
{
    if (vertexMaxNum < 0)
        throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

    if (vertexMaxNum < vertexNum)
        throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;

    vertexes = new ElemType[vexMaxNum];      // �������ɶ�����Ϣ����
    tag = new Status[vexMaxNum];                   // ���ɱ�־����
    arcs = (int **) new int *[vexMaxNum];     // �����ڽӾ���
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum]();

    for (int v = 0; v < vexNum; v++) {
        vertexes[v] = es[v];
        tag[v] = UNVISITED;
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = -1;
    }
}

template<class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexMaxNum)
// �������������������������ĿΪvertexMaxNum�Ŀ�����ͼ
{
    if (vertexMaxNum < 0)
        throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;

    vertexes = new ElemType[vexMaxNum];     // �������ɶ�����Ϣ����
    tag = new Status[vexMaxNum];                  // ���ɱ�־����
    arcs = (int **) new int *[vexMaxNum];    // �����ڽӾ���
    for (int v = 0; v < vexMaxNum; v++) {
        arcs[v] = new int[vexMaxNum]();
        for (int i = 0; i < vexNum; ++i) {
            arcs[v][i] = -1;
        }
    }

}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::Clear()
// ���������������ͼ�Ķ������ͱ�������Ϊ0.
{
    vexNum = 0;
    arcNum = 0;
}

template<class ElemType>
bool AdjMatrixUndirGraph<ElemType>::IsEmpty()
// ����������������ͼΪ�շ���true,���򷵻�false.
{
    return vexNum == 0;
}

template<class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// ����������ͷŶ�����ռ�õĿռ�
{
    delete[]vertexes;                    // �ͷŶ�������
    delete[]tag;                            // �ͷű�־

    for (int v = 0; v < vexMaxNum; v++)    // �ͷ��ڽӾ������
        delete[]arcs[v];
    delete[]arcs;                        // �ͷ��ڽӾ���
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetOrder(ElemType &d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ������-1.
{
    for (int v = 0; v < vexNum; v++)
        if (vertexes[v] == d)
            return v;        // ����d����,�����������
    return -1;            // ����d������,����-1
}

template<class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
// ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;    // v��Χ��,����Ԫ�ز�����
    else {
        d = vertexes[v];      // ������v��Ԫ��ֵ����d
        return ENTRY_FOUND;    // ����Ԫ�ش���
    }
}

template<class ElemType>
Status AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;    // v��Χ��,����λ�ô�
    else {
        vertexes[v] = d;        // ������Ԫ�ص�ֵ��Ϊd
        return SUCCESS;          // �����޸ĳɹ�
    }
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
// ������������ض������
{
    return vexNum;
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetArcNum() const
// ������������ر���
{
    return arcNum;
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�����
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");// �׳��쳣

    for (int u = 0; u < vexNum; u++)
        if (arcs[v][u] != 0 || arcs[u][v] != 0)
            return u;

    return -1;                    // ����-1��ʾ���ڽӵ�
}

template<class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");        // �׳��쳣

    for (int u = v2 + 1; u < vexNum; u++)
        if (arcs[v1][u] != 0 || arcs[u][v1] != 0)
            return u;

    return -1;                        // ����-1��ʾ����һ���ڽӵ�
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertVex(const ElemType &d)
// ������������붥��d
{
    if (vexNum == vexMaxNum)
        throw Error("ͼ�Ķ��������ܳ�������������!");    // �׳��쳣
    for (int i = 0; i < vexNum; ++i) {
        if (d == vertexes[i]) {
            throw Error("������ͬ�ڵ�!");
        }
    }
    vertexes[vexNum] = d;
    tag[vexNum] = UNVISITED;
    for (int v = 0; v <= vexNum; v++) {
        arcs[vexNum][v] = -1;
        arcs[v][vexNum] = -1;
    }
    vexNum++;
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertArc(int v1, int v2, int W)
// ���������������������v1��v2�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");// �׳��쳣

    if (arcs[v1][v2] == -1) {      // ԭ����ͼ��û�б�(v1, v2)
        arcNum++;
        arcs[v1][v2] = W;
        //arcs[v2][v1] = 1;
    }
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteVex(const ElemType &d)
// ���������ɾ��Ԫ��Ϊd�Ķ���
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (vertexes[v] == d)
            break;
    if (v == vexNum)
        throw Error("ͼ�в�����Ҫɾ���Ķ���!");    // �׳��쳣

    for (int u = 0; u < vexNum; u++)             // ɾ���붥��d������ı�
        if (arcs[v][u] == 1) {
            arcNum--;
            arcs[v][u] = -1;
            arcs[u][v] = -1;
        }

    vexNum--;
    if (v < vexNum) {
        vertexes[v] = vertexes[vexNum];
        tag[v] = tag[vexNum];
        for (int u = 0; u <= vexNum; u++)
            arcs[v][u] = arcs[vexNum][u];
        for (int u = 0; u <= vexNum; u++)
            arcs[u][v] = arcs[u][vexNum];
    }
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteArc(int v1, int v2)
// ���������ɾ����������v1��v2�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");// �׳��쳣
    if (arcs[v1][v2] == 0) {
        throw Error("�˱߲�����!");
    }
    if (arcs[v1][v2] != 0) {    // ԭ����ͼ���ڱ�(v1, v2)
        arcNum--;
        arcs[v1][v2] = -1;
        //arcs[v2][v1] = 0;
    }
}

template<class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");    // �׳��쳣

    return tag[v];
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");    // �׳��쳣

    tag[v] = val;
}

template<class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
{
    vexNum = g.vexNum;
    vexMaxNum = g.vexMaxNum;
    arcNum = g.arcNum;

    vertexes = new ElemType[vexMaxNum];        // ���ɶ�����������
    tag = new Status[vexMaxNum];            // ���ɱ�־����
    arcs = (int **) new int *[vexMaxNum];    // �����ڽӾ���
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];

    for (int v = 0; v < vexNum; v++) {    // ���ƶ�����������
        vertexes[v] = g.vertexes[v];
        tag[v] = g.tag[v];
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = g.arcs[v][u];
    }
}

template<class ElemType>
AdjMatrixUndirGraph<ElemType> &AdjMatrixUndirGraph<ElemType>::operator=(const AdjMatrixUndirGraph<ElemType> &g)
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
    if (&g != this) {
        delete[]vertexes;                // �ͷŶ�������
        delete[]tag;                          // �ͷű�־

        for (int v = 0; v < vexMaxNum; v++)    // �ͷ��ڽӾ������
            delete[]arcs[v];
        delete[]arcs;                      // �ͷ��ڽӾ���
        vexNum = g.vexNum;
        vexMaxNum = g.vexMaxNum;
        arcNum = g.arcNum;

        vertexes = new ElemType[vexMaxNum];     // ���ɶ�����������
        tag = new Status[vexMaxNum];               // ���ɱ�־����
        arcs = (int **) new int *[vexMaxNum]; // �����ڽӾ���
        for (int v = 0; v < vexMaxNum; v++)
            arcs[v] = new int[vexMaxNum];

        for (int v = 0; v < vexNum; v++) {     // ���ƶ�����������
            vertexes[v] = g.vertexes[v];
            tag[v] = g.tag[v];
            for (int u = 0; u < vexNum; u++)
                arcs[v][u] = g.arcs[v][u];
        }
    }
    return *this;
}

template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::Display()
// �������: ��ʾ�ڽӾ�������ͼ
{
    cout << "  ";
    for (int v = 0; v < vexNum; v++)
        cout << "\t" << vertexes[v];
    cout << endl;

    for (int v = 0; v < vexNum; v++) {
        cout << vertexes[v];

        for (int u = 0; u < vexNum; u++) {
            print(arcs[v][u]);
            cout << "\t" << arcs[v][u];
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl;
    }
}

#endif
