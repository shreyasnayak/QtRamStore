#include "ramstore.h"

QtRamStore* QtRamStore::_pInstance = nullptr;

/*!
    DataStore singleton class,GetInstance function will return singleton Instance.
*/
QtRamStore *QtRamStore::GetInstance(QObject *parent)
{
    if(QtRamStore::_pInstance == nullptr)
    {
        QtRamStore::_pInstance = new QtRamStore(parent);
    }
    return QtRamStore::_pInstance;
}

QtRamStore::QtRamStore(QObject *parent) : QObject(parent)
{

}

QtRamStore::~QtRamStore()
{
    QtRamStore::_pInstance = nullptr;
}

QVariant QtRamStore::getValue(const QString &group, const QString &keyName)
{
    if (database.contains(group))
    {
        QVariantHash groupMap = database.value(group);
        if(groupMap.contains(keyName)) return groupMap.value(keyName);
    }
    return QVariant();
}

QVariantHash QtRamStore::getGroupValue(const QString &group)
{
    if (database.contains(group)) return database.value(group);
    return QVariantHash();
}

void QtRamStore::writeToKey(const QString &group, const QString &key, const QVariant &value, const QString &modifiedBy)
{
    if (database.contains(group))
    {
       QHash<QString,QVariantHash>::iterator iter = database.find(group);
       iter.value()[key] = value;
    }
    else
    {
        database.insert(group,QVariantHash({{key,value}}));
    }
    emit keyValueChanged(group,key,modifiedBy);
}

void QtRamStore::writeToGroup(const QString &group, const QVariantHash &valueMap, const QString &modifiedBy)
{
    if (database.contains(group))
    {
       QHash<QString,QVariantHash>::iterator iter = database.find(group);
       QHashIterator<QString,QVariant> i(valueMap);
        while (i.hasNext()) {
            i.next();
            iter.value()[i.key()] = i.value();
        }
    }
    else
    {
        database.insert(group,valueMap);
    }
    emit groupValueChanged(group,modifiedBy);
}
