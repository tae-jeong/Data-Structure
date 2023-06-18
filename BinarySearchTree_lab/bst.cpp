
#define _CRT_SECURE_NO_WARNINGS
#define MAXWORD 80

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

typedef struct element {
	char word[MAXWORD];
	int count;
} element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

// ��ȯ���� Ž�� �Լ�
TreeNode* search(TreeNode* node, char* word)
{
	if (node == NULL) return NULL;
	int cmp = strcmp(node->data.word, word);
	if (cmp == 0)
		return node;
	else if (cmp > 0)
		return search(node->left, word);
	else
		return search(node->right, word);
}
TreeNode* new_node(char* word)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(temp->data.word, word);
	temp->data.count = 1;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* node, char* word)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(word);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	int cmp = strcmp(node->data.word, word);
	if (cmp == 0)
		node->data.count++;
	else if (cmp > 0)
		node->left = insert_node(node->left, word);
	else
		node->right = insert_node(node->right, word);

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}
// �Ʒ� �Լ��� �ϼ��Ͻÿ�. 
int get_height(TreeNode* node) {
	if (!node)
		return 0;
	else {
		int leftheight = get_height(node->left);
		int rightheight = get_height(node->right);
		return 1 + (leftheight > rightheight ? leftheight : rightheight);
	}
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
TreeNode* max_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->right != NULL)
		current = current->right;
	return current;

}
// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� 
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�. 
TreeNode* delete_node(TreeNode* root, char* word)
{
	if (root == NULL) return root;

	int cmp = strcmp(root->data.word, word);
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (cmp < 0)
		root->right = delete_node(root->right, word);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (cmp > 0)
		root->left = delete_node(root->left, word);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// �� ��° ���: �ڽ��� 2���� ���
		if (get_height(root->left) >= get_height(root->right)) {// ���ǽ��� �ϼ��Ͻÿ�.
			TreeNode* temp = max_value_node(root->left);
			// �߿� ��ȸ�� ���� ��带 �����Ѵ�. 
			root->data = temp->data;
			// �߿� ��ȸ�� ���� ��带 �����Ѵ�. 
			root->left = delete_node(root->left, temp->data.word);
		}
		else {// �Ʒ��� �ϼ��Ͻÿ�. 
			TreeNode* temp = min_value_node(root->right);
			root->data = temp->data;
			root->right = delete_node(root->right, temp->data.word);

		}
	}
	return root;
}

// ���� ��ȸ
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("%s \t%d\n", root->data.word, root->data.count);
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}

int main(void)
{
	TreeNode* root = NULL;

	FILE* fp;
	char word[MAXWORD];

	fp = fopen("data.txt", "r");
	while (fscanf(fp, "%s", word) != EOF) {
		printf("%s ", word);
		root = insert_node(root, word);
	}
	printf("\n");
	fclose(fp);

	printf("�ܾ� \tȸ��\n");
	inorder(root);

	printf("������ �ܾ�(����:0): ");
	scanf_s("%s", word, sizeof(word));
	while (word[0] != '0') {
		delete_node(root, word);
		inorder(root);
		printf("������ �ܾ�(����:0): ");
		scanf("%s", word);
	}

	return 0;
}

