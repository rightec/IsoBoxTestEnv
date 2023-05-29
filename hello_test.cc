#include <gtest/gtest.h>
#include "unittest_SimpleMath/unittest_SimpleMath.h"
#include "unittest_SimpleMath/isolatedBoxCmake.h"
#include "unittest_SimpleMath/isolatedBoxCmake.cpp"
#include "unittest_SimpleMath/isolatedBox_PID.cpp"
#include "unittest_SimpleMath/isolatedBox_actuator.cpp"

using namespace isoBoxApi;


TEST(testIsolated, boxInit)
{
    isoBox l_IsoBox = isoBox();
    /// <summary>
    ///  The initialization set points for max and min
    /// Should remain in the phisycal range determined 
    /// by the PID regulator (these are 20 and 100 expressed in Celsius)
    /// </summary>
    
 
    /// First test. Both value are under the minimum  - Negative Logic
    EXPECT_TRUE(!(l_IsoBox.init(1,2)));
    
    /// Second test. Both value are over the maximum   - Negative Logic
    EXPECT_TRUE(!(l_IsoBox.init(101, 102)));

    /// Third test. Min val is under the min treshold  - Negative Logic
    EXPECT_TRUE(!(l_IsoBox.init(1, 32)));

    /// Fourth test. Max val is over the max treshold  - Negative Logic
    EXPECT_TRUE(!(l_IsoBox.init(21, 320)));

    /// Fifth test. Max val = Min Val = default val  - Negative Logic
    EXPECT_TRUE(!(l_IsoBox.init(ISO_TEMP_SP_DEFAULT, ISO_TEMP_SP_DEFAULT)));

    /// Sixth test. Max val > Min Val both in the range - Positive Logic
    EXPECT_TRUE(l_IsoBox.init(25, 50));
    
}

TEST(testIsolated, testPointSettings)
{
    isoBox l_IsoBox = isoBox();
    temp_t l_minSetPoint = 25.0;
    temp_t l_maxSetPoint = 50.0;
    l_IsoBox.init(l_minSetPoint, l_maxSetPoint);

    /// <summary>
    /// Verify the Min set point
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    EXPECT_EQ(l_minSetPoint, l_IsoBox.getSetPoint(PID_MIN_SET_POINT));

    /// <summary>
    /// Verify the max set point
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    EXPECT_EQ(l_maxSetPoint, l_IsoBox.getSetPoint(PID_MAX_SET_POINT));

    /// <summary>
    /// By Default the target point is the minimum one
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    EXPECT_EQ(l_minSetPoint, l_IsoBox.getTargetPoint());

    /// <summary>
    /// Change the target point and verify the new setting is OK
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_IsoBox.setTargetPoint(PID_MAX_SET_POINT);
    EXPECT_EQ(l_maxSetPoint, l_IsoBox.getTargetPoint());
}

TEST(testIsolated, failCompensation_init)
{
    isoBox l_IsoBox = isoBox();
    temp_t l_minSetPoint = 21.0;
    temp_t l_maxSetPoint = 320.0;
    l_IsoBox.init(l_minSetPoint, l_maxSetPoint);

    /// <summary>
    /// The apply compensation should fail (ISO_DEF_UNDEF_TEMP) 
    /// because the init is KO
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    temp_t l_tempToMonitor = 37.0;
    EXPECT_EQ(ISO_DEF_UNDEF_TEMP, l_IsoBox.applyCompensation(l_tempToMonitor));

}

TEST(testIsolated, failCompensation_runTime)
{
    isoBox l_IsoBox = isoBox();
    temp_t l_minSetPoint = 25.0;
    temp_t l_maxSetPoint = 50.0;
    l_IsoBox.init(l_minSetPoint, l_maxSetPoint);

    /// <summary>
    /// The apply compensation should fail(ISO_DEF_UNDEF_TEMP)
    /// because the temp is in the range so we do not need to compensate
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    temp_t l_tempToMonitor = 37.0;
    EXPECT_EQ(ISO_DEF_UNDEF_TEMP, l_IsoBox.applyCompensation(l_tempToMonitor));

}

TEST(testIsolated, runCompensation)
{
    isoBox l_IsoBox = isoBox();
    temp_t l_minSetPoint = 25.0;
    temp_t l_maxSetPoint = 50.0;
    l_IsoBox.init(l_minSetPoint, l_maxSetPoint);
 
    /// <summary>
    /// The compensation should start to reach the 
    /// MAX (50.0) temperature point
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    temp_t l_tempToMonitor = 51.0;
    EXPECT_EQ(l_maxSetPoint, l_IsoBox.applyCompensation(l_tempToMonitor));

    /// <summary>
    /// The compensation starts from the MAX
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_tempToMonitor = 52.0;
    EXPECT_EQ(l_maxSetPoint, l_IsoBox.applyCompensation(l_tempToMonitor));

    /// <summary>
    /// The compensation restarts from the MIN
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_tempToMonitor = 23.0;
    EXPECT_EQ(l_minSetPoint, l_IsoBox.applyCompensation(l_tempToMonitor));

    /// <summary>
    /// The compensation should not apply because we are in the range
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_tempToMonitor = 25.0;
    EXPECT_EQ(ISO_DEF_UNDEF_TEMP, l_IsoBox.applyCompensation(l_tempToMonitor));

    /// <summary>
    /// The compensation restarts from the MIN
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_tempToMonitor = 24.999;
    EXPECT_EQ(l_minSetPoint, l_IsoBox.applyCompensation(l_tempToMonitor));

    /// <summary>
    /// The compensation should not apply because we are in the range
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_tempToMonitor = 50.0;
    EXPECT_EQ(ISO_DEF_UNDEF_TEMP, l_IsoBox.applyCompensation(l_tempToMonitor));

    /// <summary>
    /// The compensation restarts from the MAX
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    l_tempToMonitor = 50.0001;
    EXPECT_EQ(l_maxSetPoint, l_IsoBox.applyCompensation(l_tempToMonitor));

}