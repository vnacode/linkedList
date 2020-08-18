#include <QCoreApplication>
#include <linklist.h>
#include <qdebug.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LinkList list;
//    list.push_back("The ");
//    list.push_back("quick ");
//    list.push_back("brow ");
//    list.push_back("fox ");
//    list.push_back("jumps ");
//    list.push_back("over ");
//    list.push_back("the ");
//    list.push_back("lazy ");
//    list.push_back("dog.");
//    list.randomizeElements();
//    list.print();
//    std::cout << "-----------SERIALIZE----------" << std::endl;
   // std::ofstream stream;
   // list.Serialize(stream);

    std::cout << "-----------DESERIALIZE----------" << std::endl;
    std::ifstream inputStream;
    list.Deserialize(inputStream);
    list.print();

    exit(0);
    return a.exec();
}

