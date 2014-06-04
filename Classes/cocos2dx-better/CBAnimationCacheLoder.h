#pragma once

#include <vector>
#include <string>

//��֡����ͼƬ��˳��������ֱ����TexturePacker�����Ȼ������������.plist�ļ��Ϳ��԰Ѷ������ص�������
//���������ļ���ģʽ��ÿ��plist�ļ�ֻ�ܰ���һ��֡�������У������������Լ�ͨ�������趨
//һ�������ļ���ģʽ��ÿ��plist�ɰ������֡�������У����������Զ��趨
//
//֡����ͼƬ��������
//������ģʽ��xxxxx + ��_�� + �����кš� + ��.��׺��(�磺frame_01.png)
//һ����ģʽ�����������ơ� + ��_�� + �����кš� + ��.��׺��(�磺animationName_01.png)
//
//ע�⣺������ģʽ�ġ����кš���Ӧ����1(֡��С��10)��01(֡��С��100)��001(֡��С��1000)����ʽ
//��ΪTexturePacker��ʱ����֧����Ȼ������ʽ�����ʱ֡��������˳������
//���磨1��2��3��4��5��6��7��8��9��10�������гɣ�2��3��4��5��6��7��8��9��10��1��
//�������(Ҳ���Բ��أ��������Ѿ�������)�ǣ�01��02��03��04��05��06��07��08��09��10������ʽ


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
