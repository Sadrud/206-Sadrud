#include <iostream>
#include "Exception.hpp"
#include <stdexcept>

class Value {
	public:
		virtual Value* CreateZeroValue() const = 0;
		virtual Value* Duplicate() const = 0;

		virtual Value& operator+=(const Value& other) = 0;
		virtual Value& operator-=(const Value& other) = 0;
		virtual Value& operator*=(const Value& other) = 0;
		virtual Value& operator/=(const Value& other) = 0;

		virtual Value& operator%=(const Value& other) = 0;

		virtual ~Value() {}
};

class Int : public Value {
	int value;
	public:
	Int(int v = 0) : value(v) {}

	Value* CreateZeroValue() const override { return new Int(0); }
	Value* Duplicate() const override { return new Int(value); }
	int getValue() const { return value; }

	Value& operator+=(const Value& other) override;
	Value& operator-=(const Value& other) override;
	Value& operator*=(const Value& other) override;
	Value& operator/=(const Value& other) override;

	Value& operator%=(const Value& other) override;
};

class Long : public Value {
	long value;
	public:
	Long(long v = 0) : value(v) {}

	Value* CreateZeroValue() const override { return new Long(0); }
	Value* Duplicate() const override { return new Long(value); }
	long getValue() const { return value; }

	Value& operator+=(const Value& other) override;
	Value& operator-=(const Value& other) override;
	Value& operator*=(const Value& other) override;
	Value& operator/=(const Value& other) override;

	Value& operator%=(const Value& other) override;
};

void GCD(Value& a, Value& b, Value& result);
void LCM(Value& a, Value& b, Value& result);
