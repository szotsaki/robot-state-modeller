#ifndef VALUEWRAPPERFACTORY_H
#define VALUEWRAPPERFACTORY_H

#include "DataInterface.h"
#include "ValueWrapper.h"

/**
 * The ValueWrapperFactory creates a telemetry data ValueWrapper
 * which can be passed to the monitor. See more in ValueWrapper.h.
 */
class ValueWrapperFactory
{
    static ValueWrapper *	create(const dataId_t dataId);
};

#endif // VALUEWRAPPERFACTORY_H
