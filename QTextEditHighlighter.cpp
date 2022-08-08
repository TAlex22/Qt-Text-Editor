#include "QTextEditHighlighter.h"

QTextEditHighlighter::QTextEditHighlighter(QWidget* parent) :
    QTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    connect(this->document(), SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateLineNumberArea/*_2*/(int)));
    connect(this, SIGNAL(textChanged()), this, SLOT(updateLineNumberArea()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(updateLineNumberArea()));
    updateLineNumberAreaWidth(0);
}

int QTextEditHighlighter::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, this->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 13 + fontMetrics().width(QLatin1Char('9')) * (digits);

    return space;
}

void QTextEditHighlighter::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void QTextEditHighlighter::updateLineNumberArea(QRectF) {
    QTextEditHighlighter::updateLineNumberArea();
}
void QTextEditHighlighter::updateLineNumberArea(int) {
    QTextEditHighlighter::updateLineNumberArea();
}
void QTextEditHighlighter::updateLineNumberArea() {
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    QRect rect = this->contentsRect();
    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    updateLineNumberAreaWidth(0);
    int dy = this->verticalScrollBar()->sliderPosition();
    if (dy > -1) {
        lineNumberArea->scroll(0, dy);
    }

    int first_block_id = getFirstVisibleBlockId();
    if (first_block_id == 0 || this->textCursor().block().blockNumber() == first_block_id - 1)
        this->verticalScrollBar()->setSliderPosition(dy - this->document()->documentMargin());
   
}


void QTextEditHighlighter::resizeEvent(QResizeEvent* e) {
    QTextEdit::resizeEvent(e);

    QRect cr = this->contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


int QTextEditHighlighter::getFirstVisibleBlockId() {
    QTextCursor curs = QTextCursor(this->document());
    curs.movePosition(QTextCursor::Start);
    for (int i = 0; i < this->document()->blockCount(); ++i) {
        QTextBlock block = curs.block();

        QRect r1 = this->viewport()->geometry();
        QRect r2 = this->document()->documentLayout()->blockBoundingRect(block).translated(
            this->viewport()->geometry().x(), this->viewport()->geometry().y() - (
            this->verticalScrollBar()->sliderPosition()
            )).toRect();

        if (r1.contains(r2, true)) { return i; }

        curs.movePosition(QTextCursor::NextBlock);
    }

    return 0;
}

void QTextEditHighlighter::lineNumberAreaPaintEvent(QPaintEvent* event) {
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    int blockNumber = this->getFirstVisibleBlockId();

    QTextBlock block = this->document()->findBlockByNumber(blockNumber);
    QTextBlock prev_block = (blockNumber > 0) ? this->document()->findBlockByNumber(blockNumber - 1) : block;
    int translate_y = (blockNumber > 0) ? -this->verticalScrollBar()->sliderPosition() : 0;

    int top = this->viewport()->geometry().top();

    int additional_margin;
    if (blockNumber == 0)
        additional_margin = (int)this->document()->documentMargin() - 1 - this->verticalScrollBar()->sliderPosition();
    else
        additional_margin = (int)this->document()->documentLayout()->blockBoundingRect(prev_block)
        .translated(0, translate_y).intersect(this->viewport()->geometry()).height();
    top += additional_margin;

    int bottom = top + (int)this->document()->documentLayout()->blockBoundingRect(block).height();

    QColor col_1(90, 255, 30);      // Current line (custom green)
    QColor col_0(120, 120, 120);    // Other lines  (custom darkgrey)

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(120, 120, 120));
            painter.setPen((this->textCursor().blockNumber() == blockNumber) ? col_1 : col_0);
            painter.drawText(-5, top,
                lineNumberArea->width(), fontMetrics().height(),
                Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)this->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }

}