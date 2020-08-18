#ifndef LINKLIST_H
#define LINKLIST_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#include <fstream>

class Node
{
public:
    Node(std::string value)
        : prev(nullptr),
          next(nullptr),
          random(nullptr),
          data(value) {
    }
    ~Node()
    {
        data.clear();
        prev = nullptr;
        next = nullptr;
        random = nullptr;
    }
    Node *prev;
    Node *next;
    Node *random;
    std::string data;

    bool operator==(const Node &other)
    {
      return (next == other.next && prev == other.prev);
    }
    bool operator !=(const Node &other)
    {
       return !(*this == other);
    }
};

class LinkList
{
public:
    LinkList(uint size=0);
    void push_back(const std::string value);
   // void insert(Node* node, int pos);
    int indexOf(Node* node);
    Node *at(const int index);
    int Count();
    void randomizeElements();
    void print();
    void Serialize(std::ofstream &s);
    void Deserialize(std::ifstream &s);
    void clear();

    friend std::ostream &operator<<(std::ostream& os, LinkList& list);

private:
    void createEmpty(uint size);
    char *getData(std::string &source, char* data);
    Node *head;
    Node *tail;
    int m_count;
};

#endif // LINKLIST_H
