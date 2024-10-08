#include "../src/models/Attribute.h"
#include <gtest/gtest.h>
#include <fstream>

// Test constructor with parameters
TEST(AttributeTest, ConstructorWithParameters) {
    Attribute attr("A1", "kg", "Weight");
    
    EXPECT_EQ(attr.getAttributeId(), "A1");
    EXPECT_EQ(attr.getUnit(), "kg");
    EXPECT_EQ(attr.getDescription(), "Weight");
}

// Test default constructor
TEST(AttributeTest, DefaultConstructor) {
    Attribute attr;
    
    EXPECT_EQ(attr.getAttributeId(), "");
    EXPECT_EQ(attr.getUnit(), "");
    EXPECT_EQ(attr.getDescription(), "");
}

// Test getters and setters
TEST(AttributeTest, GettersAndSetters) {
    Attribute attr("A1", "m", "Length");
    
    EXPECT_EQ(attr.getUnit(), "m");
    EXPECT_EQ(attr.getDescription(), "Length");
    
    attr.setUnit("cm");
    attr.setDescription("Centimeters");
    
    EXPECT_EQ(attr.getUnit(), "cm");
    EXPECT_EQ(attr.getDescription(), "Centimeters");
}

// Test parseAttribute function
TEST(AttributeTest, ParseAttribute) {
    string line = "A1;m;Length";
    Attribute* attr = Attribute::parseAttribute(line);
    
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->getAttributeId(), "A1");
    EXPECT_EQ(attr->getUnit(), "m");
    EXPECT_EQ(attr->getDescription(), "Length");
    
    delete attr;
}

// Test initAttributes function
TEST(AttributeTest, InitAttributes) {
    // Create a test file
    std::ofstream testFile("test_attributes.csv");
    testFile << "A1;m;Length\nA2;kg;Weight\n";
    testFile.close();
    
    // Call the function
    bool result = Attribute::initAttributes("test_attributes.csv");
    
    EXPECT_TRUE(result);
    auto attributesMap = Attribute::getMapAttributes();
    
    ASSERT_EQ(attributesMap.size(), 2);
    EXPECT_EQ(attributesMap["A1"]->getAttributeId(), "A1");
    EXPECT_EQ(attributesMap["A1"]->getUnit(), "m");
    EXPECT_EQ(attributesMap["A1"]->getDescription(), "Length");
    EXPECT_EQ(attributesMap["A2"]->getAttributeId(), "A2");
    EXPECT_EQ(attributesMap["A2"]->getUnit(), "kg");
    EXPECT_EQ(attributesMap["A2"]->getDescription(), "Weight");
    
    // Clean up
    remove("test_attributes.csv");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
