#ifndef SRC_COMMON_NET_EVENT_H_
#define SRC_COMMON_NET_EVENT_H_

#define CLIENT_VERSION "0.1.0"

#include <QString>
#include <QDataStream>

namespace common {
namespace net {

/**
 * Used by the client to notify the server that the player took an action.
 * during a running game.
 * Subclasses represent specific events (such as a player movement). They add
 * their own specialized data, and implement the proper serialization and
 * deserialization methods (in the Deserializer class).
 * @see Deserializer
 */
class Event {

  public:
    /**
     * @param id a unique, strictly increasing event ID. Can be set to -1.
     * @param timestamp in milliseconds since the beginning of the game, when
     * this action took place (in the point of view of the client)
     */
    Event(quint32 id, quint64 timestamp);
    void SetId(quint32 id);
    quint32 GetId() const;
    quint64 GetTimestamp() const;

    /**
     * @return a version string identifying the version of the game run by the
     * client
     */
    QString GetClientVersion() const;

    virtual void Serialize(QDataStream& stream) const = 0;

    bool operator==(const Event& event) const;

  private:
    quint32 id_;
    quint64 timestamp_;

  protected:
    /**
     * Serialize to @a stream the base data of the event: client version, id,
     * timestamp. Intended to be called by the derived classes in their
     * implementation of Serialize.
     */
    void SerializeBaseEvent(QDataStream& stream) const;

};

QDataStream& operator<<(QDataStream& stream, const Event& event);

}
}

#endif
