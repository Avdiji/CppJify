#pragma once

#include <jni.h>

#include <cppJify/CppJify.hpp>

// #include <cppJBind/JniBindConstants.hpp>
// #include <cppJbind/utils/StringUtils.hpp>

namespace cppJify::mapper {

    template <class T, class... Additional>
    class JifyDefaultMapper {
        public:
            static const bool isTemplatedMapper();

            static const std::string CType();
            static const std::string JniType();
            static const std::string JavaType();
            static const std::string BoxedType();

            static const std::string In(const size_t& p_argId, JNIEnv* env = nullptr);
            static const std::string Out(const std::string& p_func, JNIEnv* env = nullptr);
            static const std::string Deref(const size_t& p_argId, JNIEnv* env = nullptr);

            // static void templated(const CppJify::ClassBinder<T>& p_classBinder);
    }

}  // namespace cppJify::mapper

// namespace cppJBind::cppJMapper {

//     template <class... T>
//     struct JBindMapper {

//             /**
//              * Method creates a Destructor for T.
//              *
//              * By default it creates a destructor for every datatype.
//              * In order to 'deactivate' it for a specific type make this return an empty string.
//              *
//              * @return The destructor for type T.
//              */
//             static const std::string Deref(const size_t& p_paramId) {
//                 return JBIND_JNI_CODE_TRANSFORMER<T>(

//                     JBIND_RAW(

//                         \t $ctype * toDelete = reinterpret_cast<$ctype*>(JBIND_J_ARG); \n
//                         \t delete toDelete; \n

//                         ),
//                     p_paramId);
//             }

//             static const std::string templated() { return "default templated"; }
//     };

// }  // namespace cppJBind::cppJMapper