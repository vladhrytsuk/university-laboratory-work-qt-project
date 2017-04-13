#include <QApplication>
#include <QWidget>

#include <QLabel>
#include <QSpinBox>
#include <QPlainTextEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QSlider>

int main (int argc, char **argv)
{
QApplication app(argc, argv);
    QWidget widget(0);
    QGridLayout grid_layout;
    widget.setLayout(&grid_layout);
    QFormLayout form_layout;
    grid_layout.addLayout(&form_layout, 0, 0);

// Populating the upper left box with checkboxes
QSpinBox sb1, sb2, sb3;
QLabel sb_label1, sb_label2, sb_label3;
sb_label1.setText("Red");
sb_label2.setText("Green");
sb_label3.setText("Blue");
form_layout.addRow(&sb_label1, &sb1);
form_layout.addRow(&sb_label2, &sb2);
form_layout.addRow(&sb_label3, &sb3);
form_layout.setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
// Adding a text edit in the central area
QPlainTextEdit text_edit;
grid_layout.addWidget(&text_edit, 1, 2, 0, 1); // the edit stretches for two coloumns


widget.setWindowTitle("Лабораторная работа №2");
  widget.resize(500, 400);
 widget.show();

 return app.exec();

}
