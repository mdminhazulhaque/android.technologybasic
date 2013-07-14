#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QListWidget>
#include <QRegExp>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void termSelected(QListWidgetItem *termtitle);
    void search(const QString &text);
    void process();
    void hideList(bool visible);

private:
    Ui::MainWindow *ui;
    QStringList titles;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
