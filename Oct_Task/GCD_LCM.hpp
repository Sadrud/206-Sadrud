#ifndef GCD_LCM_HPP
#define GCD_LCM_HPP

#include <iostream>
#include <stdexcept>
#include <limits>

class Value {
	public:
		int minIntVal = std::numeric_limits<int>::lowest();
		int maxIntVal = std::numeric_limits<int>::max();
		long minLongVal = std::numeric_limits<long>::lowest();
		long maxLongVal = std::numeric_limits<long>::max();
		
		virtual Value* CreateZeroValue() const = 0;
		virtual Value* Duplicate() const = 0;

		virtual Value& operator+=(const Value& other) = 0;
		virtual Value& operator-=(const Value& other) = 0;
		virtual Value& operator*=(const Value& other) = 0;
		virtual Value& operator/=(const Value& other) = 0;

		virtual Value& operator%=(const Value& other) = 0;
		virtual bool operator==(const Value& other) = 0;
		virtual Value& operator=(const Value& other) = 0;

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
	bool operator==(const Value& other) override;
	Value& operator=(const Value& other) override;
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
	bool operator==(const Value& other) override;
	Value& operator=(const Value& other) override;
};

void GCD(Value& a, Value& b, Value& result);
void LCM(Value& a, Value& b, Value& result);

#endif
