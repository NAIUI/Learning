#include "emarket.h"
#include "ui_emarket.h"

eMarket::eMarket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::eMarket)
{
    ui->setupUi(this);
    ui->toolBox->setItemText(0,"新品入库");
    ui->toolBox->setItemText(1,"预售订单");
    initMainWindow();
}

eMarket::~eMarket()
{
    delete ui;
}

void eMarket::initMainWindow()
{
    ui->stackedWidget->setCurrentIndex(1);      // 第二页商品管理页
    ui->toolBox->setCurrentIndex(0);            // 第一页新品入库页

    QSqlQueryModel *categoryModel = new QSqlQueryModel(this);   // 商品类别模型数据
    categoryModel->setQuery("select Name from category");
    ui->newCategoryComboBox->setModel(categoryModel);                      // 商品类别列表加载

    commodity_model = new QSqlTableModel(this);
    commodity_model->setTable("commodity_inf");
    commodity_model->select();
    ui->commodityTableView->setModel(commodity_model);       // 库存商品记录数据网格信息加载（新品入库）

    ui->preCategoryComboBox->setModel(categoryModel);        // 商品类别列表加载（预售订单）
    loadPreCommodity();             // 在预售订单页加载商品信息

    myMemberID = "b02020622";
    myOrdered = false;              // 当前尚未有人购物
    myOrderID = 0;
    myPaySum = 0;                   // 当前订单累计需要付款总金额
    QListWidgetItem *title = new QListWidgetItem;
    title->setText(QString(" 当前订单【编号 %1 】").arg(myOrderID));
    title->setTextAlignment (Qt::AlignCenter);
}

void eMarket::loadPreCommodity()
{
    QSqlQueryModel *commodityNameModel = new QSqlQueryModel(this);
    QString str = QString("select Name from commodity where CategoryID"
                          "=(select CategoryID from category where Name ="
                          "'%1')").arg(ui->preCategoryComboBox->currentText());
    commodityNameModel->setQuery(str);
    ui->preNameComboBox->setModel(commodityNameModel);

    onPreNameComboBoxChange();
}

void eMarket::onPreNameComboBoxChange()
{
    QSqlQueryModel *preCommodityModel = new QSqlQueryModel(this);
    QString name = ui->preNameComboBox->currentText();         //当前选中商品
    QString str = QString("select OutputPrice,Amount,Picture from "
                          "commodity where Name = '" + name + "'");
    preCommodityModel->setQuery(str);   //从数据库中查找
    QModelIndex index;

    index = preCommodityModel->index(0,0);  // 单价

    ui->preOutputPriceLabel->setText(preCommodityModel->data(index).toString());

    index = preCommodityModel->index(0,1); //库存
    ui->preAmountPriceLabel->setText(preCommodityModel->data(index).toString());
    ui->preCountSpinBox->setMaximum(ui->preAmountPriceLabel->text().toInt());
    // 下面开始获取和展示照片
    QPixmap photo;
    index = preCommodityModel->index(0,2);
    photo.loadFromData(preCommodityModel->data(index).toByteArray(), "JPG");
    ui->prePictrueLabel->setPixmap(photo);
    // 计算总价
    ui->preTotalLabel->setText(QString::number(ui->preOutputPriceLabel->
                       text().toFloat() * ui->preCountSpinBox->value()));
}

void eMarket::on_commodityTableView_clicked(const QModelIndex &index)
{
    onTableSelectChange(1);
}

void eMarket::onTableSelectChange(int row)
{
    int r = 1; // 默认索引为1
    if(row != 0) r = ui->commodityTableView->currentIndex().row();
    QModelIndex index;
    index= commodity_model->index(r,0);     // 名称
    ui->newNameLineEdit->setText (commodity_model->data(index).toString());
    index= commodity_model->index(r,1);     // 进价
    ui->newInputLineEdit->setText(commodity_model->data(index).toString());
    index= commodity_model->index(r,2);     // 售价
    ui->newOutputLineEdit->setText(commodity_model->data(index).toString());
    showCommodityPhoto();
    // 商品样照
    QSqlQuery query;
    QString str = QString("select Name from emarket.category where CategoryID= (select "
                      "CategoryID from emarket.commodity where Name='%1')").arg (ui->newNameLineEdit->text());
    query.exec(str);
    query.next();
    ui->newCategoryComboBox->setCurrentText(query.value(0).toString()); // 实现类别联动
}

