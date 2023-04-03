#ifndef DAIKIN_THERMOSTAT1_HPP
#define DAIKIN_THERMOSTAT1_HPP

/*
* This class is an implementation of the thermostat interface.
*/

#include <cmath>
#include <daikin_thermo.hpp>

class Thermostat1 : public ThermostatInterface
{
public:
    Thermostat1() = default; 
    ~Thermostat1() = default;

    virtual ThermostatAdjustment measurement(double currentTemperature,
                                             double heatingRatio,  // 1 degree in n seconds (1/n)
                                             double coolingRatio,
                                             double minimumTemperature,
                                             double maximumTemperature) override;
private:
    // round properly up or down from 0.5 and make it an integer
    int64_t roundDoubleToInt(double d) const { return static_cast<int64_t>(round(d)); }
};

#endif // DAIKIN_THERMOSTAT1_HPP
