#include <gtest/gtest.h>
#include "../src/models/PrivateIndividual.h"
#include "../src/models/Sensor.h"

/*----------------------------------------------------------------------------------------------------
TEST FIXTURE
----------------------------------------------------------------------------------------------------*/

class PrivateIndividualTest : public ::testing::Test {
protected:
    PrivateIndividual* individual;

    void SetUp() override {
        // Initialize a PrivateIndividual with some points and reliable status
        individual = new PrivateIndividual("user123", "password", 100, true);
    }

    void TearDown() override {
        delete individual;
    }
};

/*----------------------------------------------------------------------------------------------------
TEST CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

TEST_F(PrivateIndividualTest, ParameterizedConstructor) {
    // Act
    PrivateIndividual p("user123", "password", 100, true);

    // Assert
    EXPECT_EQ(p.getPoints(), 100);
    EXPECT_TRUE(p.getReliable());
    EXPECT_EQ(p.getSensors().size(), 0); // Sensors list should be empty on initialization
}

/*----------------------------------------------------------------------------------------------------
TEST GETTERS
----------------------------------------------------------------------------------------------------*/

TEST_F(PrivateIndividualTest, GetPoints) {
    // Act & Assert
    EXPECT_EQ(individual->getPoints(), 100);
}

TEST_F(PrivateIndividualTest, GetReliable) {
    // Act & Assert
    EXPECT_TRUE(individual->getReliable());
}

TEST_F(PrivateIndividualTest, GetSensors_InitiallyEmpty) {
    // Act & Assert
    EXPECT_EQ(individual->getSensors().size(), 0); // Should be empty at initialization
}

/*----------------------------------------------------------------------------------------------------
TEST SETTERS
----------------------------------------------------------------------------------------------------*/

TEST_F(PrivateIndividualTest, SetPoints) {
    // Act
    individual->setPoints(200);

    // Assert
    EXPECT_EQ(individual->getPoints(), 200);
}

TEST_F(PrivateIndividualTest, SetReliable) {
    // Act
    individual->setReliable(false);

    // Assert
    EXPECT_FALSE(individual->getReliable());
}

TEST_F(PrivateIndividualTest, SetSensors) {
    // Arrange
    Sensor* sensor1 = new Sensor("S1", "Sensor 1");
    Sensor* sensor2 = new Sensor("S2", "Sensor 2");
    std::list<Sensor*> sensorList = {sensor1, sensor2};

    // Act
    individual->setSensors(sensorList);

    // Assert
    EXPECT_EQ(individual->getSensors().size(), 2);
    EXPECT_EQ(individual->getSensors().front(), sensor1);
    EXPECT_EQ(individual->getSensors().back(), sensor2);

    // Cleanup
    delete sensor1;
    delete sensor2;
}

/*----------------------------------------------------------------------------------------------------
TEST ADD SENSOR
----------------------------------------------------------------------------------------------------*/

TEST_F(PrivateIndividualTest, AddSensor) {
    // Arrange
    Sensor* sensor = new Sensor("S1", "Sensor 1");

    // Act
    individual->addSensor(sensor);

    // Assert
    EXPECT_EQ(individual->getSensors().size(), 1);
    EXPECT_EQ(individual->getSensors().front(), sensor);

    // Cleanup
    delete sensor;
}
