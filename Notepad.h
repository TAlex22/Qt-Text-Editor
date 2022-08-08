#ifndef _NOTEPAD_
#define _NOTEPAD_

#include "Dialogs.h"
#include "SyntaxHighlighter.h"
#include "QTextEditHighlighter.h"

#include <QtGui>

#include <iostream>
#include <string>


class Notepad : public QMainWindow {
    Q_OBJECT

public:
    explicit Notepad(QMainWindow* parent = 0);

protected:
    void closeEvent(QCloseEvent*);

private:
    void CreateActions();
    void CreateStatusBar();
    void CreateToolBar();

private slots:
    void Open();
    void Save();
    void quit();
    void NewFile();
    void SaveAs();
    void Exit();

    void Undo();
    void Redo();
    void SelectAll();
    void Cut();
    void Paste();
    void Copy();
    void Clear();
    void Find();
    void FindAndReplace();

    void SetFont();
    void SetLineWrap();

    void TextChanged();
    void ChangeBackColor();
    void ChangeStrColor();
    void SetStatusBar();
    void SetToolBar();
    void SetCStxColor();
    void SetCppStxColor();
    void SetCpp20StxColor();
    void SetDefaultStx();
    void SetStxStatus();
    void SetHighlightStyle();

    void ShowHelp();

    void UpdateStatusBar();
    void UpdateCursorPosition();
    void HighlightCurrentLine();

    void SettingsToIni();

private:
    QLabel* sizeLabel;
    QLabel* cursorLabel;
    QLabel* timeLabel;
    QStatusBar* statusbar;
    QToolBar* toolbar;
    QFont font;

    QTextEdit* text;
    QAction* saveAction;
    QAction* exitAction;
    QAction* openAction;
    QAction* newAction;
    QAction* saveAsAction;
    
    QAction* undoAction;
    QAction* redoAction;
    QAction* selectAllAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* copyAction;
    QAction* clearAction;
    QAction* findAction;
    QAction* findRepAction;

    QAction* setFontAction;
    QAction* setLineWrapAction;

    QAction* changeBackColorAction;
    QAction* changeStrColorAction;
    QAction* setStatusBarAction;
    QAction* setToolBarAction;
    QAction* setLineNumberAction;

    QAction* setCStxAction;
    QAction* setCppStxAction;
    QAction* setCpp20StxAction;
    QAction* setStxStatusAction;
    QAction* setDefaultStxAction;
    QAction* setHighlightAction;
    QAction* uploadStyleAction;
    QAction* defaultStyleAction;

    QToolButton* toolButton;

    QAction* showHelpAction;
    QAction* toIniAction;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* formatMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;

    QMenu* stxMenu;
    QMenu* toolMenu;
    QMenu* highlightMenu;

    QString fileName;

    QColor currentLineColor = Qt::yellow;
    QColor textColor;
    QColor backColor;

    SyntaxHighlighter* stxHighlighter;
    QTextEditHighlighter* textEdit;
    
    bool isChanged;
    bool isSmthOpen;
    bool isStxActive;

};

#endif // !_NOTEPAD_