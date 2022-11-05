#ifndef DEMO_H
#define DEMO_H

#include "auto_json_helper.h"

namespace CppAutoSerializer {

    class Demo : public AutoJsonHelper {
    public:
        int id;
        std::string name;

        void SetJsonMapping() override {
            Map("id", id);
            Map("name", name);
        }
    };

} // namespace CppAutoSerializer

#endif // DEMO_H
