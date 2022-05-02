#ifndef SEARCH_ENGINE_SEARCH_LINE_H
#define SEARCH_ENGINE_SEARCH_LINE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SearchLine; }
QT_END_NAMESPACE

class SearchLine : public QWidget{
    Q_OBJECT

public:
    SearchLine(QWidget *parent = nullptr);
    ~SearchLine();

signals:
    void searchStarted(const QString &request_text);
    void responsesNumChanged(int value);
private:
    Ui::SearchLine *ui;
};

#endif //SEARCH_ENGINE_SEARCH_LINE_H
