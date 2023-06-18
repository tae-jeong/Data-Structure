#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

//main()애서 사용하는 함수를 완성하시오.
void init(HeapType* h)
{
	h->heap_size = 0;
}
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;

}
element delete_min_heap(HeapType* h) {

	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child <= h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item;

}





int main()
{
	int sel_num = 10;
	element list[MAX_ELEMENT];
	int size = 100;
	HeapType heap;

	init(&heap);
	srand(1);
	printf("대상  리스트");
	for (int i = 0; i < size; i++) {
		list[i].key = rand() % 10000;
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", list[i].key);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
		insert_min_heap(&heap, list[i]);

	printf("\n작은 키 %d 선택 리스트\n", sel_num);
	for (int i = 0; i < sel_num; i++)
		printf("%d ", delete_min_heap(&heap).key);
	printf("\n");

	return 0;
}
/*예시 결과
대상  리스트
41 8467 6334 6500 9169 5724 1478 9358 6962 4464
5705 8145 3281 6827 9961 491 2995 1942 4827 5436
2391 4604 3902 153 292 2382 7421 8716 9718 9895
5447 1726 4771 1538 1869 9912 5667 6299 7035 9894
8703 3811 1322 333 7673 4664 5141 7711 8253 6868
5547 7644 2662 2757 37 2859 8723 9741 7529 778
2316 3035 2190 1842 288 106 9040 8942 9264 2648
7446 3805 5890 6729 4370 5350 5006 1101 4393 3548
9629 2623 4084 9954 8756 1840 4966 7376 3931 6308
6944 2439 4626 1323 5537 1538 6118 2082 2929 6541

작은 키 10 선택 리스트
37 41 106 153 288 292 333 491 778 1101
계속하려면 아무 키나 누르십시오 . . .
*/

/*  201810771 박태정 출력결과입니다!
대상  리스트
41 8467 6334 6500 9169 5724 1478 9358 6962 4464
5705 8145 3281 6827 9961 491 2995 1942 4827 5436
2391 4604 3902 153 292 2382 7421 8716 9718 9895
5447 1726 4771 1538 1869 9912 5667 6299 7035 9894
8703 3811 1322 333 7673 4664 5141 7711 8253 6868
5547 7644 2662 2757 37 2859 8723 9741 7529 778
2316 3035 2190 1842 288 106 9040 8942 9264 2648
7446 3805 5890 6729 4370 5350 5006 1101 4393 3548
9629 2623 4084 9954 8756 1840 4966 7376 3931 6308
6944 2439 4626 1323 5537 1538 6118 2082 2929 6541

작은 키 10 선택 리스트
37 41 106 153 288 292 333 491 778 1101

C:\Users\k\source\repos\guaje1\Debug\guaje1.exe(프로세스 5752개)이(가) 종료되었습니다(코드: 0개).
디버깅이 중지될 때 콘솔을 자동으로 닫으려면[도구] ->[옵션] ->[디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요... */