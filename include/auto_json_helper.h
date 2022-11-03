#ifndef AUTO_JSON_HELPER_H
#define AUTO_JSON_HELPER_H

#include "json_serializer.h"
#include <vector>
#include <map>

namespace CppAutoSerializer {

    class AutoJsonHelper {
    public:
        virtual void SetJsonMapping() = 0;

        void SetMethod(Internal::AutoJsonMethod method) {
            this->method_ = method;
        }

        void Clear() {
            json_string_.clear();
        }

        std::string GetString() const {
            return json_string_.empty() ? "{}" : "{" + json_string_.substr(0, json_string_.size() - 1) + "}";
        }

    protected:
        Internal::AutoJsonMethod method_;
        std::string json_string_;

        // General template for unmarshalling into objects
        template <typename T>
        void _unmarshal_into_obj_(T &var, const Json::Value &dc) {
            if constexpr (std::is_same<T, int>::value) {
                if (dc.isInt()) var = dc.asInt();
            } else if constexpr (std::is_same<T, float>::value) {
                if (dc.isDouble()) var = static_cast<float>(dc.asDouble());
            } else if constexpr (std::is_same<T, double>::value) {
                if (dc.isDouble()) var = dc.asDouble();
            } else if constexpr (std::is_same<T, bool>::value) {
                if (dc.isBool()) var = dc.asBool();
            } else if constexpr (std::is_same<T, std::string>::value) {
                if (dc.isString()) var = dc.asString();
            }
        }

        // Handling std::vector<T>
        template <typename T>
        void _unmarshal_into_obj_(std::vector<T> &var, const Json::Value &dc) {
            if (dc.isArray()) {
                var.clear();
                for (const auto &item : dc) {
                    T element;
                    _unmarshal_into_obj_(element, item);
                    var.push_back(element);
                }
            }
        }

        // Handling std::map<std::string, T>
        template <typename T>
        void _unmarshal_into_obj_(std::map<std::string, T> &var, const Json::Value &dc) {
            if (dc.isObject()) {
                var.clear();
                for (const auto &member : dc.getMemberNames()) {
                    T element;
                    _unmarshal_into_obj_(element, dc[member]);
                    var[member] = element;
                }
            }
        }

        template <typename T>
        void Map(const std::string &json_key, std::vector<T> &member) {
            if (method_ == Internal::AutoJsonMethod::Marshal) {
                json_string_ += "\"" + json_key + "\":[";
                for (const auto &item : member) {
                    std::string element_json;
                    _marshal_into_obj_(item, element_json);
                    json_string_ += element_json + ",";
                }
                json_string_ = json_string_.substr(0, json_string_.size() - 1) + "],";
            }
        }

        template <typename T>
        void Map(const std::string &json_key, std::map<std::string, T> &member) {
            if (method_ == Internal::AutoJsonMethod::Marshal) {
                json_string_ += "\"" + json_key + "\":{";
                for (const auto &pair : member) {
                    std::string element_json;
                    _marshal_into_obj_(pair.second, element_json);
                    json_string_ += "\"" + pair.first + "\":" + element_json + ",";
                }
                json_string_ = json_string_.substr(0, json_string_.size() - 1) + "},";
            }
        }

    private:
        template <typename T>
        void _marshal_into_obj_(T &member, std::string &json) {
            if constexpr (std::is_same<T, int>::value || std::is_same<T, float>::value ||
                          std::is_same<T, double>::value || std::is_same<T, bool>::value) {
                json = std::to_string(member);
            } else if constexpr (std::is_same<T, std::string>::value) {
                json = "\"" + member + "\"";
            }
        }
    };

} // namespace CppAutoSerializer

#endif // AUTO_JSON_HELPER_H
