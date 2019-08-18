#include "mainwindow.h"
#include "ui_mainwindow.h"

void testMessageBox(QWidget *parent) {
    QMessageBox::question(parent, "Alert", "Just to let you know, something happened!");
    QMessageBox::warning(parent, "Alert", "Just to let you know, something happened!");
    QMessageBox::information(parent, "Alert", "Just to let you know, something happened!");
    QMessageBox::critical(parent, "Alert", "Just to let you know, something happened!");

    QMessageBox::question(parent, "Serious Question", "Am I an awesome guy?", QMessageBox::Ignore, QMessageBox::Yes);

    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Alert");
        msgBox.setText("Just to let you know, something happened!");
        msgBox.exec();
    }

    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Serious Question");
        msgBox.setText("Am I an awesome guy?");
        msgBox.addButton("Seriously Yes!", QMessageBox::YesRole);
        msgBox.addButton("Well no thanks", QMessageBox::NoRole);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();
    }

    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Serious Question");
        msgBox.setText("Am I an awesome guy?");
        msgBox.addButton("Seriously Yes!", QMessageBox::YesRole);
        msgBox.addButton("Well no thanks", QMessageBox::NoRole);
        QPixmap myIcon(":/images/icon.png");
        msgBox.setIconPixmap(myIcon);
        msgBox.exec();
    }

    if (QMessageBox::question(parent, "Question", "Some random question. Yes or no?") == QMessageBox::Yes) {
        QMessageBox::warning(parent, "Yes", "You have pressed Yes!");
    } else {
        QMessageBox::warning(parent, "No", "You have pressed No!");
    }

    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Serious Question");
        msgBox.setText("Am I an awesome guy?");
        QPushButton* yesButton = msgBox.addButton("Seriously Yes!",
        QMessageBox::YesRole);
        QPushButton* noButton = msgBox.addButton("Well no thanks",
        QMessageBox::NoRole);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();
        if (msgBox.clickedButton() == reinterpret_cast<QAbstractButton*>(yesButton)) {
            QMessageBox::warning(parent, "Yes", "Oh thanks! :)");
        } else if (msgBox.clickedButton() == reinterpret_cast<QAbstractButton*>(noButton)) {
            QMessageBox::warning(parent, "No", "Oh why... :(");
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("My test item");

    QListWidgetItem* listItem = new QListWidgetItem;
    listItem->setText("My Second Item");
    listItem->setData(100, 1000);
    ui->listWidget->addItem(listItem);

    qDebug() << listItem->data(100);

    QTreeWidgetItem* treeItem = new QTreeWidgetItem;
    treeItem->setText(0, "My Test Item");
    ui->treeWidget->addTopLevelItem(treeItem);

    QTreeWidgetItem* treeItem2 = new QTreeWidgetItem;
    treeItem2->setText(0, "My Test Subitem");
    treeItem->addChild(treeItem2);

    QTableWidgetItem* tableItem = new QTableWidgetItem;
    tableItem->setText("Testing1");
    ui->tableWidget->setItem(0, 0, tableItem);
    QTableWidgetItem* tableItem2 = new QTableWidgetItem;
    tableItem2->setText("Testing2");
    ui->tableWidget->setItem(1, 2, tableItem2);

//    testMessageBox(this);

    {
        QString fileName = QFileDialog::getOpenFileName(this);
        qDebug() << fileName;
    }

    {
        QString fileName = QFileDialog::getOpenFileName(this, "Your title", QDir::currentPath(), "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");
        qDebug() << fileName;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
