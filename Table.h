#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include <vector>
#include "PushButton.h"


class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void setRowCount(int row);
    void setColCount(int col);
    void setHeader(const std::string& header);//设置表头
    void insertData(const std::string& data);

	int rowCount()const { return m_rows; }
	int colCount()const { return m_cols; }

    void show();
    void drawTableGrid();
    void drawTableData();
    void drawButton();
    void drawHeader();
    const static std::vector<std::string> split(std::string str, char separator = '\t');//分割后的一行数据的存放
    
    void updatePage();

    void eventLoop(const ExMessage& msg);

	void clear() { m_datas.clear(); }//清空数据
private:
    int m_rows;
    int m_cols;

    //格子的宽度和高度
    int m_gridW;
    int m_gridH;

    //文字的宽度和高度
    int m_tW;
    int m_tH;
    std::string m_header;
    std::vector<std::string> m_datas;
private:    //分页处理
    int m_curPage;//当前页
    int m_maxPage;//最大页
    int m_extraPage;//如果不是整数页，最后一页剩余多少数据

    PushButton* m_prevBtn;//上一页
    PushButton* m_nextBtn;//下一页
    PushButton* m_firstBtn;//第一页
    PushButton* m_lastBtn;//结尾页
};

