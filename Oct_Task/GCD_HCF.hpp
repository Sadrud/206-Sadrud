#ifndef GCD_HCF
#define GCD_HCF

class Value {
public:
	virtual Value* CreateZeroValue() = 0;
	virtual Value* Duplicate() = 0;

	virtual Value& operator+=(const Value&) = 0;
	virtual Value& operator-=(const Value&) = 0;
	virtual Value& operator*=(const Value&) = 0;
	virtual Value& operator/=(const Value&) = 0;
	
	virtual ~Value () {}
};


class Int {
	
};

class Long {

};

#endif
