/********************************************************************************
** Form generated from reading UI file 'emarket.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMARKET_H
#define UI_EMARKET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_eMarket
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QLabel *label;
    QToolBox *toolBox;
    QWidget *page3;
    QLabel *newPictrueLabel;
    QLineEdit *newNameLineEdit;
    QLineEdit *newOutputLineEdit;
    QPushButton *newUploadPushButton;
    QTableView *commodityTableView;
    QSpinBox *newCountSpinBox;
    QComboBox *newCategoryComboBox;
    QLineEdit *newInputLineEdit;
    QPushButton *newPutinStorePushButton;
    QPushButton *newClearancePushButton;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QWidget *page4;
    QComboBox *preCategoryComboBox;
    QComboBox *preNameComboBox;
    QLabel *preOutputPriceLabel;
    QLabel *prePictrueLabel;
    QSpinBox *preCountSpinBox;
    QPushButton *preSellPushButton;
    QPushButton *prePlaceOrderPushButton;
    QListWidget *sellListWidget;
    QLabel *preAmountPriceLabel;
    QLabel *preTotalLabel;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *eMarket)
    {
        if (eMarket->objectName().isEmpty())
            eMarket->setObjectName(QString::fromUtf8("eMarket"));
        eMarket->resize(800, 489);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        eMarket->setFont(font);
        centralWidget = new QWidget(eMarket);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 781, 410));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 781, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font1.setPointSize(18);
        label->setFont(font1);
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        toolBox = new QToolBox(page_2);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(0, 30, 781, 381));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font2.setBold(true);
        font2.setWeight(75);
        toolBox->setFont(font2);
        toolBox->setFrameShape(QFrame::WinPanel);
        page3 = new QWidget();
        page3->setObjectName(QString::fromUtf8("page3"));
        page3->setEnabled(true);
        page3->setGeometry(QRect(0, 0, 777, 325));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        page3->setFont(font3);
        newPictrueLabel = new QLabel(page3);
        newPictrueLabel->setObjectName(QString::fromUtf8("newPictrueLabel"));
        newPictrueLabel->setGeometry(QRect(80, 150, 151, 151));
        newPictrueLabel->setFrameShape(QFrame::Box);
        newPictrueLabel->setFrameShadow(QFrame::Sunken);
        newPictrueLabel->setMidLineWidth(0);
        newPictrueLabel->setScaledContents(true);
        newNameLineEdit = new QLineEdit(page3);
        newNameLineEdit->setObjectName(QString::fromUtf8("newNameLineEdit"));
        newNameLineEdit->setGeometry(QRect(40, 50, 181, 20));
        newOutputLineEdit = new QLineEdit(page3);
        newOutputLineEdit->setObjectName(QString::fromUtf8("newOutputLineEdit"));
        newOutputLineEdit->setGeometry(QRect(160, 80, 61, 20));
        newUploadPushButton = new QPushButton(page3);
        newUploadPushButton->setObjectName(QString::fromUtf8("newUploadPushButton"));
        newUploadPushButton->setGeometry(QRect(164, 130, 61, 23));
        commodityTableView = new QTableView(page3);
        commodityTableView->setObjectName(QString::fromUtf8("commodityTableView"));
        commodityTableView->setGeometry(QRect(240, 0, 441, 311));
        commodityTableView->horizontalHeader()->setDefaultSectionSize(120);
        commodityTableView->horizontalHeader()->setStretchLastSection(true);
        commodityTableView->verticalHeader()->setVisible(false);
        newCountSpinBox = new QSpinBox(page3);
        newCountSpinBox->setObjectName(QString::fromUtf8("newCountSpinBox"));
        newCountSpinBox->setGeometry(QRect(40, 110, 42, 22));
        newCountSpinBox->setAlignment(Qt::AlignCenter);
        newCountSpinBox->setValue(1);
        newCategoryComboBox = new QComboBox(page3);
        newCategoryComboBox->setObjectName(QString::fromUtf8("newCategoryComboBox"));
        newCategoryComboBox->setGeometry(QRect(40, 20, 69, 22));
        newInputLineEdit = new QLineEdit(page3);
        newInputLineEdit->setObjectName(QString::fromUtf8("newInputLineEdit"));
        newInputLineEdit->setGeometry(QRect(40, 80, 51, 20));
        newPutinStorePushButton = new QPushButton(page3);
        newPutinStorePushButton->setObjectName(QString::fromUtf8("newPutinStorePushButton"));
        newPutinStorePushButton->setGeometry(QRect(20, 250, 51, 23));
        newClearancePushButton = new QPushButton(page3);
        newClearancePushButton->setObjectName(QString::fromUtf8("newClearancePushButton"));
        newClearancePushButton->setGeometry(QRect(20, 280, 51, 23));
        label_8 = new QLabel(page3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 54, 12));
        label_8->setFont(font);
        label_9 = new QLabel(page3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 50, 54, 12));
        label_9->setFont(font);
        label_10 = new QLabel(page3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 80, 54, 12));
        label_10->setFont(font);
        label_11 = new QLabel(page3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(130, 80, 54, 12));
        label_11->setFont(font);
        label_12 = new QLabel(page3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 110, 54, 12));
        label_12->setFont(font);
        label_13 = new QLabel(page3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 170, 54, 12));
        label_13->setFont(font);
        toolBox->addItem(page3, QString::fromUtf8("Page 1"));
        page4 = new QWidget();
        page4->setObjectName(QString::fromUtf8("page4"));
        page4->setGeometry(QRect(0, 0, 777, 325));
        preCategoryComboBox = new QComboBox(page4);
        preCategoryComboBox->setObjectName(QString::fromUtf8("preCategoryComboBox"));
        preCategoryComboBox->setGeometry(QRect(50, 20, 69, 22));
        preNameComboBox = new QComboBox(page4);
        preNameComboBox->setObjectName(QString::fromUtf8("preNameComboBox"));
        preNameComboBox->setGeometry(QRect(50, 60, 211, 22));
        preOutputPriceLabel = new QLabel(page4);
        preOutputPriceLabel->setObjectName(QString::fromUtf8("preOutputPriceLabel"));
        preOutputPriceLabel->setGeometry(QRect(50, 100, 71, 21));
        preOutputPriceLabel->setFrameShape(QFrame::Box);
        preOutputPriceLabel->setFrameShadow(QFrame::Sunken);
        prePictrueLabel = new QLabel(page4);
        prePictrueLabel->setObjectName(QString::fromUtf8("prePictrueLabel"));
        prePictrueLabel->setGeometry(QRect(20, 170, 151, 151));
        QFont font4;
        font4.setStyleStrategy(QFont::PreferDefault);
        prePictrueLabel->setFont(font4);
        prePictrueLabel->setFrameShape(QFrame::Box);
        prePictrueLabel->setFrameShadow(QFrame::Sunken);
        prePictrueLabel->setScaledContents(true);
        preCountSpinBox = new QSpinBox(page4);
        preCountSpinBox->setObjectName(QString::fromUtf8("preCountSpinBox"));
        preCountSpinBox->setGeometry(QRect(50, 140, 51, 21));
        preCountSpinBox->setAlignment(Qt::AlignCenter);
        preCountSpinBox->setValue(1);
        preSellPushButton = new QPushButton(page4);
        preSellPushButton->setObjectName(QString::fromUtf8("preSellPushButton"));
        preSellPushButton->setGeometry(QRect(180, 240, 75, 23));
        prePlaceOrderPushButton = new QPushButton(page4);
        prePlaceOrderPushButton->setObjectName(QString::fromUtf8("prePlaceOrderPushButton"));
        prePlaceOrderPushButton->setEnabled(false);
        prePlaceOrderPushButton->setGeometry(QRect(180, 280, 75, 23));
        sellListWidget = new QListWidget(page4);
        sellListWidget->setObjectName(QString::fromUtf8("sellListWidget"));
        sellListWidget->setGeometry(QRect(300, 0, 441, 311));
        preAmountPriceLabel = new QLabel(page4);
        preAmountPriceLabel->setObjectName(QString::fromUtf8("preAmountPriceLabel"));
        preAmountPriceLabel->setGeometry(QRect(190, 100, 71, 21));
        preAmountPriceLabel->setFrameShape(QFrame::Box);
        preAmountPriceLabel->setFrameShadow(QFrame::Sunken);
        preTotalLabel = new QLabel(page4);
        preTotalLabel->setObjectName(QString::fromUtf8("preTotalLabel"));
        preTotalLabel->setGeometry(QRect(190, 140, 71, 21));
        preTotalLabel->setFrameShape(QFrame::Box);
        preTotalLabel->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(page4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 54, 12));
        label_3 = new QLabel(page4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 60, 54, 12));
        label_4 = new QLabel(page4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 100, 54, 12));
        label_5 = new QLabel(page4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 100, 54, 12));
        label_6 = new QLabel(page4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 140, 54, 12));
        label_7 = new QLabel(page4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(160, 140, 54, 12));
        toolBox->addItem(page4, QString::fromUtf8("Page 2"));
        stackedWidget->addWidget(page_2);
        eMarket->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(eMarket);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        eMarket->setMenuBar(menuBar);
        mainToolBar = new QToolBar(eMarket);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        eMarket->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(eMarket);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        eMarket->setStatusBar(statusBar);

        retranslateUi(eMarket);

        stackedWidget->setCurrentIndex(1);
        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(eMarket);
    } // setupUi

    void retranslateUi(QMainWindow *eMarket)
    {
        eMarket->setWindowTitle(QCoreApplication::translate("eMarket", "eMarket", nullptr));
        label->setText(QCoreApplication::translate("eMarket", "\345\225\206\345\223\201\347\256\241\347\220\206", nullptr));
        newPictrueLabel->setText(QString());
        newUploadPushButton->setText(QCoreApplication::translate("eMarket", "\344\270\212 \344\274\240...", nullptr));
        newPutinStorePushButton->setText(QCoreApplication::translate("eMarket", "\345\205\245 \345\272\223", nullptr));
        newClearancePushButton->setText(QCoreApplication::translate("eMarket", "\346\270\205 \344\273\223", nullptr));
        label_8->setText(QCoreApplication::translate("eMarket", "\347\261\273\345\210\253", nullptr));
        label_9->setText(QCoreApplication::translate("eMarket", "\345\220\215\347\247\260", nullptr));
        label_10->setText(QCoreApplication::translate("eMarket", "\350\277\233\344\273\267", nullptr));
        label_11->setText(QCoreApplication::translate("eMarket", "\345\224\256\344\273\267", nullptr));
        label_12->setText(QCoreApplication::translate("eMarket", "\346\225\260\351\207\217", nullptr));
        label_13->setText(QCoreApplication::translate("eMarket", "\345\225\206\345\223\201\346\240\267\347\205\247", nullptr));
        toolBox->setItemText(toolBox->indexOf(page3), QCoreApplication::translate("eMarket", "Page 1", nullptr));
        preOutputPriceLabel->setText(QString());
        prePictrueLabel->setText(QString());
        preSellPushButton->setText(QCoreApplication::translate("eMarket", "\345\207\272 \345\224\256", nullptr));
        prePlaceOrderPushButton->setText(QCoreApplication::translate("eMarket", "\344\270\213 \345\215\225", nullptr));
        preAmountPriceLabel->setText(QString());
        preTotalLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("eMarket", "\347\261\273\345\210\253", nullptr));
        label_3->setText(QCoreApplication::translate("eMarket", "\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("eMarket", "\345\215\225\344\273\267", nullptr));
        label_5->setText(QCoreApplication::translate("eMarket", "\345\272\223\345\255\230", nullptr));
        label_6->setText(QCoreApplication::translate("eMarket", "\346\225\260\351\207\217", nullptr));
        label_7->setText(QCoreApplication::translate("eMarket", "\346\200\273\344\273\267", nullptr));
        toolBox->setItemText(toolBox->indexOf(page4), QCoreApplication::translate("eMarket", "Page 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class eMarket: public Ui_eMarket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMARKET_H
