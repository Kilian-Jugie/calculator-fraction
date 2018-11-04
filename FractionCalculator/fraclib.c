#include "fraclib.h"

int pgcd(int a, int b) {
	int r;
	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

#ifndef __cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


fraction* createFraction(int num, int denom) {
	fraction* f = malloc(sizeof(fraction));
	f->denom = denom;
	f->num = num;
	return f;
}

fraction* createFractionFromSimpleInput() {
	int num, denom;
	printf("Enter numerator: ");
	scanf("%d", &num);
	printf("Enter denominator: ");
	scanf("%d", &denom);
	return createFraction(num, denom);
}

fraction* createFractionFromInput() {
	int num, denom, size, i=0, opIndex;
	char* input = malloc(200), *buffer = malloc(200);
	printf("Enter numerator/denominator: ");
	scanf("%s", input);
	size = strlen(input);
	while (i < size&&input[i] != '/') {
		buffer[i] = input[i];
		++i;
	}
	opIndex = i;
	buffer[i] = '\0';
	num = atoi(buffer);
	++i;
	while (i < size) {
		buffer[i - opIndex-1] = input[i];
		++i;
	}
	buffer[i - opIndex-1] = '\0';
	denom = atoi(buffer);
	free(buffer);
	free(input);
	return createFraction(num, denom);
}

fraction* fadd(fraction* f1, fraction* f2) {
	fraction* ret;
	if (f1->denom != f2->denom)
		ret = createFraction(f1->num*f2->denom + f2->num*f1->denom, f1->denom*f2->denom);
	else
		ret = createFraction( f1->num + f2->num, f1->denom );
	return simplify(ret);
}

fraction* fsub(fraction* f1, fraction* f2) {
	fraction inverted = { -f2->num,f2->denom };
	return fadd(f1, &inverted);
}

fraction* fmul(fraction* f1, fraction* f2) {
	return simplify(createFraction(f1->num*f2->num, f1->denom*f2->denom));
}

fraction* fdiv(fraction* f1, fraction* f2) {
	fraction inverted = { f2->denom, f2->num };
	return fmul(f1, &inverted);
}

fraction* simplify(fraction* f) {
	int computedPgcd = pgcd(f->num, f->denom);
	f->num = f->num / computedPgcd;
	f->denom = f->denom / computedPgcd;
	return f; //Allow chaining
}

void printFraction(fraction* f) {
	printf("%d/%d", f->num, f->denom);
}

void deleteFraction(fraction* f) {
	if (f) {
		free(f);
		f = NULL;
	}
}

#else // __cplusplus
#include <iostream>
#include <string>

//On utilise un pointeur ici pour avoir une interface cohérence avec le C quitte à se compliquer un peu la vie
fraction* createFractionFromSimpleInput() {
	int num, denom;
	std::cout << "Enter numerator: ";
	std::cin >> num;
	std::cout << "Enter denominator: ";
	std::cin >> denom;
	return createFraction(num, denom);
}

//pointeur: voir createFractionFromSimpleInput
fraction* createFractionFromInput() {
	int num, denom, size, i(0);
	std::string input, buffer;
	std::cout << "Enter numerator/denominator: ";
	std::cin >> input;
	size = input.size();
	while (i < size&&input[i] != '/') {
		buffer.push_back(input[i]);
		++i;
	}
	try {
		num = atoi(buffer.c_str());
	}
	catch (...) {
		std::cerr << "ERROR: " << buffer.c_str() << " is not a number !";
		return nullptr;
	}
	buffer = "";
	++i;
	while (i < size) {
		buffer.push_back(input[i]);
		++i;
	}
	try {
		denom = atoi(buffer.c_str());
	}
	catch (...) {
		std::cerr << "ERROR: " << buffer.c_str() << " is not a number !";
		return nullptr;
	}
	return createFraction(num, denom);
}

fraction& fraction::operator+(const fraction& f) const {
	fraction copy(*this);
	return copy += f;
}

fraction& fraction::operator-(const fraction& f) const {
	fraction copy(*this);
	return copy -= f;
}

fraction& fraction::operator*(const fraction& f) const {
	fraction copy(*this);
	return copy *= f;
}

fraction& fraction::operator/(const fraction& f) const {
	fraction copy(*this);
	return copy /= f;
}

fraction& fraction::simplify() {
	int computedPgcd = pgcd(m_Num, m_Denom);
	m_Num /= computedPgcd;
	m_Denom /= computedPgcd;
	return *this; //Allow chaining
}

fraction fraction::operator-() const {
	return { -m_Num, m_Denom };
}

fraction& fraction::operator+=(const fraction& f) {
	fraction copy(f);
	if (m_Denom != copy.denom()) {
		m_Num *= copy.denom();
		copy.num() *= m_Denom;
		m_Denom = copy.denom() = m_Denom*copy.denom();
	}
	m_Num += copy.num();
	return simplify();
}

inline fraction& fraction::operator-=(const fraction& f) {
	return *this += (-f);
}

fraction& fraction::operator*=(const fraction& f) {
	m_Num *= f.num();
	m_Denom *= f.denom();
	return simplify();
}

fraction fraction::invert(const fraction& f) {
	return { f.denom(), f.num() };
}

fraction fraction::simplify(const fraction& f) {
	return fraction(f).simplify();
}

fraction& fraction::invert() {
	std::swap(m_Num, m_Denom);
	return *this;
}

fraction& fraction::operator/=(const fraction& f) {
	return *this *= fraction::invert(f);
}

#endif
