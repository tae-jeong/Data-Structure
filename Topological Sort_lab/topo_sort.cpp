#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

GraphType g;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_arr(int arr[], int in[], int s, int i, int size) {
	for (int j = 0; j < g.n; j++)
		printf("%3d", in[j]);
	printf("\n");
	for (int j = 0; j < g.n; j++)
		printf("%3d", arr[j]);
	printf("  - s:%d, i:%d, size:%d\n", s, i, size);
}
void generate(int arr[], int s, int size, int* in) {
	int i, tmp;
	int in_degree[MAX_VERTICES];
	for (i = 0; i < g.n; i++)			// copy
		in_degree[i] = in[i];

	GraphNode* node = g.adj_list[arr[s]];	//�� ������ ���� ������ ����
	while (node != NULL) {
		int u = node->vertex;
		in_degree[u]--;			//���� ������ ����
		if (in_degree[u] == 0)
			arr[size++] = u;
		node = node->link;   // ���� ����
	}
	s++;
	if (s == g.n) {
		for (i = 0; i < g.n; i++)
			printf("����%d->", arr[i]);
		printf("\n");
	}
	else {
		for (i = s; i < size; i++) {
			SWAP(arr[s], arr[i], tmp);
			generate(arr, s, size, in_degree);
			SWAP(arr[s], arr[i], tmp);
		}
	}
}
// ���������� �����Ѵ�.
void topo_sort()
{
	int i, tmp;
	int arr[MAX_VERTICES], size;
	int in_degree[MAX_VERTICES];

	// ��� ������ ���� ������ ���
	for (i = 0; i < g.n; i++)			// �ʱ�ȭ
		in_degree[i] = 0;
	for (i = 0; i < g.n; i++) {
		GraphNode* node = g.adj_list[i];//���� i���� ������ ������
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// ���� ������ 0�� ������ �迭�� ����
	size = 0;
	for (i = 0; i < g.n; i++) {
		if (in_degree[i] == 0)
			arr[size++] = i;
	}
	// ��� ���� ������ ���� 
	for (i = 0; i < size; i++) {
		SWAP(arr[0], arr[i], tmp);
		generate(arr, 0, size, in_degree);
		SWAP(arr[0], arr[i], tmp);
	}
}
//	
int main(void)
{
	graph_init(&g);
	//������ �־��� �׷����� ���� ��������Ʈ�� �ϼ��Ͻÿ�.
	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);
	insert_vertex(&g, 4);
	insert_vertex(&g, 5);

	insert_edge(&g, 0, 2);
	insert_edge(&g, 0, 3);

	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);

	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 5);

	insert_edge(&g, 3, 5);

	insert_edge(&g, 4, 5);



	//���� ���� 
	topo_sort();
	// ���� �޸� ��ȯ �ڵ� ����
	return 0;
}
/*��¿���
����0->����1->����2->����4->����3->����5->
����0->����1->����2->����3->����4->����5->
����0->����1->����4->����2->����3->����5->
����0->����2->����1->����4->����3->����5->
����0->����2->����1->����3->����4->����5->
����1->����0->����4->����2->����3->����5->
����1->����0->����2->����4->����3->����5->
����1->����0->����2->����3->����4->����5->
����1->����4->����0->����2->����3->����5->
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/

/* 201810771 ������ ��°���Դϴ�!
����0->����1->����2->����4->����3->����5->
����0->����1->����2->����3->����4->����5->
����0->����1->����4->����2->����3->����5->
����0->����2->����1->����4->����3->����5->
����0->����2->����1->����3->����4->����5->
����1->����0->����4->����2->����3->����5->
����1->����0->����2->����4->����3->����5->
����1->����0->����2->����3->����4->����5->
����1->����4->����0->����2->����3->����5->

C:\Users\k\source\repos\Project4\Debug\Project4.exe(���μ��� 19420��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������... */
