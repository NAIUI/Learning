#ifndef EMARKET_H
#define EMARKET_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class eMarket;
}

class eMarket : public QMainWindow
{
    Q_OBJECT

public:
    explicit eMarket(QWidget *parent = nullptr);
    ~eMarket();

private:
    Ui::eMarket *ui;
};

#endif // EMARKET_H
