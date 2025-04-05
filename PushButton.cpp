#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), m_text(text)//调用父类的构造函数            
{

}

void PushButton::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	//设置按钮文字的颜色
	settextcolor(BLACK);
	//把文字居中显示在按钮中间
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	//把文字居中显示在按钮中间
	::outtextxy(tx, ty, m_text.c_str());//c_str()就是将C++的string转化为C的字符串数组
	//如果鼠标没有在按钮上
	if (!isIn())
	{
		cur_c = normal_c;
	}
	else
	{
		cur_c = hover_c;
	}
}

void PushButton::eventLoop(const ExMessage& msg)
{
	m_msg = msg;//按钮把消息存储在按钮的m_msg，然后开始做isIn,isClicked这些处理
	
}

bool PushButton::isIn()//本质上是判断点是不是在一个矩形里面
{
	//msg_x和msg_y是鼠标光标的坐标
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		return true;
	}
	return false;
}

bool PushButton::isClicked()
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

std::string PushButton::getText()
{
	return m_text;
}

void PushButton::setBackGroundColor(COLORREF c)
{
	normal_c = c;
}

void PushButton::setHoverColor(COLORREF c)
{
	hover_c = c;
}





