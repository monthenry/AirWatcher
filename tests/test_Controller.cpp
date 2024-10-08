#include <gtest/gtest.h>
#include "../src/controllers/Controller.h"
#include "../src/models/Sensor.h"
#include "../src/models/Attribute.h"
#include "../src/models/Measurement.h"

TEST(ControllerTest, InitModel) {
    Controller controller;
    
    // Initialize the model
    controller.initModel();
    
    // Check if the Sensor map has been populated
    EXPECT_GT(Sensor::getSensorMap().size(), 0);

    // Check if the Attributes have been loaded
    EXPECT_GT(Attribute::getAttributes().size(), 0);

    // Check if Measurements have been loaded
    EXPECT_GT(Measurement::getMeasurements().size(), 0);
}

TEST(ControllerTest, ComputeAreaStatistics_ValidInput) {
    Controller controller;
    
    // Mock sensor data: assume initModel has populated the data
    controller.initModel();
    
    // Example inputs (latitude, longitude, radius, start time, end time)
    time_t startTime = controller.convertDateTimeToTimeT("01/01/2020 12:00:00");
    time_t endTime = controller.convertDateTimeToTimeT("01/01/2022 12:00:00");
    auto stats = controller.computeAreaStatistics(44, 0, 10, startTime, endTime);
    
    // Assert the size of the returned statistics
    EXPECT_GT(stats.size(), 0);

    // Check that specific pollutant stats are present, e.g., O3
    EXPECT_NE(stats.find("O3"), stats.end());

    // Validate that the stats (mean, max, min) for O3 are correctly calculated
    auto o3Stats = stats["O3"];
    EXPECT_GT(std::get<0>(o3Stats), 0);  // Mean
    EXPECT_GT(std::get<1>(o3Stats), 0);  // Max
    EXPECT_GT(std::get<2>(o3Stats), 0);  // Min
}

TEST(ControllerTest, ComputeAreaStatistics_InvalidTimeRange) {
    Controller controller;
    controller.initModel();

    // Invalid time range (startTime > endTime)
    time_t startTime = controller.convertDateTimeToTimeT("01/01/2022 12:00:00");
    time_t endTime = controller.convertDateTimeToTimeT("01/01/2020 12:00:00");
    
    auto stats = controller.computeAreaStatistics(44, 0, 10, startTime, endTime);
    
    // Expect the map to be empty since time range is invalid
    EXPECT_EQ(stats.size(), 0);
}

TEST(ControllerTest, ComputeSensorRanking_ValidSensor) {
    Controller controller;
    controller.initModel();
    
    // Example valid sensor ID
    Sensor* sensor = Sensor::getSensorMap()["Sensor1"];
    time_t startTime = controller.convertDateTimeToTimeT("01/01/2020 12:00:00");
    time_t endTime = controller.convertDateTimeToTimeT("01/01/2022 12:00:00");

    auto rankedSensors = controller.computeSensorRanking(*sensor, startTime, endTime);
    
    // Assert the size of the ranked sensors list
    EXPECT_GT(rankedSensors->size(), 0);

    // Validate that the list contains the correct sensor IDs and Atmo indices
    auto firstRankedSensor = rankedSensors->front();
    EXPECT_EQ(firstRankedSensor.first, "Sensor2");  // Example sensor ID
    EXPECT_GT(firstRankedSensor.second, 0);         // Atmo index
}

TEST(ControllerTest, ComputeSensorRanking_InvalidSensor) {
    Controller controller;
    controller.initModel();

    // Invalid sensor (does not exist)
    time_t startTime = controller.convertDateTimeToTimeT("01/01/2020 12:00:00");
    time_t endTime = controller.convertDateTimeToTimeT("01/01/2022 12:00:00");
    
    // Assuming "InvalidSensorID" doesn't exist
    list<string> input = {"InvalidSensorID", "01/01/2020 12:00:00", "01/01/2022 12:00:00"};
    controller.runSensorRanking(&input);
    
    // We expect the method to handle the error gracefully
    // Normally, we could assert that an error message was displayed
}

TEST(ControllerTest, ConvertDateTimeToTimeT_ValidDate) {
    Controller controller;
    time_t result = controller.convertDateTimeToTimeT("01/01/2020 12:00:00");

    // Check that the time is non-zero
    EXPECT_GT(result, 0);
}

TEST(ControllerTest, ConvertDateTimeToTimeT_InvalidDate) {
    Controller controller;
    time_t result = controller.convertDateTimeToTimeT("invalid date");

    // Expect the result to be 0 for an invalid date
    EXPECT_EQ(result, 0);
}

TEST(ControllerTest, PerformanceTests) {
    Controller controller;

    double duration1 = controller.Test1_AreaStatistics();
    double duration2 = controller.Test2_AreaStatistics();

    // Ensure tests return a valid time (positive value)
    EXPECT_GT(duration1, 0);
    EXPECT_GT(duration2, 0);
}