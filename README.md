# CppJsonHandler - C++ Serialization/Deserialization Library

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
