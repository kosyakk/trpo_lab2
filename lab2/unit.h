#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <memory>
#include <iostream>

class Unit
{
public:
    using Flags = unsigned int; //тип данных для флагов

    virtual ~Unit() = default;
    virtual void add(const std::shared_ptr<Unit>&, Flags)
    {
        throw std::runtime_error("Not supported");
    }

    virtual std::string compile(unsigned int level = 0) const = 0;

protected:
    virtual std::string generateShift(unsigned int level) const
    {
        static const auto DEFAULT_SHIFT = "     ";

        std::string result;

        for (unsigned int i = 0; i < level; i++)
        {
            result += DEFAULT_SHIFT;
        }

        return result;
    }
};

class ClassUnit : public Unit
{
public:
    enum AccessModifier
    {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        PRIVATE_PROTECTED,
        FILE,
        INTERNAL,
        PROTECTED_INTERNAL,

    };

    explicit ClassUnit(const std::string &name, unsigned int fieldsSize)
        : m_name(name), m_fields(fieldsSize){ }

    virtual ~ClassUnit() = default;

protected:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit>>; //тип данных для набора полей
    std::vector<Fields> m_fields;
};

class MethodUnit : public Unit
{
public:
    enum Modifier
    {
        STATIC = 1,
        CONST = 1 << 1, //битовые флаги для возможности устанавливать несколько модификаторов, прим. STATIC | CONST
        VIRTUAL = 1 << 2,
        INTERNAL = 1 << 3,
        FINAL = 1 << 4,
        ABSTRACT = 1 << 5
    };

public:
    MethodUnit(const std::string &name, const std::string &returnType, Flags flags)
        : m_name(name), m_returnType(returnType), m_flags(flags) { }

    virtual ~MethodUnit() = default;

    void add(const std::shared_ptr<Unit> &unit, Flags /* flags */ = 0 )
    {
        m_body.push_back(unit);
    }

protected:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

class PrintOperatorUnit : public Unit
{
public:
    explicit PrintOperatorUnit(const std::string &text) : m_text(text) { }

    virtual ~PrintOperatorUnit() = default;

protected:
    std::string m_text;
};

#endif // UNIT_H
