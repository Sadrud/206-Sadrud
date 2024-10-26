#include "Limits.hpp"
#include "GCD_LCM.hpp"
#include <stdexcept>

Value& Int::operator+=(const Value& other) {
	const Int& otherInt = dynamic_cast<const Int&>(other);
	if ((otherInt.value > 0 && value > std::numeric_limits<int>::max() - otherInt.value) || (otherInt.value < 0 && value < std::numeric_limits<int>::min() - otherInt.value)) {
		throw std::overflow_error("Переполнение при сложении");
	}
	value += otherInt.value;
	return *this;
}

Value& Int::operator-=(const Value& other) {
	const Int& otherInt = dynamic_cast<const Int&>(other);
	if ((otherInt.value > 0 && value < std::numeric_limits<int>::min() + otherInt.value) || (otherInt.value < 0 && value > std::numeric_limits<int>::max() + otherInt.value)) {
		throw std::overflow_error("Переполнение при вычитании");
	}
	value -= otherInt.value;
	return *this;
}

Value& Int::operator*=(const Value& other) {
	const Int& otherInt = dynamic_cast<const Int&>(other);
	if (value > 0 && otherInt.value > 0 && value > std::numeric_limits<int>::max() / otherInt.value) {
		throw std::overflow_error("Переполнение при умножении");
	}
	value *= otherInt.value;
	return *this;
}

Value& Int::operator/=(const Value& other) {
	const Int& otherInt = dynamic_cast<const Int&>(other);
	if (otherInt.value == 0) {
		throw std::invalid_argument("Деление на ноль");
	}
	value /= otherInt.value;
	return *this;
}

Value& Int::operator%=(const Value& other) {
	const Int& otherInt = dynamic_cast<const Int&>(other);
        if (otherInt.value == 0) {
                throw std::invalid_argument("Деление на ноль");
        }
        value %= otherInt.value;
        return *this;
}

bool Int::operator==(const Value& other) {
	return value == dynamic_cast<const Int&>(other).value;
}

Value& Int::operator=(const Value& other) {
        value = dynamic_cast<const Int&>(other).value;
        return *this;
}

Value& Long::operator+=(const Value& other) {
	const Long& otherLong = dynamic_cast<const Long&>(other);
	if ((otherLong.value > 0 && value > std::numeric_limits<long>::max() - otherLong.value) || (otherLong.value < 0 && value < std::numeric_limits<long>::min() - otherLong.value)) {
		throw std::overflow_error("Переполнение при сложении");
	}
	value += otherLong.value;
	return *this;
}

Value& Long::operator-=(const Value& other) {
	const Long& otherLong = dynamic_cast<const Long&>(other);
	if ((otherLong.value > 0 && value < std::numeric_limits<long>::min() + otherLong.value) || (otherLong.value < 0 && value > std::numeric_limits<long>::max() + otherLong.value)) {
		throw std::overflow_error("Переполнение при вычитании");
	}
	value -= otherLong.value;
	return *this;
}

Value& Long::operator*=(const Value& other) {
	const Long& otherLong = dynamic_cast<const Long&>(other);
	if (value > 0 && otherLong.value > 0 && value > std::numeric_limits<long>::max() / otherLong.value) {
		throw std::overflow_error("Переполнение при умножении");
	}
	value *= otherLong.value;
	return *this;
}

Value& Long::operator/=(const Value& other) {
	const Long& otherLong = dynamic_cast<const Long&>(other);
	if (otherLong.value == 0) {
		throw std::invalid_argument("Деление на ноль");
	}
	value /= otherLong.value;
	return *this;
}

Value& Long::operator%=(const Value& other) {
	const Long& otherLong = dynamic_cast<const Long&>(other);
	if (otherLong.value == 0) {
		throw std::invalid_argument("Деление на ноль");
	}
	value = value % otherLong.value;
	return *this;
}

bool Long::operator==(const Value& other) {
        return value == dynamic_cast<const Long&>(other).value;
}

Value& Long::operator=(const Value& other) {
	value = dynamic_cast<const Long&>(other).value;
	return *this;
}


void GCD(Value& a, Value& b, Value& result) {
	Value* zeroA = a.CreateZeroValue();
	Value* zeroB = b.CreateZeroValue();
	Value* tmpA = a.Duplicate();
	Value* tmpB = b.Duplicate();

	while (true) {
		*tmpA %= *tmpB;
		if (*tmpA == *zeroA) {
			result = *tmpB;
			break;
		}
		*tmpB %= *tmpA;
                if (*tmpB == *zeroB) {
                        result = *tmpA;
                        break;
                }
	}

	delete zeroA;
	delete zeroB;
	delete tmpA;
	delete tmpB;
}

void LCM(Value& a, Value& b, Value& result) {
	Value* gcdValue = a.Duplicate();
	GCD(a, b, *gcdValue);

	Value* multResult = a.Duplicate();
	*multResult *= b;
	*multResult /= *gcdValue;
	result = *multResult;

	delete gcdValue;
	delete multResult;
}
