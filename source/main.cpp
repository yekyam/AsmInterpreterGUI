#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QSize>
#include <QTextEdit>

#include "commandLineEdit.h"
#include "RegisterDisplay.h"

//TODO: Feed input to actual thing, display input on left, and result on right

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QWidget window;

    QTextEdit* textBox = new QTextEdit(&window);
    QFrame* vertSeperator = new QFrame(&window);

    window.setFixedSize(800, 400);

    vertSeperator->setGeometry(410, 5, 1, 390);
    vertSeperator->setStyleSheet("background-color : gray");

    textBox->move(5, 5);
    textBox->setFixedSize(QSize(400, 360));
    textBox->setFrameShadow(QFrame::Sunken);
    textBox->setFrameShape(QFrame::Box);
    textBox->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    textBox->setStyleSheet("background-color : white");
    textBox->setReadOnly(true);


    commandLineEdit commandLine(5, 370, 400, 25, 50, "Enter a command!", textBox, &window);
    window.show();
    return a.exec();
}
