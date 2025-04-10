#include "Management.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include<algorithm>

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
	m_backSearchBtn = new PushButton("返回信息查询菜单");
	m_backCountBtn = new PushButton("返回信息统计菜单");

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
		manage_btns[i]->move(bx, by+50);
	}
	//录入学生界面的按钮和输入框
	m_addBtn = new PushButton("录入", 900, 260, 80, 30);//录入学生的按钮
	m_addEdit = new LineEdit(100, 260, 750, 30);
	m_addEdit->setTitle("录入学生");
	m_addEdit->setHitText("格式:\n <姓名 性别 学号 入学时间 学制 身份证 学院 专业 班级>");

	//删除学生界面的按钮和输入框
	m_delBtn = new PushButton("删除", 650, 260, 80, 30);
	m_delEdit = new LineEdit(440, 260, 200, 30);
	m_delEdit->setTitle("删除学生");
	m_delEdit->setHitText("请输入要删除学生的学号:");
	m_delTable = new Table;//删除学生的表格
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x()-425, m_delEdit->y() + 100);

	//修改学生界面的输入框
	m_modifyBtn = new PushButton("修改", 650, 260, 80, 30);//修改学生的按钮
	m_modifyEdit = new LineEdit(440, 260, 200, 30);
	//m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);//居中显示
	m_modifyEdit->setTitle("修改学生");
	m_modifyEdit->setHitText("请输入要修改学生的学号");
	m_modifyIt = vec_stu.end();
	//修改学生信息的输入框的对象创建
	for (int i = 0; i < 9; i++)
	{
		m_stuEdits.emplace_back(new LineEdit(0, 0, 130, 30));
		if (i == 0)//姓名
		{
			m_stuEdits[i]->move(20 + i * 140, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		if (i == 1)//性别
		{
			m_stuEdits[i]->move(20+60, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		if (i == 2)//学号
		{
			m_stuEdits[i]->move(80 + 60, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(100, 30);
		}
		if (i == 3)//入学时间
		{
			m_stuEdits[i]->move(140 + 110, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(80, 30);
		}
		if (i == 4)//学制
		{
			m_stuEdits[i]->move(250 + 90, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		if (i == 5)//身份证
		{
			m_stuEdits[i]->move(340 + 60, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(150, 30);
		}
		if (i == 6)//学院
		{
			m_stuEdits[i]->move(400 + 160, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(130, 30);
		}
		if (i == 7)//专业
		{
			m_stuEdits[i]->move(560 + 140, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(100, 30);
		}
		if (i == 8)//班级
		{
			m_stuEdits[i]->move(700 + 110, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		
	}

	//陈列查询子菜单按钮
	for (int i = 0; i < search_btns.size(); i++) {
		search_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - search_btns[i]->width()) / 2;
		int vspace = (Window::height() - search_btns.size() * search_btns[i]->height()) / 2;
		int by = vspace + i * search_btns[i]->height();
		search_btns[i]->move(bx, by+100);
	}
	m_searchEdit = new LineEdit(440, 260, 200, 30);//查询输入框初始化
	m_searchEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);//居中显示
	m_searchEdit->setTitle("查询学生");
	m_searchEdit->setHitText("请输入要查询学生的学号或姓名");
	m_searchTable = new Table;//查询学生的表格
	m_searchTable->setHeader(m_header);
	m_searchTable->move(m_delEdit->x() - 425, m_delEdit->y() + 100);
	
	m_searchClassEdit = new LineEdit(440, 260, 300, 30);//查询班级输入框初始化
	m_searchClassEdit->move((Window::width() - m_searchClassEdit->width()) / 2, 260);//居中显示
	m_searchEdit->setTitle("查询某班级的所有学生");
	m_searchEdit->setHitText("请输入要查询的年级 专业 班级");

	//陈列统计子菜单按钮
	for (int i = 0; i < count_btns.size(); i++) {
		count_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - count_btns[i]->width()) / 2;
		int vspace = (Window::height() - count_btns.size() * count_btns[i]->height()) / 2;
		int by = vspace + i * count_btns[i]->height();
		count_btns[i]->move(bx, by-100);
	}
	m_countCollegeEdit = new LineEdit(440, 150, 200, 30);//统计专业输入框初始化
	m_countCollegeEdit->setTitle("统计学院数据");
	m_countCollegeEdit->setHitText("请输入要统计的学院");
	m_countMajorEdit = new LineEdit(440, 150, 200, 30);//统计专业输入框初始化
	m_countMajorEdit->setTitle("统计专业数据");
	m_countMajorEdit->setHitText("请输入要统计的专业");
	m_countClassEdit = new LineEdit(440, 150, 200, 30);//统计班级输入框初始化
	m_countClassEdit->setTitle("统计班级数据");
	m_countClassEdit->setHitText("请输入要统计的班级");
	m_countGradeEdit = new LineEdit(440, 150, 200, 30);//统计年级输入框初始化
	m_countGradeEdit->setTitle("统计年级数据");
	m_countGradeEdit->setHitText("请输入要统计的年级");
	m_countBtn = new PushButton("统计", 650, 150, 80, 30);//统计按钮初始化

	//初始化查看学生的表格
	m_showTable = new Table;//new的对象在堆上面，构造函数的在栈内存上 离开作用域后自动释放
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	m_showTable->move((Window::width()-m_showTable->width())/2, 100);
	updateTable();
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
	const char* example;
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
			}
			else if (btn->isClicked() && btn->getText() == "修改学生证信息") {
				m_manageState = Manage_Modify;
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
		example = "例：张三 男 202232310229 2022-09-01 4年 440320200312190344 生命科学学院 生命科学 2班";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip))/2, 150, tip);
		settextstyle(&originalFont); // 恢复原字体
		settextstyle(18, 0, "幼圆");
		outtextxy((Window::width() - textwidth(tip)) / 2 - 100, 200, example);
		settextstyle(&originalFont); // 恢复原字体
		m_addBtn->show();
		m_addEdit->show();

		// 检测按钮点击并确保仅触发一次
		if (m_addBtn->isClicked()&&!(m_addEdit->text().empty())) {
			if (!isProcessed) {
				vec_stu.push_back(Student::fromString(m_addEdit->text()));//存到stu的存储数组
				auto str = m_addEdit->text();
				std::replace(str.begin(), str.end(), ' ', '\t');//把输入的空格替换成'\t'，便于分割
				m_showTable->insertData(str); //存到表格
				m_addEdit->clear();
				isProcessed = true; // 标记已处理
				m_manageState = Manage_Main;
			}
		}
		else {
			isProcessed = false; // 按钮未点击时重置状态
		}
		if (m_backManageBtn->isClicked())
		{
			m_addEdit->clear();
		}
		// 返回管理菜单按钮
		displayBackBtn(1);
		break;

	case Manage_Delete://删除信息界面
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		// 显示提示信息
		tip = "请输入要删除学生的学号：";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // 恢复原字体

		m_delBtn->show();
		m_delEdit->show();

		// 输入框的实时查找逻辑（仅在未点击删除按钮时执行）
		if (!m_delEdit->text().empty() && !m_delBtn->isClicked()) {
			m_delTable->clear(); // 清空旧数据
			auto& str = m_delEdit->text();
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
				return stu.number == str;
				});

			if (it == vec_stu.end()) {
				// 显示未找到
				settextcolor(RED);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("没有找到学号为" + str + "的学生！").data());
			}
			else {
				// 显示找到
				m_delTable->insertData(it->formatInfo());
				settextcolor(GREEN);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("找到学号为" + str + "的学生！").data());
				settextcolor(BLACK);
				m_delTable->setShowPageBtn(false);//隐藏分页按钮
				m_delTable->show();
			}
		}
		// 删除按钮逻辑
		if (m_delBtn->isClicked()) {
			if (!m_delEdit->text().empty()) {
				auto& str = m_delEdit->text();
				auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
					return stu.number == str;
					});

				if (it != vec_stu.end()) { // 如果找到并删除了学生
					vec_stu.erase(it, vec_stu.end());
					updateTable();
					m_delEdit->clear();    // 清空输入框
					m_delTable->clear();   // 清空表格
				}
			}
			m_manageState = Manage_Main;
		}
		if (m_backManageBtn->isClicked())
		{
			m_delEdit->clear();
			m_delTable->clear();
		}
		// 返回管理菜单按钮
		displayBackBtn(1);
		break;
	case Manage_Modify://修改界面信息
		// 显示提示信息
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入要修改学生的学号：";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // 恢复原字体
		m_modifyBtn->show();
		m_modifyEdit->show();

		if (!m_modifyEdit->text().empty())
		{
			auto& str = m_modifyEdit->text();
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
				return stu.number == str;
				});

			if (it == vec_stu.end()) {
				// 显示未找到
				m_modifyIt = vec_stu.end();
				isFind = false;
				settextcolor(RED);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("没有找到学号为" + str + "的学生！").data());
			}
			else//找到学生
			{
				//展示修改学生的输入框
				for (auto& e : m_stuEdits)
				{
					e->show();
				}
				//设置修改框的文本
				if(isFirst)
				{
					m_stuEdits[0]->setText(it->name);
					m_stuEdits[1]->setText(it->sex);
					m_stuEdits[2]->setText(it->number);
					m_stuEdits[3]->setText(it->date);
					m_stuEdits[4]->setText(it->school_year);
					m_stuEdits[5]->setText(it->id);
					m_stuEdits[6]->setText(it->college);
					m_stuEdits[7]->setText(it->major);
					m_stuEdits[8]->setText(it->cla);
					isFirst = false;
				}
				isFind = true;

				m_modifyIt = it;
			}	
		}
		if (isFind && m_modifyIt != vec_stu.end())
		{
			for (int i = 0; i < m_stuEdits.size(); i++)
			{
				//把找到的要修改的学生信息更新为最新修改值
				m_modifyIt->name = m_stuEdits[0]->text();
				m_modifyIt->sex = m_stuEdits[1]->text();
				m_modifyIt->number = m_stuEdits[2]->text();
				m_modifyIt->date = m_stuEdits[3]->text();
				m_modifyIt->school_year = m_stuEdits[4]->text();
				m_modifyIt->id = m_stuEdits[5]->text();
				m_modifyIt->college = m_stuEdits[6]->text();
				m_modifyIt->major = m_stuEdits[7]->text();
				m_modifyIt->cla = m_stuEdits[8]->text();
				updateTable();
			}
			if (m_modifyBtn->isClicked())
			{
				isFirst = true;
				isFind = false;
				m_modifyIt = vec_stu.end();
				m_modifyEdit->clear();
				for (auto& edit : m_stuEdits) {
					edit->clear();
				}
				m_manageState = Manage_Main;
			}
		}
		// 返回管理菜单按钮
		displayBackBtn(1);
		break;
	}
}

