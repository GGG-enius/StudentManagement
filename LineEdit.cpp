#include "LineEdit.h"
#include <iostream>

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
	m_dialogShown = false;//������־λ
}

void LineEdit::show()
{
	//std::cout << "editshow" << std::endl;
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	//������������ֵ���ɫ
	settextcolor(BLACK);

	//�����־�����ʾ�ڰ�ť�м�
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	//�����־�����ʾ�ڰ�ť�м�
	::outtextxy(m_x, ty, m_text.c_str());//c_str()���ǽ�C++��stringת��ΪC���ַ�������
	//����Լ������Ի���
		/// ��֤��һ��������¼���ֻ����һ�ζԻ���
	if (isClicked() && !m_dialogShown) // ����־λ
	{
		char buf[128];//�Ի������ִ���Ļ�����
		InputBox(buf, 128, m_hitText.data(), m_title.data());
		m_text = buf;
		m_dialogShown = true; // ���ñ�־λΪ����ʾ
	}

	if (m_msg.message == WM_LBUTTONUP) // ����ͷ�ʱ���ñ�־λ
	{
		m_dialogShown = false;
	}
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

void LineEdit::eventLoop(const ExMessage& msg)
{
	m_msg = msg;//��ť����Ϣ�洢�ڰ�ť��m_msg
}

bool LineEdit::isIn()
{
	//msg_x��msg_y������������
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		return true;
	}
	return false;
}

bool LineEdit::isClicked()
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

bool LineEdit::textChanged()
{
	if (m_text.empty())//���û�������ı�
	{
		return false;//û�иı�
	}
	if (m_preText == m_text)
	{
		return false;//�ı�û�иı�
	}
	m_preText = m_text;//�����ϴε��ı�
	return true;//����ı���
}
