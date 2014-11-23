#include "ValueWrapperFactory.h"
#include <sstream>

static ValueWrapperFactory::valueType_t dataValueTypes[] =
{
    ValueWrapperFactory::kVt_Int32,
    ValueWrapperFactory::kVt_Int32,
    ValueWrapperFactory::kVt_Float64,
    ValueWrapperFactory::kVt_Float64,
    ValueWrapperFactory::kVt_Float64,
    ValueWrapperFactory::kVt_Int32Vec,
    ValueWrapperFactory::kVt_Float64Vec,
    ValueWrapperFactory::kVt_Int32
};

ValueWrapper * ValueWrapperFactory::create(const dataId_t dataId,
                                           const std::string &text)
{
    ValueWrapper *wrapper = NULL;
    valueType_t type = getValueType(dataId);
    switch (type) {
    case kVt_Int32:
    {
        std::istringstream iss(text);
        int i = 0;
        iss >> i;
        wrapper = new TValue<int>(i);
        break;
    }
    case kVt_Float64:
    {
        std::istringstream iss(text);
        double d = 0.0;
        iss >> d;
        wrapper = new TValue<double>(d);
        break;
    }
    case kVt_String:
        wrapper = new TValue<std::string>(text);
        break;
    case kVt_Int32Vec:
    case kVt_Float64Vec:
    default:
        Q_ASSERT(0);
        break;
    }
    return wrapper;
}

ValueWrapperFactory::valueType_t
ValueWrapperFactory::getValueType(const dataId_t dataId)
{
    return dataValueTypes[dataId];
}
