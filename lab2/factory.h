#ifndef FACTORY_H
#define FACTORY_H

#include "cppclass.h"
#include "csclass.h"
#include "javaclass.h"

class Factory
{
public:
    virtual ~Factory() = default;

    //интерфейсы фабричного метода, создающие класс, метод, оператор вывода
    virtual std::shared_ptr<ClassUnit> createClass(const std::string& name) const = 0;
    virtual std::shared_ptr<MethodUnit> createMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) const = 0;
    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperator(const std::string& name) const = 0;
};

// отличаются только типом создаваемого обьекта
class CppFactory : public Factory
{
public:
    std::shared_ptr<ClassUnit> createClass(const std::string& name) const
    {
        return std::make_shared<CppClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> createMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) const
    {
        return std::make_shared<CppMethodUnit>(name, returnType, flags);
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperator(const std::string& name) const
    {
        return std::make_shared<CppPrintOperatorUnit>(name);
    }
};

class CsFactory : public Factory
{
public:
    std::shared_ptr<ClassUnit> createClass(const std::string& name) const
    {
        return std::make_shared<CsClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> createMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) const
    {
        return std::make_shared<CsMethodUnit>(name, returnType, flags);
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperator(const std::string& name) const
    {
        return std::make_shared<CsPrintOperatorUnit>(name);
    }
};

class JavaFactory : public Factory
{
public:
    std::shared_ptr<ClassUnit> createClass(const std::string& name) const
    {
        return std::make_shared<JavaClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> createMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) const
    {
        return std::make_shared<JavaMethodUnit>(name, returnType, flags);
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperator(const std::string& name) const
    {
        return std::make_shared<JavaPrintOperatorUnit>(name);
    }
};

#endif // FACTORY_H
