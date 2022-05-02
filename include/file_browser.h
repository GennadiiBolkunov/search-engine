#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class FileBrowser; }
QT_END_NAMESPACE

class FileBrowser : public QWidget
{
    Q_OBJECT
private:
    QDir dir;

    Ui::FileBrowser *ui;

public:
    explicit FileBrowser(const QString &dir_name, QWidget *parent = nullptr);
    ~FileBrowser();
    void addItem(const QString &itemName);
    void clearList();
    void editListInfo(QString text);
    const QDir &getCurrentDir();

public slots:

    void resetFileList();
};
#endif // WIDGET_H
