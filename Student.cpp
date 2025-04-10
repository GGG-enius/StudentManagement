#include "Student.h"
#include <sstream>
Student::Student()
{
}

Student::Student(const std::string& name, const std::string& sex, const std::string& number, const std::string& date, const std::string& school_year, const std::string& id, const std::string& college, const std::string& major, const std::string& cla)
	:name(name), sex(sex), number(number), date(date), school_year(school_year), id(id), college(college), major(major), cla(cla)
{

}

std::string Student::formatInfo()
{
	std::stringstream ss;
	ss << name << "\t" << sex << "\t" << number << "\t" << date << "\t" << school_year << "\t"<< id << "\t" << college <<"\t" << major << "\t" << cla << std::endl;
	return ss.str();
}

std::string Student::formatInfo2()
{
	std::stringstream ss;
	ss << name << "  " << sex << "  " << number << "  " << date << "  " << school_year << "  " << id << "  " << college << "  " << major << "  " << cla;
	return ss.str();
}
std::string Student::formatInfo3()
{
	/*std::stringstream ss;
	ss << name << "\t" << sex << "\t" << "\t" << number << "\t" << date << "\t" << school_year << "\t" << "\t" << id << "\t" << "\t" << college << "\t" << major << "\t" << cla << std::endl;
	return ss.str();*/
	return name + "\t" +
		sex + "\t" +
		number + "\t" +
		date + "\t" +
		school_year + "\t" +
		id + "\t" +
		college + "\t" +
		major + "\t" +
		cla;
}

Student Student::fromString(const std::string& str)
{
	Student stu;
	std::stringstream ss(str);
	ss >> stu.name >> stu.sex >> stu.number >> stu.date >> stu.school_year >> stu.id >> stu.college >> stu.major >> stu.cla;

	return stu;
}
