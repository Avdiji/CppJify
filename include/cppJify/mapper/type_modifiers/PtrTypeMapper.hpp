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
                // clang-format off
                return JIFY_FMT(
                    JIFY_RAW(
                        \n\t\tcppJify::helper::CppJifyPtrWrapper<{}> *{} = cppJify::helper::cppJifyObjectToPtr<{}>(env, {});
                    ),
                    JifyMapper<T>::CType(), cVar, JifyMapper<T>::CType(), jniVar);
                // clang-format on
            }

            static const std::string Out(const std::string& functionCall) {
                // clang-format off
                const std::string fullJName = utils::replaceAll(JavaType(), ".", "/");

                return JIFY_FMT(
                    JIFY_RAW(

                        {} result = {};
                        \n\t\tcppJify::helper::CppJifyPtrWrapper<{}> *resultWrapper = new cppJify::helper::CppJifyPtrWrapper<{}>(result);
                        \n\t\treturn cppJify::helper::ptrToCppJifyObject(env, "{}", resultWrapper);
                    ),
                    CType(), functionCall,
                    JifyMapper<T>::CType(), JifyMapper<T>::CType(),
                    fullJName
                );
                // clang-format on
            }
    };

    template <class T>
    class JifyMapper<const T*> {
        public:
            static const std::string CType() { return "const " + JifyMapper<T>::CType() + "*"; }
            static const std::string JniType() { return JifyMapper<T>::JniType(); }
            static const std::string JavaType() { return JifyMapper<T>::JavaType(); }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                // clang-format off
                return JIFY_FMT(
                    JIFY_RAW(
                        \n\t\tcppJify::helper::CppJifyPtrWrapper<const {}> *{} = cppJify::helper::cppJifyObjectToPtr<const {}>(env, {});
                    ),
                    JifyMapper<T>::CType(), cVar, JifyMapper<T>::CType(), jniVar);
                // clang-format on
            }

            static const std::string Out(const std::string& functionCall) {
                // clang-format off
                const std::string fullJName = utils::replaceAll(JavaType(), ".", "/");

                return JIFY_FMT(
                    JIFY_RAW(

                        {} result = {};
                        \n\t\tcppJify::helper::CppJifyPtrWrapper<const {}> *resultWrapper = new cppJify::helper::CppJifyPtrWrapper<const {}>(result);
                        \n\t\treturn cppJify::helper::ptrToCppJifyObject(env, "{}", resultWrapper);
                    ),
                    CType(), functionCall,
                    JifyMapper<T>::CType(), JifyMapper<T>::CType(),
                    fullJName
                );
                // clang-format on
            }
    };
}  // namespace cppJify::mapper
