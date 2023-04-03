#include <daikin_thermostat1.hpp>

std::unique_ptr<ThermostatInterface> ThermostatInterface::getInstance()
{
    return std::unique_ptr<Thermostat1>(new Thermostat1);
}

bool operator==(ThermostatAdjustment lhs, ThermostatAdjustment rhs)
{
    return lhs.operator==(rhs);
}