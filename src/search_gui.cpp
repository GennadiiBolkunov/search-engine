#include "search_gui.h"

SearchGUI::SearchGUI(QWidget *parent)
    : QWidget(parent), converterJson()
    {
    layout = new QGridLayout (this);
    searchButton = new QPushButton("search");
    spinBox = new QSpinBox();
    lineEdit = new QLineEdit();
    fileEditBrowser = new FileEditBrowser("../../files");

    layout->addWidget(spinBox, 0,0);
    layout->addWidget(lineEdit, 0,1);
    layout->addWidget(searchButton, 0, 2);
    layout->addWidget(fileEditBrowser, 1,0,1,3);

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
        fileEditBrowser->clearList();
        fileEditBrowser->editListInfo("Search result:");
        for (auto &request: result){
            if (request.empty())
                fileEditBrowser->editListInfo("No result :(");
            for (auto &document :request){
                fileEditBrowser->addItem(QString(converterJson.getFileName(document.doc_id).c_str()));
            }
        }
    });

    connect(fileEditBrowser, &FileEditBrowser::fileCreated, [this](QString fileName){
        converterJson.addFile(fileName.toStdString());
    });

    connect(fileEditBrowser, &FileEditBrowser::fileDeleted, [this](QString fileName){
        converterJson.deleteFile(fileName.toStdString());
    });
}

SearchGUI::~SearchGUI() {
    delete layout;
}
