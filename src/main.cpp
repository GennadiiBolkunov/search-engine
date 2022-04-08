#include "inverted_index.h"
#include "converter_json.h"
#include "gtest/gtest.h"
#include "search_server.h"

int main() {
    ConverterJSON conv;
    InvertedIndex myInd;
    myInd.UpdateDocumentBase(conv.GetTextDocuments());
    SearchServer myServ(myInd);
    conv.putAnswers(myServ.search(conv.GetRequests()));
    RUN_ALL_TESTS();
    return 0;
}
