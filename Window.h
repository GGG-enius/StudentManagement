#pragma once
#include"Configure.h"

class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const std::string& title);
	int exec();

	//封装难记的函数，给图形库的函数套个壳子
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//按键操作和鼠标操作                              //指针将消息返回到ExMessage结构体中
	inline static bool hasMsg() { return ::peekmessage(&m_msg, EM_MOUSE | EM_KEY); }//判断有没有消息
	inline static ExMessage& getMsg() { return m_msg; }//有消息就返回消息

private:
	HWND m_handle;//窗口句柄
	inline ExMessage static m_msg;//消息
};

