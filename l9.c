#include <stdio.h>

int georgeSwitch() {
	FILE * george;
	FILE * newgeorge;
	char cur[1];

	george = fopen("george.txt", "r"); //open george for reading
	newgeorge = fopen("newgeorge.txt", "w"); //open newgeorge for writing

	while (!feof(george)) {
		
		fscanf(george, "%c", cur);
		if (cur <= 90 && cur >= 65) { //if capital letter then make lower
			fprintf(newgeorge, "%c", cur + 32);
		}
		else if (cur <= 122 && cur >= 97) {//if lower then make caps
			fprintf(newgeorge, "%c", cur - 32);
		}

	}
	fclose(george);
	fclose(newgeorge);
	return 0;
}

int pdfSize() {
	FILE * pdf;
	int size;
	char cur[1];

	pdf = fopen("w.pdf", "r");//open pdf to read

	while (!eof(pdf)) { //while not at end of file
		fscanf(pdf, "%c", cur);
		size++; //counts up every time it reads through a character
	}
	printf("File size is :%d\n", size);
	return 0;
}

int pdfCopy(){ //copies characters from w.pdf to new.pdf

	FILE * w;
	FILE * newp;
	char cur[1];

	w = fopen("w.pdf", "r"); //open george for reading
	newp = fopen("new.pdf", "w"); //open newgeorge for writing

	while (!feof(w)) {
		fscanf(w, "%c", cur);
		fprintf(newp, "%c", cur);
	}
	fclose(w);
	fclose(newp);
	return 0;
}

int main() {
	
	georgeSwitch();
	pdfSize();
	pdfCopy();

	system("pause");
	return 0;
}
