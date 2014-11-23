#ifndef DATA_VEC_STATE_ONLY_H_
#define DATA_VEC_STATE_ONLY_H_

#include <QDataStream>
#include <sstream>
#include "../QCircularBuffer.h"
#include "../ValueWrapper.h"
#include "DataInterface.h"
#include "State.h"

template<typename T>
class DataVecStateOnly : public DataInterface
{
    typedef std::vector< T >	_MyVal;
    typedef State< _MyVal >		_MyState;

public:
    QCircularBuffer< _MyState > states;

    virtual void sendCommand(const ValueWrapper &value,
                             QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

    virtual std::string getValueText() const;
    virtual void drawTimeChart() const;
    virtual void drawBarChart() const;
};

template <typename T>
inline void DataVecStateOnly<T>::sendCommand(const ValueWrapper &,
                                          QDataStream &,
                                          const bool)
{
    // Has no command, nothing to do.
}

template <typename T>
inline void DataVecStateOnly<T>::deserialise(QDataStream &inStream)
{
    _MyState s;
    s.deserialise(inStream);
    states.push_back(s);
}

template <typename T>
inline void DataVecStateOnly<T>::updateCommand()
{
    // Has no command, nothing update.
}

template<typename T>
inline std::string DataVecStateOnly<T>::getValueText() const
{
    if (!states.empty())
    {
        std::ostringstream oss;
        //oss << states.at(0);
        return oss.str();
    }
    return std::string();
}

template<typename T>
inline void DataVecStateOnly<T>::drawTimeChart() const
{
    // Cannot draw since state contains vectors.
}

template<typename T>
inline void DataVecStateOnly<T>::drawBarChart() const
{
    // TODO
}

#endif // DATA_VEC_STATE_ONLY_H_
