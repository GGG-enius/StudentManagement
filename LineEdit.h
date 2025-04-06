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
	inline void setHitText(const std::string& hitText) { m_hitText = hitText; }
	inline void setText(const std::string& text) { m_text = text; }//设置输入框的文本
	//把输入框输入的信息显示出来
	inline const std::string& text()const { return m_text; }
	void clear() { m_text.clear(); }//添加成功后 调用清空m_text,即可再次添加

	bool textChanged();

private:
	std::string m_preText;//上次输入的文本
	std::string m_text;
	std::string m_title;
	std::string m_hitText;

	bool m_dialogShown; // 标记是否正在处理输入
private:
	ExMessage m_msg;//存储鼠标键盘的输入数据
	COLORREF cur_c = RGB(255, 255, 255);//当前的颜色
	COLORREF normal_c = RGB(255, 255, 255);//正常时
	COLORREF hover_c = RGB(255, 253, 85);//鼠标移动上去时
};

