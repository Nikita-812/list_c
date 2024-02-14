
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <locale.h>

static int counter = 0; 

typedef struct
{
	bool value;
	bool isF;
	struct List *nptr;
	struct List *pptr;
} List;

List *list_init(); // èíèöèàëèçàöèÿ ñïèñêà çàãëàâíûì ýëåìåíòîì
void list_add(List *p, bool n);// äîáàâëåíèå ýëåìåíòà â êîíåö ñïèñêà
void list_pop(List *p);// óäàëåíèå ïîñëåäíåãî ýëåìåíòà (ò.å. ýëåìåíòà óêàçûâàþùåãî íà ïåðâóþ ñòðóêòóðà ñïèñêà)
void list_print(const List *p); //âûâîä ñîäåðæèìîãî ñïèñêà â êîíñîëü



int main()
{
	setlocale(0, "");
	List *p = list_init();
	char c = 0;
	printf_s("Введите начальные элементы списка: ");
	while ((c = getchar()) != '\n')
	{
		if (c == ' ') continue;
		list_add(p, c - '0');
	}
	printf_s("Что вы хотите сделать с вашим списком? + x добавить элемент x, - удалить последний элемент, 0 - завершить программу: \n");
	while ((c = getchar()) != '0')
	{
		char tmp = 0;
		if (c == '+')
		{
			tmp = getchar();
			getchar();
			list_add(p, tmp - '0');
		}
		else if (c == '-')
		{
			getchar();
			list_pop(p);
		}
	}
	printf_s("Ваш список: \n");
	list_print(p);
	
	return 0;
}

List *list_init()
{
	List *p = (List*) malloc(sizeof(List));
	if (p)
	{
		p->value = false;
		p->nptr = NULL;
		p->pptr = NULL;
		p->isF = false;
		counter = 1;
		return p;
	}
	else
	{
		exit(-1);
		fprintf_s(stderr, "Память не может быть аллоцирована");
	}
}
void list_add(List *p, bool n) //ññûëêà äîëæíà áûòü íà çàãëàâíûé ýëåìåíò ñïèñêà
{
	List *next = (List *)malloc(sizeof(List)); // äîáàâëÿåìûé â ñïèñîê ýëåìåíò
	if (next) {
		next->value = n;

		if (counter == 1)
		{
			p->nptr = next;
			next->isF = true;
			next->pptr = p;
			next->nptr = next;
		}
		else if (counter >= 2)
		{
			List *ptr = p->nptr;
			List *first = ptr;
			List *check = first->nptr;
			int n = counter - 2;
			while (n--)
			{
				ptr = ptr->nptr;
			}
			ptr->nptr = next;
			next->pptr = ptr;
			next->nptr = first;
			next->isF = false;
		}
		counter++;
	}
	else
	{
		exit(-1);
		fprintf_s(stderr, "Память не может быть аллоцирована");
	}
}
void list_pop(List *p) //ññûëêà äîëæíà áûòü íà çàãëàâíûé ýëåìåíò ñïèñêà, ôóíêöèÿ íå äîëæíà âûçûâàòüñÿ êîãäà ñïèñîê ñîäåðæèò òîëüêî çàãëàâíûé ýëåìåíò
{


	if (counter > 2)
	{

		List *ptr = p->nptr;
		List *first = ptr;
		List *check = first->nptr;
		List *prev = NULL;
		while (!check->isF)
		{
			ptr = ptr->nptr;
			check = ptr->nptr;
		}
		prev = ptr->pptr;
		prev->nptr = first;
		free(ptr);
	}
	else if (counter == 2)
	{
		List *ptr = p->nptr;
		p->nptr = NULL;
		free(ptr);
	}
	else
	{
		exit(-1);
		fprintf_s(stderr, "Memory cannot be allocated");
	}
	counter--;
}
void list_print(const List *p)
{
	if (p->nptr) 
	{
		List *ptr = p->nptr;
		int n = counter - 2;
		while (n)
		{
			n--;
			printf_s("%d ", ptr->value);
			ptr = ptr->nptr;
		}
		printf_s("%d", ptr->value);
	}
	else
	{
		printf_s("Список пуст");
	}
	putchar('\n');
}