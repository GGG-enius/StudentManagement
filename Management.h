#pragma once
#include "Window.h"
#include <vector>
#include "PushButton.h"
#include "Student.h"
#include "Table.h"
#include "Configure.h"
#include "LineEdit.h"

class Management
{
	enum Operator
	{
		Display,//0
		Manage,//1
		Search,//2
		Count,//3
		Exit,//4
		Menu,//5
	};
public:
	Management();
	//启动管理类
	void run();

	int menu();
	//1.查看
	void display();
	//2.管理
	void manage();
	//3.查找
	void search();
	//4.统计
	void count();
	//画背景
	void drawBackGround();
	//画菜单标题
	void drawTile();
	//画返回按钮
	void displayBackMenuBtn();//返回主菜单
	void displayBackBtn(int btnstate);//返回上一级
	void eventLoop();//事件循环

	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateTable();//更新表格
private:
	IMAGE m_bk;
	ExMessage m_msg; //系统检测到事件（如鼠标）,将自动生成Exmessage消息，然后存在m_msg中
	
	std::vector<PushButton*> menu_btns;//主菜单的按钮
	std::vector<PushButton*> manage_btns;//管理子菜单的按钮
	std::vector<PushButton*> search_btns;//查询子菜单的按钮
	std::vector<PushButton*> count_btns;//统计子菜单的按钮

	//int m_backBtnState;//返回按钮的状态
	PushButton* m_backMenuBtn;//返回主菜单按钮
	PushButton* m_backManageBtn;//返回管理菜单按钮
	PushButton* m_backSearchBtn;//返回查询菜单按钮
	PushButton* m_backCountBtn;//返回统计菜单按钮

	int m_currentOp;//保存当前op
private://读取文件 保存学生信息
	std::string m_header;//保存表头
	std::vector<Student> vec_stu;
private: 
	Table* m_showTable;//查看学生表格
	PushButton* m_saveBtn;//保存按钮

	bool isProcessed; // 记录按钮处理状态

	PushButton* m_addBtn;//录入学生的按钮
	LineEdit* m_addEdit;//录入学生的输入框

	PushButton* m_delBtn;//删除学生的按钮
	LineEdit* m_delEdit;//删除学生的输入框
	Table* m_delTable;//删除学生的表格
	
	LineEdit* m_modifyEdit;//修改学生的输入框
	bool isFind = false;//判断学生有没有找到 
	bool isFirst = true;///////重点bug!解决setText()函数的bug
	std::vector<LineEdit*> m_stuEdits;//修改学生信息的输入框
	PushButton* m_modifyBtn;//修改学生的按钮
	std::vector<Student>::iterator m_modifyIt;

	LineEdit* m_searchEdit;//查询学生的输入框
	Table* m_searchTable;//查询学生的表格

	LineEdit* m_searchClassEdit;//查询班级的输入框

	int m_countNum = 0;//统计人数
	int m_countGirls = 0;//统计女生人数
	int m_countBoys = 0;//统计男生人数
	bool isPressed = false;//判断是否按下统计按钮

	LineEdit* m_countCollegeEdit;//统计学院输入框
	LineEdit* m_countMajorEdit;//统计专业输入框
	LineEdit* m_countClassEdit;//统计班级输入框
	LineEdit* m_countGradeEdit;//统计年级输入框
	PushButton* m_countBtn;//统计按钮
private://管理子菜单界面切换
	enum ManangeState
	{
		Manage_Main,
		Manage_Add,
		Manage_Delete,
		Manage_Modify
	};
	int m_manageState = Manage_Main;
private://查询子菜单界面切换
	enum SearchState
	{
		Search_Main,
		Search_stu,
		Search_class,
	};
	int m_searchState = Search_Main;
private://统计子菜单界面切换
	enum CountState
	{
		Count_Main,
		Count_college,
		Count_major,
		Count_class,
		Count_grade,
	};
	int m_countState = Count_Main;
};

