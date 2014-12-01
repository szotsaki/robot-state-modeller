#ifndef STATE_H_
#define STATE_H_

#include <QDataStream>
#include <QDateTime>

template<typename T>
class State
{

public:
    T			getValue() const;
    QDateTime	getTimestamp() const;
    void 		deserialise(QDataStream& stream);

private:
    QDateTime timestamp;
    T value;

};

template<typename T>
inline T State<T>::getValue() const
{
    return value;
}

template<typename T>
inline QDateTime State<T>::getTimestamp() const
{
    return timestamp;
}

template<typename T>
inline void State<T>::deserialise(QDataStream &inStream)
{
    inStream >> value;
    timestamp = QDateTime::currentDateTime();
}

#endif // STATE_H_
