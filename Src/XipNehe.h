#ifdef WIN32
#ifdef  XIPNEHE_EXPORTS
#define XIPNEHE_API __declspec(dllexport)
#else
#define XIPNEHE_API __declspec(dllimport)
#endif
#else
// no export needed for non-Windows platforms       
#define XIPNEHE_API 
#endif