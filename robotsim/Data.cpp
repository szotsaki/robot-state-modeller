#include "Data.h"
#include "Random.h"

DataInt::DataInt(const dataId_t id,
                 const int32_t minVal,
                 const int32_t maxVal,
                 const int32_t init)
    : dataId(id),
      minValue(minVal),
      maxValue(maxVal),
      actual(init),
      lastSent(init),
      goal(init),
      hasCmd(false)
{
}

void DataInt::update(const bool estop)
{
    if (!hasCmd && !estop && Random::getRand(0, ROB_RP_CHANGE_GOAL) == 0)
    {
        goal = Random::getRand(minValue, maxValue);
    }
    if (actual != goal)
    {
        actual = goal;
        hasCmd = false;
    }
}

void DataInt::write(QDataStream &outStream, const bool needSync)
{
    if (actual != lastSent || needSync)
    {
        int32_t size = 12;
        outStream << size;
        outStream <<  (int32_t)dataId;
        outStream << actual;
        lastSent = actual;
    }
}

void DataInt::read(QDataStream &inStream)
{
    int32_t val;
    inStream >> val;
    goal = clamp(val, minValue, maxValue);
    hasCmd = true;
}

DataDouble::DataDouble(const dataId_t id,
                       const double minVal,
                       const double maxVal,
                       const double init,
                       const double maxDiff)
    : dataId(id),
      minValue(minVal),
      maxValue(maxVal),
      maxDiff(maxDiff),
      actual(init),
      lastSent(init),
      goal(init),
      hasCmd(false)
{
}

void DataDouble::update(const bool estop)
{
    if (!hasCmd && !estop && Random::getRand(0, ROB_RP_CHANGE_GOAL) == 0)
    {
        goal = Random::getRand(minValue, maxValue);
    }
    if (actual != goal)
    {
        double diff = (goal - actual) * 0.8;
        diff = clampMaxAbs(diff, maxDiff);
        actual += diff;

        if (hasCmd && actual == goal)
        {
            hasCmd = false;
        }
    }
}

void DataDouble::write(QDataStream &outStream, const bool needSync)
{
    if (actual != lastSent || needSync)
    {
        int size = 16;
        outStream << size;
        outStream <<  (int32_t)dataId;
        outStream << actual;
        lastSent = actual;
    }
}

void DataDouble::read(QDataStream &inStream)
{
    double val;
    inStream >> val;
    goal = clamp(val, minValue, maxValue);
    hasCmd = true;
}

void DataDouble::setEstop()
{
    goal = 0.0;
}

