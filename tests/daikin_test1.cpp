
#include <daikin_thermo.hpp>
#include <gtest/gtest.h>

class GetFullCoverageTest : public testing::Test
{
protected:
    std::unique_ptr<ThermostatInterface> m_thermostat;

    const double TestHeatingRatio   = 1.0/400;  // 1 degree in n seconds (1/n)
    const double TestCoolingRatio   = 1.0/500;
    const double TestMinTemperature = 18.0;
    const double TestMaxTemperature = 22.0;

	void SetUp() override
	{
        m_thermostat = ThermostatInterface::getInstance();
	}

	void TearDown() override
	{
	}
};

TEST_F(GetFullCoverageTest, HeatWhenIsVeryColdTest)
{
 	auto actual = m_thermostat->measurement(16.0, TestHeatingRatio, TestCoolingRatio, TestMinTemperature, TestMaxTemperature);
    const ThermostatAdjustment expected{AdjustmentEnum::Heat, 800s};
    ASSERT_EQ(expected, actual);
}

TEST_F(GetFullCoverageTest, IdleWhenIsJustColdTest)
{
 	auto actual = m_thermostat->measurement(18.01, TestHeatingRatio, TestCoolingRatio, TestMinTemperature, TestMaxTemperature);
    const ThermostatAdjustment expected{AdjustmentEnum::Idle, 0s};
    ASSERT_EQ(expected, actual);
}

TEST_F(GetFullCoverageTest, IdleWhenIsNiceTest)
{
 	auto actual = m_thermostat->measurement(20.0, TestHeatingRatio, TestCoolingRatio, TestMinTemperature, TestMaxTemperature);
    const ThermostatAdjustment expected{AdjustmentEnum::Idle, 0s};
    ASSERT_EQ(expected, actual);
}

TEST_F(GetFullCoverageTest, IdleWhenIsJustWarmTest)
{
 	auto actual = m_thermostat->measurement(21.98, TestHeatingRatio, TestCoolingRatio, TestMinTemperature, TestMaxTemperature);
    const ThermostatAdjustment expected{AdjustmentEnum::Idle, 0s};
    ASSERT_EQ(expected, actual);
}

TEST_F(GetFullCoverageTest, CoolWhenIsWarmTest)
{
 	auto actual = m_thermostat->measurement(24.5, TestHeatingRatio, TestCoolingRatio, TestMinTemperature, TestMaxTemperature);
    const ThermostatAdjustment expected{AdjustmentEnum::Cool, 1250s};
    ASSERT_EQ(expected, actual);
}

int main(int argc, char **argv) {
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
