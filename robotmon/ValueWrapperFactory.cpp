#include "ValueWrapperFactory.h"
#include <sstream>

ValueWrapper * ValueWrapperFactory::create(const dataId_t dataId,
                                           const std::string &text)
{
    ValueWrapper *wrapper = NULL;
    dataValueType_t type = dataValueTypes[dataId];
    switch (type) {
    case kDvt_Int32:
    {
        std::istringstream iss(text);
        int i = 0;
        iss >> i;
        wrapper = new TValue<int>(i);
        break;
    }
    case kDvt_Float64:
    {
        std::istringstream iss(text);
        double d = 0.0;
        iss >> d;
        wrapper = new TValue<double>(d);
        break;
    }
    case kDvt_String:
        wrapper = new TValue<std::string>(text);
        break;
    case kDvt_Int32Vec:
    case kDvt_Float64Vec:
    default:
        Q_UNREACHABLE();
        break;
    }
    return wrapper;
}
