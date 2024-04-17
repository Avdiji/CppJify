#pragma once

#include <jni.h>

#include <cppJify/utils/StringUtils.hpp>
#include <type_traits>
#include <typeinfo>

namespace cppJify::mapper {

    template <class T, class... Additional>
    class JifyDefaultMapper {
        public:
            static const std::string CType() {
                std::string result(typeid(T).name());
                utils::replaceAll(result, "class ", "");
                utils::replaceAll(result, "struct ", "");

                return result;
            }

            static const std::string JniType() { return "jlong"; }
            static const std::string JavaType() { return "long"; }
            static const std::string BoxedJavaType() { return "Long"; }

            static const std::string In(const size_t& p_argId, JNIEnv* env = nullptr) {
                return utils::JIFY_TRANSFORM(

                    JIFY_RAW(

                        \t $ctype * $carg = reinterpret_cast<$ctype*>($jarg); \n

                        ),
                    p_argId, CType());
            }

            static const std::string Out(const std::string& p_func, JNIEnv* env = nullptr) {
                return utils::JIFY_TRANSFORM(

                    JIFY_RAW(

                        \n\t $ctype * result = new $ctype($func); \n
                        \t return reinterpret_cast<jlong>(result); \n

                        ),
                    p_func, CType());
            }
            static const std::string Deref(JNIEnv* env = nullptr) { return "DEREF"; }
    };

}  // namespace cppJify::mapper
