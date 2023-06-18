
#define _CRT_SECURE_NO_WARNINGS
#define MAXWORD 80

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct element {
    char word[MAXWORD];
    int count;
} element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// �ʱ�ȭ �Լ�
ListNode* init(ListNode* head)
{
    head = (ListNode*)malloc(sizeof(ListNode));
    if (head == NULL) exit(1);
    head->link = NULL;
    return head;
}
//��� ��带 �̿��� ���� �Լ�
void insert_node(ListNode* head, char* key) {
    int cmp;
    ListNode* prev, * ptr = NULL;
    //�Ʒ��� �ϼ��Ͻÿ�
    ListNode* newnode;
    newnode = (ListNode*)malloc(sizeof(ListNode));
    newnode->data.count = 0;
    newnode->link = NULL;
    strcpy(newnode->data.word, key);

    if (head->link == NULL) {

        head->link = newnode;
        newnode->link = NULL;
        newnode->data.count++;
        return;
    }
    prev = head;
    ptr = head->link;

    while (ptr != NULL && strcmp(ptr->data.word, key) == -1) {
        ptr = ptr->link;
        prev = prev->link;

    }

    if (ptr != NULL && strcmp(ptr->data.word, key) == 0)
        ptr->data.count++;
    else {
        newnode->link = prev->link;
        prev->link = newnode;
        newnode->data.count++;
    }



}
//��� ��带 �̿��� ���� �Լ�
void delete_node(ListNode* head, char* key)
{
    int cmp;
    ListNode* prev, * ptr, * removed;

    prev = head;
    ptr = head->link;
    while (ptr != NULL) {
        cmp = strcmp(ptr->data.word, key);
        if (cmp < 0) {
            prev = ptr;
            ptr = ptr->link;
        }
        else if (cmp == 0) {
            removed = ptr;
            prev->link = ptr->link;
            free(removed);

            return;
        }
        else
            return;
    }
}
void sort_print(ListNode* head) {
    ListNode* ptr = head->link;

    printf("�ܾ� \tȸ��\n");
    while (ptr) {
        printf("%s \t%d\n", ptr->data.word, ptr->data.count);
        ptr = ptr->link;
    }
}
int main()
{
    FILE* fp;
    char word[MAXWORD];
    ListNode* head = NULL;

    head = init(head);
    FILE* fs = fopen("data.txt", "r");  //ó���� ��ü������ �ȳ��ͼ� 115�ٱ��� �߰��Ͽ����ϴ�. 
    char allword[200];
    fgets(allword, 50, fs);
    printf("%s", allword);
    fgets(allword, 50, fs);
    printf("%s", allword);
    fgets(allword, 50, fs);
    printf("%s", allword);
    fgets(allword, 50, fs);
    printf("%s", allword);


    //fopen_s(&fp, "data.txt", "r");
    fp = fopen("data.txt", "r");
    //while (fscanf_s(fp, "%s", word, sizeof(word)) != EOF) {
    while (!feof(fp))
    {
        //�������� �и��� ���� �б�
        fscanf(fp, "%s\n", word);
        insert_node(head, word);
    }
    printf("\n");
    fclose(fp);

    sort_print(head);

    printf("������ �ܾ�(����:0): ");
    scanf_s("%s", word, sizeof(word));
    while (word[0] != '0') {
        delete_node(head, word);
        sort_print(head);
        printf("������ �ܾ�: ");
        //scanf_s("%s", word, sizeof(word));
        scanf("%s", word);
    }

    return 0;


}
/*
���� ����� ����ϴ� ���� ����� ���� ���� �ƴմϴ� �ٸ� ������� ���� ȫ�ȸ���
����������� ����� ���� ��ߵ� ����ϴ� ����Դϴ�
�ܾ�    ȸ��
����    1
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�(����:0): ����
�ܾ�    ȸ��
����    1
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
ȫ�ȸ���        1
������ �ܾ�: 0
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
*/


/* 201810771 ������ ��°���Դϴ�. ó�� ��ü������ ���� �ؽ�Ʈ������ �Ϸķ� �ȵθ� ����ġ�ھ �����Ѽ����� �ʰ� ���ະ�� ��Ÿ�������ϴ�.
���� ����� ����ϴ� ����
����� ���� ���� �ƴմϴ�
�ٸ� ������� ���� ȫ�ȸ��� �����������
����� ���� ��ߵ� ����ϴ� ����Դϴ�
�ܾ�    ȸ��
����    1
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
����    1
ȫ�ȸ���        1
������ �ܾ�(����:0): ����
�ܾ�    ȸ��
����    1
����    1
�����  1
����Դϴ�      1
����    2
����    1
�ٸ�    1
�����  1
�����  1
��ߵ�  1
�������        1
����ϴ�        2
�����������    1
�ƴմϴ�        1
ȫ�ȸ���        1
������ �ܾ�: 0

C:\Users\k\source\repos\hohohohohoho\Debug\hohohohohoho.exe(���μ��� 3060��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
������� ������ �� �ܼ��� �ڵ����� �������� [����] -> [�ɼ�] -> [�����] > [������� �����Ǹ� �ڵ����� �ܼ� �ݱ�]�� ����ϵ��� �����մϴ�.
�� â�� �������� �ƹ� Ű�� ��������... */
