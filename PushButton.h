#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Window.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text = "BUTTON", int x = 0, int y = 0, int w = 200, int h = 60);
    void show() override;
    

    void eventLoop(const ExMessage& msg);//�¼�ѭ��
    void setBackGroundColor(COLORREF c);
    void setHoverColor(COLORREF c);

    bool isIn();//�ж�����Ƿ��ڵ�ǰ��ť��
    bool isClicked();//�ж�����Ƿ����˵�ǰ��ť

    std::string getText();

private:
    std::string m_text;
    ExMessage m_msg;//�洢�����̵���������

    COLORREF normal_c = RGB(245, 245, 245);//����ʱ
    COLORREF hover_c = RGB(159, 252, 253);//����ƶ���ȥʱ
    COLORREF cur_c = RGB(245, 245, 245);//��ǰ����ɫ
};

