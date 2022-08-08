#ifndef _LINE_AREA_
#define _LINE_AREA_

#include <QtGui>
#include "QTextEditHighlighter.h"

class LineNumberArea : public QWidget {
    Q_OBJECT
public:
    LineNumberArea(QTextEdit* editor);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    QTextEdit* codeEditor;
};

#endif // !_LINE_AREA_
