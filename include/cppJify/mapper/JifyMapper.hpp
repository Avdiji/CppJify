#pragma once

#include <cppJify/utils/MacroUtils.hpp>
#include <cppJify/utils/StringUtils.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace cppJify::mapper {

    /**
     * All registered Custom-Java classes.
     */
    inline std::map<std::string, std::string> registeredClasses;

    /**
     * @brief Template for all typemapings. Use this class to define custom mappings.
     * @tparam T The datatype to be mapped.
     * @tparam Additional... Additional generic types in case of std::vector<U> (or any other templated datatype).
     */
    template <class T, class... Additional>
    class JifyMapper {
        public:
            /**
             * @brief Method corresponds to the Cpp-Type of T.
             *
             * @return The Cpp datatype of T as a string.
             */
            static const std::string CType() {
                // TODO make sure this is being demangled properly...
                std::string result = typeid(T).name();
                result = utils::replaceAll(result, "struct ", "");
                result = utils::replaceAll(result, "class ", "");

                return result;
            }

            /**
             * @brief The JNI-Type of T (e.g.: std::string -> jstring).
             *
             * @return The JNI datatype of T as a string.
             */
            static const std::string JniType() { return "jobject"; }

            /**
             * @brief The Java-Type of T (e.g.: std::string -> java.lang.String).
             *
             * @return The Java datatype of T as a string.
             */
            static const std::string JavaType() {
                const std::string cppType = CType();
                const std::string& registeredJType = registeredClasses[cppType];

                if (registeredJType.empty()) { throw std::runtime_error(cppType + " has not been mapped yet..."); }

                return registeredJType;
            }

            /**
             * @brief The code conversion of Java -> JNI -> C++.
             *
             * @param cVar The name of the c-variable to be initialized.
             * @param paramName The name of the jni parameter to be converted.
             * @param identifier An Identifier in order to enable more complex mapping without generating duplicate names.
             */
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(
                        \n\t\t{} {} = *(cppJify::helper::cppJifyObjectToPtr<{}>(env, {})->get());), CType(), cVar, CType(), jniVar);
            }

            /**
             * @brief The code conversion of C++ -> JNI -> JAVA.
             *
             * @param functionCall The native function-call returning the C++ type.
             */
            static const std::string Out(const std::string& functionCall) {
                // clang-format off
                const std::string fullJName = utils::replaceAll(JavaType(), ".", "/");

                return JIFY_FMT(
                    JIFY_RAW(
                        
                        {} *result = new {}({});
                        \n\t\tcppJify::helper::CppJifyPtrWrapper<{}>* resultWrapper = new cppJify::helper::CppJifyPtrWrapper<{}>(result, true);
                        \n\t\treturn cppJify::helper::ptrToCppJifyObject(env, "{}", resultWrapper);
                    ),
                    CType(), CType(), functionCall,
                    CType(), CType(),
                    fullJName
                );
                // clang-format on
            }
    };
}  // namespace cppJify::mapper