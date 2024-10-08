#include <gtest/gtest.h>
#include "../src/models/User.h"
#include <fstream>
#include <sstream>

/*----------------------------------------------------------------------------------------------------
TEST FIXTURE
----------------------------------------------------------------------------------------------------*/

class UserTest : public ::testing::Test {
protected:
    User* user;

    void SetUp() override {
        user = new User("testUser", "testPassword");
    }

    void TearDown() override {
        delete user;
        // Clear the static map for each test
        User::getMapUsers().clear();
    }
};

/*----------------------------------------------------------------------------------------------------
TEST CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

TEST_F(UserTest, DefaultConstructor) {
    // Arrange
    User u;

    // Assert
    EXPECT_EQ(u.getUserID(), "");
    EXPECT_EQ(u.getPassword(), "");
}

TEST_F(UserTest, ParameterizedConstructor) {
    // Assert
    EXPECT_EQ(user->getUserID(), "testUser");
    EXPECT_EQ(user->getPassword(), "testPassword");
}

/*----------------------------------------------------------------------------------------------------
TEST GETTERS
----------------------------------------------------------------------------------------------------*/

TEST_F(UserTest, GetUserID) {
    EXPECT_EQ(user->getUserID(), "testUser");
}

TEST_F(UserTest, GetPassword) {
    EXPECT_EQ(user->getPassword(), "testPassword");
}

TEST_F(UserTest, GetMapUsersInitiallyEmpty) {
    EXPECT_TRUE(User::getMapUsers().empty());
}

/*----------------------------------------------------------------------------------------------------
TEST PARSE USER
----------------------------------------------------------------------------------------------------*/

TEST_F(UserTest, ParseUser) {
    // Arrange
    std::string line = "user123;password123";

    // Act
    User* parsedUser = user->parseUser(line);

    // Assert
    EXPECT_EQ(parsedUser->getUserID(), "user123");
    EXPECT_EQ(parsedUser->getPassword(), "password123");

    // Cleanup
    delete parsedUser;
}

/*----------------------------------------------------------------------------------------------------
TEST INIT USERS
----------------------------------------------------------------------------------------------------*/

TEST_F(UserTest, InitUsers) {
    // Arrange
    std::string filename = "test_users.csv";
    std::ofstream out(filename);
    out << "user1;pass1" << std::endl;
    out << "user2;pass2" << std::endl;
    out.close();

    // Act
    bool initialized = user->initUsers(filename);

    // Assert
    EXPECT_TRUE(initialized);
    EXPECT_EQ(User::getMapUsers().size(), 2);
    EXPECT_EQ(User::getMapUsers()["user1"]->getPassword(), "pass1");
    EXPECT_EQ(User::getMapUsers()["user2"]->getPassword(), "pass2");

    // Cleanup
    std::remove(filename.c_str());
}

/*----------------------------------------------------------------------------------------------------
TEST INIT USERS FILE NOT FOUND
----------------------------------------------------------------------------------------------------*/

TEST_F(UserTest, InitUsersFileNotFound) {
    // Arrange
    std::string filename = "non_existing_file.csv";

    // Act
    bool initialized = user->initUsers(filename);

    // Assert
    EXPECT_FALSE(initialized);
    EXPECT_TRUE(User::getMapUsers().empty());
}

/*----------------------------------------------------------------------------------------------------
TEST DUPLICATE USER ID IN FILE
----------------------------------------------------------------------------------------------------*/

TEST_F(UserTest, InitUsersDuplicateUserID) {
    // Arrange
    std::string filename = "duplicate_users.csv";
    std::ofstream out(filename);
    out << "user1;pass1" << std::endl;
    out << "user1;pass2" << std::endl;
    out.close();

    // Act
    bool initialized = user->initUsers(filename);

    // Assert
    EXPECT_TRUE(initialized);
    EXPECT_EQ(User::getMapUsers().size(), 1); // Only one user due to duplicate IDs
    EXPECT_EQ(User::getMapUsers()["user1"]->getPassword(), "pass2"); // The second password should overwrite the first

    // Cleanup
    std::remove(filename.c_str());
}
