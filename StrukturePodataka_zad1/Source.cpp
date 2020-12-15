#include<stdio.h>
#include<malloc.h>

using namespace std;

struct Student {
	char ime[20];
	char prezime[20];
	float bodovi;
};

int main() {
	FILE* fptr = fopen("studenti.txt", "r");
	float maxBodovi = 50;

	// koliko ima studenata
	int i = 1;
	while (!feof(fptr)) {
		if (fgetc(fptr) == (int)'\n')
			i++;
	}
	printf("Datoteka ima %d studenta\n\n", i);

	rewind(fptr); // Vrati fptr na pocekat datoteke
	
	// alokacija memorije
	Student* NizStudenata = (Student*)malloc(i * sizeof(Student));

	if (NizStudenata) { // Provjerava je li malloc uspjesno alocira memoriju
		Student* trenutniStudent;

		// upis u niz pomocu fscanf
		int j;
		for (j = 0; j < i; j++) {
			trenutniStudent = NizStudenata + j;
			(void)fscanf(fptr, "%s %s %f", trenutniStudent->ime, trenutniStudent->prezime, &(trenutniStudent->bodovi));
		}

		// ispis
		for (j = 0; j < i; j++) {
			trenutniStudent = NizStudenata + j;
			printf("%s %s %1.f (%0.f%%)\n", trenutniStudent->ime, trenutniStudent->prezime, trenutniStudent->bodovi, (trenutniStudent->bodovi / maxBodovi) * 100);
		}

		free(NizStudenata);
	}
	else printf("Nedovoljna memorija za alokaciju");

	fclose(fptr);
	return 0;
}