void Management::search()
{
	const char* tip;
	const char* example;

	switch (m_searchState)
	{
	case Search_Main: //查询主菜单
		drawTile();
		//显示查询子菜单按钮
		for (auto& btn : search_btns)
		{
			btn->show();
			btn->eventLoop(m_msg);

			if (btn->isClicked() && btn->getText() == "查询单个学生的信息") {
				m_searchState = Search_stu; // 切换到查询单个学生的状态
			}
			else if (btn->isClicked() && btn->getText() == "查询班级全部学生的信息") {
				m_searchState = Search_class;//切换到查询班级学生的状态
			}
		}
		// 返回主菜单按钮
		displayBackMenuBtn();
		break;

	case Search_stu:
		m_searchTable->clear();

		LOGFONT originalFont;
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入要查询学生的关键词（例如：学号 姓名或性别等）";
		example = "空格分隔多个条件，如：张 男";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // 恢复原字体
		settextstyle(18, 0, "幼圆");
		outtextxy((Window::width() - textwidth(tip)) / 2+100, 200, example);
		settextstyle(&originalFont); // 恢复原字体

		m_searchEdit->show();

		//没找到的逻辑
		if (!m_searchEdit->text().empty())
		{
			// 清空旧结果
			m_searchTable->clear();

			// 分割查询条件,存入keywords
			std::vector<std::string> keywords;
			std::istringstream iss(m_searchEdit->text());
			std::string keyword;
			while (iss >> keyword) {
				keywords.push_back(keyword);
			}
			// 查找匹配的学生
			std::vector<Student> results;
			for (const auto& stu : vec_stu) {
				bool matchAll = true;
				for (const auto& kw : keywords) {
					bool found =
						stu.name.find(kw) != std::string::npos ||
						stu.sex.find(kw) != std::string::npos ||
						stu.number.find(kw) != std::string::npos ||
						stu.date.find(kw) != std::string::npos ||
						stu.school_year.find(kw) != std::string::npos ||
						stu.id.find(kw) != std::string::npos ||
						stu.college.find(kw) != std::string::npos ||
						stu.major.find(kw) != std::string::npos ||
						stu.cla.find(kw) != std::string::npos;

					if (!found) {
						matchAll = false;
						break;
					}
				}
				if (matchAll) {
					results.push_back(stu);
				}
			}
			// 显示结果
			if (results.empty()) {
				settextcolor(RED);
				outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "没有找到匹配的学生！");
			}
			else {
				settextcolor(BLACK);
				int yPos = m_searchEdit->y() + 50;
				for (size_t i = 0; i < results.size(); i++)
				{
					outtextxy(m_searchEdit->x() - 200, m_searchEdit->y() + 50 + i * 20, results[i].formatInfo2().data());
				}
			}
		}
		if (m_backSearchBtn->isClicked())
		{
			m_searchEdit->clear();
			m_searchTable->clear();
		}
		displayBackBtn(2);
		break;
	case Search_class:
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入要查询的年级专业班级：";
		example = "格式：年级 专业 班级";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // 恢复原字体
		settextstyle(18, 0, "幼圆");
		outtextxy((Window::width() - textwidth(tip)) / 2, 200, example);
		settextstyle(&originalFont); // 恢复原字体

		m_searchEdit->show();
		std::string input = m_searchEdit->text();

		if (!input.empty())
		{
			std::istringstream iss(input);
			std::string grade, major, cla;
			iss >> grade >> major >> cla;
			if (grade.empty() || major.empty() || cla.empty()) {
				settextcolor(RED);
				outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "输入格式错误，请按格式输入！");
			}
			else
			{
				//查找符合条件的学生
				std::vector<Student> results;
				for (auto& stu : vec_stu)
				{
					std::string stuGrade = stu.date.substr(0, 4); // 从入学日期提取年级
					if (stuGrade == grade && stu.major == major && stu.cla == cla)
					{
						results.push_back(stu);
					}
				}
				//显示结果
				if (results.empty())
				{
					settextcolor(RED);
					outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "没有找到符合条件的学生！");
				}
				else
				{
					for (size_t i = 0; i < results.size(); i++)
					{
						outtextxy(m_searchEdit->x() - 200, m_searchEdit->y()+50 + i * 20, results[i].formatInfo2().data());
					}
					//for (auto& stu : results)
					//{
					//	m_searchTable->insertData(stu.formatInfo());
					//}
					//m_searchTable->setShowPageBtn(false);
					//m_searchTable->updatePage();//更新表格
					//m_searchTable->show();
				}
			}
		}
		if (m_backManageBtn->isClicked())
		{
			m_searchTable->clear();
			m_searchEdit->clear();
		}
		if (m_backSearchBtn->isClicked())
		{
			m_searchEdit->clear();
			m_searchTable->clear();
		}
		displayBackBtn(2);
		break;

	}
}

