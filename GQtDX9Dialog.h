#pragma once

#include <QMainWindow>
#include "ui_GQtDX9Dialog.h"

class GQtDX9Dialog : public QMainWindow
{
	Q_OBJECT

public:
	GQtDX9Dialog(QWidget *parent = Q_NULLPTR);
	~GQtDX9Dialog();

private:
	Ui::GQtDX9Dialog ui;
};