void eMarket::showCommodityPhoto()
{
    QPixmap photo;
    QModelIndex index;
    QSqlQueryModel *pictureModel = new QSqlQueryModel(this); // 商品样照模型数据
    QString name = ui->newNameLineEdit->text();
    QSqlDatabase loaclDB = QSqlDatabase::database();
//    qDebug() << "this" << loaclDB.database();
    pictureModel->setQuery("select Picture from emarket.commodity where Name='" + name + "'");
    index= pictureModel->index(0,0);
    photo.loadFromData(pictureModel->data(index).toByteArray());
    ui->newPictrueLabel->setPixmap(photo);
}

void eMarket::on_newPutinStorePushButton_clicked()
{
    QSqlQuery query;
    query.exec(QString("select CategoryID from category where Name='%1'")
               .arg(ui->newCategoryComboBox->currentText())); // (a)
    query.next();
    int categoryid = query.value(0).toInt();        // 将要入库的商品类别
    QString name = ui->newNameLineEdit->text();    // 商品名称
    float inputprice = ui->newInputLineEdit->text().toFloat(); // 进价
    float outputprice = ui->newOutputLineEdit->text().toFloat();  // 售价
    int count = ui->newCountSpinBox->value();   // 入库量
    query.exec(QString("insert into commodity(CategoryID, Name, Picture, InputPrice,"
                       "OutputPrice, Amount) values (%1,'%2', NULL, %3, %4, %5)").
                        arg(categoryid).arg(name).arg(inputprice).arg(outputprice).arg(count)); //(b)
    //  插入照片
    QByteArray picdata;
    QBuffer buffer(&picdata);
    buffer.open(QIODevice::WriteOnly);
    myPicimg.save(&buffer, "PNG");
    QVariant var(picdata);

    QString sqlstr = "update commodity set Picture=? where Name='" + name + "'";
    query.prepare(sqlstr);
    query.addBindValue(var);
    if (!query. exec())
    {
        QMessageBox::information(0, QObject::tr("提示"),"照片写入失败");
    }
    //  刷新网格信息
    commodity_model->setTable("commodity_inf");
    commodity_model->select();
    ui->commodityTableView->setModel(commodity_model);  //刷新数据网格("新品入库”页）
}

void eMarket::on_newUploadPushButton_clicked()
{
    QString picturename = QFileDialog::getOpenFileName(this, "选择商品图片 ",".",
                                                        "Image File(*.png *.jpg *.jpeg *.brnp)");
    if(picturename.isEmpty()) return;
    myPicimg.load(picturename);
    ui->newPictrueLabel->setPixmap(QPixmap::fromImage(myPicimg));
}

void eMarket::on_newClearancePushButton_clicked()
{
    QSqlQuery query;
    query.exec(QString("delete from commodity where Name='%1'").arg(ui->newNameLineEdit->text())); // 删除商品记录
    // 刷新界面
    ui->newNameLineEdit->setText("");
    ui->newInputLineEdit->setText("");
    ui->newOutputLineEdit->setText("");
    ui->newCountSpinBox->setValue(1);
    ui->newPictrueLabel->clear ();
    commodity_model->setTable("commodity_inf");
    commodity_model->select();
    ui->commodityTableView->setModel(commodity_model);
}

