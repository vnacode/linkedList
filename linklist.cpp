#include "linklist.h"
#include <QCoreApplication>
#include <random>



LinkList::LinkList(uint size)
    : head(nullptr),tail(nullptr),m_count(size)
{
    createEmpty(size);
}

void LinkList::push_back(const std::string value)
{
    Node* temp = new Node(value);
    if (head == nullptr)
    {
        head = temp;
        tail = head;
    }
    else
    {
        head->next = temp;
        temp->prev = head;
        head = temp;
    }
    m_count++;
}

int LinkList::indexOf(Node *node)
{
    if (m_count == 0)
        return -1;
    int id = 0;
    Node* current = this->tail;
    while (current != nullptr)
    {
        if (node == current)
            return id;
        current = current->next;
        id++;
    }
    return -1;
}

Node *LinkList::at(const int index)
{
    if (index > m_count) return head;
    if (index == m_count - 1)
        return head;
    if (index == 0)
        return tail;
    int currentId = 0;
    Node* current = this->tail;
    while (current->next != nullptr)
    {
        if (currentId == index)
            return current;
        current = current->next;
        currentId++;
    }
}

int LinkList::Count()
{
    return m_count;
}

void LinkList::randomizeElements()
{
    std::default_random_engine generator;
    std::mt19937 mt(generator());
    std::uniform_int_distribution<int> dist(0, m_count);
    Node* current = this->tail;
    while (current != nullptr)
    {
        int rnd = dist(mt);
        current->random = at(rnd);
        current = current->next;
    }
}

void LinkList::print()
{
    Node* current = tail;
    std::string text;
    while (current != nullptr)
    {
        std::cout<<"["<<current->data<<"]"<<" rand: "<<"["<<current->random->data<<"]"<<std::endl;
        text += current->data;
        current = current->next;
    }
    std::cout << text <<std::endl;
}

void LinkList::Serialize(std::ofstream &s)
{
    if (m_count == 0)
        return;
    s.open("output");
    s << "[";
    int currentId = 0;
    Node* current = this->tail;
    s << "SIZE:" << std::to_string(m_count) << ",";
    s << std::endl;
    while (current != nullptr)
    {
        s << "{";
        std::string prev = current->prev == nullptr ? "NONE" : std::to_string(currentId - 1);
        std::string next = current->next == nullptr ? "NONE" : std::to_string(currentId + 1);
        std::string rand = current->random == nullptr ? "NONE" : std::to_string(indexOf(current->random));

        s << "NODE:" << std::to_string(indexOf(current)) << ",";
        s << "PREV:" << prev << ",";
        s << "NEXT:" << next << ",";
        s << "RAND:" << rand << ",";
        s << "DATA:" <<current->data << ",";
        s << "}\n";
        current = current->next;
        currentId++;
    }
    s << "]";
    s.close();
}


void LinkList::Deserialize(std::ifstream &s)
{
    using namespace std;
    s.open("output");

    clear();
    uint currentIndex = 0;
    string str;

    getline(s, str);

    this->createEmpty(std::atoi(getData(str,"SIZE")));
        while (getline(s, str))
        {
            if (str.size()>1)
            {
                at(currentIndex)->data =  getData(str,"DATA");
                at(currentIndex)->random = at(std::atoi(getData(str,"RAND")));
                currentIndex++;
            }
        }
    s.close();
}

void LinkList::clear()
{
    if (m_count == 0)
        return;

    Node* current = this->tail;
    while (head != tail)
    {
        current = head;
        head = head->prev;
        delete current;
    }
    delete head;
    tail = nullptr;
    head = nullptr;
    m_count = 0;
}

void LinkList::createEmpty(uint size)
{
    if (size!=0)
    {
        for (int i = 0; i < size; i++)
            push_back("");
    }
}

char* LinkList::getData(std::string &source, char *data)
{
    uint currentPos = source.find(data);
    if (currentPos != -1)
    {
        currentPos = source.find(":", currentPos)+1;
        uint len = source.find(",",currentPos)-currentPos;
        char *value = (char*)malloc(sizeof(char)*len);
        source.copy(value, len, currentPos);
        return value;
    }
    return 0;
}



//std::size_t linklist::write(std::ostream &os, const std::string &value)
//{
//    const auto pos = os.tellp();
//    const auto len = static_cast<std::uint32_t>(value.size());
//    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
//    if (len > 0)
//        os.write(value.data(), len);
//    return static_cast<std::size_t>(os.tellp() - pos);
//}

std::ostream &operator<<(std::ostream& os, LinkList& list)
{
    Node* current = list.tail;
    while (current != nullptr)
    {
        os << current->data;
        current = current->next;
    }
    return os;
}


