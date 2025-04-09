#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // default mapper for all Ptr types
    template <class T>
    class JifyMapper<T*> {
        public:
            static const std::string CType() { return JifyMapper<T>::CType() + "*"; }
            static const std::string JniType() { return JifyMapper<T>::JniType(); }
            static const std::string JavaType() { return JifyMapper<T>::JavaType(); }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(
                    JIFY_RAW(
                        \n\t\t{} {} = cppJify::helper::GetNativePtr<{}>(env, {});
                    ),
                    CType(), cVar,
                    JifyMapper<T>::CType(), jniVar
                );
            }

            static const std::string Out(const std::string& functionCall) {
                return "TODO";
            }
    };

    template <class T>
    class JifyMapper<const T*> {
        public:
            static const std::string CType() { return "const " + JifyMapper<T>::CType() + "*"; }
            static const std::string JniType() { return JifyMapper<T>::JniType(); }
            static const std::string JavaType() { return JifyMapper<T>::JavaType(); }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(
                    JIFY_RAW(
                        \n\t\t{} {} = cppJify::helper::GetNativePtr<{}>(env, {});
                    ),
                    CType(), cVar,
                    JifyMapper<T>::CType(), jniVar
                );
            }

            static const std::string Out(const std::string& functionCall) {
                return "TODO";
            }
    };
}  // namespace cppJify::mapper
