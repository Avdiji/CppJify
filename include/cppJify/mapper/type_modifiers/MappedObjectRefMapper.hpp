#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    template <class T>
    class JifyMapper<T&> {
        public:
            static const std::string CType() { return JifyMapper<T>::CType(); }
            static const std::string JniType() {  return JifyMapper<T>::JniType(); }
            static const std::string JavaType() { return JifyMapper<T>::JavaType(); }

            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return "FITOR\n\n";
            }

            static const std::string Out(const std::string& functionCall) { return "JIFY_RAW(TODO map this properly);"; }
    };

}  // namespace cppJify::mapper
