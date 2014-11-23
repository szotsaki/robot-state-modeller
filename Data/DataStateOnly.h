#ifndef DATA_STATE_ONLY_H_
#define DATA_STATE_ONLY_H_

#include <QDataStream>
#include <sstream>
#include "../QCircularBuffer.h"
#include "../ValueWrapper.h"
#include "DataInterface.h"
#include "State.h"

template<typename T>
class DataStateOnly : public DataInterface
{

public:
    QCircularBuffer< State<T> > states;

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
inline void DataStateOnly<T>::sendCommand(const ValueWrapper &,
                                          QDataStream &,
                                          const bool)
{
    // Has no command, nothing to do.
}

template <typename T>
inline void DataStateOnly<T>::deserialise(QDataStream &inStream)
{
    State<T> s;
    s.deserialise(inStream);
    states.push_back(s);
}

template <typename T>
inline void DataStateOnly<T>::updateCommand()
{
    // Has no command, nothing update.
}

template<typename T>
inline std::string DataStateOnly<T>::getValueText() const
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
inline void DataStateOnly<T>::drawTimeChart() const
{
    // TODO
}

template<typename T>
inline void DataStateOnly<T>::drawBarChart() const
{
    // TODO
}

#endif // DATA_STATE_ONLY_H_
