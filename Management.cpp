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
	//�������ʼ����ť
	menu_btns.push_back(new PushButton("�鿴����ѧ��֤��Ϣ"));
	menu_btns.push_back(new PushButton("����ѧ��֤��Ϣ"));
	menu_btns.push_back(new PushButton("��ѯѧ��֤��Ϣ"));
	menu_btns.push_back(new PushButton("ͳ��ѧ��֤��Ϣ"));
	menu_btns.push_back(new PushButton("�˳�ϵͳ"));

	//�����Ӳ˵���ť��ʼ��
	manage_btns.push_back(new PushButton("¼��ѧ��֤��Ϣ"));
	manage_btns.push_back(new PushButton("ɾ��ѧ��֤��Ϣ"));
	manage_btns.push_back(new PushButton("�޸�ѧ��֤��Ϣ"));

	//��ѯ�Ӳ˵���ť��ʼ��
	search_btns.push_back(new PushButton("��ѯ����ѧ������Ϣ"));
	search_btns.push_back(new PushButton("��ѯ�༶ȫ��ѧ������Ϣ"));

	//ͳ���Ӳ˵���ť��ʼ��
	count_btns.push_back(new PushButton("ͳ��ĳѧԺ����"));
	count_btns.push_back(new PushButton("ͳ��ĳרҵ����"));
	count_btns.push_back(new PushButton("ͳ��ĳ�༶����"));
	count_btns.push_back(new PushButton("ͳ��ĳ�꼶����"));

	isProcessed = false;//��ť����״̬��ʼ��

	//���ؼ�
	m_backMenuBtn = new PushButton("�������˵�");
	m_backManageBtn = new PushButton("������Ϣ����˵�");
	m_backSearchBtn = new PushButton("������Ϣ��ѯ�˵�");
	m_backCountBtn = new PushButton("������Ϣͳ�Ʋ˵�");

	//�������˵���ť
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		//��ť�ŵ������м�
		menu_btns[i]->move(bx, by);
	}
	//���й����Ӳ˵���ť
	for (int i = 0; i < manage_btns.size(); i++) {
		manage_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - manage_btns[i]->width()) / 2;
		int vspace = (Window::height() - manage_btns.size() * manage_btns[i]->height()) / 2;
		int by = vspace + i * manage_btns[i]->height();
		manage_btns[i]->move(bx, by+50);
	}
	//¼��ѧ������İ�ť�������
	m_addBtn = new PushButton("¼��", 900, 260, 80, 30);//¼��ѧ���İ�ť
	m_addEdit = new LineEdit(100, 260, 750, 30);
	m_addEdit->setTitle("¼��ѧ��");
	m_addEdit->setHitText("��ʽ:\n <���� �Ա� ѧ�� ��ѧʱ�� ѧ�� ���֤ ѧԺ רҵ �༶>");

	//ɾ��ѧ������İ�ť�������
	m_delBtn = new PushButton("ɾ��", 650, 260, 80, 30);
	m_delEdit = new LineEdit(440, 260, 200, 30);
	m_delEdit->setTitle("ɾ��ѧ��");
	m_delEdit->setHitText("������Ҫɾ��ѧ����ѧ��:");
	m_delTable = new Table;//ɾ��ѧ���ı��
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x()-425, m_delEdit->y() + 100);

	//�޸�ѧ������������
	m_modifyBtn = new PushButton("�޸�", 650, 260, 80, 30);//�޸�ѧ���İ�ť
	m_modifyEdit = new LineEdit(440, 260, 200, 30);
	//m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);//������ʾ
	m_modifyEdit->setTitle("�޸�ѧ��");
	m_modifyEdit->setHitText("������Ҫ�޸�ѧ����ѧ��");
	m_modifyIt = vec_stu.end();
	//�޸�ѧ����Ϣ�������Ķ��󴴽�
	for (int i = 0; i < 9; i++)
	{
		m_stuEdits.emplace_back(new LineEdit(0, 0, 130, 30));
		if (i == 0)//����
		{
			m_stuEdits[i]->move(20 + i * 140, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		if (i == 1)//�Ա�
		{
			m_stuEdits[i]->move(20+60, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		if (i == 2)//ѧ��
		{
			m_stuEdits[i]->move(80 + 60, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(100, 30);
		}
		if (i == 3)//��ѧʱ��
		{
			m_stuEdits[i]->move(140 + 110, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(80, 30);
		}
		if (i == 4)//ѧ��
		{
			m_stuEdits[i]->move(250 + 90, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		if (i == 5)//���֤
		{
			m_stuEdits[i]->move(340 + 60, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(150, 30);
		}
		if (i == 6)//ѧԺ
		{
			m_stuEdits[i]->move(400 + 160, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(130, 30);
		}
		if (i == 7)//רҵ
		{
			m_stuEdits[i]->move(560 + 140, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(100, 30);
		}
		if (i == 8)//�༶
		{
			m_stuEdits[i]->move(700 + 110, m_modifyEdit->y() + 100);
			m_stuEdits[i]->setFixedSized(50, 30);
		}
		
	}

	//���в�ѯ�Ӳ˵���ť
	for (int i = 0; i < search_btns.size(); i++) {
		search_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - search_btns[i]->width()) / 2;
		int vspace = (Window::height() - search_btns.size() * search_btns[i]->height()) / 2;
		int by = vspace + i * search_btns[i]->height();
		search_btns[i]->move(bx, by+100);
	}
	m_searchEdit = new LineEdit(440, 260, 200, 30);//��ѯ������ʼ��
	m_searchEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);//������ʾ
	m_searchEdit->setTitle("��ѯѧ��");
	m_searchEdit->setHitText("������Ҫ��ѯѧ����ѧ�Ż�����");
	m_searchTable = new Table;//��ѯѧ���ı��
	m_searchTable->setHeader(m_header);
	m_searchTable->move(m_delEdit->x() - 425, m_delEdit->y() + 100);
	
	m_searchClassEdit = new LineEdit(440, 260, 300, 30);//��ѯ�༶������ʼ��
	m_searchClassEdit->move((Window::width() - m_searchClassEdit->width()) / 2, 260);//������ʾ
	m_searchEdit->setTitle("��ѯĳ�༶������ѧ��");
	m_searchEdit->setHitText("������Ҫ��ѯ���꼶 רҵ �༶");

	//����ͳ���Ӳ˵���ť
	for (int i = 0; i < count_btns.size(); i++) {
		count_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - count_btns[i]->width()) / 2;
		int vspace = (Window::height() - count_btns.size() * count_btns[i]->height()) / 2;
		int by = vspace + i * count_btns[i]->height();
		count_btns[i]->move(bx, by-100);
	}
	m_countCollegeEdit = new LineEdit(440, 150, 200, 30);//ͳ��רҵ������ʼ��
	m_countCollegeEdit->setTitle("ͳ��ѧԺ����");
	m_countCollegeEdit->setHitText("������Ҫͳ�Ƶ�ѧԺ");
	m_countMajorEdit = new LineEdit(440, 150, 200, 30);//ͳ��רҵ������ʼ��
	m_countMajorEdit->setTitle("ͳ��רҵ����");
	m_countMajorEdit->setHitText("������Ҫͳ�Ƶ�רҵ");
	m_countClassEdit = new LineEdit(440, 150, 200, 30);//ͳ�ư༶������ʼ��
	m_countClassEdit->setTitle("ͳ�ư༶����");
	m_countClassEdit->setHitText("������Ҫͳ�Ƶİ༶");
	m_countGradeEdit = new LineEdit(440, 150, 200, 30);//ͳ���꼶������ʼ��
	m_countGradeEdit->setTitle("ͳ���꼶����");
	m_countGradeEdit->setHitText("������Ҫͳ�Ƶ��꼶");
	m_countBtn = new PushButton("ͳ��", 650, 150, 80, 30);//ͳ�ư�ť��ʼ��

	//��ʼ���鿴ѧ���ı��
	m_showTable = new Table;//new�Ķ����ڶ����棬���캯������ջ�ڴ��� �뿪��������Զ��ͷ�
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	m_showTable->move((Window::width()-m_showTable->width())/2, 100);
	updateTable();
	//m_backBtnState = 0;
}

void Management::run()
{
	//��ȡmenu�ķ���ֵ
	m_currentOp = Menu;
	Window::beginDraw();//���Ƶ�ͼ�β���ֱ����ʾ����Ļ�ϣ����Ǵ��뵽�����������ȥ
	while (true)
	{
		Window::clear();
		drawBackGround();
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();//���ڲ�����Ϣ���·ַ�
			switch (m_msg.message)
			{
			case WM_KEYDOWN://����а�������
				if (Window::getMsg().vkcode == VK_ESCAPE)
					//��ESC�˳�������menu����
				{
					m_currentOp = Menu;
				}
				break;
			default: //������
				eventLoop();//ϵͳ��⵽�¼�������꣩��ֱ�����·ַ��¼�
				break;
			}
		}
		switch (m_currentOp)
		{
		case Menu:
			m_currentOp = menu();//opֻ�е���menu()�Ż��
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
		case Management::Exit://��opҲ����iΪ4ʱ����
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
	//��ť�߼�
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->show();//ֻ����opΪMenuʱ���ų��а�ť
		menu_btns[i]->eventLoop(m_msg);
		if (menu_btns[i]->isClicked())
		{
			return i;//���ذ�ť��Ӧ�Ĳ�����ö��ֵ��op������switch��ʼ����
		}
	}
	return Menu;//��û�б��������һֱͣ����Menu
}

void Management::display()
{
	m_showTable->show();
	//cout << "display" << endl;
	//���÷��ذ�ť
	displayBackMenuBtn();
}

void Management::manage()
{
	const char* tip;
	const char* example;
	switch (m_manageState) {
	case Manage_Main: // �������˵�
		drawTile();
		// ��ʾ�����Ӳ˵���ť
		for (auto& btn : manage_btns) {
			btn->show();
			btn->eventLoop(m_msg);

			if (btn->isClicked() && btn->getText() == "¼��ѧ��֤��Ϣ") {
				m_manageState = Manage_Add; // �л���¼��״̬
			}
			else if (btn->isClicked() && btn->getText() == "ɾ��ѧ��֤��Ϣ") {
				m_manageState = Manage_Delete;
				// ִ��ɾ������
			}
			else if (btn->isClicked() && btn->getText() == "�޸�ѧ��֤��Ϣ") {
				m_manageState = Manage_Modify;
			}
		}
		// �������˵���ť
		displayBackMenuBtn();
		break;

	case Manage_Add: // ¼����Ϣ����
		LOGFONT originalFont;
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);
		
		// ��ʾ��ʾ��Ϣ
		tip = "������ѧ����Ϣ<���� �Ա� ѧ�� ��ѧʱ�� ѧ�� ���֤ ѧԺ רҵ �༶>:";
		example = "�������� �� 202232310229 2022-09-01 4�� 440320200312190344 ������ѧѧԺ ������ѧ 2��";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip))/2, 150, tip);
		settextstyle(&originalFont); // �ָ�ԭ����
		settextstyle(18, 0, "��Բ");
		outtextxy((Window::width() - textwidth(tip)) / 2 - 100, 200, example);
		settextstyle(&originalFont); // �ָ�ԭ����
		m_addBtn->show();
		m_addEdit->show();

		// ��ⰴť�����ȷ��������һ��
		if (m_addBtn->isClicked()&&!(m_addEdit->text().empty())) {
			if (!isProcessed) {
				vec_stu.push_back(Student::fromString(m_addEdit->text()));//�浽stu�Ĵ洢����
				auto str = m_addEdit->text();
				std::replace(str.begin(), str.end(), ' ', '\t');//������Ŀո��滻��'\t'�����ڷָ�
				m_showTable->insertData(str); //�浽���
				m_addEdit->clear();
				isProcessed = true; // ����Ѵ���
				m_manageState = Manage_Main;
			}
		}
		else {
			isProcessed = false; // ��ťδ���ʱ����״̬
		}
		if (m_backManageBtn->isClicked())
		{
			m_addEdit->clear();
		}
		// ���ع���˵���ť
		displayBackBtn(1);
		break;

	case Manage_Delete://ɾ����Ϣ����
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		// ��ʾ��ʾ��Ϣ
		tip = "������Ҫɾ��ѧ����ѧ�ţ�";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // �ָ�ԭ����

		m_delBtn->show();
		m_delEdit->show();

		// ������ʵʱ�����߼�������δ���ɾ����ťʱִ�У�
		if (!m_delEdit->text().empty() && !m_delBtn->isClicked()) {
			m_delTable->clear(); // ��վ�����
			auto& str = m_delEdit->text();
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
				return stu.number == str;
				});

			if (it == vec_stu.end()) {
				// ��ʾδ�ҵ�
				settextcolor(RED);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("û���ҵ�ѧ��Ϊ" + str + "��ѧ����").data());
			}
			else {
				// ��ʾ�ҵ�
				m_delTable->insertData(it->formatInfo());
				settextcolor(GREEN);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("�ҵ�ѧ��Ϊ" + str + "��ѧ����").data());
				settextcolor(BLACK);
				m_delTable->setShowPageBtn(false);//���ط�ҳ��ť
				m_delTable->show();
			}
		}
		// ɾ����ť�߼�
		if (m_delBtn->isClicked()) {
			if (!m_delEdit->text().empty()) {
				auto& str = m_delEdit->text();
				auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
					return stu.number == str;
					});

				if (it != vec_stu.end()) { // ����ҵ���ɾ����ѧ��
					vec_stu.erase(it, vec_stu.end());
					updateTable();
					m_delEdit->clear();    // ��������
					m_delTable->clear();   // ��ձ��
				}
			}
			m_manageState = Manage_Main;
		}
		if (m_backManageBtn->isClicked())
		{
			m_delEdit->clear();
			m_delTable->clear();
		}
		// ���ع���˵���ť
		displayBackBtn(1);
		break;
	case Manage_Modify://�޸Ľ�����Ϣ
		// ��ʾ��ʾ��Ϣ
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "������Ҫ�޸�ѧ����ѧ�ţ�";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // �ָ�ԭ����
		m_modifyBtn->show();
		m_modifyEdit->show();

		if (!m_modifyEdit->text().empty())
		{
			auto& str = m_modifyEdit->text();
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
				return stu.number == str;
				});

			if (it == vec_stu.end()) {
				// ��ʾδ�ҵ�
				m_modifyIt = vec_stu.end();
				isFind = false;
				settextcolor(RED);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("û���ҵ�ѧ��Ϊ" + str + "��ѧ����").data());
			}
			else//�ҵ�ѧ��
			{
				//չʾ�޸�ѧ���������
				for (auto& e : m_stuEdits)
				{
					e->show();
				}
				//�����޸Ŀ���ı�
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
				//���ҵ���Ҫ�޸ĵ�ѧ����Ϣ����Ϊ�����޸�ֵ
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
		// ���ع���˵���ť
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
	case Search_Main: //��ѯ���˵�
		drawTile();
		//��ʾ��ѯ�Ӳ˵���ť
		for (auto& btn : search_btns)
		{
			btn->show();
			btn->eventLoop(m_msg);

			if (btn->isClicked() && btn->getText() == "��ѯ����ѧ������Ϣ") {
				m_searchState = Search_stu; // �л�����ѯ����ѧ����״̬
			}
			else if (btn->isClicked() && btn->getText() == "��ѯ�༶ȫ��ѧ������Ϣ") {
				m_searchState = Search_class;//�л�����ѯ�༶ѧ����״̬
			}
		}
		// �������˵���ť
		displayBackMenuBtn();
		break;

	case Search_stu:
		m_searchTable->clear();

		LOGFONT originalFont;
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "������Ҫ��ѯѧ���Ĺؼ��ʣ����磺ѧ�� �������Ա�ȣ�";
		example = "�ո�ָ�����������磺�� ��";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // �ָ�ԭ����
		settextstyle(18, 0, "��Բ");
		outtextxy((Window::width() - textwidth(tip)) / 2+100, 200, example);
		settextstyle(&originalFont); // �ָ�ԭ����

		m_searchEdit->show();

		//û�ҵ����߼�
		if (!m_searchEdit->text().empty())
		{
			// ��վɽ��
			m_searchTable->clear();

			// �ָ��ѯ����,����keywords
			std::vector<std::string> keywords;
			std::istringstream iss(m_searchEdit->text());
			std::string keyword;
			while (iss >> keyword) {
				keywords.push_back(keyword);
			}
			// ����ƥ���ѧ��
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
			// ��ʾ���
			if (results.empty()) {
				settextcolor(RED);
				outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "û���ҵ�ƥ���ѧ����");
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
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "������Ҫ��ѯ���꼶רҵ�༶��";
		example = "��ʽ���꼶 רҵ �༶";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 150, tip);
		settextstyle(&originalFont); // �ָ�ԭ����
		settextstyle(18, 0, "��Բ");
		outtextxy((Window::width() - textwidth(tip)) / 2, 200, example);
		settextstyle(&originalFont); // �ָ�ԭ����

		m_searchEdit->show();
		std::string input = m_searchEdit->text();

		if (!input.empty())
		{
			std::istringstream iss(input);
			std::string grade, major, cla;
			iss >> grade >> major >> cla;
			if (grade.empty() || major.empty() || cla.empty()) {
				settextcolor(RED);
				outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "�����ʽ�����밴��ʽ���룡");
			}
			else
			{
				//���ҷ���������ѧ��
				std::vector<Student> results;
				for (auto& stu : vec_stu)
				{
					std::string stuGrade = stu.date.substr(0, 4); // ����ѧ������ȡ�꼶
					if (stuGrade == grade && stu.major == major && stu.cla == cla)
					{
						results.push_back(stu);
					}
				}
				//��ʾ���
				if (results.empty())
				{
					settextcolor(RED);
					outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "û���ҵ�����������ѧ����");
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
					//m_searchTable->updatePage();//���±��
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
	case Count_Main: // ͳ�����˵�
		drawTile();
		//��ʾͳ���Ӳ˵���ť
		for (auto& btn : count_btns)
		{
			btn->show();
			btn->eventLoop(m_msg);

			if (btn->isClicked() && btn->getText() == "ͳ��ĳѧԺ����") {
				m_countState = Count_college; // �л���ͳ��ѧԺ������״̬
			}
			else if (btn->isClicked() && btn->getText() == "ͳ��ĳרҵ����") {
				m_countState = Count_major;//�л���ͳ��רҵ������״̬
			}
			else if (btn->isClicked() && btn->getText() == "ͳ��ĳ�༶����") {
				m_countState = Count_class;//�л���ͳ�ư༶������״̬
			}
			else if (btn->isClicked() && btn->getText() == "ͳ��ĳ�꼶����") {
				m_countState = Count_grade;//�л���ͳ���꼶������״̬
			}
		}
		displayBackMenuBtn();//�������˵���ť
		break;
	case Count_college://ͳ��ѧԺ����
		LOGFONT originalFont;
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "��������Ҫͳ��������ѧԺ��";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(&originalFont);// �ָ�ԭ����

		m_countCollegeEdit->show();
		m_countBtn->show();

		if (m_countBtn->isClicked()&&!m_countCollegeEdit->text().empty())
		{
			m_countNum = 0;//ѧԺ������ʼ��
			m_countBoys = 0;//����������ʼ��
			m_countGirls = 0;//Ů��������ʼ��
			isPressed = true;
			//����ѧ������
			for (auto& stu : vec_stu)
			{
				if (stu.college == m_countCollegeEdit->text())
				{
					m_countNum++;//��ѧԺ������һ
					if (stu.sex == "��")
						m_countBoys++;
					else if (stu.sex == "Ů")
						m_countGirls++;
				}
			}
		}
		//���ͳ�ƽ��
		if (m_countNum == 0&&isPressed)//û�ҵ�
		{
			settextcolor(RED);
			outtextxy(m_countCollegeEdit->x(), m_countCollegeEdit->y() + 50, std::string("û���ҵ�ѧԺΪ" + m_countCollegeEdit->text() + "��ѧ����").data());
		}
		else if (m_countNum != 0 && isPressed)//�ҵ�
		{
			gettextstyle(&originalFont); // ����ԭ����
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "����");
			std::string result = "��ѧԺ������:" + std::to_string(m_countNum) + "   " + "��ѧԺ��������:" + std::to_string(m_countBoys) + "   " + "��ѧԺŮ������:" + std::to_string(m_countGirls);
			settextcolor(BLACK);
			outtextxy(m_countCollegeEdit->x() - 200, m_countCollegeEdit->y() + 50, result.data());
			settextstyle(&originalFont);// �ָ�ԭ����
		}

		if (m_backCountBtn->isClicked())
		{
			m_countCollegeEdit->clear();
			isPressed = false;
		}
		displayBackBtn(3);
		break;
	case Count_major://ͳ��רҵ����
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "��������Ҫͳ��������רҵ��";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(&originalFont);// �ָ�ԭ����

		m_countMajorEdit->show();
		m_countBtn->show();

		//ͳ��רҵ����
		if (m_countBtn->isClicked() && !m_countMajorEdit->text().empty())
		{
			m_countNum = 0;//רҵ������ʼ��
			m_countBoys = 0;//����������ʼ��
			m_countGirls = 0;//Ů��������ʼ��
			isPressed = true;
			//����ѧ������
			for (auto& stu : vec_stu)
			{
				if (stu.major == m_countMajorEdit->text())
				{
					m_countNum++;//��רҵ������һ
					if (stu.sex == "��")
						m_countBoys++;
					else if (stu.sex == "Ů")
						m_countGirls++;
				}
			}
		}
		//���ͳ�ƽ��
		if (m_countNum == 0 && isPressed)//û�ҵ�
		{
			settextcolor(RED);
			outtextxy(m_countMajorEdit->x(), m_countMajorEdit->y() + 50, std::string("û���ҵ�רҵΪ" + m_countMajorEdit->text() + "��ѧ����").data());
		}
		else if (m_countNum != 0 && isPressed)//�ҵ�
		{
			std::string result = "��רҵ������:" + std::to_string(m_countNum) + "   " + "��רҵ��������:" + std::to_string(m_countBoys) + "   " + "��רҵŮ������:" + std::to_string(m_countGirls);
			gettextstyle(&originalFont); // ����ԭ����
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "����");
			settextcolor(BLACK);
			outtextxy(m_countMajorEdit->x() - 200, m_countMajorEdit->y() + 50, result.data());
			settextstyle(&originalFont);// �ָ�ԭ����
		}

		if (m_backCountBtn->isClicked())
		{
			m_countMajorEdit->clear();
			isPressed = false;
		}
		displayBackBtn(3);
		break;
	case Count_class://ͳ�ư༶����
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "��������Ҫ�鿴ͳ�����ݵ��꼶רҵ�༶��";
		example = "��ʽ���꼶 רҵ �༶";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(18, 0, "��Բ");
		outtextxy((Window::width() - textwidth(tip)) / 2, 100, example);
		settextstyle(&originalFont);// �ָ�ԭ����

		m_countClassEdit->show();
		m_countBtn->show();

		//ͳ�ư༶����
		if (m_countBtn->isClicked() && !m_countClassEdit->text().empty())
		{
			m_countNum = 0;//�༶������ʼ��
			m_countBoys = 0;//����������ʼ��
			m_countGirls = 0;//Ů��������ʼ��
			isPressed = true;
			//����ѧ������
			std::string input = m_countClassEdit->text();
			std::istringstream iss(input);
			std::string grade, major, cla;
			iss >> grade >> major >> cla;
			if (grade.empty() || major.empty() || cla.empty()) {
				settextcolor(RED);
				outtextxy(m_searchEdit->x(), m_searchEdit->y() + 50, "�����ʽ�����밴��ʽ���룡");
			}
			else
			{
				//���ҷ���������ѧ��
				for (auto& stu : vec_stu)
				{
					std::string stuGrade = stu.date.substr(0, 4); // ����ѧ������ȡ�꼶
					if (stuGrade == grade && stu.major == major && stu.cla == cla)
					{
						m_countNum++;
						if (stu.sex == "��")
						{
							m_countBoys++;
						}
						else if (stu.sex == "Ů")
						{
							m_countGirls++;
						}
					}
				}
			}

		}
		//���ͳ�ƽ��
		if (m_countNum == 0 && isPressed)//û�ҵ�
		{
			settextcolor(RED);
			outtextxy(m_countClassEdit->x(), m_countClassEdit->y() + 50, std::string("û���ҵ��༶Ϊ" + m_countClassEdit->text() + "��ѧ����").data());
		}
		else if (m_countNum != 0 && isPressed)//�ҵ�
		{
			std::string result = "�ð༶������:" + std::to_string(m_countNum) + "   " + "�ð༶��������:" + std::to_string(m_countBoys) + "   " + "�ð༶Ů������:" + std::to_string(m_countGirls);
			gettextstyle(&originalFont); // ����ԭ����
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "����");
			settextcolor(BLACK);
			outtextxy(m_countClassEdit->x() - 200, m_countClassEdit->y() + 50, result.data());
			settextstyle(&originalFont);// �ָ�ԭ����
		}

		if (m_backCountBtn->isClicked())
		{
			m_countClassEdit->clear();
			isPressed = false;
		}
		displayBackBtn(3);
		break;
	case Count_grade://ͳ���꼶����
		gettextstyle(&originalFont); // ����ԭ����
		setbkmode(TRANSPARENT);

		tip = "��������Ҫ�鿴ͳ�����ݵ��꼶��";
		settextstyle(26, 0, "����");
		outtextxy((Window::width() - textwidth(tip)) / 2, 50, tip);
		settextstyle(&originalFont);// �ָ�ԭ����

		m_countGradeEdit->show();
		m_countBtn->show();

		//ͳ���꼶����
		if (m_countBtn->isClicked() && !m_countGradeEdit->text().empty())
		{
			m_countNum = 0;//�꼶������ʼ��
			m_countBoys = 0;//����������ʼ��
			m_countGirls = 0;//Ů��������ʼ��
			isPressed = true;
			//����ѧ������
			for (auto& stu : vec_stu)
			{
				std::string stuGrade = stu.date.substr(0, 4); // ����ѧ������ȡ�꼶
				if (stuGrade == m_countGradeEdit->text())
				{
					m_countNum++;//���꼶������һ
					if (stu.sex == "��")
						m_countBoys++;
					else if (stu.sex == "Ů")
						m_countGirls++;
				}
			}
		}
		//���ͳ�ƽ��
		if (m_countNum == 0 && isPressed)//û�ҵ�
		{
			settextcolor(RED);
			outtextxy(m_countGradeEdit->x(), m_countGradeEdit->y() + 50, std::string("û���ҵ��꼶Ϊ" + m_countGradeEdit->text() + "��ѧ����").data());
		}
		else if (m_countNum != 0 && isPressed)//�ҵ�
		{
			std::string result = "���꼶������:" + std::to_string(m_countNum) + "   " + "���꼶��������:" + std::to_string(m_countBoys) + "   " + "���꼶Ů������:" + std::to_string(m_countGirls);
			gettextstyle(&originalFont); // ����ԭ����
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, "����");
			settextcolor(BLACK);
			outtextxy(m_countGradeEdit->x() - 200, m_countGradeEdit->y() + 50, result.data());
			settextstyle(&originalFont);// �ָ�ԭ����
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
	gettextstyle(&originalFont); // ����ԭ����
	setbkmode(TRANSPARENT);

	std::string title;

	if (m_currentOp == Menu)
	{
		settextstyle(50, 0, "����");
		title = "ѧ��֤��Ϣ����ϵͳ";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 120, title.c_str());
	}
	else if (m_currentOp == Manage)
	{
		settextstyle(50, 0, "��Բ");
		title = "��Ϣ����";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 200, title.c_str());
	}
	else if (m_currentOp == Search)
	{
		settextstyle(50, 0, "��Բ");
		title = "��Ϣ��ѯ";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 300, title.c_str());
	}
	else if (m_currentOp == Count)
	{
		settextstyle(50, 0, "��Բ");
		title = "��Ϣͳ��";
		int textWidth = textwidth(title.c_str());
		outtextxy((Window::width() - textWidth) / 2, 70, title.c_str());
	}

	
	settextstyle(&originalFont); // �ָ�ԭ����
}

