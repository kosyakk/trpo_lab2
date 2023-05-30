#include <QCoreApplication>

#include "unit.h"
#include "factory.h"

std::string generateProgram(const std::shared_ptr<Factory> &factory)
{
    auto class_a = factory->createClass("ClassA");
    auto class_b = factory->createClass("ClassB");

    class_b->add(factory->createMethod("testFunc1", "void", 0), ClassUnit::PUBLIC);
    class_a->add(class_b, ClassUnit::PUBLIC);
    class_a->add(factory->createMethod("testFunc2", "void", MethodUnit::STATIC), ClassUnit::PRIVATE);

    auto method = factory->createMethod("testFunc4", "void", MethodUnit::STATIC); // создание метода

    method->add(factory->createPrintOperator("Hello, world!"));
    class_a->add(method, ClassUnit::PROTECTED);
    class_a->add(factory->createMethod("testFunc3", "void", MethodUnit::VIRTUAL | MethodUnit::CONST), ClassUnit::PUBLIC);

    return class_a->compile();
}

int main(int argc, char *argv[])
{

    std::cout << "c++:\n" << generateProgram(std::make_shared<CppFactory>()) << std::endl;
    std::cout << "c#:\n" << generateProgram(std::make_shared<CsFactory>()) << std::endl;
    std::cout << "java:\n" << generateProgram(std::make_shared<JavaFactory>()) << std::endl;


    return 0;
}
