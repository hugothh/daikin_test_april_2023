add_library(daikinthermolib STATIC ./thermo/daikin_thermo.cpp ./thermo/daikin_thermostat1.cpp)

target_include_directories(daikinthermolib PUBLIC ./thermo ./thermo/include)