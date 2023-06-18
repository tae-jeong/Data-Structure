
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

// 초기화 함수
ListNode* init(ListNode* head)
{
    head = (ListNode*)malloc(sizeof(ListNode));
    if (head == NULL) exit(1);
    head->link = NULL;
    return head;
}
//헤더 노드를 이용한 삽입 함수
void insert_node(ListNode* head, char* key) {
    int cmp;
    ListNode* prev, * ptr = NULL;
    //아래를 완성하시오
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
//헤더 노드를 이용한 삭제 함수
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

    printf("단어 \t회수\n");
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
    FILE* fs = fopen("data.txt", "r");  //처음에 전체문장이 안나와서 115줄까지 추가하였습니다. 
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
        //공백으로 분리된 파일 읽기
        fscanf(fp, "%s\n", word);
        insert_node(head, word);
    }
    printf("\n");
    fclose(fp);

    sort_print(head);

    printf("삭제할 단어(종료:0): ");
    scanf_s("%s", word, sizeof(word));
    while (word[0] != '0') {
        delete_node(head, word);
        sort_print(head);
        printf("삭제할 단어: ");
        //scanf_s("%s", word, sizeof(word));
        scanf("%s", word);
    }

    return 0;


}
/*
내가 당신을 사랑하는 것은 까닭이 없는 것이 아닙니다 다른 사람들은 나의 홍안만을
사랑하지마는 당신은 나의 백발도 사랑하는 까닭입니다
단어    회수
것은    1
것이    1
까닭이  1
까닭입니다      1
나의    2
내가    1
다른    1
당신은  1
당신을  1
백발도  1
사람들은        1
사랑하는        2
사랑하지마는    1
아닙니다        1
없는    1
홍안만을        1
삭제할 단어(종료:0): 없는
단어    회수
것은    1
것이    1
까닭이  1
까닭입니다      1
나의    2
내가    1
다른    1
당신은  1
당신을  1
백발도  1
사람들은        1
사랑하는        2
사랑하지마는    1
아닙니다        1
홍안만을        1
삭제할 단어: 0
계속하려면 아무 키나 누르십시오 . . .
*/


/* 201810771 박태정 출력결과입니다. 처음 전체문장은 원본 텍스트파일을 일렬로 안두면 못고치겠어서 원본훼손하지 않고 각행별로 나타내었습니다.
내가 당신을 사랑하는 것은
까닭이 없는 것이 아닙니다
다른 사람들은 나의 홍안만을 사랑하지마는
당신은 나의 백발도 사랑하는 까닭입니다
단어    회수
것은    1
것이    1
까닭이  1
까닭입니다      1
나의    2
내가    1
다른    1
당신은  1
당신을  1
백발도  1
사람들은        1
사랑하는        2
사랑하지마는    1
아닙니다        1
없는    1
홍안만을        1
삭제할 단어(종료:0): 없는
단어    회수
것은    1
것이    1
까닭이  1
까닭입니다      1
나의    2
내가    1
다른    1
당신은  1
당신을  1
백발도  1
사람들은        1
사랑하는        2
사랑하지마는    1
아닙니다        1
홍안만을        1
삭제할 단어: 0

C:\Users\k\source\repos\hohohohohoho\Debug\hohohohohoho.exe(프로세스 3060개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요... */
