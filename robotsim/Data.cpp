#include "Data.h"
#include <algorithm>

DataInt::DataInt(const dataId_t id,
                 const int32_t minVal,
                 const int32_t maxVal,
                 const int32_t init)
    : dataId(id),
      minValue(minVal),
      maxValue(maxVal),
      actual(init),
      lastSent(init),
      goal(init)
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
        actual!= goal;
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

int32_t DataInt::clamp(const int32_t d, const int32_t dMin, const int32_t dMax)
{
    return std::min(dMax, std::max(dMin, d));
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
      goal(init)
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

double DataDouble::clamp(const double d, const double dMin, const double dMax)
{
    return std::min(dMax, std::max(dMin, d));
}

double DataDouble::clampMaxAbs(const double d, const double dMaxAbs)
{
    double res = d;
    if (abs(d) > dMaxAbs)
    {
        res *= dMaxAbs / abs(d);
    }
    return res;
}

