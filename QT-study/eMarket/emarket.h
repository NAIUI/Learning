#ifndef EMARKET_H
#define EMARKET_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QListWidget>
#include <QBuffer>
#include <QFileDialog>
#include <QTime>

namespace Ui {
class eMarket;
}

class eMarket : public QMainWindow
{
    Q_OBJECT

public:
    explicit eMarket(QWidget *parent = nullptr);
    ~eMarket();
    void initMainWindow();              // 界面初始化
    void loadPreCommodity();            // 加载预售订单页商品名称列表
    void onPreNameComboBoxChange();     // 预售订单页商品与表单联动;
    void onTableSelectChange(int row);  // 商品信息数据网格与表单联动
    void showCommodityPhoto();          // 显示商品样照

private slots:
    void on_commodityTableView_clicked(const QModelIndex &index);     // 商品信息数据网格单击事件槽
//    void on_preCategoryComboBox_currentindexChanged(int index);     // 类别与商品名列表联动信息槽
//    void on_preNameComboBox_currentindexChanged(int index);         // 改选商品名信息槽
//    void on_preCountSpinBox_valueChanged(int argl);                 // 售出商品数改变信息槽
    void on_preSellPushButton_clicked ();                            // "出售”按钮单击事件
    void on_prePlaceOrderPushButton_clicked();                  // " 下单”按钮单击事件
    void on_newUploadPushButton_clicked ();                         // "上传．．．”按钮单击事件槽
    void on_newPutinStorePushButton_clicked();                        // "入库"按钮单击事件槽
    void on_newClearancePushButton_clicked();                        // "清仓”按钮单击事件槽


private:
    Ui::eMarket *ui;

    QSqlTableModel *commodity_model;        // 访问数据库商品信息视图的模型
    QImage myPicimg;                        // 保存商品样照（界面显示）
    QString myMemberID;                     // 会员账号
    bool myOrdered;                         // 是否正在购买（订单己写入数据库）
    int myOrderID;                          // 订单编号
    float myPaySum;                         // 当前订单累计需要付款的总金额
};

#endif // EMARKET_H
