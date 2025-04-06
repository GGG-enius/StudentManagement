#include "Table.h"
#include<iostream>
Table::Table(int row, int col)
	:BasicWidget(0, 0, 0, 0), m_rows(row), m_cols(col)
	,m_curPage(0)
	,m_maxPage(0)
	,m_extraPage(0)
{
	m_prevBtn = new PushButton("��һҳ");
	m_nextBtn = new PushButton("��һҳ");
	m_firstBtn = new PushButton("��һҳ");
	m_lastBtn = new PushButton("��βҳ");
}

Table::~Table()
{
	delete m_prevBtn;
	delete m_nextBtn;
	delete m_firstBtn;
	delete m_lastBtn;
}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::setHeader(const std::string& header)
{
	m_header = header;
	m_cols = 9;
	
	//������ֵĿ��
	m_tW = 120;
	m_tH = ::textheight(m_header.c_str());
	//���ӵĿ��
	m_gridW = m_tW + 10;
	m_gridH = m_tH + 10;
	//���Ŀ��
	m_w = m_gridW * m_cols;
	m_h = m_gridH * (m_rows + 1);
}

void Table::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();//�����������ٸ���
}

void Table::show()
{
	drawTableGrid();
	drawHeader();
	drawTableData();
}

void Table::drawTableGrid()
{
	//ȷ���������ж�����
	setlinecolor(BLACK);
	//������
	for (size_t i = 0;i < m_rows + 1;i++)//��������������һ
	{
		line(m_x, m_y + i * m_gridH, m_x + m_cols * m_gridW, m_y + i * m_gridH);
	}
	//������
	for (size_t i = 0;i < m_cols + 1;i++)
	{
		line(m_x + i * m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	//���ư�ť
	if (m_maxPage > 0&& m_showPageBtn)//ֻ��һҳ���û�
	{
		drawButton();
	}
}

void Table::drawTableData()
{
	int begPos = m_curPage * m_rows;//���ݿ�ʼ��λ��
	int endPos = m_curPage * m_rows + m_rows;//���ݽ�����λ��
	if (m_curPage == m_maxPage)//��ֹԽ��
	{//��������һҳ��ֻ����ʣ������
		endPos = m_curPage * m_rows + m_extraPage;
	}
	for (size_t i = begPos, r=0;i <endPos;i++, r++)//��
	{
		const auto& line_data = split(m_datas[i]);
		for (size_t k= 0;k < line_data.size();k++)//��
		{
			int tx = m_x + k * m_gridW + (m_gridW - ::textwidth(line_data[k].c_str())) / 2;
			int ty = m_y + r * m_gridH + 10;
			settextstyle(14, 0, "����");
			outtextxy(tx, ty, line_data[k].c_str());
		}
	}
}

void Table::drawButton()
{
	//���Ч�ʣ���֤�ڳ������е��ڼ�ֻŲ��һ�Σ��ռ任ʱ��
	static bool flag = false;
	if (!flag)
	{
		m_prevBtn->setFixedSized(m_gridW, m_gridH);
		m_nextBtn->setFixedSized(m_gridW, m_gridH);
		m_firstBtn->setFixedSized(m_gridW, m_gridH);
		m_lastBtn->setFixedSized(m_gridW, m_gridH);


		m_prevBtn->move(m_x, m_h + 100);
		m_nextBtn->move(m_prevBtn->x() + m_prevBtn->width(), m_prevBtn->y());
		m_firstBtn->move(m_nextBtn->x() + m_nextBtn->width(), m_nextBtn->y());
		m_lastBtn->move(m_firstBtn->x() + m_firstBtn->width(), m_firstBtn->y());
		flag = 1;
	}
	m_prevBtn->show();
	m_nextBtn->show();
	m_firstBtn->show();
	m_lastBtn->show();

	//ҳ����ʾ
	char str[30] = {0};
	sprintf_s(str, "��%dҳ/��%dҳ", m_curPage + 1, m_maxPage + 1);
	settextstyle(20, 0, "����");
	outtextxy(m_lastBtn->x() + m_lastBtn->width() + 100, m_lastBtn->y(), str);
}

void Table::drawHeader()
{
	setlinestyle(PS_SOLID, 2);
	::rectangle(m_x, m_y - 30, m_x + m_w, m_y);
	//������
	for (size_t i = 0;i < m_cols;i++)
	{
		line(m_x + i * m_gridW, m_y - 30, m_x + i * m_gridW, m_y);
	}
	//setlinestyle(PS_SOLID, 1);//��ԭ��ֻ�ñ�ͷ�Ǵֵ�

	//�ָ��ͷ����
	auto headers = split(m_header);
	//std::cout << headers.size() << std::endl;
	for (size_t i=0;i<headers.size();i++)
	{
			int spaceH = (m_gridW - ::textwidth(headers[i].c_str())) / 2;//ˮƽ���
			int spaceV = (30 - ::textheight(headers[i].c_str())) / 2;//��ֱ���
			outtextxy(m_x + i * m_gridW + spaceH, m_y - m_gridH + spaceV, headers[i].c_str());
	}
}

const std::vector<std::string> Table::split(std::string str, char separator)
{
	std::vector<std::string> res;//������
	
	for (size_t pos = 0; ; ) {  // ����ѭ�����ֶ������˳�
		pos = str.find(separator);  // �ҷָ���λ��
		std::string substr = str.substr(0, pos);  // ��ȡ��ǰ�ֶ�

		// ���������˿��ֶΣ�ֱ��������
		if (!substr.empty()) {
			res.push_back(substr);
		}

		// �ѷָ���ϣ��˳�ѭ��
		if (pos == std::string::npos) {
			break;
		}
		// �� substr ��ȡʣ�ಿ�֣�����Խ�磩
		str = str.substr(pos + 1);  //! ע������ֱ���� std::string ����
	}
	//for (size_t pos = 0;pos != std::string::npos; )
	//{
	//	//����ָ���ָ��ַ���λ��
	//	pos = str.find(separator);//���������ַ���str�в���\t
	//	//ȡ���ַ��� 0-pos
	//	res.push_back(str.substr(0, pos));
	//	//��ʣ�µ��ַ������浽str
	//	str = std::string(str.c_str() + pos + 1);
	//}
	return res;
}

void Table::updatePage()
{
	if (m_rows == 0 && !m_datas.empty())
	{
		m_rows = m_datas.size();

	}
	if (m_cols == 0 && !m_datas.empty())
	{
	}

	//datas 82
	if (m_rows >= m_datas.size())//ֻ��һҳ��һҳ����
	{
		m_maxPage = 0;//��0��ʼ
		m_extraPage = m_datas.size();
	}
	else
	{
		m_maxPage = m_datas.size() / m_rows;
		m_extraPage = m_datas.size() % m_rows;
	}
	
	
}

void Table::eventLoop(const ExMessage& msg)//���������յ�����Ϣ�����ĸ�������ť
{
		m_prevBtn->eventLoop(msg);
		m_nextBtn->eventLoop(msg);
		m_firstBtn->eventLoop(msg);
		m_lastBtn->eventLoop(msg);
		//����ť����¼�
		if (m_prevBtn->isClicked())
		{
			if (m_curPage != 0)//������һҳ
			{
				m_curPage--;
			}
		}
		if (m_nextBtn->isClicked())
		{
			if (m_curPage != m_maxPage)//û�е����ҳ
			{
				m_curPage++;
			}
		}
		if (m_firstBtn->isClicked())
		{
			m_curPage = 0;
		}
		if (m_lastBtn->isClicked())
		{
			m_curPage = m_maxPage;
		}
		/*if (m_backBtn->isClicked())
		{
			op = Menu;
		}*/
}
