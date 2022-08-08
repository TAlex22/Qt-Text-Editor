#ifndef _DIALOGS_
#define _DIALOGS

#include <QLineEdit>
#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>

class InputDialog : public QDialog {
    Q_OBJECT

public:
    InputDialog(QWidget* parent = 0);
    ~InputDialog();

    QString getFind() const;
    QString getReplace() const;

private:
    QLineEdit* m_edit1;
    QLineEdit* m_edit2;
};

#endif // !_DIALOGS_
