#include "Notepad.h"

Notepad::Notepad(QMainWindow* parent) : QMainWindow(parent)
    , fileName("[No Name]"), isChanged(false), isSmthOpen(false)
    , isStxActive(false) 
{
    CreateActions();

    connect(openAction, SIGNAL(triggered()), this, SLOT(Open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(Exit()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(newAction, SIGNAL(triggered()), this, SLOT(NewFile()));

    connect(undoAction, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(SelectAll()));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(Paste()));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(Copy()));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(Clear()));
    connect(findAction, SIGNAL(triggered()), this, SLOT(Find()));
    connect(findRepAction, SIGNAL(triggered()), this, SLOT(FindAndReplace()));

    connect(setFontAction, SIGNAL(triggered()), this, SLOT(SetFont()));
    connect(setLineWrapAction, SIGNAL(triggered()), this, SLOT(SetLineWrap()));

    connect(changeBackColorAction, SIGNAL(triggered()), this, SLOT(ChangeBackColor()));
    connect(changeStrColorAction, SIGNAL(triggered()), this, SLOT(ChangeStrColor()));
    connect(setStatusBarAction, SIGNAL(triggered()), this, SLOT(SetStatusBar()));
    connect(setStxStatusAction, SIGNAL(triggered()), this, SLOT(SetStxStatus()));
    connect(setToolBarAction, SIGNAL(triggered()), this, SLOT(SetToolBar()));

    connect(setCStxAction, SIGNAL(triggered()), this, SLOT(SetCStxColor()));
    connect(setCppStxAction, SIGNAL(triggered()), this, SLOT(SetCppStxColor()));
    connect(setCpp20StxAction, SIGNAL(triggered()), this, SLOT(SetCpp20StxColor()));
    connect(setDefaultStxAction, SIGNAL(triggered()), this, SLOT(SetDefaultStx()));

    connect(setHighlightAction, SIGNAL(triggered()), this, SLOT(SetHighlightStyle()));

    connect(showHelpAction, SIGNAL(triggered()), this, SLOT(ShowHelp()));
    connect(toIniAction, SIGNAL(triggered()), this, SLOT(SettingsToIni()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    editMenu = menuBar()->addMenu(tr("&Edit"));
    formatMenu = menuBar()->addMenu(tr("&Format"));
    viewMenu = menuBar()->addMenu(tr("&View"));

    stxMenu       = new QMenu(tr("&Syntax Version"), viewMenu);
    highlightMenu = new QMenu(tr("&Syntax Style"));
    helpMenu = menuBar()->addMenu(tr("&Help")); 

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(clearAction);
    editMenu->addAction(selectAllAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(findRepAction);

    formatMenu->addAction(setFontAction);
    formatMenu->addAction(setLineWrapAction);

    viewMenu->addAction(changeBackColorAction);
    viewMenu->addAction(changeStrColorAction);
    viewMenu->addSeparator();
    viewMenu->addAction(setStatusBarAction);
    viewMenu->addAction(setStxStatusAction);
    viewMenu->addAction(setToolBarAction);
    viewMenu->addSeparator();
    viewMenu->addMenu(stxMenu);
    viewMenu->addMenu(highlightMenu);

    stxMenu->addAction(setCStxAction);
    stxMenu->addAction(setCppStxAction);
    stxMenu->addAction(setCpp20StxAction);
    stxMenu->addAction(setDefaultStxAction);

    highlightMenu->addAction(setHighlightAction);
    highlightMenu->addAction(uploadStyleAction);
    highlightMenu->addAction(defaultStyleAction);

    helpMenu->addAction(showHelpAction);
    helpMenu->addAction(toIniAction);

    text = new QTextEdit;

    textEdit = new QTextEditHighlighter(text);
    setCentralWidget(textEdit);

    connect(textEdit, SIGNAL(textChanged()), this, SLOT(TextChanged()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(UpdateStatusBar()));
    connect(textEdit, SIGNAL(cursorPositionChanged()),this, SLOT(UpdateCursorPosition()));

    CreateToolBar();
    CreateStatusBar();
    UpdateStatusBar();

    textEdit->setTabStopWidth(20);

    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(HighlightCurrentLine()));

    setWindowTitle(fileName);
}

void Notepad::CreateActions() {
    const QIcon newIcon   = QIcon::fromTheme("document-new", QIcon("new_big.png"));
    const QIcon openIcon  = QIcon::fromTheme("document-open", QIcon("open.png"));
    const QIcon saveIcon  = QIcon::fromTheme("document-save", QIcon("save.png"));
    const QIcon undoIcon  = QIcon::fromTheme("document-undo", QIcon("undo.png"));
    const QIcon redoIcon  = QIcon::fromTheme("document-redo", QIcon("redo.png"));
    const QIcon copyIcon  = QIcon::fromTheme("document-copy", QIcon("copy.png"));
    const QIcon cutIcon   = QIcon::fromTheme("document-cut", QIcon("cut.png"));
    const QIcon pasteIcon = QIcon::fromTheme("document-paste", QIcon("paste.png"));
    const QIcon findIcon  = QIcon::fromTheme("document-find", QIcon("find.png"));

    openAction   = new QAction(openIcon, tr("&Open"), this);
    saveAction   = new QAction(tr("&Save"), this);
    exitAction   = new QAction(tr("&Exit"), this);
    newAction    = new QAction(newIcon, tr("&New"), this);
    saveAsAction = new QAction(saveIcon, tr("&Save As..."), this);

    undoAction      = new QAction(undoIcon, tr("&Undo"), this);
    redoAction      = new QAction(redoIcon, tr("&Redo"), this);
    selectAllAction = new QAction(tr("&Select All"), this);
    cutAction       = new QAction(cutIcon, tr("&Cut"), this);
    pasteAction     = new QAction(pasteIcon, tr("&Paste"), this);
    copyAction      = new QAction(copyIcon, tr("&Copy"), this);
    clearAction     = new QAction(tr("&Clear"), this);
    findAction      = new QAction(tr("&Find..."), this);
    findRepAction   = new QAction(findIcon, tr("&Find And Replace..."), this);

    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    findAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));

    setFontAction     = new QAction(tr("&Set Font"), this);
    setLineWrapAction = new QAction(tr("&Line Wrap"), this);
    setLineWrapAction->setCheckable(true);
    setLineWrapAction->setChecked(true);

    changeBackColorAction = new QAction(tr("&Set Background Color"), this);
    changeStrColorAction  = new QAction(tr("&Set Line Color"), this);
    setStatusBarAction    = new QAction(tr("&Status Bar"), this);
    setStxStatusAction    = new QAction(tr("&Syntax Highlight"), this);
    setToolBarAction      = new QAction(tr("&Tool Bar"), this);
    setLineNumberAction   = new QAction(tr("&Line Numbers"), this);

    setStatusBarAction->setCheckable(true);
    setStatusBarAction->setChecked(true);
    setStxStatusAction->setCheckable(true);
    setStxStatusAction->setChecked(false);
    setToolBarAction->setCheckable(true);
    setToolBarAction->setChecked(true);
    setLineNumberAction->setCheckable(true);
    setLineNumberAction->setChecked(true);

    setCStxAction       = new QAction(tr("&C89"), this);
    setCppStxAction     = new QAction(tr("&C++03"), this);
    setCpp20StxAction   = new QAction(tr("&C++20"), this);
    showHelpAction      = new QAction(tr("&Show Information"), this);
    setDefaultStxAction = new QAction(tr("&Default"), this);
    setHighlightAction  = new QAction(tr("&Save Style"), this);
    uploadStyleAction   = new QAction(tr("&Upload Style"), this);
    defaultStyleAction  = new QAction(tr("&Default"), this);
    defaultStyleAction->setCheckable(true);
    defaultStyleAction->setChecked(true);


    setDefaultStxAction->setCheckable(true);
    setDefaultStxAction->setChecked(true);
    setCpp20StxAction->setCheckable(true);
    setCpp20StxAction->setChecked(false);
    setCppStxAction->setCheckable(true);
    setCppStxAction->setChecked(false);
    setCStxAction->setCheckable(true);
    setCStxAction->setChecked(false);

    toIniAction = new QAction(tr("&Settings To Ini"), this);

}

void Notepad::CreateStatusBar() {
    statusbar = new QStatusBar;

    sizeLabel = new QLabel;
    timeLabel = new QLabel;
    cursorLabel = new QLabel;

    sizeLabel->setMinimumWidth(150);
    timeLabel->setMinimumWidth(200);
    cursorLabel->setMinimumWidth(150);
    statusbar->addWidget(cursorLabel);
    statusbar->addWidget(timeLabel);
    statusbar->addWidget(sizeLabel);
    cursorLabel->setText("Line: " + QString::number(0) + " Column: " + QString::number(0));
    sizeLabel->setText("Length: " + QString::number(0) + " Lines: " + QString::number(0)
        + " Symbols: " + QString::number(0) + " Size: " + QString::number(0));
    cursorLabel->setText("Line: " + QString::number(1) + " Column: " + QString::number(1));
    setStatusBar(statusbar);
}

void Notepad::CreateToolBar() {
    toolbar = addToolBar(tr("Tool Bar"));
    toolbar->setContextMenuPolicy(Qt::PreventContextMenu);
    toolbar->addAction(newAction);
    toolbar->addAction(openAction);
    toolbar->addAction(saveAsAction);
    toolbar->addSeparator();
    toolbar->addAction(undoAction);
    toolbar->addAction(redoAction);
    toolbar->addSeparator();
    toolbar->addAction(copyAction);
    toolbar->addAction(cutAction);
    toolbar->addAction(pasteAction);
    toolbar->addSeparator();
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(16, 16));
    toolButton = new QToolButton;
    toolMenu   = new QMenu(tr("&Menu"), this);
    toolMenu->addAction(findRepAction);
    toolMenu->addAction(findAction);
    toolButton->setMenu(toolMenu);
    toolButton->setPopupMode(QToolButton::InstantPopup);
    toolbar->addWidget(toolButton);
    const QIcon findIcon = QIcon::fromTheme("document-find", QIcon("find.png"));
    toolButton->setIcon(findIcon);
    toolButton->setToolTip("Find/Find And Replace...");
}

