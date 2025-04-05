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
    

    void eventLoop(const ExMessage& msg);//事件循环
    void setBackGroundColor(COLORREF c);
    void setHoverColor(COLORREF c);

    bool isIn();//判断鼠标是否在当前按钮上
    bool isClicked();//判断鼠标是否点击了当前按钮

    std::string getText();

private:
    std::string m_text;
    ExMessage m_msg;//存储鼠标键盘的输入数据

    COLORREF normal_c = RGB(245, 245, 245);//正常时
    COLORREF hover_c = RGB(159, 252, 253);//鼠标移动上去时
    COLORREF cur_c = RGB(245, 245, 245);//当前的颜色
};

