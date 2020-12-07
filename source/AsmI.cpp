#include "AsmI.h"

AsmI::AsmI()
{
    int i = 0;
    for (const auto& x : registerNames)
    {
        registers[i].registerID = getRegisterID(x);
        registers[i].registerValue = 0;
        i++;
    }
}

void AsmI::handleInput(const std::string& input)
{
    std::string word;
    for (const auto& x : input)
    {
        if (x == ',') {}
        else if (x == ' ')
        {
            arguments.push_back(word);
            word = "";
        }
        else
        {
            word += x;
        }
    }
    arguments.push_back(word);
}

QString AsmI::command()
{
    QString messages;
    if (arguments.size() < 1)
    {
        messages += "Invalid number of arguments! Must have at least one argument!";
    }
    else if (arguments.size() == 1)
    {
        std::string command = lowercase(arguments.at(0));

        if (command == "help") messages += printHelp();
        else  messages += "Error! Invalid command!";
        arguments.clear();
    }
    else if (arguments.size() == 2)
    {
        std::string command = lowercase(arguments.at(0));
        std::string arg1 = uppercase(arguments.at(1));

        if (command == "push") pushRegister(arg1);
        else if (command == "pop") popRegister(arg1);
        else  messages += "Error! Invalid command!";
        arguments.clear();
    }
    else {
        std::string command = lowercase(arguments.at(0));
        std::string arg1 = uppercase(arguments.at(1));
        std::string arg2 = uppercase(arguments.at(2));

        if (command == "mov") mov(arg1, arg2);
        else if (command == "or") orRegister(arg1, arg2);
        else if (command == "xor") xorRegister(arg1, arg2);
        else if (command == "and") andRegister(arg1, arg2);
        else if (command == "shl") shlRegister(arg1, arg2);
        else if (command == "shr") shrRegister(arg1, arg2);
        else if (command == "add") addRegister(arg1, arg2);
        else if (command == "sub") subRegister(arg1, arg2);
        else if (command == "mul") mulRegister(arg1, arg2);
        else if (command == "div") divRegister(arg1, arg2);
        else if (command == "cmp") cmpRegister(arg1, arg2);
        else  messages += "Error! Invalid command!";
        arguments.clear();
    }
    return messages;
}

int AsmI::getRegisterID(const std::string& name)
{
    int result = 0;
    for (const auto& x : name)
        result += static_cast<int>(x);
    return result;
}

void AsmI::setRegister(const std::string& registerName, u8 value)
{
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(registerName))
        {
            x.registerValue = value;
            break;
        }
    }
}

void AsmI::mov(const std::string& arg1, const std::string& arg2)
{
    try
    {
        int value = std::stoi(arg2);
        if (value > 255)
        {
            return;
        }
        setRegister(arg1, (u8)value);
    }
    catch (std::exception e)
    {
        bool isRegister1 = false;
        u8 value;
        for (auto& x : registers)
        {
            if (x.registerID == getRegisterID(arg2))
            {
                value = x.registerValue;
            }
            if (x.registerID == getRegisterID(arg1))
            {
                isRegister1 = true;
            }
        }
        if (isRegister1)
        {
            setRegister(arg1, value);
        }
    }
}

void AsmI::orRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 | value2);
    }
}

void AsmI::xorRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 ^ value2);
    }
}

void AsmI::andRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 & value2);
    }
}

void AsmI::shlRegister(const std::string& arg1, const std::string& arg2)
{
    try
    {
        int shiftNum = std::stoi(arg2);
        if (shiftNum > 7)
        {
            return;
        }

        for (auto& x : registers)
        {
            if (x.registerID == getRegisterID(arg1))
            {
                setRegister(arg1, x.registerValue << shiftNum);
            }
        }
    }
    catch (std::exception& e)
    {
        u8 value1, value2;
        bool foundReg1 = false, foundReg2 = false;
        for (auto& x : registers)
        {
            if (x.registerID == getRegisterID(arg2))
            {
                foundReg1 = true;
                value2 = x.registerValue;
            }
            if (x.registerID == getRegisterID(arg1))
            {
                foundReg2 = true;
                value1 = x.registerValue;
            }
        }
        if (foundReg1 && foundReg2)
        {
            setRegister(arg1, value1 << value2);
        }
    }

}

