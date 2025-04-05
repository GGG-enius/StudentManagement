#include "Management.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
using namespace std;
Management::Management()
{
	readFile("./image/student.txt");
	::loadimage(&m_bk, "./image/stubk.jpg", Window::width(), Window::height());
	//主界面初始化按钮
	menu_btns.push_back(new PushButton("查看所有学生证信息"));
	menu_btns.push_back(new PushButton("管理学生证信息"));
	menu_btns.push_back(new PushButton("查询学生证信息"));
	menu_btns.push_back(new PushButton("统计学生证信息"));
	menu_btns.push_back(new PushButton("退出系统"));

	//管理子菜单按钮初始化
	manage_btns.push_back(new PushButton("录入学生证信息"));
	manage_btns.push_back(new PushButton("删除学生证信息"));
	manage_btns.push_back(new PushButton("修改学生证信息"));

	//查询子菜单按钮初始化
	search_btns.push_back(new PushButton("查询单个学生的信息"));
	search_btns.push_back(new PushButton("查询班级全部学生的信息"));

	//统计子菜单按钮初始化
	count_btns.push_back(new PushButton("统计某学院人数"));
	count_btns.push_back(new PushButton("统计某专业人数"));
	count_btns.push_back(new PushButton("统计某班级人数"));
	count_btns.push_back(new PushButton("统计某年级人数"));

	isProcessed = false;//按钮处理状态初始化

	//返回键
	m_backMenuBtn = new PushButton("返回主菜单");
	m_backManageBtn = new PushButton("返回信息管理菜单");

	//陈列主菜单按钮
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		//按钮放到窗口中间
		menu_btns[i]->move(bx, by);
	}
	//陈列管理子菜单按钮
	for (int i = 0; i < manage_btns.size(); i++) {
		manage_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - manage_btns[i]->width()) / 2;
		int vspace = (Window::height() - manage_btns.size() * manage_btns[i]->height()) / 2;
		int by = vspace + i * manage_btns[i]->height();
		manage_btns[i]->move(bx, by+100);
	}
	m_addBtn = new PushButton("录入", 900, 260, 80, 30);//录入学生的按钮
	m_addEdit = new LineEdit(100, 260, 750, 30);
	m_addEdit->setTitle("请输入学生信息");
	m_addEdit->setHitText("格式:\n <姓名 性别 学号 入学时间 学制 身份证 学院 专业 班级>");
	//陈列查询子菜单按钮
	for (int i = 0; i < search_btns.size(); i++) {
		search_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - search_btns[i]->width()) / 2;
		int vspace = (Window::height() - search_btns.size() * search_btns[i]->height()) / 2;
		int by = vspace + i * search_btns[i]->height();
		search_btns[i]->move(bx, by+100);
	}
	
	//陈列统计子菜单按钮
	for (int i = 0; i < count_btns.size(); i++) {
		count_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - count_btns[i]->width()) / 2;
		int vspace = (Window::height() - count_btns.size() * count_btns[i]->height()) / 2;
		int by = vspace + i * count_btns[i]->height();
		count_btns[i]->move(bx, by-100);
	}

	//初始化查看学生的表格
	m_showTable = new Table;//new的对象在堆上面，构造函数的在栈内存上 离开作用域后自动释放
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	m_showTable->move((Window::width()-m_showTable->width())/2, 100);
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
	//m_backBtnState = 0;
}
void Management::run()
{
	//获取menu的返回值
	m_currentOp = Menu;
	Window::beginDraw();//绘制的图形不会直接显示在屏幕上，而是存入到这个函数里面去
	while (true)
	{
		Window::clear();
		drawBackGround();
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();//窗口捕获消息向下分发
			switch (m_msg.message)
			{
			case WM_KEYDOWN://如果有按键按下
				if (Window::getMsg().vkcode == VK_ESCAPE)
					//按ESC退出，返回menu界面
				{
					m_currentOp = Menu;
				}
				break;
			default: //鼠标操作
				eventLoop();//系统检测到事件（如鼠标），直接向下分发事件
				break;
			}
		}
		switch (m_currentOp)
		{
		case Menu:
			m_currentOp = menu();//op只有调用menu()才会变
			break;
		case Management::Display:
			display();
			break;
		case Management::Manage:
			manage();
			break;
		case Management::Search:
			search();
			break;
		case Management::Count:
			count();
			break;
		case Management::Exit://当op也就是i为4时进入
			saveFile("./image/test.txt");
			exit(0);
			break;
		default:
			break;
		}
		Window::flushDraw();
	}
	Window::endDraw();
}

int Management::menu()
{
	drawTile();
	//按钮逻辑
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->show();//只有在op为Menu时，才陈列按钮
		menu_btns[i]->eventLoop(m_msg);
		if (menu_btns[i]->isClicked())
		{
			return i;//返回按钮对应的操作的枚举值给op，进入switch开始操作
		}
	}
	return Menu;//若没有被点击，则一直停留在Menu
}

void Management::display()
{
	m_showTable->show();
	//cout << "display" << endl;
	//设置返回按钮
	displayBackMenuBtn();
}


