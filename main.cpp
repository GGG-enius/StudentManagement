#include "Management.h"
#include "Window.h"
int main()
{
	Window w(1200, 750, EW_SHOWCONSOLE);
	w.setWindowTitle("学生证管理系统");
	Management m;
	m.run();
	return w.exec();//防闪退
}