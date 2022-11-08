# CppAutoSerializer - C++ Serialization/Deserialization Library

## Overview
This library provides a simple and flexible way to serialize and deserialize C++ objects to and from JSON format, using template metaprogramming for type safety and extensibility.

## Key Features
- Automatic mapping of C++ class members to JSON fields.
- Support for basic data types and complex structures like nested objects.
- Easy integration into existing C++ projects.
- Robust error handling and type safety.

## Getting Started

### Prerequisites
- [Jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- C++11 or later
- [GoogleTest](https://github.com/google/googletest) for unit testing

### Example Usage

```cpp
#include "demo.h"
#include "json_serializer.h"
#include <iostream>

using namespace CppAutoSerializer;

int main() {
    // Create and populate a Demo object
    Demo demo;
    demo.id = 42;
    demo.name = "Alice";

    // Serialize the Demo object to a JSON string
    std::string json_string = JsonSerializer::Serialize(demo);
    std::cout << "Serialized JSON: " << json_string << std::endl;

    // Prepare a JSON string for deserialization
    std::string json_input = R"({"id": 123, "name": "Bob"})";

    // Deserialize the JSON string into a new Demo object
    Demo new_demo;
    JsonSerializer::Deserialize(json_input, new_demo);

    // Output the deserialized object’s values
    std::cout << "Deserialized Demo ID: " << new_demo.id << std::endl;
    std::cout << "Deserialized Demo Name: " << new_demo.name << std::endl;

    return 0;
}
