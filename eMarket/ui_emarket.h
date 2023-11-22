/********************************************************************************
** Form generated from reading UI file 'emarket.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
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
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QPushButton *newUpoadPushButton;
    QTableView *tableView;
    QSpinBox *newCountSpinBox;
    QComboBox *comboBox;
    QLineEdit *lineEdit_2;
    QPushButton *newPutinStorePushButton;
    QPushButton *newClearancePushButton;
    QWidget *page4;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *eMarket)
    {
        if (eMarket->objectName().isEmpty())
            eMarket->setObjectName(QStringLiteral("eMarket"));
        eMarket->resize(800, 489);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        eMarket->setFont(font);
        centralWidget = new QWidget(eMarket);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 781, 410));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label = new QLabel(page_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 781, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font1.setPointSize(18);
        label->setFont(font1);
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        toolBox = new QToolBox(page_2);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(0, 30, 781, 381));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font2.setBold(true);
        font2.setWeight(75);
        toolBox->setFont(font2);
        toolBox->setFrameShape(QFrame::WinPanel);
        page3 = new QWidget();
        page3->setObjectName(QStringLiteral("page3"));
        page3->setEnabled(true);
        page3->setGeometry(QRect(0, 0, 777, 325));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        page3->setFont(font3);
        newPictrueLabel = new QLabel(page3);
        newPictrueLabel->setObjectName(QStringLiteral("newPictrueLabel"));
        newPictrueLabel->setGeometry(QRect(80, 150, 151, 151));
        newPictrueLabel->setFrameShape(QFrame::Box);
        newPictrueLabel->setFrameShadow(QFrame::Sunken);
        newPictrueLabel->setMidLineWidth(0);
        newPictrueLabel->setScaledContents(true);
        lineEdit = new QLineEdit(page3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(40, 50, 181, 20));
        lineEdit_3 = new QLineEdit(page3);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(160, 80, 61, 20));
        newUpoadPushButton = new QPushButton(page3);
        newUpoadPushButton->setObjectName(QStringLiteral("newUpoadPushButton"));
        newUpoadPushButton->setGeometry(QRect(164, 130, 61, 23));
        tableView = new QTableView(page3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(240, 0, 441, 311));
        tableView->horizontalHeader()->setDefaultSectionSize(120);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        newCountSpinBox = new QSpinBox(page3);
        newCountSpinBox->setObjectName(QStringLiteral("newCountSpinBox"));
        newCountSpinBox->setGeometry(QRect(40, 110, 42, 22));
        newCountSpinBox->setAlignment(Qt::AlignCenter);
        newCountSpinBox->setValue(1);
        comboBox = new QComboBox(page3);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(40, 20, 69, 22));
        lineEdit_2 = new QLineEdit(page3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(40, 80, 51, 20));
        newPutinStorePushButton = new QPushButton(page3);
        newPutinStorePushButton->setObjectName(QStringLiteral("newPutinStorePushButton"));
        newPutinStorePushButton->setGeometry(QRect(20, 250, 51, 23));
        newClearancePushButton = new QPushButton(page3);
        newClearancePushButton->setObjectName(QStringLiteral("newClearancePushButton"));
        newClearancePushButton->setGeometry(QRect(20, 280, 51, 23));
        toolBox->addItem(page3, QStringLiteral("Page 1"));
        page4 = new QWidget();
        page4->setObjectName(QStringLiteral("page4"));
        page4->setGeometry(QRect(0, 0, 777, 325));
        comboBox_2 = new QComboBox(page4);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(50, 20, 69, 22));
        comboBox_3 = new QComboBox(page4);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(50, 60, 211, 22));
        label_3 = new QLabel(page4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 100, 71, 21));
        label_3->setFrameShape(QFrame::Box);
        label_3->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(page4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 170, 151, 151));
        QFont font4;
        font4.setStyleStrategy(QFont::PreferDefault);
        label_5->setFont(font4);
        label_5->setFrameShape(QFrame::Box);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setScaledContents(true);
        spinBox = new QSpinBox(page4);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(50, 140, 51, 21));
        spinBox->setAlignment(Qt::AlignCenter);
        spinBox->setValue(1);
        pushButton = new QPushButton(page4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(180, 240, 75, 23));
        pushButton_2 = new QPushButton(page4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(180, 280, 75, 23));
        listWidget = new QListWidget(page4);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(290, 0, 441, 311));
        label_6 = new QLabel(page4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 100, 71, 21));
        label_6->setFrameShape(QFrame::Box);
        label_6->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(page4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(190, 140, 71, 21));
        label_7->setFrameShape(QFrame::Box);
        label_7->setFrameShadow(QFrame::Sunken);
        toolBox->addItem(page4, QStringLiteral("Page 2"));
        stackedWidget->addWidget(page_2);
        eMarket->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(eMarket);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        eMarket->setMenuBar(menuBar);
        mainToolBar = new QToolBar(eMarket);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        eMarket->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(eMarket);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        eMarket->setStatusBar(statusBar);

        retranslateUi(eMarket);

        stackedWidget->setCurrentIndex(1);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(eMarket);
    } // setupUi

    void retranslateUi(QMainWindow *eMarket)
    {
        eMarket->setWindowTitle(QApplication::translate("eMarket", "eMarket", nullptr));
        label->setText(QApplication::translate("eMarket", "\345\225\206\345\223\201\347\256\241\347\220\206", nullptr));
        newPictrueLabel->setText(QString());
        newUpoadPushButton->setText(QApplication::translate("eMarket", "\344\270\212 \344\274\240...", nullptr));
        newPutinStorePushButton->setText(QApplication::translate("eMarket", "\345\205\245 \345\272\223", nullptr));
        newClearancePushButton->setText(QApplication::translate("eMarket", "\346\270\205 \344\273\223", nullptr));
        toolBox->setItemText(toolBox->indexOf(page3), QApplication::translate("eMarket", "Page 1", nullptr));
        label_3->setText(QString());
        label_5->setText(QString());
        pushButton->setText(QApplication::translate("eMarket", "\345\207\272 \345\224\256", nullptr));
        pushButton_2->setText(QApplication::translate("eMarket", "\344\270\213 \345\215\225", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page4), QApplication::translate("eMarket", "Page 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class eMarket: public Ui_eMarket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMARKET_H
