module;
#include <math.h>
#include <iostream>
export module Math;
export class Complex
{
	double m_re;
	double m_im;
public:
	Complex() 
	{
		m_re = 0;
		m_im = 0;
	}
	Complex(double re) 
	{
		m_re = re;
		m_im = 0;
	}
	Complex(double re, double im) 
	{
		m_re = re;
		m_im = im;
	}

	Complex static FromExponentialForm(double mod, double arg) 
	{
		Complex newObj{ mod * cos(arg), mod * sin(arg) };
		return newObj;
	}

	Complex static FromAlgebraicForm(double re, double im) 
	{
		Complex newObj{ re, im };
		return newObj;
	}

	double Re() const 
	{
		return m_re;
	}

	double Im() const 
	{
		return m_im;
	}

	double Mod() const 
	{
		return sqrt(m_re * m_re + m_im * m_im);
	}

	double Arg() const 
	{
		return atan2(m_im, m_re);
	}

	explicit operator double() { return m_re; }

	Complex operator-() const
	{
		return Complex(-m_re, -m_im);
	}

	Complex& operator++()
	{
		m_re++;
		return *this;
	}

	Complex operator++(int)
	{
		Complex newObj(*this);
		++(*this);
		return newObj;
	}

	Complex& operator--()
	{
		m_re--;
		return *this;
	}

	Complex operator--(int)
	{
		Complex newObj(*this);
		--(*this);
		return newObj;
	}

	Complex& operator+=(Complex y)
	{
		m_re += y.m_re;
		m_im += y.m_im;
		return *this;
	}

	Complex& operator-=(Complex y)
	{
		m_re -= y.m_re;
		m_im -= y.m_im;
		return *this;
	}

	Complex& operator*=(Complex y)
	{
		double re = m_re * y.m_re - m_im * y.m_im;
		double im = m_re * y.m_im + m_im * y.m_re;
		m_re = re;
		m_im = im;
		return *this;
	}

	Complex& operator/=(Complex y)
	{
		double rex = m_re, rey = y.m_re, re;
		double imx = m_im, imy = y.m_im, im;
		re = (rex * rey + imx * imy) / (rey * rey + imy * imy);
		im = (rey * imx - rex * imy) / (rey * rey + imy * imy);
		m_re = re;
		m_im = im;
		return *this;
	}
	friend Complex operator+(const Complex&, const Complex&);
	friend Complex operator-(const Complex&, const Complex&);
	friend Complex operator*(const Complex&, const Complex&);
	friend Complex operator/(const Complex&, const Complex&);
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	friend Complex operator ""i(long double);
	friend Complex operator ""i(unsigned long long);
	friend Complex sin(const Complex&);
};


export Complex sin(const Complex& obj) 
{
	Complex newObj = obj;
	return Complex(sin((double)newObj));
}

export Complex operator+(const Complex& x, const Complex& y)
{
	return Complex(x.m_re + y.m_re, x.m_im + y.m_im);
}

export Complex operator-(const Complex& x, const Complex& y)
{
	return Complex(x.m_re - y.m_re, x.m_im - y.m_im);
}

export Complex operator*(const Complex& x, const Complex& y)
{
	double re = x.m_re * y.m_re - x.m_im * y.m_im;
	double im = x.m_re * y.m_im + x.m_im * y.m_re;
	return Complex(re, im);
}

export Complex operator/(const Complex& x, const Complex& y)
{
	double rex = x.m_re, rey = y.m_re, re;
	double imx = x.m_im, imy = y.m_im, im;
	re = (rex * rey + imx * imy) / (rey * rey + imy * imy);
	im = (rey * imx - rex * imy) / (rey * rey + imy * imy);
	return Complex(re, im);
}

export Complex operator ""i(unsigned long long im) 
{
	return Complex(0.0, (double)im);
}
export Complex operator ""i(long double im) 
{
	return Complex(0.0, (double)im);
}
export std::ostream& operator<<(std::ostream& stream, const Complex& inst) 
{
	if (inst.m_im < 0) 
	{
		stream << inst.m_re << inst.m_im << "i";
	}
	else 
	{
		stream << inst.m_re << "+" << inst.m_im << "i";
	}
	return stream;
}

export int FindGreatestCommonDivisor(int a, int b) 
{
	if (a < 0) 
	{
		a *= -1;
	}
	if (b < 0) 
	{
		b *= -1;
	}
	while (a != 0 && b != 0) 
	{
		if (a > b) 
		{
			a %= b;
		}
		else 
		{
			b %= a;
		}
	}
	return a + b;
}

export int FindLeastCommonMultiple(int a, int b) 
{
	return abs(a * b) / FindGreatestCommonDivisor(a, b);
}

export class Rational 
{

	int m_nominator;
	int m_denominator;

	void norm() 
	{
		int gcd = FindGreatestCommonDivisor(m_nominator, m_denominator);
		m_nominator /= gcd;
		m_denominator /= gcd;
		if (m_denominator < 0) 
		{
			m_denominator *= -1;
			m_nominator *= -1;
		}
	}

public:
	Rational()
	{
		m_nominator = 0;
		m_denominator = 1;
	}
	Rational(int nominator, int denominator) 
	{
		m_nominator = nominator;
		m_denominator = denominator;
		norm();
	}
	Rational(int nominator) 
	{
		m_nominator = nominator;
		m_denominator = 1;
		norm();
	}
	int Nominator() const 
	{
		return m_nominator;
	}

