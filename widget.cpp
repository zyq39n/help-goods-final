#include "widget.h"
#include "ui_widget.h"
#include "kindlist.h"
#include "objectlist.h"
#include "userlist.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QString>
#include <QListWidget>

ObjectList objectList;
UserList userList;
KindList kindList;
userNode currentUser;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //从文件中读入
    objectList.readTXT();
    userList.readTXT();
    kindList.readTXT();


    //登录页面
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->pushButton, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->pushButton_2, &QPushButton::clicked,this,&Widget::logIn);

    //注册页面
    connect(ui->pushButton_3, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->pushButton_4, &QPushButton::clicked,this,&Widget::regist);

    //主界面
    connect(ui->addObject, &QPushButton::clicked,this,[=](){  //添加物品
        ui->stackedWidget->setCurrentIndex(5);
        for (int i=0; i < kindList.length(); ++i)
        {
            QStringList list = kindList.visit(i);
            //qDebug() << list[0];
            ui->addObject1->addItem(list[0]);
        }
    });
    connect(ui->findObject, &QPushButton::clicked,this,[=](){  //查找物品
        ui->stackedWidget->setCurrentIndex(6);
        for (int i=0; i < kindList.length(); ++i)
        {
            QStringList list = kindList.visit(i);
            //qDebug() << list[0];
            ui->findObject1->addItem(list[0]);
        }
    });
    connect(ui->logOut, &QPushButton::clicked,this,[=](){  //登出
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->deleteObject, &QPushButton::clicked,this,[=](){  //删除物品
        ui->stackedWidget->setCurrentIndex(8);
        int *a = objectList.searchByOwner(currentUser.name);
        QString myObject;
        for (int i=0; i<objectList.length(); ++i)
        {
            if (a[i]) {
                myObject.append(objectList.visit(i).name);
                myObject.append(" ");
                myObject.append(objectList.visit(i).information);
                myObject.append(" ");
                myObject.append(objectList.visit(i).atb1);
                myObject.append(" ");
                myObject.append(objectList.visit(i).atb2);
                myObject.append(" ");
                myObject.append(objectList.visit(i).atb3);
                ui->listWidget_2->addItem(myObject);
                myObject.clear();
            }
        }
        delete []a;
    });
    connect(ui->addKind, &QPushButton::clicked,this,[=](){  //添加类型
        if (currentUser.authority < 2) QMessageBox::information(this,"提示","抱歉，您不是管理员");
        else ui->stackedWidget->setCurrentIndex(3);
    });
    connect(ui->modifyKind, &QPushButton::clicked,this,[=](){  //修改类型
        if (currentUser.authority < 2) QMessageBox::information(this,"提示","抱歉，您不是管理员");
        else {
            ui->stackedWidget->setCurrentIndex(4);
            for (int i=0; i < kindList.length(); ++i)
            {
                QStringList list = kindList.visit(i);
                //qDebug() << list[0];
                ui->modifyKind3->addItem(list[0]);
            }
        }
    });
    connect(ui->manegeUser, &QPushButton::clicked,this,[=](){  //管理用户
        if (currentUser.authority < 2) QMessageBox::information(this,"提示","抱歉，您不是管理员");
        else {
            ui->stackedWidget->setCurrentIndex(7);
            int *a = userList.searchByAuthority(0);
            QString registeringUser;
            for (int i=0; i < userList.length(); ++i)
            {
                if (a[i]) {
                    registeringUser.append(userList.visit(i).name);
                    registeringUser.append("  ");
                    registeringUser.append(userList.visit(i).phone);
                    registeringUser.append("  ");
                    registeringUser.append(userList.visit(i).mail);
                    registeringUser.append("  ");
                    registeringUser.append(userList.visit(i).adress);
                    ui->listWidget->addItem(registeringUser);
                    registeringUser.clear();
                }
            }
            delete []a;
        }
    });

    //添加类型页面
    connect(ui->addKind5, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        ui->addKind1->setText("");
        ui->addKind2->setText("");
        ui->addKind3->setText("");
        ui->addKind4->setText("");
    });
    connect(ui->addKind6, &QPushButton::clicked,this,[=](){
        QStringList list;
        list << ui->addKind1->text() << ui->addKind2->text()<< ui->addKind3->text()<< ui->addKind4->text();
        kindList.append(list);
        kindList.saveTXT();
        QMessageBox::information(this,"提示","添加新类型成功");
        ui->addKind1->setText("");
        ui->addKind2->setText("");
        ui->addKind3->setText("");
        ui->addKind4->setText("");
    });

    //修改类型页面
    connect(ui->modifyKind1, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        ui->modifyKind3->clear();
        ui->modifyKind4->setText("");
        ui->modifyKind5->setText("");
        ui->modifyKind6->setText("");
        ui->modifyKind7->setText("");
    });
    connect(ui->modifyKind2, &QPushButton::clicked,this,[=](){
        int i = ui->modifyKind3 ->currentIndex();
        kindList.remove(i);
        QStringList list;
        list << ui->modifyKind4->text() << ui->modifyKind5->text()<< ui->modifyKind6->text()<< ui->modifyKind7->text();
        kindList.insert(i,list);
        kindList.saveTXT();
        QMessageBox::information(this,"提示","修改类型成功");
        ui->modifyKind4->setText("");
        ui->modifyKind5->setText("");
        ui->modifyKind6->setText("");
        ui->modifyKind7->setText("");
    });

    //添加物品界面
    connect(ui->addObject2, &QPushButton::clicked,this,[=](){
        int i = ui->addObject1->currentIndex();
        QStringList list = kindList.visit(i);
        ui->atbName1->setText(list[1]);
        ui->atbName2->setText(list[2]);
        ui->atbName3->setText(list[3]);
    });
    connect(ui->addObject9, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        ui->addObject1->clear();
        ui->addObject3->setText("");
        ui->addObject4->setText("");
        ui->addObject5->setText("");
        ui->addObject6->setText("");
        ui->addObject7->setText("");
        ui->addObject8->setText("");
    });
    connect(ui->addObject10, &QPushButton::clicked,this,[=](){
        objectNode newObjct;
        newObjct.name = ui->addObject3->text();
        newObjct.information = ui->addObject4->text();
        newObjct.owner = currentUser.name;
        newObjct.atb1 = ui->addObject6->text();
        newObjct.atb2 = ui->addObject7->text();
        newObjct.atb3 = ui->addObject8->text();
        newObjct.rank = ui->addObject1->currentIndex();
        objectList.append(newObjct);
        objectList.saveTXT();
        currentUser.objectNum++;
        QMessageBox::information(this,"提示","添加物品成功");
        ui->addObject3->setText("");
        ui->addObject4->setText("");
        ui->addObject5->setText("");
        ui->addObject6->setText("");
        ui->addObject7->setText("");
        ui->addObject8->setText("");
    });

    //查找物品界面
    connect(ui->findObject3, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        ui->findObject1->clear();
        ui->findObject2->clear();
        ui->tableWidget->clear();
    });
    connect(ui->findObject4, &QPushButton::clicked,this,[=](){
        int rank = ui->findObject1->currentIndex();
        QStringList list = kindList.visit(rank);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"物品名称"<<"详细信息"<<list[1]<<list[2]<<list[3]<<"所有者"<<"联系方式");
        objectNode node;
        userNode owner;
        int j=0;
        for (int i=0; i < objectList.length(); ++i)
        {
            node = objectList.visit(i);
            if (node.rank != rank) continue;
            if ((node.name.indexOf(ui->findObject2->text()) != -1)||(node.information.indexOf(ui->findObject2->text()) != -1))
            {
                ui->tableWidget->insertRow(j);
                owner = userList.visit(userList.search(node.owner));
                ui->tableWidget->setItem(j,0,new QTableWidgetItem(node.name));
                ui->tableWidget->setItem(j,1,new QTableWidgetItem(node.information));
                ui->tableWidget->setItem(j,2,new QTableWidgetItem(node.atb1));
                ui->tableWidget->setItem(j,3,new QTableWidgetItem(node.atb2));
                ui->tableWidget->setItem(j,4,new QTableWidgetItem(node.atb3));
                ui->tableWidget->setItem(j,5,new QTableWidgetItem(node.owner));
                ui->tableWidget->setItem(j,6,new QTableWidgetItem(owner.phone));
                ++j;
            }
        }
    });

    //管理用户界面
    connect(ui->manegeUser1, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        ui->listWidget->clear();
    });
    connect(ui->manegeUser2, &QPushButton::clicked,this,[=](){
        QString str = ui->listWidget->currentItem()->text();
        int i =str.indexOf(" ");
        str = str.left(i);
        userList.addUser(str);
        ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
        delete ui->listWidget->currentItem();
        userList.saveTXT();
    });
    connect(ui->manegeUser3, &QPushButton::clicked,this,[=](){
        QString str = ui->listWidget->currentItem()->text();
        int i =str.indexOf(" ");
        str = str.left(i);
        userList.remove(userList.search(str));
        ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
        delete ui->listWidget->currentItem();
        userList.saveTXT();
    });

    //删除物品界面
    connect(ui->deleteObject1, &QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        ui->listWidget_2->clear();
    });
    connect(ui->deleteObject2, &QPushButton::clicked,this,[=](){
        QString str = ui->listWidget_2->currentItem()->text();
        QStringList list = str.split(" ");
        objectNode node;
        for (int i=0; i<objectList.length(); ++i)
        {
            node = objectList.visit(i);
            if ((list[0]==node.name)&&(list[1]==node.information)&&(list[2]==node.atb1)&&(list[3]==node.atb2)&&(list[4]==node.atb3))
            {
                objectList.remove(i);
                ui->listWidget_2->removeItemWidget(ui->listWidget_2->currentItem());
                delete ui->listWidget_2->currentItem();
                objectList.saveTXT();
            }
        }
    });


}

