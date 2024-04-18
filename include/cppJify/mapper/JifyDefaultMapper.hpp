#pragma once

#include <jni.h>

#include <cppJify/utils/StringUtils.hpp>
#include <map>
#include <type_traits>
#include <typeinfo>

namespace cppJify::mapper {

    template <class T, class... Additional>
    class JifyDefaultMapper {
        private:
            // Mainly exists to track the Java - Types. Key = CType, Val = JavaType
            static inline std::map<std::string, std::string> _javaTypes = {};

        public:
            /**
             * Method is used to register a new Javatype when binding a C++ class.
             *
             * @param p_javaType The java type to register.
             */
            static void registerJavaType(const std::string& p_javaType) { _javaTypes[CType()] = p_javaType; }

            /**
             * Getter for the JNI Type of T
             *
             * @return The corresponding JNI-Type of T.
             */
            static const std::string JniType() { return "jlong"; }

            /**
             * Getter for a String representation of T
             *
             * @return A String representation of T.
             */
            static const std::string CType() {
                std::string result(typeid(T).name());
                utils::replaceAll(result, "class ", "");
                utils::replaceAll(result, "struct ", "");

                return result;
            }

            /**
             * Getter for the Java type of T
             *
             * @return The corresponding Java type of T.
             */
            static const std::string JavaType() {
                if (_javaTypes.count(CType()) == 0) {
                    throw std::runtime_error("Unknown Java Type for: " + CType() + ". Try mapping " + CType() +
                                             " using this Mapper as a base.");
                }
                return _javaTypes[CType()];
            }

            /**
             * Getter for the Boxed Javatype (e.g: int -> Integer).
             *
             * @return The correpsonding boxed Java type of T.
             */
            static const std::string BoxedJavaType() { return JavaType(); }

            /**
             * Method defines how Java types are translated to their corresponding C++ type.
             *
             * Initialize $carg (placeholder) using $jarg (placeholder).
             *
             * @param p_argId The identifier for the Placeholders
             * @param env nullptr by default. exists to make the mapping more intuitive.
             *
             * @return The Code, which transforms Java -> C++.
             */
            static const std::string In(const size_t& p_argId, JNIEnv* env = nullptr) {
                return utils::JIFY_TRANSFORM(

                    JIFY_RAW(

                        \t $ctype * $carg = reinterpret_cast<$ctype*>($jarg); \n

                        ),
                    p_argId, CType());
            }

            /**
             * Method defines how C++ types are translated to their corresponding Java type.
             *
             * Return $func (placeholder) as a Javatype.
             *
             * @param p_func Value that replaces the placeholder.
             * @param env nullptr by default. exists to make the mapping more intuitive.
             *
             * @return The Code, which transforms C++ -> Java.
             */
            static const std::string Out(const std::string& p_func, JNIEnv* env = nullptr) {
                return utils::JIFY_TRANSFORM(

                    JIFY_RAW(

                        \n\t $ctype * result = new $ctype($func); \n
                        \t return reinterpret_cast<jlong>(result); \n

                        ),
                    p_func, CType());
            }

            // TODO
            static const std::string Deref(JNIEnv* env = nullptr) { return "DEREF"; }
    };

}  // namespace cppJify::mapper
