#include <gtest/gtest.h>
#include "../src/models/GovernmentAgent.h"
#include <string>

TEST(GovernmentAgentTest, Constructor_ValidInput) {
    // Arrange
    std::string id = "agent123";
    std::string pwd = "password123";

    // Act
    GovernmentAgent agent(id, pwd);

    // Assert
    // Check that the object was initialized correctly
    EXPECT_EQ(agent.getId(), id);   // Assuming getId() is accessible from User
    EXPECT_EQ(agent.getPassword(), pwd);  // Assuming getPassword() is accessible from User
}

TEST(GovernmentAgentTest, Destructor_NoMemoryLeak) {
    // Arrange
    std::string id = "agent123";
    std::string pwd = "password123";

    // Act & Assert
    // Create an object inside a scope and check if it gets destroyed properly.
    {
        GovernmentAgent agent(id, pwd);
        // Object goes out of scope here, triggering the destructor
    }

    // If there is no crash or memory leak detected, the test passes.
    SUCCEED();
}