void Notepad::SetToolBar() {
    if (toolbar->isHidden()) {
        toolbar->show();
    } else {
        toolbar->hide();
    }
}

void Notepad::Open() {
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Cannot open file"));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    }
    isSmthOpen = true;
    setWindowTitle(fileName);
}

void Notepad::Save() {
    if (fileName == "[No Name]") {
        SaveAs();
    }
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", 
            "file can't be saved!\nNote: if this is 1st time to save notes in a file,\nYou have to choose where to save it\n");
        return;
    }
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
    setWindowTitle(fileName);
}

void Notepad::quit() {}

void Notepad::NewFile() {
    if (isSmthOpen) {
        if (fileName == "[No Name]") {
            fileName = "Untiteled.txt";
        }
        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Cannot save file"));
            } else {
                QTextStream stream(&file);
                stream << textEdit->toPlainText();
                stream.flush();
                file.close();
            }
        }
        textEdit->clear();
        setWindowTitle("[No Name]");
    }
    textEdit->clear();
    setWindowTitle("[No Name]");
}

void Notepad::SaveAs() {
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Cannot save file"));
        } else {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
    setWindowTitle(fileName);
}

void Notepad::Exit() {
    int n = QMessageBox::warning(0,
        "Warning!",
        "Do you want to save the file?",
        QMessageBox::Yes,
        QMessageBox::No,
        QMessageBox::Cancel
        );

    if (n == QMessageBox::Cancel) {
        return;
    }
    if (n == QMessageBox::Yes) {
        SaveAs();
        qApp->quit();
    }
    if (n == QMessageBox::No) {
        qApp->quit();
    }
}

