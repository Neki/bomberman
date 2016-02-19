#include "ServerDialog.h"
#include <QIntValidator>
#include <QGridLayout>
#include "easylogging++.h"

ServerDialog::ServerDialog(QWidget *parent) : QDialog(parent) {
    host_label_ = new QLabel("Server name:");
    port_label_ = new QLabel("Server port:");

    host_line_edit_ = new QLineEdit("127.0.0.1");
    port_line_edit_ = new QLineEdit("4567");
    port_line_edit_->setValidator(new QIntValidator(1, 65535, this));

    host_label_->setBuddy(host_line_edit_);
    port_label_->setBuddy(port_line_edit_);

    ok_button_ = new QPushButton("Join");
    ok_button_->setDefault(true);

    close_button_ = new QPushButton("Cancel");

    button_box_ = new QDialogButtonBox;
    button_box_->addButton(ok_button_, QDialogButtonBox::ActionRole);
    button_box_->addButton(close_button_, QDialogButtonBox::RejectRole);

    connect(ok_button_, SIGNAL(clicked()), this, SLOT(accept()));
    connect(close_button_, SIGNAL(clicked()), this, SLOT(reject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(host_label_, 0, 0);
    mainLayout->addWidget(host_line_edit_, 0, 1);
    mainLayout->addWidget(port_label_, 1, 0);
    mainLayout->addWidget(port_line_edit_, 1, 1);
    mainLayout->addWidget(button_box_, 2, 0, 1, 2);
    setLayout(mainLayout);

    host_line_edit_->setFocus();
}

QString ServerDialog::GetServerAddress() {
    return host_line_edit_->text();
}

int ServerDialog::GetServerPort() {
    return port_line_edit_->text().toInt();
}
