#include "mainwindow.h"
#include "picView/picview.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QDir>

static void emptyJsonObject(QJsonObject& obj){
    if(obj.size()>0){
        QJsonObject::iterator it;
        do{
            it = obj.erase(obj.begin());
        }while(it != obj.end());
    }
}


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  tabW = new QTabWidget(this);
  tabW->setTabsClosable(false);
  setCentralWidget(tabW);
  QFile propertiesFile;
  propertiesFile.setFileName("../raspPicViewer/properties.json");
  if(!propertiesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
    qWarning()<<"Could not open properties file.";
    return;
  }
  QByteArray val = propertiesFile.readAll();
  QJsonDocument doc(QJsonDocument::fromJson(val));
  propertiesFile.close();
  QJsonObject root = doc.object();
  if(root.contains("Tabs")){
    QJsonArray tabs = root["Tabs"].toArray();
    int tabNum = tabs.size();
    qWarning()<<tabNum;
    QJsonObject tabObj;
    for(int j = 0; j < tabNum; ++j){
      qWarning()<<j;
      emptyJsonObject(tabObj);
      tabObj = tabs.at(j).toObject();
      if(tabObj.contains("type") && tabObj.contains("name")){
        QString str(tabObj["type"].toString());
        if(str == "picView"){
          if(tabObj.contains("location")){
            picView* cur = new picView(this);
            tabW->addTab(cur,tabObj["name"].toString());
          }else {
            qWarning()<<"Could not read picView";
          }
        }else if(str == "webView"){

            if(tabObj.contains("url")){
              picView* cur = new picView(this);
              tabW->addTab(cur,tabObj["name"].toString());
            }else {
              qWarning()<<"Could not read webView";
            }

        }else{
          qWarning()<<"Could not read JsonObject at Array Location "<<j;
        }
      }else{
        qWarning()<<"Could not read JsonObject at Array Location "<<j;
      }
    }
  }else {


  }




  tabW->show();
}

MainWindow::~MainWindow()
{

}