void Notepad::closeEvent(QCloseEvent* event) {
    int n = QMessageBox::warning(0,
        "Warning!",
        "Do you want to save the file?",
        QMessageBox::Yes,
        QMessageBox::No,
        QMessageBox::Cancel
        );

    if (n == QMessageBox::Cancel) {
        event->ignore();
        return;
    }
    if (n == QMessageBox::Yes) {
        SaveAs();
        qApp->quit();
    }
    if (n == QMessageBox::No) {
        qApp->quit();
    }

}

void Notepad::Undo() {
    textEdit->undo();
}

void Notepad::Redo() {
    textEdit->redo();
}

void Notepad::SelectAll() {
    textEdit->selectAll();
}

void Notepad::Cut() {
    textEdit->cut();
}

void Notepad::Paste() {
    textEdit->paste();
}

void Notepad::Copy() {
    textEdit->copy();
}

void Notepad::Clear() {
    textEdit->clear();
}

void Notepad::Find() {
    QString str = QInputDialog::getText(this, "Find", "Find");
    QTextCursor cursor = textEdit->document()->find(str);
    if (!cursor.isNull()) {
        textEdit->setTextCursor(cursor);
    }
}

void Notepad::FindAndReplace() {
    InputDialog dmd(this);
    dmd.exec();
    QTextCursor cursor = textEdit->document()->find(dmd.getFind());
    if (!cursor.isNull()) {
        textEdit->setTextCursor(cursor);
        textEdit->insertPlainText(dmd.getReplace());
    }
}