void Management::manage()
{
	const char* tip;
	switch (m_manageState) {
	case Manage_Main: // 管理主菜单
		drawTile();
		// 显示管理子菜单按钮
		for (auto& btn : manage_btns) {
			btn->show();
			btn->eventLoop(m_msg);

			if (btn->isClicked() && btn->getText() == "录入学生证信息") {
				m_manageState = Manage_Add; // 切换到录入状态
			}
			else if (btn->isClicked() && btn->getText() == "删除学生证信息") {
				m_manageState = Manage_Delete;
				// 执行删除操作
				std::cout << "进入删除界面" << std::endl;
			}
			else if (btn->isClicked() && btn->getText() == "修改学生证信息") {
				m_manageState = Manage_Modify;
				// 执行修改操作
				std::cout << "进入修改界面" << std::endl;
			}
		}
		// 返回主菜单按钮
		displayBackMenuBtn();
		break;

	case Manage_Add: // 录入信息界面
		LOGFONT originalFont;
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);
		
		// 显示提示信息
		tip = "请输入学生信息<姓名 性别 学号 入学时间 学制 身份证 学院 专业 班级>:";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip))/2, 150, tip);
		// 返回管理菜单按钮
		settextstyle(&originalFont); // 恢复原字体
		m_addBtn->show();
		m_addBtn->eventLoop(m_msg);
		m_addEdit->show();
		m_addEdit->eventLoop(m_msg);
		// 检测按钮点击并确保仅触发一次
		if (m_addBtn->isClicked()) {
			if (!isProcessed) {
				std::cout << m_addEdit->text() << std::endl;
				isProcessed = true; // 标记已处理
			}
		}
		else {
			isProcessed = false; // 按钮未点击时重置状态
		}
		displayBackBtn(1);
		break;

	case Manage_Delete://删除信息界面
		// 显示提示信息
		tip = "请输入要删除学生的学号：";
		outtextxy(100, 100, tip);
		// 返回管理菜单按钮
		displayBackBtn(1);
		break;
	case Manage_Modify://修改界面信息
		// 显示提示信息
		tip = "请输入要修改学生的学号：";
		outtextxy(100, 100, tip);
		// 返回管理菜单按钮
		displayBackBtn(1);
		break;
	}
}

void Management::search()
{
	drawTile();
	displayBackMenuBtn();

	//显示查询子菜单按钮
	for (auto& btn : search_btns)
	{
		btn->show();
		btn->eventLoop(m_msg);
	}

}

void Management::count()
{
	drawTile();
	displayBackMenuBtn();
	//显示统计子菜单按钮
	for (auto& btn : count_btns)
	{
		btn->show();
		btn->eventLoop(m_msg);
	}
}

void Management::drawBackGround()
{
	::putimage(0, 0, &m_bk);
}

void Management::drawTile()
{
	LOGFONT originalFont;
	gettextstyle(&originalFont); // 保存原字体
	setbkmode(TRANSPARENT);

	std::string title;

	if (m_currentOp == Menu)
	{
		settextstyle(50, 0, "黑体");
		title = "学生证信息管理系统";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 120, title.c_str());
	}
	else if (m_currentOp == Manage)
	{
		settextstyle(50, 0, "幼圆");
		title = "信息管理";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 200, title.c_str());
	}
	else if (m_currentOp == Search)
	{
		settextstyle(50, 0, "幼圆");
		title = "信息查询";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 300, title.c_str());
	}
	else if (m_currentOp == Count)
	{
		settextstyle(50, 0, "幼圆");
		title = "信息统计";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 70, title.c_str());
	}

	
	settextstyle(&originalFont); // 恢复原字体
}


void Management::displayBackMenuBtn()
{
	//设置返回按钮
	m_backMenuBtn->setFixedSized(100, 25);
	m_backMenuBtn->show();
	m_backMenuBtn->eventLoop(m_msg);//将事件分发到返回按钮
	if (m_backMenuBtn->isClicked())
	{
		m_currentOp = Menu;
	}
}

void Management::displayBackBtn(int btnState)
{
	if (btnState == 1)
	{
		//设置返回按钮
		m_backManageBtn->setFixedSized(200, 35);
		m_backManageBtn->show();
		m_backManageBtn->eventLoop(m_msg);//将事件分发到返回按钮
		if (m_backManageBtn->isClicked())
		{
			// 返回管理主界面
			m_manageState = Manage_Main;
		}
	}
}

void Management::eventLoop()
{
	m_showTable->eventLoop(m_msg);//把收到的事件消息m_msg传（分发）给表格组件
}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);

	if (!read.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}
	//读取表头
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;
	
	//读取数据
	while (!read.eof())
	{
		char data[1024] = {0};//定义顺便清空了内存
		read.getline(data, 1024);
		//跳过空行
		if (strlen(data) == 0)
		{
			break;
		}
		//格式化读取
		Student stu;//定义一个临时对象
		stringstream ss(data);
		//把数据以空格分隔流进stu的成员变量
		ss >> stu.name >> stu.sex >> stu.number >> stu.date >> stu.school_year >> stu.id >> stu.college >> stu.major >> stu.cla;
		vec_stu.push_back(stu);//stu存好文件中的数据后存入vec_stu
		//cout << stu.name + " " << stu.sex + " " << stu.number + " " << stu.date + " " << stu.school_year + " " << stu.id + " " << stu.college + " " <<stu.major + " " << stu.cla<< endl;
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);//写和创建 
	if (!write.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}
	//写表头
	m_header += "\n";//给表头添加一个换行
	write.write(m_header.c_str(), m_header.size());
	//写数据
	for (auto& val : vec_stu)
	{
		std::string info = val.formatInfo();
		write.write(info.c_str(), info.size());
	}
	write.close();
}
