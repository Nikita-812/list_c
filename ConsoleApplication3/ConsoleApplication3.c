#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>

static ULONG64 counter = 0;

typedef struct
{
	bool value;
	bool isF;
	struct List *nptr;
	struct List *pptr;
} List;

List *list_init(); // инициализация списка заглавным элементом
void list_add(List *p, bool n); // добавление элемента в конец списка
void list_pop(List *p); // удаление последнего элемента (т.е. элемента указывающего на первую структура списка)
void list_print(const List *p); //вывод содержимого списка в консоль



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
		} else if (c == '-')
		{
			getchar();
			list_pop(p);
		}
	}
	printf_s("Ваш список: \n");
	list_print(p);

	return 0 * _getch();
}

List *list_init()
{
	List *p = (List *) malloc(sizeof(List));
	if (p)
	{
		p->value = false;
		p->nptr = NULL;
		p->pptr = NULL;
		p->isF = false;
		counter = 1;
		return p;
	} else
	{
		fprintf_s(stderr, "Память не может быть аллоцирована");
		exit(-1);
	}
}
void list_add(List *p, bool n)//ссылка должна быть на заглавный элемент списка
{
	List *next = (List *) malloc(sizeof(List)); // добавляемый в список элемент
	if (next)
	{
		next->value = n;
		if (counter == 1)
		{
			p->nptr = next;
			next->isF = true;
			next->pptr = p;
			next->nptr = next;
		} else if (counter >= 2)
		{
			List *ptr = p->nptr;
			List *first = ptr;
			List *check = first->nptr;
			ULONG64 n = counter - 2;
			while (n--) ptr = ptr->nptr;

			ptr->nptr = next;
			next->pptr = ptr;
			next->nptr = first;
			next->isF = false;
		}
		counter++;
	} else
	{
		fprintf_s(stderr, "Память не может быть аллоцирована");
		exit(-1);
	}
}
void list_pop(List *p)
{ //ссылка должна быть на заглавный элемент списка, функция не долж-на вызываться когда список содержит только заглавный элемент{
	if (counter > 2)
	{
		List *ptr = p->nptr;
		List *first = ptr;
		List *prev = NULL;
		ULONG64 n = counter - 2;
		while (n--) ptr = ptr->nptr;

		prev = ptr->pptr;
		prev->nptr = first;
		free(ptr);
	} else if (counter == 2)
	{
		List *ptr = p->nptr;
		p->nptr = NULL;
		free(ptr);
	} else
	{
		fprintf_s(stderr, "Удаление элемента из пустого списка");
		exit(-1);
	}
	counter--;
}
void list_print(const List *p)
{
	if (p->nptr)
	{
		List *ptr = p->nptr;
		ULONG64 n = counter - 2;
		while (n)
		{
			n--;
			printf_s("%d ", ptr->value);
			ptr = ptr->nptr;
		}
		printf_s("%d", ptr->value);
	} else printf_s("Список пуст");

	putchar('\n');
}