void Management::count()
{
	const char* tip;
	const char* example;
	switch (m_countState)
	{
	case Count_Main: // 统计主菜单
		drawTile();
		//显示统计子菜单按钮
		for (auto& btn : count_btns)
		{
			btn->show();
			btn->eventLoop(m_msg);

			if (btn->isClicked() && btn->getText() == "统计某学院人数") {
				m_countState = Count_college; // 切换到统计学院人数的状态
			}
			else if (btn->isClicked() && btn->getText() == "统计某专业人数") {
				m_countState = Count_major;//切换到统计专业人数的状态
			}
			else if (btn->isClicked() && btn->getText() == "统计某班级人数") {
				m_countState = Count_class;//切换到统计班级人数的状态
			}
			else if (btn->isClicked() && btn->getText() == "统计某年级人数") {
				m_countState = Count_grade;//切换到统计年级人数的状态
			}
		}
		displayBackMenuBtn();//返回主菜单按钮
		break;
	case Count_college://统计学院人数
		LOGFONT originalFont;
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入你要统计人数的学院：";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(&originalFont);// 恢复原字体

		m_countCollegeEdit->show();
		m_countBtn->show();

		if (m_countBtn->isClicked()&&!m_countCollegeEdit->text().empty())
		{
			m_countNum = 0;//学院人数初始化
			m_countBoys = 0;//男生人数初始化
			m_countGirls = 0;//女生人数初始化
			isPressed = true;
			//遍历学生数据
			for (auto& stu : vec_stu)
			{
				if (stu.college == m_countCollegeEdit->text())
				{
					m_countNum++;//该学院人数加一
					if (stu.sex == "男")
						m_countBoys++;
					else if (stu.sex == "女")
						m_countGirls++;
				}
			}
		}
		//输出统计结果
		if (m_countNum == 0&&isPressed)//没找到
		{
			settextcolor(RED);
			outtextxy(m_countCollegeEdit->x(), m_countCollegeEdit->y() + 50, std::string("没有找到学院为" + m_countCollegeEdit->text() + "的学生！").data());
		}
		else if (m_countNum != 0 && isPressed)//找到
		{
			gettextstyle(&originalFont); // 保存原字体
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "黑体");
			std::string result = "该学院总人数:" + std::to_string(m_countNum) + "   " + "该学院男生人数:" + std::to_string(m_countBoys) + "   " + "该学院女生人数:" + std::to_string(m_countGirls);
			settextcolor(BLACK);
			outtextxy(m_countCollegeEdit->x() - 200, m_countCollegeEdit->y() + 50, result.data());
			settextstyle(&originalFont);// 恢复原字体
		}

		if (m_backCountBtn->isClicked())
		{
			m_countCollegeEdit->clear();
			isPressed = false;
		}
		displayBackBtn(3);
		break;
	case Count_major://统计专业人数
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入你要统计人数的专业：";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(&originalFont);// 恢复原字体

		m_countMajorEdit->show();
		m_countBtn->show();

		//统计专业人数
		if (m_countBtn->isClicked() && !m_countMajorEdit->text().empty())
		{
			m_countNum = 0;//专业人数初始化
			m_countBoys = 0;//男生人数初始化
			m_countGirls = 0;//女生人数初始化
			isPressed = true;
			//遍历学生数据
			for (auto& stu : vec_stu)
			{
				if (stu.major == m_countMajorEdit->text())
				{
					m_countNum++;//该专业人数加一
					if (stu.sex == "男")
						m_countBoys++;
					else if (stu.sex == "女")
						m_countGirls++;
				}
			}
		}
		//输出统计结果
		if (m_countNum == 0 && isPressed)//没找到
		{
			settextcolor(RED);
			outtextxy(m_countMajorEdit->x(), m_countMajorEdit->y() + 50, std::string("没有找到专业为" + m_countMajorEdit->text() + "的学生！").data());
		}
		else if (m_countNum != 0 && isPressed)//找到
		{
			std::string result = "该专业总人数:" + std::to_string(m_countNum) + "   " + "该专业男生人数:" + std::to_string(m_countBoys) + "   " + "该专业女生人数:" + std::to_string(m_countGirls);
			gettextstyle(&originalFont); // 保存原字体
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "黑体");
			settextcolor(BLACK);
			outtextxy(m_countMajorEdit->x() - 200, m_countMajorEdit->y() + 50, result.data());
			settextstyle(&originalFont);// 恢复原字体
		}

		if (m_backCountBtn->isClicked())
		{
			m_countMajorEdit->clear();
			isPressed = false;
		}
		displayBackBtn(3);
		break;
	case Count_class://统计班级人数
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入你要查看统计数据的年级专业班级：";
		example = "格式：年级 专业 班级";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(18, 0, "幼圆");
		outtextxy((Window::width() - textwidth(tip)) / 2, 100, example);
		settextstyle(&originalFont);// 恢复原字体

		m_countClassEdit->show();
		m_countBtn->show();

		//统计班级人数
		if (m_countBtn->isClicked() && !m_countClassEdit->text().empty())
		{
			m_countNum = 0;//班级人数初始化
			m_countBoys = 0;//男生人数初始化
			m_countGirls = 0;//女生人数初始化
			isPressed = true;
			//遍历学生数据
			std::string input = m_countClassEdit->text();
			std::istringstream iss(input);
			std::string grade, major, cla;
			iss >> grade >> major >> cla;
			if (grade.empty() || major.empty() || cla.empty()) {
				settextcolor(RED);
				outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "输入格式错误，请按格式输入！");
			}
			else
			{
				//查找符合条件的学生
				for (auto& stu : vec_stu)
				{
					std::string stuGrade = stu.date.substr(0, 4); // 从入学日期提取年级
					if (stuGrade == grade && stu.major == major && stu.cla == cla)
					{
						m_countNum++;
						if (stu.sex == "男")
						{
							m_countBoys++;
						}
						else if (stu.sex == "女")
						{
							m_countGirls++;
						}
					}
				}
			}

		}
		//输出统计结果
		if (m_countNum == 0 && isPressed)//没找到
		{
			settextcolor(RED);
			outtextxy(m_countClassEdit->x(), m_countClassEdit->y() + 50, std::string("没有找到班级为" + m_countClassEdit->text() + "的学生！").data());
		}
		else if (m_countNum != 0 && isPressed)//找到
		{
			std::string result = "该班级总人数:" + std::to_string(m_countNum) + "   " + "该班级男生人数:" + std::to_string(m_countBoys) + "   " + "该班级女生人数:" + std::to_string(m_countGirls);
			gettextstyle(&originalFont); // 保存原字体
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "黑体");
			settextcolor(BLACK);
			outtextxy(m_countClassEdit->x() - 200, m_countClassEdit->y() + 50, result.data());
			settextstyle(&originalFont);// 恢复原字体
		}

		if (m_backCountBtn->isClicked())
		{
			m_countClassEdit->clear();
			isPressed = false;
		}
		displayBackBtn(3);
		break;
	case Count_grade://统计年级人数
		gettextstyle(&originalFont); // 保存原字体
		setbkmode(TRANSPARENT);

		tip = "请输入你要查看统计数据的年级：";
		settextstyle(26, 0, "楷体");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(&originalFont);// 恢复原字体

		m_countGradeEdit->show();
		m_countBtn->show();

		//统计年级人数
		if (m_countBtn->isClicked() && !m_countGradeEdit->text().empty())
		{
			m_countNum = 0;//年级人数初始化
			m_countBoys = 0;//男生人数初始化
			m_countGirls = 0;//女生人数初始化
			isPressed = true;
			//遍历学生数据
			for (auto& stu : vec_stu)
			{
				std::string stuGrade = stu.date.substr(0, 4); // 从入学日期提取年级
				if (stuGrade == m_countGradeEdit->text())
				{
					m_countNum++;//该年级人数加一
					if (stu.sex == "男")
						m_countBoys++;
					else if (stu.sex == "女")
						m_countGirls++;
				}
			}
		}
		//输出统计结果
		if (m_countNum == 0 && isPressed)//没找到
		{
			settextcolor(RED);
			outtextxy(m_countGradeEdit->x(), m_countGradeEdit->y() + 50, std::string("没有找到年级为" + m_countGradeEdit->text() + "的学生！").data());
		}
		else if (m_countNum != 0 && isPressed)//找到
		{
			std::string result = "该年级总人数:" + std::to_string(m_countNum) + "   " + "该年级男生人数:" + std::to_string(m_countBoys) + "   " + "该年级女生人数:" + std::to_string(m_countGirls);
			gettextstyle(&originalFont); // 保存原字体
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "黑体");
			settextcolor(BLACK);
			outtextxy(m_countGradeEdit->x() - 200, m_countGradeEdit->y() + 50, result.data());
			settextstyle(&originalFont);// 恢复原字体
		}

		if (m_backCountBtn->isClicked())
		{
			m_countGradeEdit->clear();
			isPressed = false;
		}

		displayBackBtn(3);
		break;

	default:
		break;
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
	else if (btnState == 2)
	{
		//设置返回按钮
		m_backSearchBtn->setFixedSized(200, 35);
		m_backSearchBtn->show();
		m_backSearchBtn->eventLoop(m_msg);//将事件分发到返回按钮
		if (m_backSearchBtn->isClicked())
		{
			// 返回查询主界面
			m_searchState = Search_Main;
		}
	}
	else if (btnState == 3)
	{
		//设置返回按钮
		m_backCountBtn->setFixedSized(200, 35);
		m_backCountBtn->show();
		m_backCountBtn->eventLoop(m_msg);//将事件分发到返回按钮
		if (m_backCountBtn->isClicked())
		{
			// 返回统计主界面
			m_countState = Count_Main;
		}
	}
}

void Management::eventLoop()
{
	m_showTable->eventLoop(m_msg);//把收到的事件消息m_msg传（分发）给表格组件
	m_delTable->eventLoop(m_msg);

	m_addBtn->eventLoop(m_msg);
	m_addEdit->eventLoop(m_msg);

	m_delBtn->eventLoop(m_msg);
	m_delEdit->eventLoop(m_msg);

	m_modifyEdit->eventLoop(m_msg);
	m_modifyBtn->eventLoop(m_msg);
	for (int i = 0; i < 9; i++)
	{
		m_stuEdits[i]->eventLoop(m_msg);
	}

	m_searchEdit->eventLoop(m_msg);
	m_searchClassEdit->eventLoop(m_msg);
	m_searchTable->eventLoop(m_msg);

	m_countBtn->eventLoop(m_msg);
	m_countCollegeEdit->eventLoop(m_msg);
	m_countMajorEdit->eventLoop(m_msg);
	m_countClassEdit->eventLoop(m_msg);
	m_countGradeEdit->eventLoop(m_msg);

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
		
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out);//写和创建 
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
		std::string info = val.formatInfo3();
		write.write(info.c_str(), info.size());
	}
	write.close();
}

void Management::updateTable()
{
	m_showTable->clear();
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
}
	