void Notepad::SetFont() {
    bool isSelected;
    font = QFontDialog::getFont(&isSelected, this);
    if (isSelected) {
        textEdit->setFont(font);
    }
}

void Notepad::SetLineWrap() {
    if (setLineWrapAction->isChecked()) {
        setLineWrapAction->setChecked(true);
        textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    } else {
        textEdit->setLineWrapMode(QTextEdit::NoWrap);
        setLineWrapAction->setChecked(false);
    }
}

void Notepad::TextChanged() {
    isChanged = true;
    setWindowTitle("*"+fileName);
}

void Notepad::ChangeBackColor() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    QPalette palette;
    palette.setColor(QPalette::Base, color);
    if (color.isValid()) {
        textEdit->setPalette(palette);
        backColor = color;
    }
}

void Notepad::ChangeStrColor() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        currentLineColor = color;
    }
}

void Notepad::SetStatusBar() {
    if (statusbar->isHidden()) {
        statusBar()->show();
    } else {
        statusBar()->hide();
    }
}

void Notepad::SetStxStatus() {
    if (isStxActive) {
        delete stxHighlighter;
        stxHighlighter = new SyntaxHighlighter(textEdit->document(), 0);
        isStxActive = false;
        setDefaultStxAction->setChecked(true);
        setCpp20StxAction->setChecked(false);
        setCppStxAction->setChecked(false);
        setCStxAction->setChecked(false);
    } else {
        stxHighlighter = new SyntaxHighlighter(textEdit->document(), 2);
        isStxActive = true;
        setDefaultStxAction->setChecked(false);
        setCpp20StxAction->setChecked(false);
        setCppStxAction->setChecked(true);
        setCStxAction->setChecked(false);
    }
}

void Notepad::SetHighlightStyle() {
    QSettings sett("style/style", QSettings::IniFormat);
    sett.beginGroup("STYLE");
    sett.setValue("KeyWordColor", stxHighlighter->wordColor);
    sett.setValue("InludeColor", stxHighlighter->includeColor);
    sett.setValue("CommentColor", stxHighlighter->commentColor);
    sett.setValue("StringColor", stxHighlighter->strColor);
    sett.endGroup();
}

