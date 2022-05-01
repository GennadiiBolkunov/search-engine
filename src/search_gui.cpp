#include "search_gui.h"

SearchGUI::SearchGUI(QWidget *parent)
    : QWidget(parent), converterJson(), fileBrowser("../../files")
    {
    layout = new QGridLayout (this);
    searchButton = new QPushButton("search");
    spinBox = new QSpinBox();
    lineEdit = new QLineEdit();

    layout->addWidget(spinBox, 0,0);
    layout->addWidget(lineEdit, 0,1);
    layout->addWidget(searchButton, 0, 2);
    layout->addWidget(&fileBrowser, 1,0,1,3);

    connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value){
        converterJson.setMaxResponses(value);
    });

    connect(searchButton, &QPushButton::clicked, [this](){
        converterJson.setRequest(lineEdit->text().toStdString());
        auto docs = converterJson.GetTextDocuments();
        auto requests = converterJson.GetRequests();
        InvertedIndex invertedIndex;
        invertedIndex.UpdateDocumentBase(docs);
        SearchServer searchServer(invertedIndex);
        auto result = searchServer.search(requests);
        converterJson.putAnswers(result);

        fileBrowser.clearList();
        fileBrowser.editListInfo("Search result:");
        for (auto &request: result){
            if (request.empty())
                fileBrowser.editListInfo("No result :(");
            for (auto &document :request){
                fileBrowser.addItem(QString(converterJson.getFileName(document.doc_id).c_str()));
            }
        }

    });
}

SearchGUI::~SearchGUI() {
    delete layout;
}
