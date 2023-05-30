#ifndef JAVACLASS_H
#define JAVACLASS_H

#include "unit.h"

class JavaClassUnit : public ClassUnit
{
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

public:
    explicit JavaClassUnit(const std::string &name)
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
        std::string result = "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++)
        {
            for (const auto &f : m_fields[i])
            {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(level + 1);
            }
        }

        result += generateShift(level) + "};\n";

        return result;
    }
};

const std::vector<std::string> JavaClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };

class JavaMethodUnit : public MethodUnit
{
public:
    JavaMethodUnit(const std::string &name, const std::string &returnType, Flags flags)
        : MethodUnit(name, returnType, flags) { }

    std::string compile(unsigned int level = 0) const
    {
        std::string result = "";

        if (m_flags & STATIC)
        {
            result += "static ";
        }
        if (m_flags & FINAL) //++
        {
            result += "final ";
        }
        if (m_flags & ABSTRACT) //++
        {
            result += "abstract ";
        }

        result += m_returnType + " ";
        result += m_name + "() {\n";

        for (const auto &b : m_body)
        {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};

// языковая конструкция оператора вывода языка Java
class JavaPrintOperatorUnit : public PrintOperatorUnit
{
public:
    explicit JavaPrintOperatorUnit(const std::string &text)
        : PrintOperatorUnit(text) { }

    std::string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "System.out.println(\"" + m_text + "\");\n";
    }
};

#endif // JAVACLASS_H
