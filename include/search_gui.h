#ifndef SEARCH_ENGINE_SEARCH_GUI_H
#define SEARCH_ENGINE_SEARCH_GUI_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include "file_browser.h"
#include "inverted_index.h"
#include "converter_json.h"
#include "search_server.h"
#include <QSpinBox>
#include "search_line.h"

class SearchGUI : public QWidget{
    Q_OBJECT

private:
    QGridLayout *layout;
    SearchLine *searchLine;
    FileBrowser fileBrowser;

    ConverterJSON converterJson;
public:
    explicit SearchGUI(QWidget *parent=nullptr);
    ~SearchGUI() override;
};

#endif //SEARCH_ENGINE_SEARCH_GUI_H
