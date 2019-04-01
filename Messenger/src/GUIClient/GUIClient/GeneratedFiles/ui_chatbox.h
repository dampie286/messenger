/********************************************************************************
** Form generated from reading UI file 'chatbox.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOX_H
#define UI_CHATBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatBox
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *display;
    QHBoxLayout *horizontalLayout;
    QLineEdit *message;
    QPushButton *send;
    QPushButton *disc;

    void setupUi(QWidget *ChatBox)
    {
        if (ChatBox->objectName().isEmpty())
            ChatBox->setObjectName(QString::fromUtf8("ChatBox"));
        ChatBox->resize(682, 438);
        ChatBox->setMinimumSize(QSize(682, 438));
        ChatBox->setMaximumSize(QSize(682, 438));
        gridLayout = new QGridLayout(ChatBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        display = new QTextBrowser(ChatBox);
        display->setObjectName(QString::fromUtf8("display"));

        gridLayout->addWidget(display, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        message = new QLineEdit(ChatBox);
        message->setObjectName(QString::fromUtf8("message"));

        horizontalLayout->addWidget(message);

        send = new QPushButton(ChatBox);
        send->setObjectName(QString::fromUtf8("send"));

        horizontalLayout->addWidget(send);

        disc = new QPushButton(ChatBox);
        disc->setObjectName(QString::fromUtf8("disc"));

        horizontalLayout->addWidget(disc);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(ChatBox);

        QMetaObject::connectSlotsByName(ChatBox);
    } // setupUi

    void retranslateUi(QWidget *ChatBox)
    {
        ChatBox->setWindowTitle(QApplication::translate("ChatBox", "ChatBox", nullptr));
        send->setText(QApplication::translate("ChatBox", "Send", nullptr));
        disc->setText(QApplication::translate("ChatBox", "Closed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatBox: public Ui_ChatBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOX_H
