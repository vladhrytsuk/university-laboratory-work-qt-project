/********************************************************************************
** Form generated from reading UI file 'viewdescription.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWDESCRIPTION_H
#define UI_VIEWDESCRIPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewDescription
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *signButton;

    void setupUi(QWidget *ViewDescription)
    {
        if (ViewDescription->objectName().isEmpty())
            ViewDescription->setObjectName(QStringLiteral("ViewDescription"));
        ViewDescription->resize(529, 340);
        verticalLayout_2 = new QVBoxLayout(ViewDescription);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(ViewDescription);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(ViewDescription);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        backButton = new QPushButton(ViewDescription);
        backButton->setObjectName(QStringLiteral("backButton"));

        horizontalLayout->addWidget(backButton);

        signButton = new QPushButton(ViewDescription);
        signButton->setObjectName(QStringLiteral("signButton"));

        horizontalLayout->addWidget(signButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ViewDescription);

        QMetaObject::connectSlotsByName(ViewDescription);
    } // setupUi

    void retranslateUi(QWidget *ViewDescription)
    {
        ViewDescription->setWindowTitle(QApplication::translate("ViewDescription", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\272\321\203\321\200\321\201\320\260", 0));
        label->setText(QApplication::translate("ViewDescription", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\272\321\203\321\200\321\201\320\260", 0));
        backButton->setText(QApplication::translate("ViewDescription", "\320\235\320\260\320\267\320\260\320\264", 0));
        signButton->setText(QApplication::translate("ViewDescription", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214\321\201\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewDescription: public Ui_ViewDescription {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDESCRIPTION_H
