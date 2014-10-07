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

class NetworkWorker : public QObject {
  Q_OBJECT

  public:
    NetworkWorker(quint8 client_id, QHostAddress address, quint16 server_port, quint16 local_port);
    // can be called from another thread
    // can not be a slot, as this would require the event to be copied
    // if this slot was called from another thread (which is the purpose of this
    // method)
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
