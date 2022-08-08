#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent, int what)
	: QSyntaxHighlighter(parent), whatStx(what){
	cppKeywords
		<< "and" << "and_eq" << "asm"  << "bitand"
		<< "bitor" << "bool" << "break" << "case" << "catch" << "class" << "compl"
		<< "const" << "const_cast" << "continue" << "default" << "delete" << "do"
		<< "double" << "dynamic_cast" << "else" << "enum" << "explicit"
		<< "extern" << "false" << "float" << "for" << "friend" << "goto" << "if"
		<< "inline" << "int" << "long" << "mutable" << "namespace" << "new"
		<< "not" << "not_eq" << "nullptr" << "operator" << "or" << "or_eq" << "private"
		<< "protected" << "public" << "reflexpr" << "register" << "reinterpret_cast"
		<< "return" << "short" << "signed" << "sizeof" << "static"
		<< "static_cast" << "struct" << "switch" << "synchronized" << "template" << "this"
		<< "throw" << "true" << "try" << "typedef" << "typeid" << "typename" << "union"
		<< "unsigned" << "using" << "virtual" << "void" << "volatile" << "wchar_t" << "while"
		<< "xor" << "xor_eq" << "xor_eq" << "->" << ">>" << "<<" << ">" << "<"
		<< "(" << ")" << "{" << "}" << "[" << "]" << "+" << "-" << "*" << "/"
		<< "=" << "!" << "." << "," << ";" << ":" << "&" << "|";

	cKeywords << "auto" << "break" << "case"
		<< "char" << "const" << "continue"
		<< "default" << "do" << "double" << "else"
		<< "enum" << "extern" << "float" << "for"
		<< "goto" << "if" << "int" << "long" << "register"
		<< "return" << "short" << "signed" << "sizeof"
		<< "static" << "struct" << "switch" << "typedef"
		<< "union" << "unsigned" << "void"
		<< "volatile" << "while" << "->" << ">>" << "<<" << ">" << "<"
		<< "(" << ")" << "{" << "}" << "["
		<< "]" << "+" << "-" << "*" << "/"
		<< "=" << "!" << "." << "," << ";"
		<< ":" << "&" << "|";

	cpp20Keywords << "alignas" << "alignof"
		<< "and" << "and_eq" << "asm" << "atomic_cancel"
		<< "atomic_commit" << "atomic_noexcept" << "auto" << "bitand"
		<< "bitor" << "bool" << "break" << "case" << "catch"
		<< "char" << "char8_t" << "char16_t"
		<< "char32_t" << "class" << "compl"
		<< "concept" << "const" << "consteval"
		<< "constexpr" << "constinit" << "const_cast" << "continue" << "co_await"
		<< "co_return" << "co_yield"
		<< "decltype" << "default" << "delete" << "do"
		<< "double" << "dynamic_cast" << "else" << "enum" << "explicit" << "export"
		<< "extern" << "false" << "float" << "for" << "friend" << "goto" << "if"
		<< "inline" << "int" << "long" << "mutable" << "namespace" << "new" << "noexcept"
		<< "not" << "not_eq" << "nullptr"
		<< "operator" << "or" << "or_eq" << "private" << "protected" << "public" << "reflexpr"
		<< "register" << "reinterpret_cast" << "requires"
		<< "return" << "short" << "signed" << "sizeof" << "static"
		<< "static_assert" << "static_cast" << "struct" << "switch"
		<< "synchronized" << "template" << "this" << "thread_local"
		<< "throw" << "true" << "try" << "typedef" << "typeid" << "typename" << "union"
		<< "unsigned" << "using" << "virtual" << "void" << "volatile" << "wchar_t" << "while"
		<< "xor" << "xor_eq" << "xor_eq" << "->" << ">>" << "<<" << ">" << "<"
		<< "{" << "}" << "+" << "-" << "*" << "/"
		<< "=" << "!" << "." << "," << ";"
		<< ":" << "&" << "|";

}

void SyntaxHighlighter::highlightBlock(const QString& str) {
	int nState = previousBlockState();
	int nStart = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (nState == InsideCStyleComment) {
			if (str.mid(i, 2) == "*/") {
				nState = NormalState;
				if (whatStx == 0) {
					setFormat(nStart, i - nStart + 2, Qt::black);
				}
				setFormat(nStart, i - nStart + 2, commentColor);
				i++;
			}
		} else if (nState == InsideCString) {
			if (str.mid(i, 1) == "\"" || str.mid(i, 1) == "\'") {
				if (str.mid(i - 1, 2) != "\\\""
					&& str.mid(i - 1, 2) != "\\\'"
					) {
					nState = NormalState;
					if (whatStx == 0) {
						setFormat(nStart, i - nStart + 1, Qt::black);
					}
					setFormat(nStart, i - nStart + 1, strColor);
				}
			}
		} else {
			if (str.mid(i, 2) == "//") {
				if (whatStx == 0) {
					setFormat(nStart, str.length() - i, Qt::black);
				}
				setFormat(i, str.length() - i, commentColor);
				break;
			} else if (str.mid(i, 1) == "#") {
				if (whatStx == 0) {
					setFormat(nStart, str.length() - i, Qt::black);
				}
				setFormat(i, str.length() - i, includeColor);
				break;
			}  else if (str.mid(i, 2) == "/*") {
				nStart = i;
				nState = InsideCStyleComment;
			} else if (str.mid(i, 1) == "\"" || str.mid(i, 1) == "\'") {
				nStart = i;
				nState = InsideCString;
			} else {
				QString strKeyword = getKeyword(i, str);
				if (!strKeyword.isEmpty()) {
					if (whatStx == 0) {
						setFormat(nStart, strKeyword.length(), Qt::black);
					}
					setFormat(i, strKeyword.length(), wordColor);
					i += strKeyword.length() - 1;
				}
			}
		}
	}
	if (whatStx == 0) {
		setFormat(nStart, str.length()-nStart, Qt::black);
	}
	if (nState == InsideCStyleComment) {
		setFormat(nStart, str.length() - nStart, commentColor);
	}
	if (nState == InsideCString) {
		setFormat(nStart, str.length() - nStart, strColor);
	}
	setCurrentBlockState(nState);
}

QString SyntaxHighlighter::getKeyword(int nPos, const QString& str) const {
	QString strTemp = "";
	QStringList keywords;
	if (whatStx == 1) {
		keywords = cKeywords;
	} else if (whatStx == 2) {
		keywords = cppKeywords;
	} else if (whatStx == 3) {
		keywords = cpp20Keywords;
	}
	foreach(QString strKeyword, keywords) {
		if (str.mid(nPos, strKeyword.length()) == strKeyword) {
			strTemp = strKeyword;
			break;
		}
	}
	return strTemp;
}