#include "commandLineEdit.h"

//lineEdit->move(5, 370);
//lineEdit->setFixedSize(QSize(400, 25));
//lineEdit->setMaxLength(50);
//lineEdit->setPlaceholderText("Enter a command");

commandLineEdit::commandLineEdit(int ax, int ay, int width, int height, int textLength, QString placeHolderText, QTextEdit* textBox, QWidget* parent)
{
    this->m_regDispl = new RegisterDisplay(parent);
    this->m_lineEdit = new QLineEdit(parent);
    this->m_lineEdit->move(ax, ay);
    this->m_lineEdit->setFixedSize(QSize(width, height));
    this->m_lineEdit->setMaxLength(textLength);
    this->m_lineEdit->setPlaceholderText(placeHolderText);

    this->m_textBox = textBox;

    QObject::connect(this->m_lineEdit, SIGNAL(returnPressed()), this, SLOT(handleCommand()));
}

void commandLineEdit::handleCommand()
{
    QString newText = this->m_lineEdit->text();
    QString messages = "";

    if (newText == "clear" || newText == "cls")
    {
        this->m_textBox->setHtml("");
        this->m_lineEdit->setText("");
        return;
    }
    if (!newText.isEmpty())
    {
        m_asmI.handleInput(newText.toStdString());
        messages = m_asmI.command();
        if (!messages.isEmpty())
        {
            QString colorHtml = "<font color=\"Red\">";
            QString endHtml = "</font><br>";
            messages = colorHtml += messages += endHtml;
        }
        else
        {
            messages = "";
        }
        newText += "<br>";
        this->m_textBox->insertHtml(newText += messages);
        this->m_lineEdit->setText("");
        updateRegisters();
    }

}

void commandLineEdit::updateRegisters()
{
    m_regDispl->updateRegisters(m_asmI.registers[AL].registerValue, m_asmI.registers[BL].registerValue, m_asmI.registers[CL].registerValue);
}

