#pragma once

#include <vector>
#include <string>

//将帧动画图片按顺序命名后直接用TexturePacker打包，然后用这个类加载.plist文件就可以把动画加载到缓存中
//两个参数的加载模式，每个plist文件只能包含一个帧动画序列，动画名称由自己通过参数设定
//一个参数的加载模式，每个plist可包含多个帧动画序列，动画名称自动设定
//
//帧动画图片命名规则：
//两参数模式：xxxxx + “_” + “序列号” + “.后缀”(如：frame_01.png)
//一参数模式：“动画名称” + “_” + “序列号” + “.后缀”(如：animationName_01.png)
//
//注意：这两种模式的“序列号”都应该是1(帧数小于10)或01(帧数小于100)或001(帧数小于1000)的形式
//因为TexturePacker暂时还不支持自然数排序方式，打包时帧动画序列顺序会出错
//比如（1、2、3、4、5、6、7、8、9、10）会排列成（2、3、4、5、6、7、8、9、10、1）
//所以最好(也可以不必，代码里已经处理了)是（01、02、03、04、05、06、07、08、09、10）的形式


class CBAnimationCacheLoder
{
public:

	static CBAnimationCacheLoder* sharedCacheLoder(void);

	void LoadAnimationCacheWithFile(
		const char* plist,
		const char* keyName);

	void unLoadAnimationCacheWithFile(
		const char* plist,
		const char* keyName);

	void LoadAnimationCacheWithFile(const char* plist);

	void unLoadAnimationCacheWithFile(const char* plist);

private:

	void qSortAnimationFrame(std::string *p, int l, int r);

private:

	CBAnimationCacheLoder();

	virtual ~CBAnimationCacheLoder();

	static CBAnimationCacheLoder* m_pInstance;
};