Widget::~Widget()
{
    delete ui;
}

void Widget::logIn()
{
    int i = userList.search(ui->lineEdit->text());
    if (i == -1) QMessageBox::critical(this,"错误","用户不存在");
    else {
        currentUser = userList.visit(i);
        if (currentUser.authority == 0) QMessageBox::information(this,"提示","请等待管理员审核");
        else if (currentUser.password != ui->lineEdit_2->text()) QMessageBox::critical(this,"错误","密码错误");
             else {
                   ui->stackedWidget->setCurrentIndex(2);
                   ui->lineEdit->setText("");
                   ui->lineEdit_2->setText("");
        }
    }
}

void Widget::regist()
{
    if (ui->lineEdit_5->text() != ui->lineEdit_4->text())  QMessageBox::critical(this,"错误","密码不一致");
    else {
        userNode newUser;
        newUser.name = ui->lineEdit_3->text();
        newUser.password = ui->lineEdit_4->text();
        newUser.adress = ui->lineEdit_6->text();
        newUser.phone = ui->lineEdit_7->text();
        newUser.mail = ui->lineEdit_8->text();
        newUser.authority = 0;
        newUser.objectNum = 0;
        userList.append(newUser);
        userList.saveTXT();
        QMessageBox::information(this,"提示","注册成功，请等待管理员审核");
    }
}
