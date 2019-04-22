#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
  Q_OBJECT
  QTabWidget* tabW;
  QWidget** tabs;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
};

#endif // MAINWINDOW_H
