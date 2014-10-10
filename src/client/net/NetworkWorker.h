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
#include "src/common/net/Event.h"

namespace common {
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
    NetworkWorker(quint8 client_id, QHostAddress address, quint16 server_port, quint16 local_port);

    /**
     * Adds an event in the list of events to send to the server.
     * Can be called from any thread.
     * Is not a slot, as inter-thread communication with slots would require a
     * copy of the event.
     */
    void AddEvent(std::unique_ptr<Event> event);

  signals:
    //void Latency(int latency);
    //void WorldReceived();

  private slots:
    void SendPendingEvents();

  private:
    std::map<quint64, std::unique_ptr<Event>> pending_; // can be accessed from two threads
    QUdpSocket socket_;
    QByteArray buffer_;
    QDataStream buffer_stream_;
    quint64 last_event_id_;
    quint64 last_packet_id_;
    quint8 client_id_;
    int time_between_packets_; // in ms
    QTimer timer_;
    QMutex pending_events_mutex_;

    const unsigned char kProtocolId = 0xBC;
    const unsigned char kClientVersion = 0x01;
    const unsigned char kEventPacketId = 0x02;

    quint64 GetNextEventId();
    quint64 GetNextPacketId();
    quint64 PrepareHeader(QDataStream& stream, quint8 packet_type);
    void ReadPendingDatagrams();
    void ProcessDatagram(const QByteArray& datagram);

};

}
}

#endif
