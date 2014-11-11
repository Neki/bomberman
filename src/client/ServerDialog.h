#ifndef SRC_CLIENT_SERVERDIALOG_H_
#define SRC_CLIENT_SERVERDIALOG_H_
#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

class ServerDialog : public QDialog {
    Q_OBJECT

public:
    ServerDialog(QWidget *parent = 0);
    QString GetServerAddress();
    int GetServerPort();

private:
    QLabel *host_label_;
    QLabel *port_label_;
    QLineEdit *host_line_edit_;
    QLineEdit *port_line_edit_;
    QPushButton *ok_button_;
    QPushButton *close_button_;
    QDialogButtonBox *button_box_;
};

#endif
