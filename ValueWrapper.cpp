#include "ValueWrapper.h"

ValueWrapper::ValueWrapper(const int value)
    : type(Type::kInt32)
{
    val.int32 = value;
}

ValueWrapper::ValueWrapper(const double value)
    : type(Type::kFloat64)
{
    val.float64 = value;
}

ValueWrapper::ValueWrapper(const std::vector<int> &value)
    : type(Type::kInt32Vec)
{
    val.int32Vec = new std::vector<int>(value);
}

ValueWrapper::ValueWrapper(const std::vector<double> &value)
    : type(Type::kFloat64Vec)
{
    val.float64Vec = new std::vector<double>(value);
}

ValueWrapper::ValueWrapper(const std::string &value)
    : type(Type::kString)
{
    val.string = new std::string(value);
}

ValueWrapper::~ValueWrapper()
{
    if (isInt32Vec())
    {
        delete val.int32Vec;
    }
    else if (isFloat64Vec())
    {
        delete val.float64Vec;
    }
    else if (isString())
    {
        delete val.string;
    }
}

int ValueWrapper::getInt32() const
{
    if (type == Type::kInt32)
    {
        return val.int32;
    }
    return 0;
}

double ValueWrapper::getFloat64() const
{
    if (type == Type::kFloat64)
    {
        return val.float64;
    }
    return 0.0;
}

std::vector<int> ValueWrapper::getInt32Vec() const
{
    if (type == Type::kInt32Vec)
    {
        return *val.int32Vec;
    }
    return std::vector<int>();
}

std::vector<double> ValueWrapper::getFloat64Vec() const
{
    if (type == Type::kFloat64Vec)
    {
        return *val.float64Vec;
    }
    return std::vector<double>();
}

std::string ValueWrapper::getString() const
{
    if (type == Type::kString)
    {
        return *val.string;
    }
    return std::string();
}
