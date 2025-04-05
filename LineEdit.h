#pragma once
#include "BasicWidget.h"
#include "Configure.h"
class LineEdit:public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 150, int h = 30);
	void show() override;
	void eventLoop(const ExMessage& msg);//事件循环

	bool isIn();//判断鼠标是否在当前按钮上
	bool isClicked();//判断鼠标是否点击了当前按钮

	inline void setTitle(const std::string& title) { m_title = title; }
	inline void setHitText(const std::string& text) { m_hitText = text; }
	//把输入框输入的信息显示出来
	inline const std::string& text()const { return m_text; }
private:
	std::string m_text;
	std::string m_title;
	std::string m_hitText;
private:
	ExMessage m_msg;//存储鼠标键盘的输入数据
	COLORREF cur_c = RGB(255, 255, 255);//当前的颜色
};

