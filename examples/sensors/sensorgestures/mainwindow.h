// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <qsensorgesture.h>
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap <QString, QSensorGesture *> recognizerMap;

private slots:
    void detectedShake(const QString&);
    void onShake();

    void on_pushButton_clicked();

    void on_startPushButton_clicked();
    void on_stopPushButton_clicked();
};


QT_END_NAMESPACE

#endif // MAINWINDOW_H
