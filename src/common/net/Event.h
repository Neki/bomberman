#ifndef SRC_COMMON_NET_EVENT_H_
#define SRC_COMMON_NET_EVENT_H_

#define CLIENT_VERSION "0.1.0"

#include <QString>
#include <QDataStream>

namespace common {
namespace net {

class Event {

  public:
    Event(quint32 id, quint64 timestamp);
    void SetId(quint32 id);
    quint32 GetId() const;
    quint64 GetTimestamp() const;
    QString GetClientVersion() const;

    virtual void Serialize(QDataStream& stream) const = 0;

    bool operator==(const Event& event) const;

  private:
    quint32 id_;
    quint64 timestamp_;

  protected:
    void SerializeBaseEvent(QDataStream& stream) const;

};

QDataStream& operator<<(QDataStream& stream, const Event& event);

}
}

#endif
