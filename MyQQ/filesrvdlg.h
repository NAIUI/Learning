#ifndef FILESRVDLG_H
#define FILESRVDLG_H

#include <QDialog>

namespace Ui {
class FileSrvDlg;
}

class FileSrvDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FileSrvDlg(QWidget *parent = nullptr);
    ~FileSrvDlg();
    void cntRefused();

private:
    Ui::FileSrvDlg *ui;
};

#endif // FILESRVDLG_H
