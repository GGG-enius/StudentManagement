#pragma once
#include"Configure.h"

class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const std::string& title);
	int exec();

	//��װ�Ѽǵĺ�������ͼ�ο�ĺ����׸�����
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//����������������                              //ָ�뽫��Ϣ���ص�ExMessage�ṹ����
	inline static bool hasMsg() { return ::peekmessage(&m_msg, EM_MOUSE | EM_KEY); }//�ж���û����Ϣ
	inline static ExMessage& getMsg() { return m_msg; }//����Ϣ�ͷ�����Ϣ

private:
	HWND m_handle;//���ھ��
	inline ExMessage static m_msg;//��Ϣ
};