void eMarket::on_preSellPushButton_clicked()
{
    QSqlDatabase loaclDB = QSqlDatabase::database();
    QSqlQuery query;
    if (!myOrdered) // (a)
    {
        query.exec(QString("insert into orders(MemberID, PaySum, PayWay, OTime) "
                           "values('%1', NULL, NULL, NULL)") .arg(myMemberID));
        myOrdered = true;
        // qDebug() << query.lastError().text();
        query.exec(QString("select OrderID from orders where MemberID = '%1'").arg(myMemberID));
        query.next();
        myOrderID = query.value(0).toInt();
    }
    // 下面开始预售
    query.exec(QString("select CommodityID from commodity where Name='%1'").arg(ui->preNameComboBox->currentText()));
    query.next();
    int commodityid = query.value(0).toInt();        // 本次预售商品编号
    int count = ui->preCountSpinBox->value ();       // 预售量
    int amount = ui->preCountSpinBox->maximum()-count;   // 剩余库存量
    QSqlDatabase::database().transaction();         //  开始一个事务
    bool insOk =query.exec(QString("insert into orderitems(OrderID, CommodityID, Count) values(%1, %2, %3)").arg(myOrderID)
                           .arg(commodityid).arg(count));
    // 新增订单项
    bool uptOk =query.exec(QString("update commodity set Amount=%1 where CommodityID =%2").arg(amount).arg(commodityid));  //  更新库存
    if (insOk && uptOk)
    {
        QSqlDatabase::database().commit();
        onPreNameComboBoxChange();
        // 显示预售清单
        QString curtime = QTime::currentTime().toString("hh:mm:ss");
        QString curname = ui->preNameComboBox->currentText();
        QString curcount = QString::number(count, 10);
        QString curoutprice = ui->preOutputPriceLabel->text();
        QString curtotal = ui->preTotalLabel->text ();
        myPaySum += curtotal.toFloat();
        QString sell_record= curtime +" "+"售出: "+ curname + "\r\n数量: " + curcount + "; 单价: " + curoutprice + "¥; 总价： " + curtotal + "¥";
        QListWidgetItem *split= new QListWidgetItem;
        split->setText(" 一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.一.");
        split->setTextAlignment(Qt::AlignCenter);
        ui->sellListWidget->addItem(split);
        ui->sellListWidget->addItem(sell_record);
        ui->prePlaceOrderPushButton->setEnabled(true);
        QMessageBox::information(0, QObject::tr(" 提示"), "已加入订单！");
    }
    else
    {
        QSqlDatabase::database().rollback();
    }
}

void eMarket::on_prePlaceOrderPushButton_clicked()
{
    QSqlDatabase loaclDB = QSqlDatabase::database();
    QSqlQuery query;
    QString otime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QSqlDatabase::database().transaction();         // 开始一个事务
    bool ordOk = query.exec(QString("update orders set PaySum= %1, OTime='%2' where OrderID= %3")
                            .arg(myPaySum).arg (otime).arg (myOrderID)); //下订单
    bool uptOk = query.exec (QString ("update orderitems set Affirm=1, SendGoods=1 where OrderID= %1").arg (myOrderID));          // 确认发货
    if (ordOk && uptOk)
    {
        QSqlDatabase:: database().commit();
        ui->prePlaceOrderPushButton->setEnabled(false);
        // 显示下单记录
        QString order_record = "日期： " + otime + "\r\n 订单号： " + QString("%1").arg(myOrderID)
            + "\r\n 应付款总额 "+ QString("%1¥").arg(myPaySum) + "\r\n 下单成功!";
        QListWidgetItem *split= new QListWidgetItem;
        split->setText("*** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***");
        split->setTextAlignment(Qt::AlignCenter);
        ui->sellListWidget->addItem(split);
        ui->sellListWidget->addItem(order_record);
        myPaySum = 0;
        QMessageBox::information(0, QObject::tr(" 提示"), "下单成功！");
        commodity_model->setTable("commodi y_inf");
        commodity_model->select ();
        ui->commodityTableView->setModel(commodity_model);
        // 刷新数据网格("新品入库”页）
    }
    else
    {
        QSqlDatabase::database().rollback();
    }
}
