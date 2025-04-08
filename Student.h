#pragma once
#include "Configure.h"
class Student
{
public:
	Student();//Ĭ�Ϲ��캯��
	Student(const std::string& name, const std::string& sex, const std::string& number, const std::string& date,
		const std::string& school_year, const std::string& id, const std::string& college, const std::string& major, const std::string& cla);
	std::string formatInfo();//�Ʊ����ʽ������
	std::string formatInfo2();//�ո��ʽ������
	static Student fromString(const std::string& str);  //�����ַ��������Student�ṹ��

public:
	std::string name;//����
	std::string sex;//�Ա�
	std::string number;//ѧ��
	std::string date;//��ѧʱ��
	std::string school_year;//ѧ��
	std::string id;//���֤
	std::string college;//ѧԺ
	std::string major;//רҵ
	std::string cla;//�����༶
};

