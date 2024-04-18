#pragma once

#include <cppJify/utils/StringUtils.hpp>

namespace cppJify::jbinder {

    class JavaBinder {
        public:
            bool operator<(const JavaBinder& other);
            explicit JavaBinder(const std::string& p_packageName, const std::string& p_className);

            JavaBinder& bindMethod();

        private:
            std::string _packageName;
            std::string _className;
    };

}  // namespace cppJify::jbinder