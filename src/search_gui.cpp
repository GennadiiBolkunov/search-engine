#include "search_gui.h"


SearchGUI::SearchGUI(QWidget *parent)
    : QWidget(parent), converterJson(), fileBrowser("../../files")
    {
    layout = new QGridLayout (this);
    searchLine = new SearchLine;

    layout->addWidget(searchLine, 0,0);
    layout->addWidget(&fileBrowser, 1,0);

    connect(searchLine, &SearchLine::responsesNumChanged, [this](int value){
        converterJson.setMaxResponses(value);
    });

    connect(searchLine, &SearchLine::searchStarted, [this](const QString &request_text){
        converterJson.updateFiles(fileBrowser.getCurrentDir());
        converterJson.setRequest(request_text.toStdString());
        auto docs = converterJson.GetTextDocuments(fileBrowser.getCurrentDir());
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
