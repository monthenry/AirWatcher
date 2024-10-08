#include <gtest/gtest.h>
#include "../src/views/View.h"
#include <sstream>
#include <map>

/*----------------------------------------------------------------------------------------------------
TEST FIXTURE
----------------------------------------------------------------------------------------------------*/

class ViewTest : public ::testing::Test {
protected:
    View* view;

    void SetUp() override {
        view = new View();
    }

    void TearDown() override {
        delete view;
    }
};

/*----------------------------------------------------------------------------------------------------
TEST INPUT FUNCTIONS
----------------------------------------------------------------------------------------------------*/

TEST_F(ViewTest, GetUserChoiceValidInput) {
    // Arrange
    std::istringstream input("2\n");
    std::cin.rdbuf(input.rdbuf());

    // Act
    int choice = view->getUserChoice();

    // Assert
    EXPECT_EQ(choice, 2);
}

TEST_F(ViewTest, GetUserChoiceInvalidInput) {
    // Arrange
    std::istringstream input("invalid\n");
    std::cin.rdbuf(input.rdbuf());

    // Act
    int choice = view->getUserChoice();

    // Assert
    EXPECT_EQ(choice, 999);  // When input is invalid, 999 should be returned
}

TEST_F(ViewTest, GetAreaStatisticsInput) {
    // Arrange
    std::istringstream input("45.76\n4.83\n10\n01/01/2020 00:00:00\n31/12/2020 23:59:59\n");
    std::cin.rdbuf(input.rdbuf());

    // Act
    list<string>* params = view->getAreaStatisticsInput();

    // Assert
    ASSERT_EQ(params->size(), 5);
    auto it = params->begin();
    EXPECT_EQ(*it++, "45.76");
    EXPECT_EQ(*it++, "4.83");
    EXPECT_EQ(*it++, "10");
    EXPECT_EQ(*it++, "01/01/2020 00:00:00");
    EXPECT_EQ(*it++, "31/12/2020 23:59:59");

    // Cleanup
    delete params;
}

TEST_F(ViewTest, GetSensorRankingInput) {
    // Arrange
    std::istringstream input("sensor123\n01/01/2020 00:00:00\n31/12/2020 23:59:59\n");
    std::cin.rdbuf(input.rdbuf());

    // Act
    list<string>* params = view->getSensorRankingInput();

    // Assert
    ASSERT_EQ(params->size(), 3);
    auto it = params->begin();
    EXPECT_EQ(*it++, "sensor123");
    EXPECT_EQ(*it++, "01/01/2020 00:00:00");
    EXPECT_EQ(*it++, "31/12/2020 23:59:59");

    // Cleanup
    delete params;
}

/*----------------------------------------------------------------------------------------------------
TEST DISPLAY FUNCTIONS
----------------------------------------------------------------------------------------------------*/

TEST_F(ViewTest, DisplayTitleSeparator) {
    // Capture output
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    // Act
    view->displayTitleSeparator("Test Title");

    // Assert
    std::string expectedOutput = "--------------------------------------------------------------------\nTest Title\n--------------------------------------------------------------------\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST_F(ViewTest, DisplayErrorMessage) {
    // Capture output
    std::ostringstream output;
    std::cerr.rdbuf(output.rdbuf());

    // Act
    view->displayErrorMessage("An error occurred");

    // Assert
    std::string expectedOutput = "--------------------------------------------------------------------\nError : An error occurred\n--------------------------------------------------------------------\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST_F(ViewTest, DisplayPerformanceTestResult) {
    // Capture output
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    // Act
    view->displayPerformanceTestResult(1.12345678, 2.23456789, 3.34567890, 4.45678901, 5.56789012, 6.67890123, 7.78901234, 8.89012345);

    // Assert
    std::string expectedOutput =
        "--------------------------------------------------------------------\n"
        "PERFORMANCE VALUES OF PREVIOUS TESTS (in seconds)\n"
        "--------------------------------------------------------------------\n"
        "|-------------------------------------------------|\n"
        "| Test number | Area Statistics | Sensors ranking |\n"
        "|-------------|-----------------|-----------------|\n"
        "|            1|       1.12345678|       5.56789012|\n"
        "|-------------|-----------------|-----------------|\n"
        "|            2|       2.23456789|       6.67890123|\n"
        "|-------------|-----------------|-----------------|\n"
        "|            3|       3.34567890|       7.78901234|\n"
        "|-------------|-----------------|-----------------|\n"
        "|            4|       4.45678901|       8.89012345|\n"
        "|-------------------------------------------------|\n";
    
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST_F(ViewTest, DisplaySensorList) {
    // Arrange
    std::map<std::string, Sensor*> sensors;
    sensors["sensor1"] = new Sensor("sensor1");
    sensors["sensor2"] = new Sensor("sensor2");

    // Capture output
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    // Act
    view->displaySensorList(sensors);

    // Assert
    std::string expectedOutput = 
        "--------------------------------------------------------------------\n"
        "SENSOR LIST\n"
        "--------------------------------------------------------------------\n"
        "sensor1\n"
        "sensor2\n";
    EXPECT_EQ(output.str(), expectedOutput);

    // Cleanup
    for (auto& pair : sensors) {
        delete pair.second;
    }
}

TEST_F(ViewTest, DisplayAreaStatistics) {
    // Arrange
    std::map<std::string, std::tuple<int, int, int>> mapMean = {
        {"PM10", std::make_tuple(50, 100, 25)},
        {"NO2", std::make_tuple(40, 90, 20)}
    };

    // Capture output
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    // Act
    view->displayAreaStatistics(&mapMean);

    // Assert
    std::string expectedOutput = 
        "--------------------------------------------------------------------\n"
        "STATISTICS IN THE SELECTED AREA AND TIMEFRAME\n"
        "--------------------------------------------------------------------\n"
        "PM10 : mean = 50; max = 100; min = 25\n"
        "NO2 : mean = 40; max = 90; min = 20\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST_F(ViewTest, DisplaySensorRanking) {
    // Arrange
    std::list<std::pair<std::string, int>> sensorRanked = { 
        {"sensor1", 75}, 
        {"sensor2", 80}
    };

    // Capture output
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    // Act
    view->displaySensorRanking("sensor123", 78, &sensorRanked);

    // Assert
    std::string expectedOutput = 
        "--------------------------------------------------------------------\n"
        "SIMILARITY RANKING TO SENSOR : sensor123\n"
        "--------------------------------------------------------------------\n"
        "Sensor ID : sensor1 | Atmo index : 75 | Delta : 3\n"
        "Sensor ID : sensor2 | Atmo index : 80 | Delta : 2\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

