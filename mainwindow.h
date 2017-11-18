#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "connectiontabwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void setSerialConnected(bool connected);
	void appendRawData(QString line);
	void appendProcessedData(QString line);

signals:
	void connectSerialPort(QString portName);

private slots:
	void onConnectSerialButtonClicked(QString portName);

private:
	QTabWidget* tabWidget;
	QTextEdit* rawDataTextEdit;
	QTextEdit* processedDataTextEdit;
	ConnectionTabWidget* connectionTabWidget;

};

#endif // MAINWINDOW_H
