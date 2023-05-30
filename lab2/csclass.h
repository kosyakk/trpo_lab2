#ifndef CSCLASS_H
#define CSCLASS_H

#include <unit.h>

class CsClassUnit : public ClassUnit
{
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

public:
    explicit CsClassUnit(const std::string &name)
        : ClassUnit(name, ACCESS_MODIFIERS.size()) { }

    void add(const std::shared_ptr<Unit> &unit, Flags flags = 0)
    {

        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size())
        {
            accessModifier = flags;
        }

        m_fields[accessModifier].push_back(unit);
    }

    std::string compile(unsigned int level = 0) const
    {
        std::string result = "class " + m_name + " {\n"; // класс мб подклассом с модификатором доступа, за отступ первой строки отвечает вышестоящий обьект

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++)
        {
            /*
             * тело класса не делится на поля с модификаторами доступа, за отступ первой строки элемента класса отвечает
             * сам класс, в начало объявления метода дописывается модификатор доступа
             */
            for (const auto &f : m_fields[i])
            {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(level + 1);
            }
        }

        result += generateShift(level) + "};\n";

        return result;
    }
};

//++
const std::vector<std::string> CsClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private", "private protected", "file", "internal", "protected internal",  };

class CsMethodUnit : public MethodUnit
{
public:
    CsMethodUnit(const std::string &name, const std::string &returnType, Flags flags)
        : MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const
    {
        std::string result = ""; // отступа нет, как и у класса за него отвечает вышестоящий объект

        if (m_flags & STATIC)
        {
            result += "static ";
        }
        else if (m_flags & VIRTUAL)
        {
            result += "virtual ";
        }
        if(m_flags & INTERNAL) //++
        {
            result += "internal ";
        }

        result += m_returnType + " ";
        result += m_name + "() {\n"; //в C# нет методов с типом const

        for (const auto &b : m_body)
        {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};

class CsPrintOperatorUnit : public PrintOperatorUnit
{
public:
    explicit CsPrintOperatorUnit(const std::string &text)
        : PrintOperatorUnit(text) { }

    std::string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "Console.WriteLine(\"" + m_text + "\");\n";
    }
};


#endif // CSCLASS_H
