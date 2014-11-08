#ifndef SRC_CLIENT_NET_NETWORKWORKER_H_
#define SRC_CLIENT_NET_NETWORKWORKER_H_

#include <memory>
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QByteArray>
#include "src/common/net/InGameEvent.h"
#include "src/common/GameTimer.h"
#include "ServerEntity.h"

#define LOG_PACKET_LEVEL 5

using common::net::InGameEvent;
using common::GameTimer;
using namespace common::entity;

namespace net {

/**
 * Internal class for the network API (not intended for direct use by the user).
 * Instances are meant to be run in a thread separate from  the main thread, and
 * contain the main loop (run by Qt) that actually communicates with the server
 * on the network during a game. Network communication when in lobby is outside
 * the scope of this class.
 * @see NetworkManager
 */
class NetworkWorker : public QObject {
  Q_OBJECT

  public:
    /**
     * @param client_id the unique client ID given by the server in the game
     *        lobby
     * @param address the address of the server running the game
     * @param server_port port on the server to connect to
     * @param local_port port on the client used to receive data (todo:
     * communicate this port to the server)
     */
    NetworkWorker(quint8 client_id, QHostAddress address, quint16 server_port, quint16 local_port, std::shared_ptr<GameTimer> game_timer);

    /**
     * Adds an event in the list of events to send to the server.
     * Can be called from any thread.
     * Is not a slot, as inter-thread communication with slots would require a
     * copy of the event.
     */
    void AddEvent(std::unique_ptr<InGameEvent> event);

  signals:
    /**
     * Emitted when a new measure of the latency between the server and the
     * client is available. This value has already been pre-processed and can be
     * consumed without any further checks or modifications (this is not a raw
     * value).
     */
    void Latency(int latency);

    void EntityReceived(ServerEntity& entity);

  private slots:
    void SendPendingEvents();
    void SendPingPacket();
    void ReadPendingDatagrams();
    /**
     * Delete all data about ping packets sent more than 5 seconds ago.
     * Useful to prevent memory leaks when packrts are lost (as otherwise the
     * only time when this data is deleted is when an answer to a ping packet is
     * received)
     */
    void CleanPingData();
    void SocketError(QAbstractSocket::SocketError);

  private:
    std::map<quint32, std::unique_ptr<InGameEvent>> pending_; // can be accessed from two threads
    std::map<quint32, quint32> ping_timestamps_; // packet id -> timestamp
    QUdpSocket socket_;
    QUdpSocket receive_socket_;
    quint32 last_event_id_;
    quint32 last_packet_id_;
    quint8 client_id_;
    quint32 round_trip_time_; // in ms
    QTimer timer_;
    QTimer ping_timer_;
    QTimer clean_ping_data_timer_;
    std::shared_ptr<GameTimer> game_timer_;
    QMutex pending_events_mutex_;

    static const unsigned char kProtocolId = 0xBC;
    static const unsigned char kClientVersion = 0x01;
    static const unsigned char kPingPacketId = 0x01;
    static const unsigned char kEventPacketId = 0x02;
    static const unsigned char kEntitiesPacketId = 0x03;
    static const unsigned char kEventAckPacketId = 0x04;

    quint32 GetNextEventId();
    quint32 GetNextPacketId();
    quint32 PrepareHeader(QDataStream& stream, quint8 packet_type);
    void ProcessDatagram(const QByteArray& datagram);
    bool CheckProtocolAndVersion(QDataStream& stream);
    quint32 GetPacketId(QDataStream& stream);
    quint8 GetPacketType(QDataStream& stream);
    void ProcessPingPacket(QDataStream& stream);
    void ProcessEntitiesPacket(QDataStream& stream);
    void UpdateRoundTripTime(quint32 send_time);
    void DeserializeEntity(QDataStream& stream, quint32 timestamp);
    void ProcessEventAck(QDataStream& stream);

    bool CheckStreamStatus(const QDataStream& stream) const;

};

}

#endif
