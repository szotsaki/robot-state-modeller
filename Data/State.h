#ifndef STATE_H_
#define STATE_H_

#include <QDataStream>
#include <QDateTime>

template<typename T>
class State
{

public:
    T getValue() const;
	void deserialise(QDataStream& stream);
	void draw();

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
inline void State<T>::deserialise(QDataStream &inStream)
{
    Q_UNUSED(inStream);
    //inStream >> value;
    timestamp = QDateTime::currentDateTime();
}

template<typename T>
inline void State<T>::draw()
{
    // TODO: implement.
}

#endif // STATE_H_
