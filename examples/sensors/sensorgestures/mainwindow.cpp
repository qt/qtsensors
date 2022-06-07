// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtCore/QDebug>
#include <QtWidgets/QTreeWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qsensorgesture.h>
#include <qsensorgesturemanager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //! [0]

    QSensorGestureManager manager;

    for (const QString &gesture : manager.gestureIds()) {

        QTreeWidgetItem *gestureId = new QTreeWidgetItem(ui->treeWidget);
        QStringList recognizerSignals =  manager.recognizerSignals(gesture);
        gestureId->setText(0,gesture);

        for (int i = 0; i < recognizerSignals.count(); i++) {
            QTreeWidgetItem *oneSignal = new QTreeWidgetItem(gestureId);
            oneSignal->setText(0,recognizerSignals.at(i));
        }
        ui->treeWidget->insertTopLevelItem(0,gestureId);
    }
    //! [0]


    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::detectedShake(const QString &name)
{
    QString str = "<font size=+2><B>"+name+"</b></font><br>";
    ui->textEdit->insertHtml(str);
    ui->textEdit->ensureCursorVisible();
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::onShake()
{
    QString str = "<font size=+2><B>onShake()</b></font><br>";
    ui->textEdit->insertHtml(str);
    ui->textEdit->ensureCursorVisible();
}

void MainWindow::on_startPushButton_clicked()
{
    if (ui->treeWidget->currentItem() == 0)
            return;
    QString currentRecognizer;

    if (ui->treeWidget->currentItem()->childCount() == 0) {
        currentRecognizer = ui->treeWidget->currentItem()->parent()->text(0);
    } else {
        currentRecognizer = ui->treeWidget->currentItem()->text(0);
    }

    if (recognizerMap.contains(currentRecognizer))
        return;
    //! [1]
    QSensorGestureManager manager;
    QSensorGesture *thisGesture = new QSensorGesture(QStringList() << currentRecognizer, this);

    if (currentRecognizer.contains("QtSensors.shake")) {
        connect(thisGesture,SIGNAL(shake()),
                this,SLOT(onShake()));
    }

    connect(thisGesture,SIGNAL(detected(QString)),
            this,SLOT(detectedShake(QString)));
    thisGesture->startDetection();

    //! [1]

    recognizerMap.insert(currentRecognizer,thisGesture);

    QString str = QString("<font size=+2><B>Started %1</b></font><br>").arg(currentRecognizer);
    ui->textEdit->insertHtml(str);
    ui->textEdit->ensureCursorVisible();
}

void MainWindow::on_stopPushButton_clicked()
{
    if (ui->treeWidget->currentItem() == 0)
            return;
    QString currentRecognizer;

    if (ui->treeWidget->currentItem()->childCount() == 0) {
        currentRecognizer = ui->treeWidget->currentItem()->parent()->text(0);
    } else {
        currentRecognizer = ui->treeWidget->currentItem()->text(0);
    }

    if (!recognizerMap.contains(currentRecognizer))
        return;
    //! [2]

        recognizerMap[currentRecognizer]->stopDetection();

        if (currentRecognizer == "QtSensors.shake") {
            disconnect(recognizerMap[currentRecognizer],SIGNAL(shake()),
                       this,SLOT(onShake()));
        }
        disconnect(recognizerMap[currentRecognizer],SIGNAL(detected(QString)),
                   this,SLOT(detectedShake(QString)));
        //! [2]

        recognizerMap.take(currentRecognizer);

    QString str = QString("<font size=+2><B>Stopped %1</b></font><br>").arg(currentRecognizer);
    ui->textEdit->insertHtml(str);
    ui->textEdit->ensureCursorVisible();
}
