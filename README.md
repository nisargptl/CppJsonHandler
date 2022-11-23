# CppJsonHandler - C++ Serialization/Deserialization Library

## Overview
CppJsonHandler is a C++ library designed to simplify the process of serializing and deserializing C++ objects to and from JSON format. The library leverages template metaprogramming to ensure type safety and provides a flexible, easy-to-use interface for mapping class members to JSON fields.

## Key Features
- **Automatic Mapping**: Automatically maps C++ class members to JSON fields with minimal configuration.
- **Type Safety**: Ensures that only objects with the required methods can be serialized or deserialized, using SFINAE (Substitution Failure Is Not An Error).
- **Support for Various Data Types**: Handles primitive types like `int`, `float`, `double`, `bool`, and `std::string`, as well as complex structures like `std::vector<T>` and `std::map<std::string, T>`.
- **Easy Integration**: Designed to be easily integrated into existing C++ projects with minimal setup.
- **Comprehensive Error Handling**: Provides robust error handling during JSON parsing and serialization.

## Getting Started

### Prerequisites
- **JsonCpp**: A JSON parsing library for C++. You can install it via your package manager or build it from source.
  - On Ubuntu: `sudo apt-get install libjsoncpp-dev`
  - On macOS: `brew install jsoncpp`
- **C++11 or later**: The library uses features introduced in C++11.
- **GoogleTest** (optional, for testing): A unit testing library for C++. You can install it via your package manager or build it from source.
  - On Ubuntu: `sudo apt-get install libgtest-dev`
  - On macOS: `brew install googletest`

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/CppJsonHandler.git
   cd CppJsonHandler
   ```

2. Include the headers in your project:
   - Add `include/json_serializer.h` and `include/json_helper.h` to your project.
   - Optionally, you can include `include/CppJsonHandler.h` for a single-point inclusion.

### Example Usage

Here is an example of how to use `CppJsonHandler` to serialize and deserialize a simple class:

```cpp
#include "demo.h"
#include "json_serializer.h"
#include <iostream>

using namespace CppJsonHandler;

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
```

### Running the Tests
If you have GoogleTest installed, you can run the provided unit tests to verify the functionality of the library.

1. Compile the tests:
   ```bash
   g++ -std=c++11 -Iinclude -I/path/to/googletest/include test/test_auto_json.cpp -L/path/to/googletest/lib -lgtest -lgtest_main -pthread -o test_auto_json
   ```

2. Run the tests:
   ```bash
   ./test_auto_json
   ```




---

Enjoy using CppJsonHandler! We hope it simplifies your C++ JSON serialization and deserialization tasks.
