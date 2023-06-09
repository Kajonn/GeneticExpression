#include "TokenValue.h"
#include <sstream>

TokenValue::TokenValue(double value) : ExpressionToken(Value), _value(value)
{
}


TokenValue::~TokenValue()
{
}


double TokenValue::evaluate() const
{
	return _value;
}


std::string TokenValue::toString() const {
	std::stringstream ss;
	ss << _value;
	return ss.str();
};
