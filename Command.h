#ifndef COMMAND_H_
#define COMMAND_H_

#include <QDataStream>

#include "progress_t.h"

template<typename T>
class Command
{

public:
    progress_t progress;

    void serialise(QDataStream& stream);
    void update(T state);
    bool inProgess();

private:
	T value;

};
#endif //  COMMAND_H_