void AsmI::shrRegister(const std::string& arg1, const std::string& arg2)
{
    try
    {
        int shiftNum = std::stoi(arg2);
        if (shiftNum > 7)
        {
            return;
        }

        for (auto& x : registers)
        {
            if (x.registerID == getRegisterID(arg1))
            {
                setRegister(arg1, x.registerValue >> shiftNum);
            }
        }
    }
    catch (std::exception& e)
    {
        u8 value1, value2;
        bool foundReg1 = false, foundReg2 = false;
        for (auto& x : registers)
        {
            if (x.registerID == getRegisterID(arg2))
            {
                foundReg1 = true;
                value2 = x.registerValue;
            }
            if (x.registerID == getRegisterID(arg1))
            {
                foundReg2 = true;
                value1 = x.registerValue;
            }
        }
        if (foundReg1 && foundReg2)
        {
            setRegister(arg1, value1 >> value2);
        }
    }

}

void AsmI::addRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 + value2);
    }
}

void AsmI::subRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 - value2);
    }
}

void AsmI::mulRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 * value2);
    }
}

void AsmI::divRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    bool foundReg1 = false, foundReg2 = false;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            foundReg1 = true;
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            foundReg2 = true;
            value1 = x.registerValue;
        }
    }
    if (foundReg1 && foundReg2)
    {
        setRegister(arg1, value1 / value2);
    }
}

void AsmI::cmpRegister(const std::string& arg1, const std::string& arg2)
{
    u8 value1, value2;
    for (auto& x : registers)
    {
        if (x.registerID == getRegisterID(arg2))
        {
            value2 = x.registerValue;
        }
        if (x.registerID == getRegisterID(arg1))
        {
            value1 = x.registerValue;
        }
    }
    if ((value1 - value2) == 0)
    {
        isEqual = true;
        return;
    }
    isEqual = false;
}

void AsmI::pushRegister(const std::string& arg)
{
    try
    {
        int value = std::stoi(arg);
        if (value > 255)
        {
            return;
        }
        stack.push((u8)value);
    }
    catch (const std::exception& e)
    {
        for (auto& x : registers)
        {
            if (getRegisterID(arg) == x.registerID)
            {
                stack.push(x.registerValue);
                x.registerValue = 0;
            }
        }
    }
}

void AsmI::popRegister(const std::string& registerName)
{
    if (stack.size() < 1)
    {
        return;
    }
    for (auto& x : registers)
    {
        if (getRegisterID(registerName) == x.registerID)
        {
            x.registerValue = stack.top();
            stack.pop();
        }
    }
}

QString AsmI::printHelp()
{
    QString help;
    help =  "Welcome to the Assembly Interpreter!<br>"
            "Commands:<br><br>mov   (to reg) (value)<br>"
            "mov   (to reg) (from reg)<br>"
            "or    (to reg) (from reg)<br>"
            "and   (to reg) (from reg)<br>"
            "xor   (to reg) (from reg)<br>"
            "shl   (to reg) (num bits)<br>"
            "shr   (to reg) (num bits)<br>"
            "add   (to reg) (from reg)<br>"
            "cmp   (to reg) (from reg)<br>"
            "add   (to reg) (from reg)<br>"
            "sub   (to reg) (from reg)<br>"
            "div   (to reg) (from reg)<br>"
            "mul   (to reg) (from reg)<br>"
            "mod   (to reg) (from reg)<br>"
            "push  (reg)<br>"
            "pop   (reg)";
    return help;
}
