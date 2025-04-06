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
	m_modifyEdit = new LineEdit(440, 260, 200, 30);
	m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);//������ʾ
	m_modifyEdit->setTitle("�޸�ѧ��");
	m_modifyEdit->setHitText("������Ҫ�޸�ѧ����ѧ��");

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
		
	}//�޸�ѧ����Ϣ�������Ķ��󴴽�

	//���в�ѯ�Ӳ˵���ť
	for (int i = 0; i < search_btns.size(); i++) {
		search_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - search_btns[i]->width()) / 2;
		int vspace = (Window::height() - search_btns.size() * search_btns[i]->height()) / 2;
		int by = vspace + i * search_btns[i]->height();
		search_btns[i]->move(bx, by+100);
	}
	
	//����ͳ���Ӳ˵���ť
	for (int i = 0; i < count_btns.size(); i++) {
		count_btns[i]->setFixedSized(250, 50);
		int bx = (Window::width() - count_btns[i]->width()) / 2;
		int vspace = (Window::height() - count_btns.size() * count_btns[i]->height()) / 2;
		int by = vspace + i * count_btns[i]->height();
		count_btns[i]->move(bx, by-100);
	}

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
				//m_addEdit->text();
				m_addEdit->clear();
				isProcessed = true; // ����Ѵ���
			}
		}
		else {
			isProcessed = false; // ��ťδ���ʱ����״̬
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
		m_modifyEdit->show();

		if (!m_modifyEdit->text().empty())
		{
			auto& str = m_modifyEdit->text();
			auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {
				return stu.number == str;
				});

			if (it == vec_stu.end()) {
				// ��ʾδ�ҵ�
				isFind = false;
				settextcolor(RED);
				outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("û���ҵ�ѧ��Ϊ" + str + "��ѧ����").data());
			}
			else
			{
				//չʾ�޸�ѧ���������
				for (auto& e : m_stuEdits)
				{
					e->show();
				}
				//�����޸Ŀ���ı�
				m_stuEdits[0]->setText(it->name);
				m_stuEdits[1]->setText(it->sex);
				m_stuEdits[2]->setText(it->number);
				m_stuEdits[3]->setText(it->date);
				m_stuEdits[4]->setText(it->school_year);
				m_stuEdits[5]->setText(it->id);
				m_stuEdits[6]->setText(it->college);
				m_stuEdits[7]->setText(it->major);
				m_stuEdits[8]->setText(it->cla);

				for (int i = 0; i < m_stuEdits.size(); i++)
				{
						switch (i)
						{
						case 0:
							it->name = m_stuEdits[0]->text();
							break;
						case 1:
							it->sex = m_stuEdits[1]->text();
							break;
						case 2:
							it->number = m_stuEdits[2]->text();
							break;
						case 3:
							it->date = m_stuEdits[3]->text();
							break;
						case 4:
							it->school_year = m_stuEdits[4]->text();
							break;
						case 5:
							it->id = m_stuEdits[5]->text();
							break;
						case 6:
							it->college = m_stuEdits[6]->text();
							break;
						case 7:
							it->major = m_stuEdits[7]->text();
							break;
						case 8:
							it->cla = m_stuEdits[8]->text();
							break;
						default:
							break;
						}
						updateTable();
				}

				isFind = true;
			}
		}

		// ���ع���˵���ť
		displayBackBtn(1);
		break;
	}
}

void Management::search()
{
	drawTile();
	displayBackMenuBtn();

	//��ʾ��ѯ�Ӳ˵���ť
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
	//��ʾͳ���Ӳ˵���ť
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
	for (auto& e : m_stuEdits)//�޸�ѧ����������¼�ѭ��
	{
		e->eventLoop(m_msg);
	}
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
		//cout << stu.name + " " << stu.sex + " " << stu.number + " " << stu.date + " " << stu.school_year + " " << stu.id + " " << stu.college + " " <<stu.major + " " << stu.cla<< endl;
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);//д�ʹ��� 
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
		std::string info = val.formatInfo();
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
	
