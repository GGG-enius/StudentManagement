#include "LineEdit.h"
#include <iostream>

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
	m_text = "hello world";
}

void LineEdit::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	//设置按钮文字的颜色
	settextcolor(BLACK);
	//把文字居中显示在按钮中间
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	//把文字居中显示在按钮中间
	::outtextxy(m_x, ty, m_text.c_str());//c_str()就是将C++的string转化为C的字符串数组
	//点击自己弹出对话框
	if (isClicked())
	{
		char buf[128];//对话框文字传入的缓冲区
		InputBox(buf, 128, m_hitText.data(), m_title.data());
		m_text = buf;
		m_msg.message = 0;
	}
}

void LineEdit::eventLoop(const ExMessage& msg)
{
	m_msg = msg;//按钮把消息存储在按钮的m_msg
}

bool LineEdit::isIn()
{
	//msg_x和msg_y是鼠标光标的坐标
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		return true;
	}
	return false;
}

bool LineEdit::isClicked()
{
	if (isIn())//如果鼠标在按钮上，才能判断是否点击
	{
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}
	}
	return false;
}
