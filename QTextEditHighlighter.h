#ifndef _TEXT_HIGHLIGHTER_
#define _TEXT_HIGHLIGHTER_

#include "LineNumberArea.h"

//#include <QPainter>
#include <QtGui>

class QTextEditHighlighter : public QTextEdit {
    Q_OBJECT
public:

    explicit QTextEditHighlighter(QWidget* parent = 0);

    int getFirstVisibleBlockId();
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

public slots:

    void resizeEvent(QResizeEvent* e);

private slots:

    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(QRectF /*rect_f*/);
    void updateLineNumberArea(int /*slider_pos*/);
    void updateLineNumberArea();

private:

    QWidget* lineNumberArea;

};

#endif // !_TEXT_HIGHLIGHTER_
