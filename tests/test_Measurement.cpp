#include <gtest/gtest.h>
#include "../src/models/Measurement.h"
#include "../src/models/Sensor.h"
#include "../src/models/Attribute.h"
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

/*----------------------------------------------------------------------------------------------------
TEST FIXTURE
----------------------------------------------------------------------------------------------------*/

class MeasurementTest : public ::testing::Test {
protected:
    time_t testTime;
    float testValue;
    Sensor* testSensor;
    Attribute* testAttribute;

    void SetUp() override {
        // Sample time setup (2024-10-08 10:00:00)
        struct tm timeinfo = {};
        timeinfo.tm_year = 2024 - 1900;
        timeinfo.tm_mon = 9; // October (0-based index, so 9 is October)
        timeinfo.tm_mday = 8;
        timeinfo.tm_hour = 10;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
        testTime = mktime(&timeinfo);

        testValue = 42.5;

        // Create a mock Sensor and Attribute
        testSensor = new Sensor("S1", "Sensor 1");
        testAttribute = new Attribute("A1", "Attribute 1");
    }

    void TearDown() override {
        delete testSensor;
        delete testAttribute;
    }
};

/*----------------------------------------------------------------------------------------------------
TEST CONSTRUCTORS
----------------------------------------------------------------------------------------------------*/

TEST_F(MeasurementTest, DefaultConstructor) {
    // Act
    Measurement m;

    // Assert
    EXPECT_EQ(m.getTime(), time_t(0));    // Default time should be 0
    EXPECT_EQ(m.getValue(), 0.0f);        // Default value should be 0
    EXPECT_EQ(m.getSensor(), nullptr);    // Default sensor should be null
    EXPECT_EQ(m.getAttribute(), nullptr); // Default attribute should be null
}

TEST_F(MeasurementTest, ParameterizedConstructor) {
    // Act
    Measurement m(testTime, testValue, testAttribute, testSensor);

    // Assert
    EXPECT_EQ(m.getTime(), testTime);
    EXPECT_EQ(m.getValue(), testValue);
    EXPECT_EQ(m.getSensor(), testSensor);
    EXPECT_EQ(m.getAttribute(), testAttribute);
}

/*----------------------------------------------------------------------------------------------------
TEST GETTERS
----------------------------------------------------------------------------------------------------*/

TEST_F(MeasurementTest, Getters) {
    // Arrange
    Measurement m(testTime, testValue, testAttribute, testSensor);

    // Act & Assert
    EXPECT_EQ(m.getTime(), testTime);
    EXPECT_EQ(m.getValue(), testValue);
    EXPECT_EQ(m.getSensor(), testSensor);
    EXPECT_EQ(m.getAttribute(), testAttribute);
}

/*----------------------------------------------------------------------------------------------------
TEST PARSE MEASUREMENT
----------------------------------------------------------------------------------------------------*/

TEST_F(MeasurementTest, ParseMeasurement_ValidLine) {
    // Arrange
    string line = "2024-10-08 10:00:00;S1;A1;42.5";

    // Mock Sensor and Attribute maps
    Sensor::getSensorMap()["S1"] = testSensor;
    Attribute::getMapAttributes()["A1"] = testAttribute;

    // Act
    Measurement* m = Measurement::parseMeasurement(line);

    // Assert
    EXPECT_EQ(m->getTime(), testTime);
    EXPECT_EQ(m->getValue(), 42.5f);
    EXPECT_EQ(m->getSensor(), testSensor);
    EXPECT_EQ(m->getAttribute(), testAttribute);

    // Clean up
    delete m;
}

/*----------------------------------------------------------------------------------------------------
TEST INIT MEASUREMENTS
----------------------------------------------------------------------------------------------------*/

TEST_F(MeasurementTest, InitMeasurements_FileExists) {
    // Arrange
    string filename = "test_measurements.csv";
    
    // Create a mock file (assuming we have write access for test purposes)
    ofstream testFile(filename);
    testFile << "2024-10-08 10:00:00;S1;A1;42.5\n";
    testFile.close();

    // Mock Sensor and Attribute maps
    Sensor::getSensorMap()["S1"] = testSensor;
    Attribute::getMapAttributes()["A1"] = testAttribute;

    // Act
    Measurement m;
    bool result = m.initMeasurements(filename);

    // Assert
    EXPECT_TRUE(result); // File exists and was processed successfully

    // Cleanup test file
    remove(filename.c_str());
}

TEST_F(MeasurementTest, InitMeasurements_FileNotFound) {
    // Act
    Measurement m;
    bool result = m.initMeasurements("non_existent_file.csv");

    // Assert
    EXPECT_FALSE(result); // File should not exist, so initMeasurements should return false
}
