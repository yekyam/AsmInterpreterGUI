#include "RegisterDisplay.h"

RegisterDisplay::RegisterDisplay(QWidget* parent)
{
    m_widget = new QTableWidget(3, 2, parent);

    m_widget->setGeometry(460, 5, 280, 140);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalHeaderLabels(QStringList() << "AL" << "BL" << "CL");
    m_widget->setHorizontalHeaderLabels(QStringList() << "Values" << "Bits");

    for (int i = 0; i < 3; i++)
    {
        m_registerValuesItems[i] = new QTableWidgetItem(QString("%1").arg(0));
        m_registerValuesItems[i]->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_registerValuesItems[i]->setFlags(Qt::NoItemFlags);
        m_widget->setItem(i, 0, m_registerValuesItems[i]);

        m_registerBitsItems[i] = new QTableWidgetItem(QString("%1").arg(00000000));
        m_registerBitsItems[i]->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_registerBitsItems[i]->setFlags(Qt::NoItemFlags);
        m_widget->setItem(i, 1, m_registerBitsItems[i]);
    }
    updateRegisters(0, 0, 0);
}

void RegisterDisplay::updateRegisters(unsigned int al, unsigned int bl, unsigned int cl)
{
    m_registerValuesItems[AL]->setText(QString("%1").arg(al));
    m_registerValuesItems[BL]->setText(QString("%1").arg(bl));
    m_registerValuesItems[CL]->setText(QString("%1").arg(cl));

    m_registerBitsItems[AL]->setText(QString::fromStdString(std::bitset<8>(al).to_string()));
    m_registerBitsItems[BL]->setText(QString::fromStdString(std::bitset<8>(bl).to_string()));
    m_registerBitsItems[CL]->setText(QString::fromStdString(std::bitset<8>(cl).to_string()));
}
