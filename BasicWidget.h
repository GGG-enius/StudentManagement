#pragma once
//所有控件的抽象基类
//按钮类，表格类
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);//类的构造函数
	virtual ~BasicWidget() {};
	int width();//获取w
	int height();//获取h
	void setFixedSized(int w, int h);

	int x();//获取x
	int y();//获取y
	void move(int x, int y);

	virtual void show() = 0;//纯虚函数，只能被子类重写实现，该类不能实例化对象，相当于抽象类,相当于抽象类

protected://用于继承的成员变量
	int m_x;
	int m_y;
	int m_w;
	int m_h;
};

