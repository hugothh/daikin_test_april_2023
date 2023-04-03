#include "daikin_thermostat1.hpp"


ThermostatAdjustment Thermostat1::measurement(double currentTemperature,
                                              double heatingRatio,  // 1 degree in n seconds (1/n)
                                              double coolingRatio,
                                              double minimumTemperature,
                                              double maximumTemperature)
{
    ThermostatAdjustment rtn;

    double heatDiff = minimumTemperature - currentTemperature;
    if (heatDiff > AdjustmentTolerance)
    {
        rtn.adjustment = AdjustmentEnum::Heat;
        rtn.duration = static_cast<std::chrono::seconds>(roundDoubleToInt(heatDiff/heatingRatio));
    }
    else
    {
        double coolDiff = currentTemperature - maximumTemperature;
        if (coolDiff > AdjustmentTolerance)
        {
            rtn.adjustment = AdjustmentEnum::Cool;
            rtn.duration = static_cast<std::chrono::seconds>(roundDoubleToInt(coolDiff/coolingRatio));
        }
    }

    return rtn;
}
