#ifndef AUTO_JSON_HELPER_H
#define AUTO_JSON_HELPER_H

#include "json_serializer.h"

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
    };

} // namespace CppAutoSerializer

#endif // AUTO_JSON_HELPER_H
