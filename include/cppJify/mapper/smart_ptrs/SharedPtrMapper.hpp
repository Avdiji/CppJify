#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <memory>

namespace cppJify::mapper {

    // default mapper for all Ptr types
    template <class T>
    class JifyMapper<std::shared_ptr<T>> {
        public:
            static const std::string CType() { return JIFY_FMT("std::shared_ptr<{}>", JifyMapper<T>::CType()); }
            static const std::string JniType() { return JifyMapper<T>::JniType(); }
            static const std::string JavaType() { return JifyMapper<T>::JavaType(); }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                // clang-format off
                return JIFY_FMT(
                    JIFY_RAW(
                        \n\t\t{} {} = static_cast<{}>(*cppJify::helper::cppJifyObjectToPtr<{}>(env, {}));
                    ),
                    CType(), cVar, CType(), JifyMapper<T>::CType(), jniVar);
                // clang-format on
            }

            static const std::string Out(const std::string& functionCall) {
                // clang-format off
                const std::string fullJName = utils::replaceAll(JavaType(), ".", "/");

                return JIFY_FMT(
                    JIFY_RAW(
                        cppJify::helper::CppJifyPtrWrapper<{}> *result = new cppJify::helper::CppJifyPtrWrapper<{}>({});
                        \n\t\treturn cppJify::helper::ptrToCppJifyObject(env, "{}", result);
                    ),
                    JifyMapper<T>::CType(), JifyMapper<T>::CType() , functionCall,
                    fullJName
                );
                // clang-format on
            }
    };

}  // namespace cppJify::mapper
