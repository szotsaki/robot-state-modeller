#ifndef DATA_H_
#define DATA_H_

#include <QDataStream>

#include "../QCircularBuffer.h"
#include "../ValueWrapper.h"
#include "Command.h"
#include "DataInterface.h"
#include "State.h"

template<typename T>
class Data : public DataInterface
{

public:
    Command<T> command;
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

template<typename T>
inline void Data<T>::sendCommand(const ValueWrapper &value,
                          QDataStream &outStream,
                          const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(value, outStream);
    }
}

template<typename T>
inline void Data<T>::deserialise(QDataStream &inStream)
{
    State<T> s;
    s.deserialise(inStream);
    states.push_back(s);
}

template<typename T>
inline void Data<T>::updateCommand()
{
    const T value = states.at(0).getValue();
    command.update(value);
}

template<typename T>
inline std::string Data<T>::getValueText() const
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
inline void Data<T>::drawTimeChart() const
{
    // TODO
}

template<typename T>
inline void Data<T>::drawBarChart() const
{
    // TODO
}

#endif // DATA_H_
