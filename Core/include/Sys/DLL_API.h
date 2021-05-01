
#ifdef _DLL_// defined(_DLL_)
	#ifdef _WIN32
		#define DLL_API		__declspec(dllexport)
	#else
		//#include <QtCore/qglobal.h>
		#define DLL_API		__attribute__ ((visibility("default")))//Q_DECL_EXPORT//__attribute__ ((dllexport)) //
	#endif
#else
	#ifdef _WIN32
        #define DLL_API		__declspec(dllimport)
	#else
		//#include <QtCore/qglobal.h>
		#define DLL_API		__attribute__ ((visibility("default")))//Q_DECL_IMPORT
		//#define DLL_API		__attribute__ ((dllimport)) //Q_DECL_IMPORT
	#endif
#endif

//template<bool Condition, typename T = void> struct enable_if{};
//template<typename T> struct enable_if<true, T>{	typedef T type;};
//
//template<class> struct is_function : std::false_type { };//https://en.cppreference.com/w/cpp/types/is_function
//template <class T> constexpr bool is_function_v = is_function<T>::value;
//
//class ProcPtr {
//public:
//	explicit ProcPtr(FARPROC ptr) : _ptr(ptr) {}
//
//	template <typename T, typename = enable_if<is_function_v<T>>> 
//	operator T *() const {
//		return reinterpret_cast<T *>(_ptr);
//	}
//
//private:
//	FARPROC _ptr;
//};
//
//class DllHelper {
//public:
//	explicit DllHelper(LPCTSTR filename) : _module(LoadLibrary(filename)) {}
//
//	~DllHelper() { FreeLibrary(_module); }
//
//	ProcPtr operator[](LPCSTR proc_name) const {
//		return ProcPtr(GetProcAddress(_module, proc_name));
//	}
//
//	static HMODULE _parent_module;
//
//private:
//	HMODULE _module;
//};
//struct ShellApi {
//	DllHelper _dll{ "Shell32.dll" };
//	decltype(ShellAboutA) *shellAbout = _dll["ShellAboutA"];
//};
//
//int main() {
//	ShellApi shellApi;
//	shellApi.shellAbout(NULL, "hello", "world", NULL);
//}

// for __stdcall(WINAPI) use macro #define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)  usage: int WINAPI Test(void){#pragma EXPORT	return 1;} + __declspec(dllexport) is not required