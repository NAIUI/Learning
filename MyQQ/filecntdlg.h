#ifndef FILECNTDLG_H
#define FILECNTDLG_H

#include <QDialog>

namespace Ui {
class FileCntDlg;
}

class FileCntDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FileCntDlg(QWidget *parent = nullptr);
    ~FileCntDlg();

private:
    Ui::FileCntDlg *ui;
};

#endif // FILECNTDLG_H
