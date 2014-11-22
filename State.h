#ifndef STATE_H_
#define STATE_H_

#include <QDataStream>
#include <QDateTime>

template<typename T>
class State
{

public:
	T value;
	QDateTime timestamp;

	void deserialise(QDataStream& stream);
	void draw();

};
#endif // STATE_H_
