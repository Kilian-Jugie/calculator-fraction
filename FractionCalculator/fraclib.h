#ifndef _FRACLIB_GUARD__
#define _FRACLIB_GUARD__

int pgcd(int, int);

#ifndef __cplusplus
struct _fraction {
	int num, denom;
};

typedef struct _fraction fraction;


fraction *createFraction(int, int);
fraction *createFractionFromSimpleInput();
fraction *createFractionFromInput();

fraction* fadd(fraction*, fraction*);
fraction* fsub(fraction*, fraction*);
fraction* fmul(fraction*, fraction*);
fraction* fdiv(fraction*, fraction*);

fraction* simplify(fraction*);
void deleteFraction(fraction*);
void printFraction(fraction*);



#else
#include <iostream>
class fraction {
	int m_Num, m_Denom;
public:
	inline fraction(const int& numerator, const int& denominator) : m_Num(numerator), m_Denom(denominator) {};
	fraction(const fraction&) = default;
	~fraction() = default;

	fraction& operator+(const fraction&) const;
	fraction& operator-(const fraction&) const;
	fraction& operator*(const fraction&) const;
	fraction& operator/(const fraction&) const;

	fraction& operator+=(const fraction&);
	fraction& operator-=(const fraction&);
	fraction& operator*=(const fraction&);
	fraction& operator/=(const fraction&);

	fraction operator-() const;

	fraction& simplify();
	fraction& invert();
	static fraction simplify(const fraction&);
	static fraction invert(const fraction&);

	inline const int& num() const {
		return m_Num;
	}

	inline const int& denom() const {
		return m_Denom;
	}

	inline int& num() {
		return m_Num;
	}

	inline int& denom() {
		return m_Denom;
	}
};

namespace {
	inline std::ostream &operator<<(std::ostream &os, fraction const &m) {
		return os << m.num() << "/" << m.denom();
	}
}

//C interface compatibility
inline fraction* fadd(fraction* f1, fraction* f2) { return &(*f1 + *f2); }
inline fraction* fsub(fraction* f1, fraction* f2) { return &(*f1 - *f2); }
inline fraction* fmul(fraction* f1, fraction* f2) { return &(*f1 * *f2); }
inline fraction* fdiv(fraction* f1, fraction* f2) { return &(*f1 / *f2); }

inline fraction *createFraction(int n, int d) { return new fraction(n, d); }
fraction *createFractionFromSimpleInput();
fraction *createFractionFromInput();

inline fraction* simplify(fraction* f) { return &f->simplify(); }

inline void deleteFraction(fraction* f) { delete f; }
inline void printFraction(fraction* f) { std::cout << *f; }

#endif
#endif