void Notepad::SetCStxColor() {
    if (stxHighlighter && isStxActive) {
        delete stxHighlighter;
    }
    stxHighlighter = new SyntaxHighlighter(textEdit->document(), 1);
    setDefaultStxAction->setChecked(false);
    setCpp20StxAction->setChecked(false);
    setCppStxAction->setChecked(false);
    setCStxAction->setChecked(true);
    isStxActive = true;
}

void Notepad::SetCppStxColor() {
    if (stxHighlighter && isStxActive) {
        delete stxHighlighter;
    }
    stxHighlighter = new SyntaxHighlighter(textEdit->document(), 2);
    setDefaultStxAction->setChecked(false);
    setCpp20StxAction->setChecked(false);
    setCppStxAction->setChecked(true);
    setCStxAction->setChecked(false);
    isStxActive = true;
}

void Notepad::SetCpp20StxColor() {
    if (stxHighlighter && isStxActive) {
        delete stxHighlighter;
    }
    stxHighlighter = new SyntaxHighlighter(textEdit->document(), 3);
    setDefaultStxAction->setChecked(false);
    setCpp20StxAction->setChecked(true);
    setCppStxAction->setChecked(false);
    setCStxAction->setChecked(false);
    isStxActive = true;
}

void Notepad::SetDefaultStx() {
    if (stxHighlighter && isStxActive) {
        delete stxHighlighter;
        stxHighlighter = new SyntaxHighlighter(textEdit->document(), 0);
        isStxActive = false;
    }
}

void Notepad::ShowHelp() {
    QString str = QT_VERSION_STR;
    QMessageBox about;
    about.setText("Ala gvim");
    about.setInformativeText("Alexander Trisch\nBuilt 05.11.20\nBuild version - 4.8.7\nUser's version - " + str);
    about.setStandardButtons(QMessageBox::Ok);
    QPixmap pic(16, 16);
    pic.load("me.png");
    about.setIconPixmap(pic);
    about.setDefaultButton(QMessageBox::Ok);
    about.setWindowTitle("About");
    about.show();
    about.exec();
}

void Notepad::UpdateStatusBar() {
    QString text = textEdit->toPlainText();
    int wordCount = text.split(QRegExp("(\\s|\\n|\\r)+")
        , QString::SkipEmptyParts).count();
    int lineCount = textEdit->document()->lineCount();
    int symbCount = textEdit->document()->characterCount();
    double textsize = symbCount / 1024.0;
    
    QFileInfo fileInfo(fileName);
    QDateTime date = fileInfo.lastModified();
    sizeLabel->setText("Length: " + QString::number(wordCount) + " Lines: " + QString::number(lineCount)
        + " Symbols: " + QString::number(symbCount) + " Size: " + QString::number(textsize, 'g', 2) + "KB");
    timeLabel->setText("Last modified: " + date.toString());
}

void Notepad::UpdateCursorPosition() {
    QTextCursor cursor = textEdit->textCursor();
    int y = cursor.blockNumber() + 1;
    int x = cursor.columnNumber() + 1;
    cursorLabel->setText("Line: " + QString::number(y) + " Column: " + QString::number(x));
}

void Notepad::HighlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    QColor lineColor = QColor(currentLineColor).lighter(160);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textEdit->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
    textEdit->setExtraSelections(extraSelections);
}

void Notepad::SettingsToIni() {
    QSettings sett("settings/settings", QSettings::IniFormat);
    sett.beginGroup("SETTINGS");
    sett.setValue("LineColor", currentLineColor);
    sett.setValue("SyntaxHighlight", isStxActive);
    sett.setValue("Font", font);
    sett.setValue("TextColor", textColor);
    sett.setValue("BackgroundColor", backColor);
    sett.endGroup();
}
