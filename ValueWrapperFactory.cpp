#include "ValueWrapperFactory.h"

ValueWrapper * ValueWrapperFactory::create(const dataId_t)
{
    // TODO: hierarchy based wrapper.
    return new ValueWrapper(0);
}
