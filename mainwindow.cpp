#include "mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	tabWidget = new QTabWidget;
	rawDataTextEdit = new QTextEdit;
	processedDataTextEdit = new QTextEdit;
	connectionTabWidget = new ConnectionTabWidget;

	tabWidget->addTab(connectionTabWidget, "Connect");
	tabWidget->addTab(rawDataTextEdit, "Raw data");
	tabWidget->addTab(processedDataTextEdit, "Processed data");

	this->setCentralWidget(tabWidget);
	this->setGeometry(100, 100, 640, 480);

	connectionTabWidget->setSerialConnected(false);

	connect(connectionTabWidget, SIGNAL(connectButtonClicked(QString)), this, SLOT(onConnectSerialButtonClicked(QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setSerialConnected(bool connected)
{
	connectionTabWidget->setSerialConnected(connected);
}

void MainWindow::appendRawData(QString line)
{
	rawDataTextEdit->append(line);
}

void MainWindow::appendProcessedData(QString line)
{
	processedDataTextEdit->append(line);
}

void MainWindow::onConnectSerialButtonClicked(QString portName)
{
	emit connectSerialPort(portName);
}
