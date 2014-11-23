#ifndef VALUEWRAPPER_H
#define VALUEWRAPPER_H

#include <string>
#include <vector>

/**
 * Wrapper class for telemetry data value.
 * Using wrapper, monitor object does not need to know which concrete
 * telemetry value types are present in the program. The user can wrap
 * the actual value inside this generic class and pass it to monitor.
 */
/*
 * Note: This could be also implemented with a WrapperInterface and
 *       concrete implementations (Wrapper<T>), but it would require
 *       a downcast on the hierarchy :(.
 *
 * This will be implemented, supported by a factory which creates a
 * Wrapper interface for a given data identifier.
 */
class ValueWrapper
{

public:
    enum class Type
    {
        kInt32,
        kFloat64,
        kInt32Vec,
        kFloat64Vec,
        kString
    };

    ValueWrapper(const int value);
    ValueWrapper(const double value);
    ValueWrapper(const std::vector<int> &value);
    ValueWrapper(const std::vector<double> &value);
    ValueWrapper(const std::string &value);
    ~ValueWrapper();

    bool isInt32() const { return type == Type::kInt32; }
    bool isFloat64() const { return type == Type::kFloat64; }
    bool isInt32Vec() const { return type == Type::kInt32Vec; }
    bool isFloat64Vec() const { return type == Type::kFloat64Vec; }
    bool isString() const { return type == Type::kString; }

    int	getInt32() const;
    double getFloat64() const;
    std::vector<int> getInt32Vec() const;
    std::vector<double> getFloat64Vec() const;
    std::string getString() const;

private:
    union _val
    {
        int	int32;
        double float64;
        std::vector<int> *int32Vec;
        std::vector<double> *float64Vec;
        std::string *string;
    } val;
    Type type;

};

#endif // VALUEWRAPPER_H
