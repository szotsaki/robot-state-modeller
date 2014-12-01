#ifndef ROBOTSIM__DATAVEC_H
#define ROBOTSIM__DATAVEC_H

#include <array>
#include <stdint.h>
#include <QDataStream>
#include <QVector>
#include "DataCommon.h"
#include "Random.h"

/**
 * Represents a readable 32bit integer array data of the robot simulator.
 */
template <size_t n>
class DataVecInt
{
public:
    DataVecInt(const dataId_t id,
               const int32_t minVal,
               const int32_t maxVal,
               const int32_t init);

    void    update(const bool estop);
    void    write(QDataStream &outStream, const bool needSync);

private:
    const dataId_t  dataId;
    const int32_t   minValue;
    const int32_t   maxValue;
    std::array<int32_t, n>  actual;
    std::array<int32_t, n>  lastSent;
    std::array<int32_t, n>  goal;
};

/**
 * Represents a readable 64bit floating point array data of the robot
 * simulator.
 */
template <size_t n>
class DataVecDouble
{
public:
    DataVecDouble(const dataId_t id,
                  const double minVal,
                  const double maxVal,
                  const double init,
                  const double maxDiff);

    void    update(const bool estop);
    void    write(QDataStream &outStream, const bool needSync);

private:
    const dataId_t  dataId;
    const double    minValue;
    const double    maxValue;
    const double    maxDiff;
    std::array<double, n>   actual;
    std::array<double, n>   lastSent;
    std::array<double, n>   goal;
};

template <size_t n>
DataVecInt<n>::DataVecInt(const dataId_t id,
                          const int32_t minVal,
                          const int32_t maxVal,
                          const int32_t init)
    : dataId(id),
      minValue(minVal),
      maxValue(maxVal)
{
    for (size_t i = 0; i < n; ++i)
    {
        actual[i] = lastSent[i] = goal[i] = init;
    }
}

template <size_t n>
void DataVecInt<n>::update(const bool estop)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (!estop && Random::getRand(0, ROB_RP_CHANGE_GOAL) == 0)
        {
            goal[i] = Random::getRand(minValue, maxValue);
        }
        if (actual[i] != goal[i])
        {
            actual[i] = goal[i];
        }
    }
}

template <size_t n>
void DataVecInt<n>::write(QDataStream &outStream, const bool needSync)
{
    if (needSync || actual != lastSent)
    {
        int32_t size = 8 + n*4;
        outStream << size;
        outStream << (int32_t)dataId;

        std::vector<int32_t> auxVector;
        auxVector.assign(&actual[0], &actual[0] + n);
        QVector<int32_t> toSend = QVector<int>::fromStdVector(auxVector);

        outStream << toSend;
        lastSent = actual;
    }
}

template <size_t n>
DataVecDouble<n>::DataVecDouble(const dataId_t id,
                                const double minVal,
                                const double maxVal,
                                const double init,
                                const double maxDiff)
    : dataId(id),
      minValue(minVal),
      maxValue(maxVal),
      maxDiff(maxDiff)
{
    for (size_t i = 0; i < n; ++i)
    {
        actual[i] = lastSent[i] = goal[i] = init;
    }
}

template <size_t n>
void DataVecDouble<n>::update(const bool estop)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (!estop && Random::getRand(0, ROB_RP_CHANGE_GOAL) == 0)
        {
            goal[i] = Random::getRand(minValue, maxValue);
        }
        if (actual[i] != goal[i])
        {
            double diff = (goal[i] - actual[i]) * 0.8;
            diff = clampMaxAbs(diff, maxDiff);
            actual[i] += diff;
        }
    }
}

template <size_t n>
void DataVecDouble<n>::write(QDataStream &outStream, const bool needSync)
{
    if (needSync || actual != lastSent)
    {
        int size = 8 + n*8;
        outStream << size;
        outStream << (int32_t)dataId;

        std::vector<double> auxVector;
        auxVector.assign(&actual[0], &actual[0] + n);
        QVector<double> toSend = QVector<double>::fromStdVector(auxVector);

        outStream << toSend;
        lastSent = actual;
    }
}

#endif // !ROBOTSIM__DATAVEC_H

