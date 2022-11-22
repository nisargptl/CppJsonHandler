#ifndef DEMO_H
#define DEMO_H

#include "auto_json_helper.h"

namespace CppJsonHandler {

    class Demo : public AutoJsonHelper {
    public:
        int id;
        std::string name;

        void SetJsonMapping() override {
            Map("id", id);
            Map("name", name);
        }
    };

} // namespace CppJsonHandler

#endif // DEMO_H
