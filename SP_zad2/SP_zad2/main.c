#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct OSOBA;
typedef struct OSOBA Osoba;
typedef struct OSOBA* pOsoba;
struct OSOBA {
	char name[50];
	char surname[50];
	int yob;
	pOsoba next;
};

int addEnd(pOsoba, char*, char*, int);
int addBegining(pOsoba, char*, char*, int);
int ispis(pOsoba);
pOsoba find(pOsoba, char*);
void deletePerson(pOsoba, char*);

int main() {
	Osoba head;
	head.next = NULL;

	addEnd(&head, "Mate", "Matic", 2002);
	addBegining(&head, "Jure", "Juric", 2000);
	addEnd(&head, "Luka", "Lukic", 1998);
	deletePerson(&head, "Juric");
	ispis(&head);

	return EXIT_SUCCESS;
}

int addBegining(pOsoba head, char* name, char* surname, int yob) {
	pOsoba temp = head->next;
	head->next = (pOsoba)malloc(sizeof(Osoba));
	if (head->next) {
		strcpy(head->next->name, name);
		strcpy(head->next->surname, surname);
		head->next->yob = yob;
		head->next->next = temp;
	}
	else {
		printf("Neuspjesna allokacija memorije");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int addEnd(pOsoba head, char* name, char* surname, int yob) {
	while (head->next != NULL) {
		head = head->next;
	}
	return addBegining(head, name, surname, yob);
}

pOsoba find(pOsoba head, char* surname) {
	head = head->next;
	while (head != NULL && strcmp(head->surname, surname) != 0) {
		head = head->next;
	}
	return head; // return = NULL ako ne moze pronaci osobu
}

void deletePerson(pOsoba head, char* surname) {
	pOsoba delOsoba = find(head, surname);

	if (delOsoba) {
		while (head->next != delOsoba) {
			head = head->next;
		}
		pOsoba temp = head->next->next;
		free(delOsoba);
		head->next = temp;
	}
}

int ispis(pOsoba head) {

	if (NULL == head->next) {
		printf("Lista je prazna");
	}

	head = head->next;
	int i = 1;
	while (NULL != head) {
		printf("%d. %s %s %d\n", i, head->name, head->surname, head->yob);
		i++;
		head = head->next;
	}
	return EXIT_SUCCESS;
}