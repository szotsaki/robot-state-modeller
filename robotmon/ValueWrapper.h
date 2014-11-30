#ifndef VALUEWRAPPER_H
#define VALUEWRAPPER_H

#include <string>
#include <vector>

/**
 * Wrapper class for telemetry data value.
 * Using wrapper, monitor object does not need to know which concrete
 * telemetry value types are present in the program. The user can wrap
 * the actual value inside this generic class and pass it to monitor.
 *
 * This is implemented with a Wrapper interface and concrete
 * implementations (TValue<T>), it requires a downcast on the hierarchy
 * to fetch the actual value.
 *
 * This also supported by a factory which creates a Wrapper interface
 * for a given data identifier.
 */
class ValueWrapper
{

public:
    virtual ~ValueWrapper();

};

/**
 * Value class with actual telemetry data value.
 */
template<class T>
class TValue : public ValueWrapper
{

public:
    TValue(const T &val) : value(val) {}
    T getValue() const { return value; }

private:
    T	value;

};

#endif // VALUEWRAPPER_H
