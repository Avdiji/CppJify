#pragma once

#include <jni.h>

#include <memory>
#include <string>
#include <type_traits>

namespace cppJify::helper {

	template <typename FunctionType>
	struct RemoveFirstArg;
	
	template <typename Ret, typename FirstArg, typename... Args>
	struct RemoveFirstArg<Ret(FirstArg, Args...)> {
		using type = Ret(Args...);  // Remove FirstArg from the function signature
	};

    ///////////////////////////////////////////////
    // Checker determines whether T is a unique_ptr
    template <typename T>
    struct is_unique_ptr : std::false_type {};
    template <typename T>
    struct is_unique_ptr<std::unique_ptr<T>> : std::true_type {};
    ///////////////////////////////////////////////

    // clang-format off
	template<class T> 
	class CppJifyPtrWrapper 
	{ 
		public: 
			explicit CppJifyPtrWrapper(T* instance, bool owns = false) { _raw = instance; _owns = owns;} 
			explicit CppJifyPtrWrapper(std::shared_ptr<T> instance, bool owns = false) { _shared = std::move(instance); _owns = owns; } 
			explicit CppJifyPtrWrapper(std::unique_ptr<T> instance, bool owns = false) { _unique = std::move(instance); _owns = owns; } 

			~CppJifyPtrWrapper() { if(_raw && _owns) delete _raw; } 

			operator std::shared_ptr<T>&() { 
				if(_shared) { return _shared; } 
				if(_raw && _owns) { 
					_shared = std::shared_ptr<T>(_raw); 
					_raw = nullptr; 
					return _shared; 
				} 
				if(_unique && _owns) { 
					_shared = std::move(_unique); 
					_unique = nullptr; 
					return _shared; 
				} 
				throw std::runtime_error("Object is in a illegal state, unable to transfer ownership to shared_ptr"); 
			} 

			operator std::unique_ptr<T>() { 
				if(_unique) { return std::move(_unique); } 
				if(_raw && _owns) { 
					_unique = std::unique_ptr<T>(_raw); 
					_raw = nullptr; 
					return std::move(_unique); 
				} 
				throw std::runtime_error("Object is in a illegal state, unable to transfer ownership to unique_ptr"); 
			} 

            operator std::unique_ptr<T>&() {
                if(_unique) { return _unique; }
                if(_raw && _owns) {
                    _unique = std::unique_ptr<T>(_raw);
                    _raw = nullptr;
                    return _unique;
                }
                throw std::runtime_error("Object is in a illegal state, unable to transfer ownership to unique_ptr"); 
            }

			T* get() { 
				if(_raw) return _raw; 
				if(_shared) return _shared.get(); 
				if(_unique) return _unique.get(); 
				throw std::runtime_error("No Instance is being persisted in this wrapper"); 
			} 

		private: 
			bool _owns; 
			T* _raw = nullptr; 
			std::shared_ptr<T> _shared = nullptr; 
			std::unique_ptr<T> _unique = nullptr; 
			std::weak_ptr<T> _weak; 
	};
    // clang-format on

    template <typename T>
    inline CppJifyPtrWrapper<T>* cppJifyObjectToPtr(JNIEnv* env, jobject obj) {
        jclass cls = env->GetObjectClass(obj);
        jmethodID mid = env->GetMethodID(cls, "getNativeHandle", "()J");
        return reinterpret_cast<CppJifyPtrWrapper<T>*>(env->CallLongMethod(obj, mid));
    }

    template <typename T>
    inline jobject ptrToCppJifyObject(JNIEnv* env, const std::string& classname, CppJifyPtrWrapper<T>* ptr) {
        jclass cls = env->FindClass(classname.c_str());
        jmethodID constructor = env->GetMethodID(cls, "<init>", "(J)V");
        return env->NewObject(cls, constructor, reinterpret_cast<jlong>(ptr));
    }
}  // namespace cppJify::helper