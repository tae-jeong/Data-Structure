#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000

int list[MAX_SIZE];
//�ݺ� ����
int search_binary1(int key, int low, int high) {
    int middle;
    while (low <= high) { 				// ���� Ű���� ���� ������
        middle = (low + high) / 2;
        if (key == list[middle]) 
            return middle; 	// Ž�� ����
        else if (key < list[middle]) 
            low = middle + 1; 	// ������ �κи���Ʈ Ž��
        else high = middle - 1; 			// ���� �κи���Ʈ Ž��
    }
    return -1; 					// Ž�� ����
}

//��ȯ ����
int search_binary2(int key, int low, int high) {
//�Ʒ��� �ϼ��Ͻÿ�.
    int middle;

    if (low <= high) {
        middle = (low + high) / 2;
        if (key == list[middle])
            return middle;
        else if (key < list[middle])
            return  search_binary2(key, middle + 1, high);
        else
            return  search_binary2(key, low, middle - 1);
    }
    return -1;


}
int compare(const void* v1, const void* v2)	// ���Լ� ����
{
    int cmpvalue1, cmpvalue2;

    cmpvalue1 = *(int*)v1;	
    cmpvalue2 = *(int*)v2;

    //return cmpvalue1 - cmpvalue2;	// �������� ����
    return cmpvalue2 - cmpvalue1;	// �������� ����
}
int main(void)
{
    //srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_SIZE; i++)
        list[i] = rand() % 1000;
    qsort(list, MAX_SIZE, sizeof(int), compare);
    int key = 10, index;
    
    index= search_binary1(key, 0, MAX_SIZE - 1);
    printf("�ݺ� ���� Ž�� �ε���: %d\n", index);

    index= search_binary2(key, 0, MAX_SIZE - 1);
    printf("��ȯ ���� Ž�� �ε���: %d\n", index);

    return 0;
}
/*���� ���
�ݺ� ���� Ž�� �ε���: 9896
��ȯ ���� Ž�� �ε���: 9896
����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .

�������
�ݺ� ���� Ž�� �ε���: 9896
��ȯ ���� Ž�� �ε���: 9896

C:\Users\k\source\repos\Project9\Debug\Project9.exe(���μ��� 9904��)��(��) ����Ǿ����ϴ�(�ڵ�: 0��).
�� â�� �������� �ƹ� Ű�� ��������...


*/