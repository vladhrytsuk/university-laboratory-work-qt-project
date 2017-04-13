/********************************************************************************
** Form generated from reading UI file 'coursecatalog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSECATALOG_H
#define UI_COURSECATALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourseCatalog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *viewDescButton;

    void setupUi(QWidget *CourseCatalog)
    {
        if (CourseCatalog->objectName().isEmpty())
            CourseCatalog->setObjectName(QStringLiteral("CourseCatalog"));
        CourseCatalog->resize(379, 197);
        verticalLayout_2 = new QVBoxLayout(CourseCatalog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(CourseCatalog);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(CourseCatalog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        backButton = new QPushButton(CourseCatalog);
        backButton->setObjectName(QStringLiteral("backButton"));

        horizontalLayout->addWidget(backButton);

        viewDescButton = new QPushButton(CourseCatalog);
        viewDescButton->setObjectName(QStringLiteral("viewDescButton"));

        horizontalLayout->addWidget(viewDescButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(CourseCatalog);

        QMetaObject::connectSlotsByName(CourseCatalog);
    } // setupUi

    void retranslateUi(QWidget *CourseCatalog)
    {
        CourseCatalog->setWindowTitle(QApplication::translate("CourseCatalog", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263 \320\272\321\203\321\200\321\201\320\276\320\262", 0));
        label->setText(QApplication::translate("CourseCatalog", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263 \320\272\321\203\321\200\321\201\320\276\320\262", 0));
        backButton->setText(QApplication::translate("CourseCatalog", "\320\235\320\260\320\267\320\260\320\264", 0));
        viewDescButton->setText(QApplication::translate("CourseCatalog", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265", 0));
    } // retranslateUi

};

namespace Ui {
    class CourseCatalog: public Ui_CourseCatalog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSECATALOG_H
