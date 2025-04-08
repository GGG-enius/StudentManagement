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
	//����������
	void run();

	int menu();
	//1.�鿴
	void display();
	//2.����
	void manage();
	//3.����
	void search();
	//4.ͳ��
	void count();
	//������
	void drawBackGround();
	//���˵�����
	void drawTile();
	//�����ذ�ť
	void displayBackMenuBtn();//�������˵�
	void displayBackBtn(int btnstate);//������һ��
	void eventLoop();//�¼�ѭ��

	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateTable();//���±��
private:
	IMAGE m_bk;
	ExMessage m_msg; //ϵͳ��⵽�¼�������꣩,���Զ�����Exmessage��Ϣ��Ȼ�����m_msg��
	
	std::vector<PushButton*> menu_btns;//���˵��İ�ť
	std::vector<PushButton*> manage_btns;//�����Ӳ˵��İ�ť
	std::vector<PushButton*> search_btns;//��ѯ�Ӳ˵��İ�ť
	std::vector<PushButton*> count_btns;//ͳ���Ӳ˵��İ�ť

	//int m_backBtnState;//���ذ�ť��״̬
	PushButton* m_backMenuBtn;//�������˵���ť
	PushButton* m_backManageBtn;//���ع���˵���ť
	PushButton* m_backSearchBtn;//���ز�ѯ�˵���ť
	PushButton* m_backCountBtn;//����ͳ�Ʋ˵���ť

	int m_currentOp;//���浱ǰop
private://��ȡ�ļ� ����ѧ����Ϣ
	std::string m_header;//�����ͷ
	std::vector<Student> vec_stu;
private: 
	Table* m_showTable;//�鿴ѧ�����

	bool isProcessed; // ��¼��ť����״̬

	PushButton* m_addBtn;//¼��ѧ���İ�ť
	LineEdit* m_addEdit;//¼��ѧ���������

	PushButton* m_delBtn;//ɾ��ѧ���İ�ť
	LineEdit* m_delEdit;//ɾ��ѧ���������
	Table* m_delTable;//ɾ��ѧ���ı��
	
	LineEdit* m_modifyEdit;//�޸�ѧ���������
	bool isFind = false;//�ж�ѧ����û���ҵ� 
	bool isFirst = true;///////�ص�bug!���setText()������bug
	std::vector<LineEdit*> m_stuEdits;//�޸�ѧ����Ϣ�������
	PushButton* m_modifyBtn;//�޸�ѧ���İ�ť
	std::vector<Student>::iterator m_modifyIt;

	LineEdit* m_searchEdit;//��ѯѧ���������
	Table* m_searchTable;//��ѯѧ���ı��

	LineEdit* m_searchClassEdit;//��ѯ�༶�������

	LineEdit* m_countCollegeEdit;//ͳ��ѧԺ�����
	LineEdit* m_countMajorEdit;//ͳ��רҵ�����
	LineEdit* m_countClassEdit;//ͳ�ư༶�����
	LineEdit* m_countGradeEdit;//ͳ���꼶�����
	PushButton* m_countBtn;//ͳ�ư�ť
private://�����Ӳ˵������л�
	enum ManangeState
	{
		Manage_Main,
		Manage_Add,
		Manage_Delete,
		Manage_Modify
	};
	int m_manageState = Manage_Main;
private://��ѯ�Ӳ˵������л�
	enum SearchState
	{
		Search_Main,
		Search_stu,
		Search_class,
	};
	int m_searchState = Search_Main;
private://ͳ���Ӳ˵������л�
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

