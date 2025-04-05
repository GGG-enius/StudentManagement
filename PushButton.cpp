#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), m_text(text)//���ø���Ĺ��캯��            
{

}

void PushButton::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	//���ð�ť���ֵ���ɫ
	settextcolor(BLACK);
	//�����־�����ʾ�ڰ�ť�м�
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	//�����־�����ʾ�ڰ�ť�м�
	::outtextxy(tx, ty, m_text.c_str());//c_str()���ǽ�C++��stringת��ΪC���ַ�������
	//������û���ڰ�ť��
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
	m_msg = msg;//��ť����Ϣ�洢�ڰ�ť��m_msg��Ȼ��ʼ��isIn,isClicked��Щ����
	
}

bool PushButton::isIn()//���������жϵ��ǲ�����һ����������
{
	//msg_x��msg_y������������
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		return true;
	}
	return false;
}

bool PushButton::isClicked()
{
	if (isIn())//�������ڰ�ť�ϣ������ж��Ƿ���
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





