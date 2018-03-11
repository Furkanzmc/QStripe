#pragma once
#include <QObject>

namespace QStripe
{

class PaymentSource : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sourceID READ sourceID WRITE setSourceID NOTIFY sourceIDChanged)

public:
    explicit PaymentSource(QObject *parent = nullptr);

public:
    /**
     * @brief Returns the current sourceID. The default value is an empty string.
     * @return QString
     */
    QString sourceID() const;

    /**
     * @brief Sets the source ID.
     * @param id
     */
    void setSourceID(const QString &id);

signals:
    /**
     * @brief Emitted when the sourceID changes.
     */
    void sourceIDChanged();

private:
    QString m_SourceID;
};

}
