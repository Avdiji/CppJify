#pragma once

#include <string>

namespace cppJify::mapper {

    /**
     * @brief Template for all typemapings. Use this class to define custom mappings.
     * @tparam T The datatype to be mapped.
     * @tparam Additional... Additional generic types in case of std::vector<U> (or any other templated datatype).
     *
     * @author Fitor Avdiji
     */
    template <class T, class... Additional>
    class JifyMapper {
        public:
            /**
             * @brief Method corresponds to the Cpp-Type of T.
             *
             * @return The Cpp datatype of T as a string.
             */
            static const std::string CType() {}

            /**
             * @brief The JNI-Type of T (e.g.: std::string -> jstring). Default = long.
             *
             * @return The JNI datatype of T as a string.
             */
            static const std::string JniType(){return "jlong"}

            /**
             * @brief The Java-Type of T (e.g.: std::string -> java.lang.String).
             *
             * @return The Java datatype of T as a string.
             */
            static const std::string JavaType() {}

            /**
             * @brief The boxed Java-Type of T (e.g.: int -> Integer).JifyMapper
             *
             * @return The boxed Java datatype of T as a string.
             */
            static const std::string BoxedJavaType() {}
    };

}  // namespace cppJify::mapper