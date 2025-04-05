#pragma once
#include "BasicWidget.h"
#include "Configure.h"
class LineEdit:public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 150, int h = 30);
	void show() override;
	void eventLoop(const ExMessage& msg);//�¼�ѭ��

	bool isIn();//�ж�����Ƿ��ڵ�ǰ��ť��
	bool isClicked();//�ж�����Ƿ����˵�ǰ��ť

	inline void setTitle(const std::string& title) { m_title = title; }
	inline void setHitText(const std::string& text) { m_hitText = text; }
	//��������������Ϣ��ʾ����
	inline const std::string& text()const { return m_text; }
private:
	std::string m_text;
	std::string m_title;
	std::string m_hitText;
private:
	ExMessage m_msg;//�洢�����̵���������
	COLORREF cur_c = RGB(255, 255, 255);//��ǰ����ɫ
};

