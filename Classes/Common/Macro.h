#pragma once


#ifndef SYNTHESIZE
#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: virtual varType get##funcName(void) const { return varName; }\
public: virtual void set##funcName(varType var){ varName = var; }
#endif

#ifndef SYNTHESIZE_READONLY
#define SYNTHESIZE_READONLY(varType, varName, funcName)\
protected: varType varName;\
public: virtual varType get##funcName(void) const { return varName; }
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	do { if(p) { delete (p); (p) = 0; } } while(0)
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	do { if(p) { delete[] (p); (p) = 0; } } while(0)
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	do { if(p) { (p)->release(); } } while(0)
#endif

#ifndef SAFE_RELEASE_NULL
#define SAFE_RELEASE_NULL(p)	do { if(p) { (p)->release(); (p) = 0; } } while(0)
#endif

#ifndef SAFE_RETAIN
#define SAFE_RETAIN(p)	do { if(p) { (p)->retain(); } } while(0)
#endif


#ifndef SINGLETON
#define SINGLETON(className, funcName)\
	public:\
	static className* funcName()\
	{\
		static className *pInstance = 0;\
		if (pInstance == 0)\
		{\
			pInstance = new className();\
		}\
		return pInstance;\
	}
#endif


#ifndef SINGLETON_CLEAR
#define SINGLETON_CLEAR(className, shareFuncName, clearFuncName)\
	private: static className* pInstance;\
	public:\
	static className* shareFuncName()\
	{\
		if (pInstance == 0)\
		{\
			pInstance = new className();\
		}\
		return pInstance;\
	}\
	static void clearFuncName()\
	{\
		if (pInstance)\
		{\
			delete pInstance;\
			pInstance = 0;\
		}\
	}
#endif