	int Denominator() const 
	{
		return m_denominator;
	}

	explicit operator double() const 
	{
		return (double)m_nominator / m_denominator;
	}

	Rational operator-() const 
	{
		return Rational(-m_nominator, m_denominator);
	}


	Rational& operator++()
	{
		m_nominator += m_denominator;
		norm();
		return *this;
	}

	Rational operator++(int)
	{
		Rational newObj(*this);
		++(*this);
		norm();
		return newObj;
	}

	Rational& operator--()
	{
		m_nominator -= m_denominator;
		norm();
		return *this;
	}

	Rational operator--(int)
	{
		Rational newObj(*this);
		--(*this);
		norm();
		return newObj;
	}

	Rational& operator+=(Rational y)
	{
		int denominator = FindLeastCommonMultiple(m_denominator, y.m_denominator);
		int nominator = denominator / m_denominator * m_nominator;
		nominator += denominator / y.m_denominator * y.m_nominator;
		m_nominator = nominator;
		m_denominator = denominator;
		norm();
		return *this;
	}

	Rational& operator-=(Rational y)
	{
		int denominator = FindLeastCommonMultiple(m_denominator, y.m_denominator);
		int nominator = denominator / m_denominator * m_nominator;
		nominator -= denominator / y.m_denominator * y.m_nominator;
		m_nominator = nominator;
		m_denominator = denominator;
		norm();
		return *this;
	}

	Rational& operator*=(Rational y)
	{
		m_nominator *= y.m_nominator;
		m_denominator *= y.m_denominator;
		norm();
		return *this;
	}

	Rational& operator/=(Rational y)
	{
		m_nominator *= y.m_denominator;
		m_denominator *= y.m_nominator;
		norm();
		return *this;
	}
	friend Rational operator+ (const Rational& x, const Rational& y);
	friend Rational operator- (const Rational& x, const Rational& y);
	friend Rational operator* (const Rational& x, const Rational& y);
	friend Rational operator/(const Rational& x, const Rational& y);
	friend bool operator==(const Rational& x, const Rational& y);
	friend bool operator>(const Rational& x, const Rational& y);
	friend bool operator<(const Rational& x, const Rational& y);
	friend bool operator>=(const Rational& x, const Rational& y);
	friend bool operator<=(const Rational& x, const Rational& y);
	friend std::ostream& operator<<(std::ostream& stream, const Rational& instance);
	friend Rational sin(const Rational& value);
};


export Rational sin(const Rational& value) 
{
	double result = sin((double)value);

	int nom = (int)(result * 10000);
	int denom = 10000;

	return Rational(nom, denom);
}

export Rational operator+ (const Rational& x, const Rational& y) 
{
	int denominator = FindLeastCommonMultiple(x.m_denominator, y.m_denominator);
	int nominator = denominator / x.m_denominator * x.m_nominator;
	nominator += denominator / y.m_denominator * y.m_nominator;
	return Rational(nominator, denominator);
}

export Rational operator-(const Rational& x, const Rational& y)
{
	int denominator = FindLeastCommonMultiple(x.m_denominator, y.m_denominator);
	int nominator = denominator / x.m_denominator * x.m_nominator;
	nominator -= denominator / y.m_denominator * y.m_nominator;
	return Rational{ nominator, denominator };
}

export Rational operator*(const Rational& x, const Rational& y)
{
	return Rational(x.m_nominator * y.m_nominator, y.m_denominator * x.m_denominator);
}

export Rational operator/(const Rational& x, const Rational& y)
{
	return Rational(x.m_nominator * y.m_denominator, x.m_denominator * y.m_nominator);
}

export bool operator==(const Rational& x, const Rational& y)
{
	return x.m_nominator == y.m_nominator && x.m_denominator == y.m_denominator;
}

export bool operator>(const Rational& x, const Rational& y)
{
	int lcm = FindLeastCommonMultiple(x.m_denominator, y.m_denominator);
	return lcm / x.m_denominator * x.m_nominator > lcm / y.m_denominator * y.m_nominator;
}
export bool operator<(const Rational& x, const Rational& y)
{
	int lcm = FindLeastCommonMultiple(x.m_denominator, y.m_denominator);
	return lcm / x.m_denominator * x.m_nominator < lcm / y.m_denominator * y.m_nominator;
}
export bool operator>=(const Rational& x, const Rational& y)
{
	int lcm = FindLeastCommonMultiple(x.m_denominator, y.m_denominator);
	return lcm / x.m_denominator * x.m_nominator >= lcm / y.m_denominator * y.m_nominator;
}
export bool operator<=(const Rational& x, const Rational& y)
{
	int lcm = FindLeastCommonMultiple(x.m_denominator, y.m_denominator);
	return lcm / x.m_denominator * x.m_nominator <= lcm / y.m_denominator * y.m_nominator;
}

export std::ostream& operator<<(std::ostream& stream, const Rational& inst) 
{
	stream << inst.m_nominator << "/" << inst.m_denominator;
	return stream;
}

export Complex f(const Complex& u) 
{
	Complex a = Complex(0.0, 1.0);
	return 2 * u + sin(u - a);
}

export Rational f(const Rational& u) 
{
	Rational a(1, 2);
	return 2 * u + sin(u - a);
}

export double f(double u) 
{
	double a = 0.5;
	return 2 * u + sin(u - a);
}