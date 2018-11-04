#include "fraclib.h"
#include <stdlib.h>
#include <stdio.h>

#define FRACLIB_TEST

#ifndef __cplusplus
void ctest() {
	int success = 0;
	do {
		fraction* f1 = createFractionFromInput();

		printf("Enter operator: ");
		char* op = malloc(50);
		scanf("%s", op);

		fraction* f2 = createFractionFromInput();

		printf("Executing operation: ");
		printFraction(f1);
		printf(" %c ", *op);
		printFraction(f2);
		printf("\n");

		fraction* fret;
		switch (*op) {
		case '+': fret = fadd(f1, f2);
			break;
		case '-': fret = fsub(f1, f2);
			break;
		case '*': fret = fmul(f1, f2);
			break;
		case '/': fret = fdiv(f1, f2);
			break;
		default:
			fret = createFraction(0, 0);
			--success;
			break;
		}
		++success;
		free(op);
		printFraction(fret);
		printf("\n");
		deleteFraction(fret);
		deleteFraction(f1);
		deleteFraction(f2);
		if (!success) {
			system("cls");
			printf("ERROR: operator entered is incorrect !\n");
		}
	} while (!success);
	
}
#else
#include <iostream>
void cpptest() {
	int success = 0;
	do {
		fraction* f1 = createFractionFromInput();

		std::cout << "Enter operator: ";
		char op;
		try {
			std::cin >> op;
		}
		catch (...) {
			system("cls");
			std::cerr << "ERROR: " << op << " is not a valid operator !\n";
			continue;
		}

		fraction* f2 = createFractionFromInput();
		std::cout << "Executing operation: " << *f1 << " " << op << " " << *f2 << "\n";

		fraction fret(0,0);
		switch (op) {
		case '+': fret = *f1 + *f2;
			break;
		case '-': fret = *f1 - *f2;
			break;
		case '*': fret = *f1 * *f2;
			break;
		case '/': fret = *f1 / *f2;
			break;
		default:
			--success;
			break;
		}
		++success;
		std::cout << "Result: " << fret << "\n";
		deleteFraction(f1);
		deleteFraction(f2);
		if (!success) {
			system("cls");
			printf("ERROR: an error occured !\n");
		}
	} while (!success);

}

#endif

#ifdef FRACLIB_TEST
int main() {
#ifndef __cplusplus
	ctest();
#else
	cpptest();
#endif
	system("pause");
	return 0;
}
#endif