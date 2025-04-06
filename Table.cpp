#include "Table.h"
#include<iostream>
Table::Table(int row, int col)
	:BasicWidget(0, 0, 0, 0), m_rows(row), m_cols(col)
	,m_curPage(0)
	,m_maxPage(0)
	,m_extraPage(0)
{
	m_prevBtn = new PushButton("上一页");
	m_nextBtn = new PushButton("下一页");
	m_firstBtn = new PushButton("第一页");
	m_lastBtn = new PushButton("结尾页");
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
	
	//求出文字的宽高
	m_tW = 120;
	m_tH = ::textheight(m_header.c_str());
	//格子的宽高
	m_gridW = m_tW + 10;
	m_gridH = m_tH + 10;
	//表格的宽高
	m_w = m_gridW * m_cols;
	m_h = m_gridH * (m_rows + 1);
}

void Table::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();//插入完数据再更新
}

void Table::show()
{
	drawTableGrid();
	drawHeader();
	drawTableData();
}

void Table::drawTableGrid()
{
	//确定表格多少行多少列
	setlinecolor(BLACK);
	//画横线
	for (size_t i = 0;i < m_rows + 1;i++)//横线数比行数加一
	{
		line(m_x, m_y + i * m_gridH, m_x + m_cols * m_gridW, m_y + i * m_gridH);
	}
	//画竖线
	for (size_t i = 0;i < m_cols + 1;i++)
	{
		line(m_x + i * m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	//绘制按钮
	if (m_maxPage > 0&& m_showPageBtn)//只有一页不用画
	{
		drawButton();
	}
}

void Table::drawTableData()
{
	int begPos = m_curPage * m_rows;//数据开始的位置
	int endPos = m_curPage * m_rows + m_rows;//数据结束的位置
	if (m_curPage == m_maxPage)//防止越界
	{//如果是最后一页，只遍历剩余数据
		endPos = m_curPage * m_rows + m_extraPage;
	}
	for (size_t i = begPos, r=0;i <endPos;i++, r++)//行
	{
		const auto& line_data = split(m_datas[i]);
		for (size_t k= 0;k < line_data.size();k++)//列
		{
			int tx = m_x + k * m_gridW + (m_gridW - ::textwidth(line_data[k].c_str())) / 2;
			int ty = m_y + r * m_gridH + 10;
			settextstyle(14, 0, "宋体");
			outtextxy(tx, ty, line_data[k].c_str());
		}
	}
}

void Table::drawButton()
{
	//提高效率，保证在程序运行的期间只挪动一次，空间换时间
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

	//页码提示
	char str[30] = {0};
	sprintf_s(str, "第%d页/共%d页", m_curPage + 1, m_maxPage + 1);
	settextstyle(20, 0, "黑体");
	outtextxy(m_lastBtn->x() + m_lastBtn->width() + 100, m_lastBtn->y(), str);
}

void Table::drawHeader()
{
	setlinestyle(PS_SOLID, 2);
	::rectangle(m_x, m_y - 30, m_x + m_w, m_y);
	//画竖线
	for (size_t i = 0;i < m_cols;i++)
	{
		line(m_x + i * m_gridW, m_y - 30, m_x + i * m_gridW, m_y);
	}
	//setlinestyle(PS_SOLID, 1);//还原，只让表头是粗的

	//分割表头数据
	auto headers = split(m_header);
	//std::cout << headers.size() << std::endl;
	for (size_t i=0;i<headers.size();i++)
	{
			int spaceH = (m_gridW - ::textwidth(headers[i].c_str())) / 2;//水平间距
			int spaceV = (30 - ::textheight(headers[i].c_str())) / 2;//垂直间距
			outtextxy(m_x + i * m_gridW + spaceH, m_y - m_gridH + spaceV, headers[i].c_str());
	}
}

const std::vector<std::string> Table::split(std::string str, char separator)
{
	std::vector<std::string> res;//保存结果
	
	for (size_t pos = 0; ; ) {  // 无限循环，手动控制退出
		pos = str.find(separator);  // 找分隔符位置
		std::string substr = str.substr(0, pos);  // 截取当前字段

		// 新增：过滤空字段（直接跳过）
		if (!substr.empty()) {
			res.push_back(substr);
		}

		// 已分割完毕，退出循环
		if (pos == std::string::npos) {
			break;
		}
		// 用 substr 截取剩余部分（避免越界）
		str = str.substr(pos + 1);  //! 注意这里直接用 std::string 操作
	}
	//for (size_t pos = 0;pos != std::string::npos; )
	//{
	//	//查找指定分割字符的位置
	//	pos = str.find(separator);//传进来的字符串str中查找\t
	//	//取出字符串 0-pos
	//	res.push_back(str.substr(0, pos));
	//	//把剩下的字符串保存到str
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
	if (m_rows >= m_datas.size())//只有一页，一页处理
	{
		m_maxPage = 0;//从0开始
		m_extraPage = m_datas.size();
	}
	else
	{
		m_maxPage = m_datas.size() / m_rows;
		m_extraPage = m_datas.size() % m_rows;
	}
	
	
}

void Table::eventLoop(const ExMessage& msg)//表格组件把收到的消息传给四个导航按钮
{
		m_prevBtn->eventLoop(msg);
		m_nextBtn->eventLoop(msg);
		m_firstBtn->eventLoop(msg);
		m_lastBtn->eventLoop(msg);
		//处理按钮点击事件
		if (m_prevBtn->isClicked())
		{
			if (m_curPage != 0)//才能上一页
			{
				m_curPage--;
			}
		}
		if (m_nextBtn->isClicked())
		{
			if (m_curPage != m_maxPage)//没有到最大页
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
