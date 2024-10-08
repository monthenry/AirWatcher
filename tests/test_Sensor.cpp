#include <gtest/gtest.h>
#include "../src/models/Sensor.h"
#include "../src/models/Measurement.h"
#include "../src/models/Attribute.h"
#include <ctime>

/*----------------------------------------------------------------------------------------------------
TEST FIXTURE
----------------------------------------------------------------------------------------------------*/

class SensorTest : public ::testing::Test {
protected:
    Sensor* sensor;

    void SetUp() override {
        sensor = new Sensor("S1", 45.7640, 4.8357, true);
    }

    void TearDown() override {
        delete sensor;
    }
};

/*----------------------------------------------------------------------------------------------------
TEST CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, ParameterizedConstructor) {
    // Act
    Sensor s("S2", 48.8566, 2.3522, false);

    // Assert
    EXPECT_EQ(s.getSensorId(), "S2");
    EXPECT_EQ(s.getLatitude(), 48.8566);
    EXPECT_EQ(s.getLongitude(), 2.3522);
    EXPECT_FALSE(s.getFunctionning());
}

/*----------------------------------------------------------------------------------------------------
TEST GETTERS
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, GetSensorId) {
    EXPECT_EQ(sensor->getSensorId(), "S1");
}

TEST_F(SensorTest, GetLatitude) {
    EXPECT_EQ(sensor->getLatitude(), 45.7640);
}

TEST_F(SensorTest, GetLongitude) {
    EXPECT_EQ(sensor->getLongitude(), 4.8357);
}

TEST_F(SensorTest, GetFunctionning) {
    EXPECT_TRUE(sensor->getFunctionning());
}

TEST_F(SensorTest, GetMeasurementsInitiallyEmpty) {
    EXPECT_TRUE(sensor->getMeasurements().empty());
}

/*----------------------------------------------------------------------------------------------------
TEST SETTERS
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, SetLatitude) {
    sensor->setLatitude(40.7128);
    EXPECT_EQ(sensor->getLatitude(), 40.7128);
}

TEST_F(SensorTest, SetLongitude) {
    sensor->setLongitude(-74.0060);
    EXPECT_EQ(sensor->getLongitude(), -74.0060);
}

TEST_F(SensorTest, SetFunctionning) {
    sensor->setFunctionning(false);
    EXPECT_FALSE(sensor->getFunctionning());
}

TEST_F(SensorTest, SetMeasurements) {
    // Arrange
    list<Measurement*> measurements;
    time_t now = time(0);
    Attribute* attr = new Attribute("O3");
    Sensor* dummySensor = new Sensor();
    Measurement* m = new Measurement(now, 50, attr, dummySensor);
    measurements.push_back(m);

    // Act
    sensor->setMeasurements(measurements);

    // Assert
    EXPECT_EQ(sensor->getMeasurements().size(), 1);

    // Cleanup
    delete attr;
    delete dummySensor;
    delete m;
}

/*----------------------------------------------------------------------------------------------------
TEST ADD MEASUREMENT
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, AddMeasurement) {
    // Arrange
    time_t now = time(0);
    Attribute* attr = new Attribute("NO2");
    Sensor* dummySensor = new Sensor();
    Measurement* m = new Measurement(now, 60, attr, dummySensor);

    // Act
    sensor->addMeasurement(m);

    // Assert
    EXPECT_EQ(sensor->getMeasurements().size(), 1);
    EXPECT_EQ(sensor->getMeasurements().front(), m);

    // Cleanup
    delete attr;
    delete dummySensor;
    delete m;
}

/*----------------------------------------------------------------------------------------------------
TEST PARSE SENSOR
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, ParseSensor) {
    // Arrange
    string line = "S1;4.8357;45.7640";

    // Act
    Sensor* parsedSensor = sensor->parseSensor(line);

    // Assert
    EXPECT_EQ(parsedSensor->getSensorId(), "S1");
    EXPECT_EQ(parsedSensor->getLongitude(), 4.8357);
    EXPECT_EQ(parsedSensor->getLatitude(), 45.7640);

    // Cleanup
    delete parsedSensor;
}

/*----------------------------------------------------------------------------------------------------
TEST INIT SENSOR
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, InitSensor) {
    // Arrange
    string filename = "test_sensors.csv"; // A test CSV file with valid sensor data
    std::ofstream out(filename);
    out << "S1;4.8357;45.7640" << std::endl;
    out.close();

    // Act
    bool initialized = sensor->initSensor(filename);

    // Assert
    EXPECT_TRUE(initialized);
    EXPECT_EQ(Sensor::getSensorMap().size(), 1);
    EXPECT_NE(Sensor::getSensorMap().find("S1"), Sensor::getSensorMap().end());

    // Cleanup
    remove(filename.c_str());
}

/*----------------------------------------------------------------------------------------------------
TEST ATMO INDEX
----------------------------------------------------------------------------------------------------*/

TEST_F(SensorTest, GetAtmoIndex) {
    // Arrange
    time_t now = time(0);
    Attribute* attrO3 = new Attribute("O3");
    Attribute* attrNO2 = new Attribute("NO2");
    Sensor* dummySensor = new Sensor();
    Measurement* m1 = new Measurement(now, 250, attrO3, dummySensor); // O3 measurement
    Measurement* m2 = new Measurement(now, 150, attrNO2, dummySensor); // NO2 measurement
    sensor->addMeasurement(m1);
    sensor->addMeasurement(m2);

    // Act
    int atmoIndex = sensor->getAtmoIndex(now - 10, now + 10);

    // Assert
    EXPECT_EQ(atmoIndex, 9); // Expected Atmo Index based on provided values

    // Cleanup
    delete attrO3;
    delete attrNO2;
    delete dummySensor;
    delete m1;
    delete m2;
}
