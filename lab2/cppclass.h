#ifndef CPPCLASS_H
#define CPPCLASS_H

#include "unit.h"

class CppClassUnit : public ClassUnit
{
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

    explicit CppClassUnit(const std::string &name)
        : ClassUnit(name, ACCESS_MODIFIERS.size()) { }

    void add(const std::shared_ptr<Unit> &unit, Flags flags)
    {

        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size()) // отсеивание модификаторов доступа, не поддерживающихся данным языком
        {
            accessModifier = flags;
        }

        m_fields[accessModifier].push_back(unit); // добавление в поле с соотвествующим модификатором доступа
    }

    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level) + "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++) // перебор набора полей модификаторов доступа
        {
            if (m_fields[i].empty())
            {
                continue;
            }

            result += generateShift(level) + ACCESS_MODIFIERS[i] + ":\n";

            for (const auto &f : m_fields[i]) // перебор всех полей модификатора доступа
            {
                result += f->compile(level + 1); // вывод языковых конструкций, с учетом отступа
            }

            result += "\n";
        }

        result += generateShift(level) + "};\n";

        return result;
    }
};

const std::vector<std::string> CppClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };

class CppMethodUnit : public MethodUnit
{
public:
    CppMethodUnit(const std::string &name, const std::string &returnType, Flags flags)
        : MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level);

        if (m_flags & STATIC)
        {
            result += "static ";
        }
        else if (m_flags & VIRTUAL)
        {
            result += "virtual ";
        }

        result += m_returnType + " ";
        result += m_name + "()";

        if (m_flags & CONST)
        {
            result += " const";
        }

        result += " {\n";

        for (const auto &b : m_body) // перебор всех конструкций, находящихся в данном методе
        {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};

class CppPrintOperatorUnit : public PrintOperatorUnit
{
public:
    explicit CppPrintOperatorUnit(const std::string &text)
        : PrintOperatorUnit(text) { }

    std::string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "std::cout << \"" + m_text + "\" << std::endl;\n";
    }
};

#endif // CPPCLASS_H
