#ifndef QTRAMSTORE_H
#define QTRAMSTORE_H
#include <QObject>
#include <QVariant>

class QtRamStore : public QObject
{
    Q_OBJECT
public:
    static QtRamStore *GetInstance(QObject *parent = nullptr);

private:
    explicit QtRamStore(QObject *parent);
    ~QtRamStore();
    QHash<QString, QVariantHash> database;
    static QtRamStore* _pInstance;
signals:
    void keyValueChanged(const QString &group,const QString &key,const QString &modifiedBy);
    void groupValueChanged(const QString &group,const QString &modifiedBy);

public slots:
    /** @brief Read key value */
    QVariant getValue(const QString &group,const QString &keyName);

    /** @brief Read entire group data */
    QVariantHash getGroupValue(const QString &group);

    /** @brief Write key value*/
    void writeToKey(const QString &group,const QString &key,const QVariant &value,const QString &modifiedBy);

    /** @brief Write entire group value */
    void writeToGroup(const QString &group,const QVariantHash &valueMap,const QString &modifiedBy);

};
Q_DECLARE_INTERFACE(QtRamStore, "com.github.shreyasnayak.QtRamStore/0.1")
#endif // QTRAMSTORE_H
