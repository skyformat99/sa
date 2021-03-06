﻿#ifndef QWTPLOTITEMDATAMODEL_H
#define QWTPLOTITEMDATAMODEL_H
#include "SAChartGlobals.h"
#include <QAbstractTableModel>
#include <QList>
#include <algorithm>
#include <vector>
#include <qwt_plot_item.h>
#include <limits>
class SA_CHART_EXPORT QwtPlotItemDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QwtPlotItemDataModel(QObject *p = 0);
    void setQwtPlotItems(const QList<QwtPlotItem*>& items);
    void clear();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    void enableBackgroundColor(bool enable, int alpha = 30);

    static double nan();

protected:
    //获取item的最大行数
    virtual int calcItemDataRowCount(QwtPlotItem* item);
    virtual int calcItemDataColumnCount(QwtPlotItem* item);
    virtual double getItemData(int row,int col) const;
    //获取绘图数据维度的描述
    virtual QString getItemDimDescribe(QwtPlotItem* item,int index) const;
private:
    //更新最大行数
    void updateMaxRow();
    void updateColumnCount();
    void updateItemColor();

    QwtPlotItem* getItemFromCol(int col, int *dataColumnDim = nullptr) const;
    QString getItemNameFromCol(int col) const;

public:
    QColor getItemColor(QwtPlotItem* item) const;
    int getItemRowCount(QwtPlotItem* item) const;
private:
    QList<QwtPlotItem*> m_items;
    QMap<QwtPlotItem*,int> m_itemsRowCount;
    QMap<QwtPlotItem*,QColor> m_itemsColor;///< 记录item的颜色，以免频繁读取
    QMap<QwtPlotItem*,int> m_itemsColumnStartIndex;///< 记录数据开始的那一列的索引
    int m_rowCount;
    bool m_enableBkColor;///< 是否允许背景色
    int m_bkAlpha;///< 背景透明度
    QMap<int,QPair<QwtPlotItem*,int> > m_columnMap;
};

#endif // QWTPLOTITEMDATAMODEL_H
