#ifndef SANOA_ADDDEVICE_H
#define SANOA_ADDDEVICE_H

#include <QDialog>
#include "libmtp.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class AddDevice : public QDialog
{
    Q_OBJECT

public:
    AddDevice(QWidget *parent = 0);
    QLineEdit *nameText;
    QTextEdit *addressText;

private:
    QLabel *nameLabel;
    QLabel *addressLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // SANOA_ADDDEVICE_H
