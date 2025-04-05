#pragma once
//���пؼ��ĳ������
//��ť�࣬�����
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);//��Ĺ��캯��
	virtual ~BasicWidget() {};
	int width();//��ȡw
	int height();//��ȡh
	void setFixedSized(int w, int h);

	int x();//��ȡx
	int y();//��ȡy
	void move(int x, int y);

	virtual void show() = 0;//���麯����ֻ�ܱ�������дʵ�֣����಻��ʵ���������൱�ڳ�����,�൱�ڳ�����

protected://���ڼ̳еĳ�Ա����
	int m_x;
	int m_y;
	int m_w;
	int m_h;
};

