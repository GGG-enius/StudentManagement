#include "Management.h"
#include "Window.h"
int main()
{
	Window w(1200, 750, EW_SHOWCONSOLE);
	w.setWindowTitle("ѧ��֤����ϵͳ");
	Management m;
	m.run();
	return w.exec();//������
}