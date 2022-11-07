#include "demo.h"
#include "json_serializer.h"
#include <gtest/gtest.h>

using namespace CppAutoSerializer;

TEST(AutoJsonTest, SerializationTest) {
    Demo demo;
    demo.id = 42;
    demo.name = "Alice";

    std::string json_string = JsonSerializer::Serialize(demo);
    ASSERT_FALSE(json_string.empty());
    ASSERT_NE(json_string.find("\"id\":42"), std::string::npos);
    ASSERT_NE(json_string.find("\"name\":\"Alice\""), std::string::npos);
}

TEST(AutoJsonTest, DeserializationTest) {
    std::string json_string = R"({"id":123,"name":"Bob"})";
    Demo demo;
    JsonSerializer::Deserialize(json_string, demo);

    ASSERT_EQ(demo.id, 123);
    ASSERT_EQ(demo.name, "Bob");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
