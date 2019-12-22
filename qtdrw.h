#pragma once

#include <QtWidgets/QMainWindow>
#include "mainwindow.h"
#include "ui_qtdrw.h"

class qtdrw : public MainWindow
{
	Q_OBJECT

public:
	qtdrw(QWidget *parent = Q_NULLPTR);

private:
	Ui::qtdrwClass ui;
};
