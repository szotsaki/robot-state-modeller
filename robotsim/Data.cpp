#include "Data.h"

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
    if (!hasCmd && !estop && rand(ROB_RP_CHANGE_GOAL) == 0)
    {
        goal = rand(minValue, maxValue);
    }
    if (actual != goal)
    {
        actual = goal;
        hasCmd = false;
    }
}

void DataInt::write(const bool needSync)
{
    if (actual != lastSent || needSync)
    {
        int size = 12;
        writeInteger(size);
        writeInteger(dataId);
        writeInteger(actual);
        lastSent = actual;
    }
}

void DataInt::read()
{
    goal = clamp(readInteger(), minValue, maxValue);
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
    if (!hasCmd && !estop && rand(ROB_RP_CHANGE_GOAL) == 0)
    {
        goal = rand(minValue, maxValue);
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

void DataDouble::write(const bool needSync)
{
    if (actual != lastSent || needSync)
    {
        int size = 16;
        writeInteger(size);
        writeInteger(dataId);
        writeDouble(actual);
        lastSent = actual;
    }
}

void DataDouble::setEstop()
{
    goal = 0.0;
}

