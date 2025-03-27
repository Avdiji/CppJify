#pragma once

#include <cppJify/utils/StringUtils.hpp>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace cppJify::mapper
{

    /**
     * @brief Template for all typemapings. Use this class to define custom mappings.
     * @tparam T The datatype to be mapped.
     * @tparam Additional... Additional generic types in case of std::vector<U> (or any other templated datatype).
     *
     */
    template <class T, class... Additional>
    class JifyMapper
    {
        public:
            /**
             * @brief Method corresponds to the Cpp-Type of T.
             *
             * @return The Cpp datatype of T as a string.
             */
            static const std::string CType()
            {
                // TODO ensure that the return value is being demangled properly...
                std::string ctype = typeid(T).name();
                ctype = utils::replaceAll(ctype, R"(class |struct )", "");
                return ctype;
            }

            /**
             * @brief The JNI-Type of T (e.g.: std::string -> jstring).
             *
             * @return The JNI datatype of T as a string.
             */
            static const std::string JniType() { throw std::runtime_error("JNI type for: '" + CType() + "' is unknown"); }

            /**
             * @brief The Java-Type of T (e.g.: std::string -> java.lang.String).
             *
             * @return The Java datatype of T as a string.
             */
            static const std::string JavaType() { throw std::runtime_error("Java type for: '" + CType() + "' is unknown"); }

            /**
             * @brief The boxed Java-Type of T (e.g.: int -> Integer).JifyMapper
             *
             * @return The boxed Java datatype of T as a string.
             */
            static const std::string BoxedJavaType() { return JavaType(); }

            /**
             * @brief The code conversion of Java -> JNI -> C++.
             *
             * @param paramName The name of the jni parameter to be converted.
             * @param identifier An Identifier in order to enable more complex mapping without generating duplicate names.
             */
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id)
            {
                return JIFY_RAW(TODO map this properly);
            }

            /**
             * @brief The code conversion of C++ -> JNI -> JAVA.
             *
             * @param functionCall The native function-call returning the C++ type.
             */
            static const std::string Out(const std::string& functionCall) { return JIFY_RAW(TODO map this properly); }
    };

}  // namespace cppJify::mapper