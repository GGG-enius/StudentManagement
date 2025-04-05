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
    void setHeader(const std::string& header);//���ñ�ͷ
    void insertData(const std::string& data);

	int rowCount()const { return m_rows; }
	int colCount()const { return m_cols; }

    void show();
    void drawTableGrid();
    void drawTableData();
    void drawButton();
    void drawHeader();
    const static std::vector<std::string> split(std::string str, char separator = '\t');//�ָ���һ�����ݵĴ��
    
    void updatePage();

    void eventLoop(const ExMessage& msg);

	void clear() { m_datas.clear(); }//�������
private:
    int m_rows;
    int m_cols;

    //���ӵĿ�Ⱥ͸߶�
    int m_gridW;
    int m_gridH;

    //���ֵĿ�Ⱥ͸߶�
    int m_tW;
    int m_tH;
    std::string m_header;
    std::vector<std::string> m_datas;
private:    //��ҳ����
    int m_curPage;//��ǰҳ
    int m_maxPage;//���ҳ
    int m_extraPage;//�����������ҳ�����һҳʣ���������

    PushButton* m_prevBtn;//��һҳ
    PushButton* m_nextBtn;//��һҳ
    PushButton* m_firstBtn;//��һҳ
    PushButton* m_lastBtn;//��βҳ
};

