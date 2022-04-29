#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QDialogButtonBox>

class FileEditBrowser : public QWidget
{
    Q_OBJECT
private:
    QDir *dir;

    QVBoxLayout *layout;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    QListWidget *list;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *resetButton;
    QPushButton *removeButton;

    QLabel *fileListInfo;
    QLabel *mode;
    QTextEdit *textEdit;
    QFile *currentFile;
    QString currentDirName;
    QString currentFileName;
    QDialogButtonBox *insure;

public:
    void addItem(const QString &itemName);
    void clearList();
    void editListInfo(QString text);
    explicit FileEditBrowser(const QString &dirName, QWidget *parent = nullptr);
    ~FileEditBrowser();

public slots:
    void createFile();
    void editItem();
    void removeItem();
    void resetFileList();

    signals:
    void fileCreated(QString fileName);
    void fileDeleted(QString fileName);

};
#endif // WIDGET_H
