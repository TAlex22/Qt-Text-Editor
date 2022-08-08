#ifndef _SyntaxHighlighter_h_
#define _SyntaxHighlighter_h_

#include <QSyntaxHighlighter>

class QTextDocument;

class SyntaxHighlighter : public QSyntaxHighlighter {
	Q_OBJECT
private:
	QStringList cKeywords;
	QStringList cppKeywords;
	QStringList cpp20Keywords;
	int whatStx; // 0 - off, 1- c89, 2 - c++03, 3 - c++20
protected:
	enum { NormalState = -1, InsideCStyleComment, InsideCString };
	virtual void highlightBlock(const QString&);
	QString getKeyword(int i, const QString& str) const;
public:
	SyntaxHighlighter(QTextDocument* parent = 0, int what = 0);
	QColor strColor = Qt::cyan;
	QColor commentColor = Qt::darkGray;
	QColor wordColor = Qt::darkBlue;
	QColor includeColor = Qt::green;
};
#endif //_SyntaxHighlighter_h_