#pragma once
#include "Configure.h"
class Student
{
public:
	Student();//默认构造函数
	Student(const std::string& name, const std::string& sex, const std::string& number, const std::string& date,
		const std::string& school_year, const std::string& id, const std::string& college, const std::string& major, const std::string& cla);
	std::string formatInfo();//制表符格式化数据
	std::string formatInfo2();//空格格式化数据
	static Student fromString(const std::string& str);  //根据字符串构造出Student结构体

public:
	std::string name;//姓名
	std::string sex;//性别
	std::string number;//学号
	std::string date;//入学时间
	std::string school_year;//学制
	std::string id;//身份证
	std::string college;//学院
	std::string major;//专业
	std::string cla;//所属班级
};

