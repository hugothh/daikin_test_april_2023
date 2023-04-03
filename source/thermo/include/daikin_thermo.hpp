#ifndef DAIKIN_THERMO_HPP
#define DAIKIN_THERMO_HPP

/*
* This class is the interface of a thermostat module that will be deployed from a library.
* Client code can get an instance and invoke the 'measurement' function.
* The input of the function is the current status of room temperature and device.
* The output is what the device is expected to do.   
*/

#include <memory>
#include <chrono>

constexpr double AdjustmentTolerance = 1.25; // degrees C

using namespace std::chrono_literals;

enum class AdjustmentEnum : short
{
    Heat,
    Cool,
    Idle
};

struct ThermostatAdjustment
{
    AdjustmentEnum adjustment = AdjustmentEnum::Idle;
    std::chrono::seconds duration = 0s;

    bool operator==(ThermostatAdjustment rhs) { return (adjustment == rhs.adjustment &&
                                                        duration == rhs.duration); }
};

bool operator==(ThermostatAdjustment lhs, ThermostatAdjustment rhs);

class ThermostatInterface
{
public:
    ThermostatInterface() = default;  
    virtual ~ThermostatInterface() = default;

    // The heating and cooling ratios represent the adjustable power of the device.
    // They allow to predict the time needed to reach the minimum or maximum temperature.
    virtual ThermostatAdjustment measurement(double currentTemperature,
                                             double heatingRatio,  // 1 degree in n seconds (1/n)
                                             double coolingRatio,
                                             double minimumTemperature,
                                             double maximumTemperature) = 0;

    // client owns the memory of the instance
    static std::unique_ptr<ThermostatInterface> getInstance();
};

#endif // DAIKIN_THERMO_HPP
