#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    //db = QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName("localhost");
    //db.setUserName("root");
    //db.setPassword("sas7mhs");
    //db.setDatabaseName("default");
    //db.setDatabaseName("/data/data/com.minhazulhaque.android.technologybasic/technologybasic.db");

    QString dbfilepath_data = "/data/data/com.minhazulhaque.android.technologybasic/files/technologybasic.db";
    QString dbfilepath_sdcard = "/mnt/sdcard/technologybasic.db";

    if(QFile(dbfilepath_data).exists())
        db.setDatabaseName(dbfilepath_data);
    else if(QFile(dbfilepath_sdcard).exists())
            db.setDatabaseName(dbfilepath_sdcard);
    else
    {
        QString dbfilepath_custom = QFileDialog::getOpenFileName(this,
                                 "Select database path",
                                 "/mnt/");
        db.setDatabaseName(dbfilepath_custom);
    }


    if(db.open())
    {
        QSqlQuery query("SELECT `title` from `tb_terms`");
        while (query.next())
            titles << query.value(0).toString();

        for(int i=0;i<titles.size();i++)
            ui->termlist->addItem(titles.at(i));

        // Select term
        connect(ui->termlist, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(termSelected(QListWidgetItem*)));

        // Exit button
        //connect(ui->bExit, SIGNAL(clicked()), this, SLOT(process()));
        connect(ui->bExit, SIGNAL(clicked()), qApp, SLOT(quit()));

        // Search
        connect(ui->searchbox, SIGNAL(textChanged(QString)), this, SLOT(search(QString)));

       // Hide list
        connect(ui->bHide, SIGNAL(toggled(bool)), this, SLOT(hideList(bool)));

        //showFullScreen();
        showMaximized();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Could not connect to database");
        qApp->quit();
    }

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::termSelected(QListWidgetItem *termtitle)
{
    QString querytext = QString("SELECT `details` FROM `tb_terms` WHERE `title` = '%1'")
            .arg(termtitle->text());

    QSqlQuery query(querytext);
    query.next();
    QString details = query.value(0).toString();
    ui->termdetails->setText(details);

//    querytext = QString("UPDATE `tb_terms` SET `details`='%1' WHERE `title`='%2'")
//            .arg(ui->termdetails->toPlainText())
//            .arg(termtitle->text());

//    query.exec(querytext);
//    query.next();

    //qDebug() << querytext; // query.value(0).toString();


}

void MainWindow::search(const QString &text)
{
    QRegExp filter(text,Qt::CaseInsensitive,QRegExp::Wildcard);
    ui->termlist->clear();
    ui->termlist->addItems(titles.filter(filter));
}

void MainWindow::process()
{
    qApp->exit();
}

void MainWindow::hideList(bool visible)
{
    if(visible)
    {
        ui->bHide->setText("Show List");
        ui->searchbox->hide();
        ui->termlist->hide();
    }
    else
    {
        ui->bHide->setText("Hide List");
        ui->searchbox->show();
        ui->termlist->show();
    }
}
