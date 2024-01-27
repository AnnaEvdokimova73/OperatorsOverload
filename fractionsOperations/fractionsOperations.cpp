#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;

	int minDen(Fraction right)
	{
		int maxDen = abs(denominator_ * right.denominator_);
		int min = maxDen;
		for (int i = maxDen; i >= 1; --i)
		{
			if ((i % denominator_ == 0) && (i % right.denominator_ == 0))
			{
				min = i;
			}
		}
		return min;
	}

	int factor(Fraction right, int den)
	{
		return abs(minDen(right) / den);
	}

	Fraction minValue(Fraction frac)
	{
		int max = frac.denominator_;
		for (int i = 1; i < frac.denominator_; ++i)
		{
			if ((frac.numerator_ % i == 0) && (frac.denominator_ % i == 0))
			{
				max = i;
			}
		}
		int num = frac.numerator_ / max;
		int den = frac.denominator_ / max;
		return Fraction(num, den);
	}

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}

	int getNum()
	{
		return this->numerator_;
	}

	int getDen()
	{
		return this->denominator_;
	}

	Fraction operator+(Fraction right)
	{
		int num = numerator_ * factor(right, denominator_) + right.numerator_ * factor(right, right.denominator_);
		int den = minDen(right);
		return minValue(Fraction(num, den));
		// return *this; // Тогда новые значения записываются в левый операнд
	}

	Fraction operator-(Fraction right)
	{
		int num = numerator_ * factor(right, denominator_) - right.numerator_ * factor(right, right.denominator_);
		int den = minDen(right);
		return minValue(Fraction(num, den));
	}

	Fraction operator*(Fraction right)
	{
		int num = numerator_ * right.numerator_;
		int den = denominator_ * right.denominator_;
		return minValue(Fraction(num, den));
	}

	Fraction operator/(Fraction right)
	{
		int num = numerator_ * right.denominator_;
		int den = denominator_ * right.numerator_;
		return minValue(Fraction(num, den));
	}

	Fraction operator++()
	{
		numerator_ = numerator_ + denominator_;
		denominator_ = denominator_;
		return minValue(*this);
	}

	Fraction operator--(int)
	{
		numerator_ = numerator_ - denominator_;
		denominator_ = denominator_;
		return minValue(*this);
	}


	friend std::ostream& operator<<(std::ostream& left, Fraction right);

};

std::ostream& operator<<(std::ostream& left, Fraction right)
{
	left << right.numerator_ << "/" << right.denominator_;
	return left;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int num1, num2;
	int den1, den2;
	std::cout << "Введите числитель дроби 1: ";
	std::cin >> num1;
	std::cout << "Введите знаменатель дроби 1: ";
	std::cin >> den1;
	std::cout << "Введите числитель дроби 2: ";
	std::cin >> num2;
	std::cout << "Введите знаменатель дроби 2: ";
	std::cin >> den2;

	Fraction f1(num1, den1);
	Fraction f2(num2, den2);

	std::cout << f1.getNum() << "/" << f1.getDen() << " + " << f2.getNum() << "/" << f2.getDen() << " = " << f1 + f2 << std::endl;
	std::cout << f1.getNum() << "/" << f1.getDen() << " - " << f2.getNum() << "/" << f2.getDen() << " = " << f1 - f2 << std::endl;
	std::cout << f1.getNum() << "/" << f1.getDen() << " * " << f2.getNum() << "/" << f2.getDen() << " = " << f1 * f2 << std::endl;
	std::cout << f1.getNum() << "/" << f1.getDen() << " / " << f2.getNum() << "/" << f2.getDen() << " = " << f1 / f2 << std::endl;
	std::cout << "++" << f1.getNum() << "/" << f1.getDen() << " * " << f2.getNum() << "/" << f2.getDen() << " = " << ++f1 * f2 << std::endl;
	std::cout << "Значение дроби 1 = " << f1 << std::endl;
	std::cout << f1.getNum() << "/" << f1.getDen() << "-- * " << f2.getNum() << "/" << f2.getDen() << " = " << (f1-- * f2) << std::endl;
	std::cout << "Значение дроби 1 = " << f1 << std::endl;
	return 0;
}