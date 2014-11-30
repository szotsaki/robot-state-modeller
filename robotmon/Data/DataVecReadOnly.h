#ifndef DATA_VEC_READ_ONLY_H_
#define DATA_VEC_READ_ONLY_H_

#include <QDataStream>
#include <QVector>
#include <sstream>
#include "../QCircularBuffer.h"
#include "../ValueWrapper.h"
#include "DataInterface.h"
#include "State.h"

/**
 * Read-only vector telemetry data.
 * Uses a vector type for its value.
 * Read-only means it only stores received states, which
 * can be displayed on a diagram.
 */
template<typename T>
class DataVecReadOnly : public DataInterface
{
    typedef QVector< T >	_MyVal;
    typedef State< _MyVal >		_MyState;

public:
    QCircularBuffer< _MyState > states;

    virtual void setCommand(const ValueWrapper &value);
    virtual void sendCommand(QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

    virtual std::string getValueText() const;
    virtual void drawTimeChart(QCustomPlot *customPlot) const;
    virtual void drawBarChart(QCustomPlot *customPlot) const;
};

template <typename T>
inline void DataVecReadOnly<T>::setCommand(const ValueWrapper &)
{
    // Has no command, nothing to do.
}

template <typename T>
inline void DataVecReadOnly<T>::sendCommand(QDataStream &,
                                            const bool)
{
    // Has no command, nothing to do.
}

template <typename T>
inline void DataVecReadOnly<T>::deserialise(QDataStream &inStream)
{
    _MyState s;
    s.deserialise(inStream);
    states.push_back(s);
}

template <typename T>
inline void DataVecReadOnly<T>::updateCommand()
{
    // Has no command, nothing update.
}

template<typename T>
inline std::string DataVecReadOnly<T>::getValueText() const
{
    if (!states.empty())
    {
        std::ostringstream oss;
        _MyVal val = states.at(0).getValue();
        for (T elem : val)
        {
            oss << elem << ',';
        }
        return oss.str();
    }
    return std::string();
}

template<typename T>
inline void DataVecReadOnly<T>::drawTimeChart(QCustomPlot *customPlot) const
{
    Q_UNUSED(customPlot)
    // Cannot draw since state contains vectors.
}

template<typename T>
inline void DataVecReadOnly<T>::drawBarChart(QCustomPlot *customPlot) const
{
    // TODO
}

#endif // DATA_VEC_READ_ONLY_H_
