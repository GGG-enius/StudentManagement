#include "LineEdit.h"
#include <iostream>

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
	m_dialogShown = false;//新增标志位
}

void LineEdit::show()
{
	//std::cout << "editshow" << std::endl;
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	//设置输入框文字的颜色
	settextcolor(BLACK);

	//把文字居中显示在按钮中间
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	//把文字居中显示在按钮中间
	::outtextxy(m_x, ty, m_text.c_str());//c_str()就是将C++的string转化为C的字符串数组
	//点击自己弹出对话框
		/// 保证在一次鼠标点击事件中只弹出一次对话框
	if (isClicked() && !m_dialogShown) // 检查标志位
	{
		char buf[128];//对话框文字传入的缓冲区
		InputBox(buf, 128, m_hitText.data(), m_title.data());
		m_text = buf;
		m_dialogShown = true; // 设置标志位为已显示
	}

	if (m_msg.message == WM_LBUTTONUP) // 鼠标释放时重置标志位
	{
		m_dialogShown = false;
	}
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

bool LineEdit::textChanged()
{
	if (m_text.empty())//如果没有输入文本
	{
		return false;//没有改变
	}
	if (m_preText == m_text)
	{
		return false;//文本没有改变
	}
	m_preText = m_text;//保存上次的文本
	return true;//否则改变了
}
