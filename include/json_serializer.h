#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <string>
#include <type_traits>
#include <json/json.h>

enum class AutoJsonMethod {
    Default,
    Marshal,
    Unmarshal
};

class JsonSerializer {
public:
    template <typename T>
    static std::string Serialize(T& obj) {
        Json::Value root;
        obj.SetMethod(AutoJsonMethod::Marshal);
        obj.SetJsonMapping();
        return obj.GetString();
    }

    template <typename T>
    static void Deserialize(const std::string& json_string, T& obj) {
        Json::Value root;
        Json::CharReaderBuilder reader;
        std::istringstream s(json_string);
        std::string errs;
        if (Json::parseFromStream(reader, s, &root, &errs)) {
            obj.SetMethod(AutoJsonMethod::Unmarshal);
            obj.SetJsonMapping();
            obj._unmarshal_internal(root);
        } else {
            throw std::runtime_error("Failed to parse JSON: " + errs);
        }
    }
};

#endif // JSON_SERIALIZER_H
