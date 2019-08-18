#include "task.h"
#include "ui_task.h"

#include <QInputDialog>
#include <QDebug>

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);

    setName(name);

    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->removeButton, &QPushButton::clicked, [this, name] {
        // lambda: [capture-list] (param)            -> return  { body      } (input_param)
        //         []             (QString taskName) -> QString { return... } (name)
        qDebug() << "Trying to remove " << [] (const QString &taskName) -> QString {
                                                  return "----" + taskName.toUpper();
                                              } (name);
        emit removed(this);
    });
    connect(ui->checkBox, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name) {
    ui->checkBox->setText(name);
}

QString Task::name() const {
    return ui->checkBox->text();
}

bool Task::isCompleted() const {
    return ui->checkBox->isChecked();
}

void Task::rename() {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Edit Task"), tr("Task Name:"), QLineEdit::Normal, this->name(), &ok);

    if (ok && !name.isEmpty()) {
        setName(name);
    }
}

void Task::checked(bool checked) {
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit statusChanged(this);
}