void Management::displayBackMenuBtn()
{
	//���÷��ذ�ť
	m_backMenuBtn->setFixedSized(100, 25);
	m_backMenuBtn->show();
	m_backMenuBtn->eventLoop(m_msg);//���¼��ַ������ذ�ť
	if (m_backMenuBtn->isClicked())
	{
		m_currentOp = Menu;
	}
}

void Management::displayBackBtn(int btnState)
{
	if (btnState == 1)
	{
		//���÷��ذ�ť
		m_backManageBtn->setFixedSized(200, 35);
		m_backManageBtn->show();
		m_backManageBtn->eventLoop(m_msg);//���¼��ַ������ذ�ť
		if (m_backManageBtn->isClicked())
		{
			// ���ع���������
			m_manageState = Manage_Main;
		}
	}
	else if (btnState == 2)
	{
		//���÷��ذ�ť
		m_backSearchBtn->setFixedSized(200, 35);
		m_backSearchBtn->show();
		m_backSearchBtn->eventLoop(m_msg);//���¼��ַ������ذ�ť
		if (m_backSearchBtn->isClicked())
		{
			// ���ز�ѯ������
			m_searchState = Search_Main;
		}
	}
	else if (btnState == 3)
	{
		//���÷��ذ�ť
		m_backCountBtn->setFixedSized(200, 35);
		m_backCountBtn->show();
		m_backCountBtn->eventLoop(m_msg);//���¼��ַ������ذ�ť
		if (m_backCountBtn->isClicked())
		{
			// ����ͳ��������
			m_countState = Count_Main;
		}
	}
}

void Management::eventLoop()
{
	m_showTable->eventLoop(m_msg);//���յ����¼���Ϣm_msg�����ַ�����������
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
		cout << "�޷����ļ�" << endl;
		return;
	}
	//��ȡ��ͷ
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;
	
	//��ȡ����
	while (!read.eof())
	{
		char data[1024] = {0};//����˳��������ڴ�
		read.getline(data, 1024);
		//��������
		if (strlen(data) == 0)
		{
			break;
		}
		//��ʽ����ȡ
		Student stu;//����һ����ʱ����
		stringstream ss(data);
		//�������Կո�ָ�����stu�ĳ�Ա����
		ss >> stu.name >> stu.sex >> stu.number >> stu.date >> stu.school_year >> stu.id >> stu.college >> stu.major >> stu.cla;
		vec_stu.push_back(stu);//stu����ļ��е����ݺ����vec_stu
		
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out);//д�ʹ��� 
	if (!write.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}
	//д��ͷ
	m_header += "\n";//����ͷ���һ������
	write.write(m_header.c_str(), m_header.size());
	//д����
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
	