/*��°�� ����
The output from Huffmans algorithm can be viewed as a variable length code table
for encoding a source symbol such as a character in a file The algorithm derive
s this table from the estimated probability or frequency of occurrence for each
possible value of the source symbol As in other entropy encoding methods more co
mmon symbols are generally represented using fewer bits than less common symbols
Huffmans method can be efficiently implemented finding a code in time linear to
the number of input weights if these weights are sorted However although optima
l among methods encoding symbols separately Huffman coding is not always optimal
among all compression methods it is replaced with arithmetic coding or asymmetr
ic numeral systems if better compression ratio is required
�ܾ�    ȸ��
As      1
However         1
Huffman         1
Huffmans        2
The     2
a       5
algorithm       2
all     1
although        1
always  1
among   2
are     2
arithmetic      1
as      2
asymmetric      1
be      2
better  1
bits    1
can     2
character       1
code    2
coding  2
common  2
compression     2
derives         1
each    1
efficiently     1
encoding        3
entropy         1
estimated       1
fewer   1
file    1
finding         1
for     2
frequency       1
from    2
generally       1
if      2
implemented     1
in      3
input   1
is      3
it      1
length  1
less    1
linear  1
method  1
methods         3
more    1
not 1
number  1
numeral         1
occurrence      1
of      3
optimal         2
or 2
other   1
output  1
possible        1
probability     1
ratio   1
replaced        1
represented     1
required        1
separately      1
sorted  1
source  2
such    1
symbol  2
symbols         3
systems         1
table   2
than    1
the     3
these   1
this    1
time    1
to      1
using   1
value   1
variable        1
viewed  1
weights         2
with    1
������ �ܾ�(����:0) : the
As      1
However         1
Huffman         1
Huffmans        2
The     2
a       5
algorithm       2
all     1
although        1
always  1
among   2
are     2
arithmetic      1
as      2
asymmetric      1
be      2
better  1
bits    1
can     2
character       1
code    2
coding  2
common  2
compression     2
derives         1
each    1
efficiently     1
encoding        3
entropy         1
estimated       1
fewer   1
file    1
finding         1
for     2
frequency       1
from    2
generally       1
if      2
implemented     1
in      3
input   1
is      3
it      1
length  1
less    1
linear  1
method  1
methods         3
more    1
not 1
number  1
numeral         1
occurrence      1
of      3
optimal         2
or 2
other   1
output  1
possible        1
probability     1
ratio   1
replaced        1
represented     1
required        1
separately      1
sorted  1
source  2
such    1
symbol  2
symbols         3
systems         1
table   2
than    1
these   1
this    1
time    1
to      1
using   1
value   1
variable        1
viewed  1
weights         2
with    1
������ �ܾ�(����:0) : 0
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/


/* 201810771 ������ ��°���Դϴ�!
The output from Huffmans algorithm can be viewed as a variable length code table
for encoding a source symbol such as a character in a file The algorithm derives
this table from the estimated probability or frequency of occurrence for each
possible value of the source symbol As in other entropy encoding methods more co
mmon symbols are generally represented using fewer bits than less common symbols
Huffmans method can be efficiently implemented finding a code in time linear to
the number of input weights if these weights are sorted However although optima
l among methods encoding symbols separately Huffman coding is not always optimal
among all compression methods it is replaced with arithmetic coding or asymmetr
ic numeral systems if better compression ratio is required
�ܾ�    ȸ��
As      1
However         1
Huffman         1
Huffmans        2
The     2
a       5
algorithm       2
all     1
although        1
always  1
among   2
are     2
arithmetic      1
as      2
asymmetric      1
be      2
better  1
bits    1
can     2
character       1
code    2
coding  2
common  2
compression     2
derives         1
each    1
efficiently     1
encoding        3
entropy         1
estimated       1
fewer   1
file    1
finding         1
for     2
frequency       1
from    2
generally       1
if      2
implemented     1
in      3
input   1
is      3
it      1
length  1
less    1
linear  1
method  1
methods         3
more    1
not 1
number  1
numeral         1
occurrence      1
of      3
optimal         2
or 2
other   1
output  1
possible        1
probability     1
ratio   1
replaced        1
represented     1
required        1
separately      1
sorted  1
source  2
such    1
symbol  2
symbols         3
systems         1
table   2
than    1
the     3
these   1
this    1
time    1
to      1
using   1
value   1
variable        1
viewed  1
weights         2
with    1
������ �ܾ�(����:0) : the
As      1
However         1
Huffman         1
Huffmans        2
The     2
a       5
algorithm       2
all     1
although        1
always  1
among   2
are     2
arithmetic      1
as      2
asymmetric      1
be      2
better  1
bits    1
can     2
character       1
code    2
coding  2
common  2
compression     2
derives         1
each    1
efficiently     1
encoding        3
entropy         1
estimated       1
fewer   1
file    1
finding         1
for     2
frequency       1
from    2
generally       1
if      2
implemented     1
in      3
input   1
is      3
it      1
length  1
less    1
linear  1
method  1
methods         3
more    1
not 1
number  1
numeral         1
occurrence      1
of      3
optimal         2
or 2
other   1
output  1
possible        1
probability     1
ratio   1
replaced        1
represented     1
required        1
separately      1
sorted  1
source  2
such    1
symbol  2
symbols         3
systems         1
table   2
than    1
these   1
this    1
time    1
to      1
using   1
value   1
variable        1
viewed  1
weights         2
with    1
������ �ܾ�(����:0) : 0

C : \Users\k\source\repos\WOrd\Debug\WOrd.exe(���μ��� 13560��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� ��������[����] ->[�ɼ�] ->[�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������...*/
