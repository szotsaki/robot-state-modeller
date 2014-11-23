#ifndef VALUEWRAPPERFACTORY_H
#define VALUEWRAPPERFACTORY_H

#include "Data/DataInterface.h"
#include "ValueWrapper.h"

/**
 * The ValueWrapperFactory creates a telemetry data ValueWrapper
 * which can be passed to the monitor. See more in ValueWrapper.h.
 */
class ValueWrapperFactory
{

public:
    typedef enum
    {
        kVt_Int32,
        kVt_Float64,
        kVt_Int32Vec,
        kVt_Float64Vec,
        kVt_String
    } valueType_t;

    static ValueWrapper *	create(const dataId_t dataId,
                                   const std::string &text);

private:
    static valueType_t getValueType(const dataId_t dataId);
};

#endif // VALUEWRAPPERFACTORY_H
