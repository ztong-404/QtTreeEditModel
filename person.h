#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QList>
#include<QVariant>

class Person
{
public:
    Person(const QVector<QVariant> &data,Person * parent = nullptr);
    ~Person();
    void appendChild(Person * childParam);
    Person * child( int row);
    int childCount() const;
    QVariant data(int column) const;
    int row () const;
    Person *parentPerson();
    void showInfo();

    //可编辑树模型
    int columnCount() const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    //Return the index  of this item in the list of its parent children
    int childNumber() const;
    bool setData(int column, const QVariant &value);



private:

    QList<Person*> children;
    QVector <QVariant> columnFields;
    Person * parent;
};

#endif // PERSON_H
