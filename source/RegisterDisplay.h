#ifndef REGISTERDISPLAY_H
#define REGISTERDISPLAY_H

#include <QFrame>
#include <QRect>
#include <QTableWidget>
#include <QString>
#include <bitset>

#include "AsmI.h"

class RegisterDisplay : QObject
{
    Q_OBJECT

public:
    RegisterDisplay(QWidget* parent);
    void updateRegisters(unsigned int al, unsigned int bl, unsigned int cl);

private:
    QTableWidget* m_widget;
    QTableWidgetItem* m_registerValuesItems[NUM_REGISTERS];
    QTableWidgetItem* m_registerBitsItems[NUM_REGISTERS];
};

#endif // REGISTERDISPLAY_H
