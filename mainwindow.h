#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "linked_list.h"
#include "QPixmap"
#include "image.h"
#include "bst.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_prev_clicked();

    void on_button_next_clicked();

    void on_pushback_clicked();

    void on_pushfront_clicked();

    void on_save_clicked();

    void on_Delete_clicked();

    void on_Reserva_clicked();

    void on_Search_name_clicked();

private:
    Ui::MainWindow *ui;

    linked_list<Image> li;
    bst<Image> bst_li;
    linked_list<Image>::iterator it_p;
    QPixmap pixmap;
    int n_link;
};

#endif // MAINWINDOW_H
