#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <string>
#include <type_traits>
#include "json/json.h"

namespace CppAutoSerializer {
    namespace Internal {

        enum class AutoJsonMethod {
            Default,
            Marshal,
            Unmarshal
        };

        // SFINAE to check if a class has a SetJsonMapping method
        template <typename T>
        class has_SetJsonMapping {
        private:
            template <typename U>
            static auto test(U*) -> decltype(std::declval<U>().SetJsonMapping(), std::true_type());

            template <typename>
            static std::false_type test(...);

        public:
            static constexpr bool value = std::is_same<decltype(test<T>(nullptr)), std::true_type>::value;
        };

    } // namespace Internal

    class JsonSerializer {
    public:
        template <typename T, typename std::enable_if<Internal::has_SetJsonMapping<T>::value, int>::type = 0>
        static std::string Serialize(T& obj) {
            obj.SetMethod(Internal::AutoJsonMethod::Marshal);
            obj.SetJsonMapping();
            return obj.GetString();
        }

        template <typename T, typename std::enable_if<Internal::has_SetJsonMapping<T>::value, int>::type = 0>
        static void Deserialize(const std::string& json_string, T& obj) {
            Json::Value root;
            Json::CharReaderBuilder reader;
            std::istringstream s(json_string);
            std::string errs;
            if (Json::parseFromStream(reader, s, &root, &errs)) {
                obj.SetMethod(Internal::AutoJsonMethod::Unmarshal);
                obj.SetJsonMapping();
                obj._unmarshal_internal(root);
            } else {
                throw std::runtime_error("Failed to parse JSON: " + errs);
            }
        }
    };

} // namespace CppAutoSerializer

#endif // JSON_SERIALIZER_H
