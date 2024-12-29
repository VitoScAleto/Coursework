#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H
#include <QPrintDialog>
#include <QPrinter>
#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QPushButton>
#include <QTextEdit>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QFileDialog>
#include <QDomDocument>
#include <QFontDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>
#include <toolbar.h>
#include <QInputDialog>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeyEvent>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QRegularExpression>
#include <QTextBlockFormat>
#include <QDomNode>

class TextManager : public QWidget
{
    Q_OBJECT

public:
    TextManager(QWidget *parent = nullptr, int user_id = -1, QString name = "null");

    QTextEdit *currentTextEdit() const
    {
            return qobject_cast<QTextEdit *>(textStack->currentWidget());
    }
    void savePagesToXml(const QString &filePath);

    void loadPagesFromXml(const QString &filePath);
    void showContextMenu(const QPoint &pos);
    void renamePage(int index);
    void keyPressEvent(QKeyEvent *event);
    void onTextCursorChanged();
    void handleCursorChange();

     //Database
    bool savePageToDatabase(int pageIndex);

    void updatePagesInDatabase();

    bool deletePageFromDatabase(int pageIndex);

    bool loadPagesFromDatabase();
    void addPageFromDb(QString& title,QString& content);
    void openSettings();
    void applyTheme(const QString &theme);

    // Database
    void printCurrentPage();
    bool eventFilter(QObject *obj, QEvent *event);
    void setupEventFilter();
    QPushButton* createButtonWithIcon(const QString &iconPath, void (TextManager::*slot)());
private slots:
    void addPage();
    void onTextChanged();
    void deletePage();

    void switchPage(int index);
private:

    struct PageInfo {
        int document_id;  // ID документа в базе данных
        QString title;    // Заголовок страницы
        QString content;  // Содержимое страницы
    };


    QList<PageInfo> pageInfoList;

    int q_user_id;
    QString q_name;
    QStackedWidget *textStack;
    QListWidget *pageList;
    ToolBar* toolbar;
};
#endif // TEXTMANAGER_H
