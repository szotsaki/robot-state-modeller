#ifndef COMMAND_H_
#define COMMAND_H_

#include <QDataStream>

enum class commandProgress_t
{
    kCp_InProgress,
    kCp_Success,
    kCp_Failed
};

/**
 * This class represents a command which can be sent to the robot.
 * The command can have a meaningful payload, e.g. change acceleration to X,
 * but can also exist without real payload, e.g. emergency stop.
 * The class also tracks the progression of its command.
 */
template<typename T>
class Command
{

public:
    commandProgress_t progress;

    void serialise(QDataStream &outStream);
    void update(const T &state);
    bool inProgess();

private:
    T value;

};
#endif //  COMMAND_H_
