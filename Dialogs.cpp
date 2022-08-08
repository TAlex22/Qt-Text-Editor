#include "Dialogs.h"

InputDialog::InputDialog(QWidget* parent) : QDialog(parent) {
    QBoxLayout* layout = new QHBoxLayout;
    m_edit1 = new QLineEdit;
    m_edit2 = new QLineEdit;
    layout->addWidget(m_edit1);
    layout->addWidget(m_edit2);

    QPushButton* findButton = new QPushButton("Find And Replace");
    connect(findButton, SIGNAL(clicked()), SLOT(reject()));
    layout->addWidget(findButton);

    setLayout(layout);
}

InputDialog::~InputDialog() {
}

QString InputDialog::getFind() const {
    return m_edit1->text();
}

QString InputDialog::getReplace() const {
    return m_edit2->text();
}