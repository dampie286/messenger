/********************************************************************************
** Form generated from reading UI file 'guiclient.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUICLIENT_H
#define UI_GUICLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GUIClientClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nick;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *ipAD;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *port;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok;
    QPushButton *noOK;

    void setupUi(QDialog *GUIClientClass)
    {
        if (GUIClientClass->objectName().isEmpty())
            GUIClientClass->setObjectName(QString::fromUtf8("GUIClientClass"));
        GUIClientClass->resize(430, 166);
        GUIClientClass->setMinimumSize(QSize(430, 166));
        GUIClientClass->setMaximumSize(QSize(430, 166));
        verticalLayout = new QVBoxLayout(GUIClientClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(GUIClientClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        nick = new QLineEdit(GUIClientClass);
        nick->setObjectName(QString::fromUtf8("nick"));

        horizontalLayout->addWidget(nick);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(GUIClientClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        ipAD = new QLineEdit(GUIClientClass);
        ipAD->setObjectName(QString::fromUtf8("ipAD"));

        horizontalLayout_2->addWidget(ipAD);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(GUIClientClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        port = new QLineEdit(GUIClientClass);
        port->setObjectName(QString::fromUtf8("port"));

        horizontalLayout_3->addWidget(port);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        ok = new QPushButton(GUIClientClass);
        ok->setObjectName(QString::fromUtf8("ok"));

        horizontalLayout_4->addWidget(ok);

        noOK = new QPushButton(GUIClientClass);
        noOK->setObjectName(QString::fromUtf8("noOK"));

        horizontalLayout_4->addWidget(noOK);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(GUIClientClass);

        QMetaObject::connectSlotsByName(GUIClientClass);
    } // setupUi

    void retranslateUi(QDialog *GUIClientClass)
    {
        GUIClientClass->setWindowTitle(QApplication::translate("GUIClientClass", "GUIClient", nullptr));
        label->setText(QApplication::translate("GUIClientClass", "Nick:", nullptr));
        label_2->setText(QApplication::translate("GUIClientClass", "Ip Adress:", nullptr));
        label_3->setText(QApplication::translate("GUIClientClass", "Port:", nullptr));
        ok->setText(QApplication::translate("GUIClientClass", "Connect", nullptr));
        noOK->setText(QApplication::translate("GUIClientClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIClientClass: public Ui_GUIClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUICLIENT_H
