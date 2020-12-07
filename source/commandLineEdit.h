#ifndef COMMANDLINEEDIT_H
#define COMMANDLINEEDIT_H

#include <QLineEdit>
#include <QSize>
#include <QString>
#include <QLabel>
#include <QTextEdit>

#include "AsmI.h"
#include "RegisterDisplay.h"

//TODO: Change QLabel to an actual QTextBox, then release!

class commandLineEdit : QLineEdit
{
    Q_OBJECT
public:
    commandLineEdit(int ax, int ay, int width, int height, int textLength, QString placeHolderText, QTextEdit* textBox = nullptr, QWidget* parent = nullptr);
    QLineEdit* m_lineEdit;
    QTextEdit* m_textBox;
    AsmI m_asmI;
    RegisterDisplay* m_regDispl;

public slots:
    void handleCommand();
    void updateRegisters();

};

#endif // COMMANDLINEEDIT_H
