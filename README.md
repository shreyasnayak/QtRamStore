# QtRamStore

QtRamStore is a Qt C++ Libary to store and retrieve the data.

# How to build (Linux)

`qmake /<PATH-TO-QtRamStore>/QtRamStore/QtRamStore.pro`

`make`

`sudo make install`

# How to use in Qt Project

## Include library in Qt Project

```
    unix:{
        INCLUDEPATH +=/usr/local/include
        LIBS += -L/usr/local/lib/ -lQtRamStore
    }
```

## Example Code

```
    #include <QCoreApplication>
    #include <ramstore.h>
    #include <QDebug>
    const QString PageName = "Main.cpp";

    int main(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);
        QtRamStore *dataBase = QtRamStore::GetInstance();

        dataBase->writeToKey("Group-1","First Name","Shreyas",PageName);
        dataBase->writeToKey("Group-1","Last Name","Nayak",PageName);

        dataBase->writeToGroup("Group-2",QVariantHash{
                                                {"First Name","Shreyas"},
                                                {"Last Name","Nayak"}
                                                },PageName);

        qInfo()<< "Group-1 Value : " << dataBase->getGroupValue("Group-1");
        qInfo()<< "Group-2 Value : " << dataBase->getGroupValue("Group-2");

        return a.exec();
    }

```
