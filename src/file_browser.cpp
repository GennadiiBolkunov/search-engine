#include "file_browser.h"
#include <QInputDialog>
#include <QTextStream>



//изменение директория
//добавить подтверждение удаления файлов


FileEditBrowser::FileEditBrowser(const QString &dirName, QWidget *parent)
    : QWidget(parent), currentDirName(dirName), currentFile(nullptr)
{
    hbox = new QHBoxLayout;
    vbox = new QVBoxLayout;
    list = new QListWidget;
    addButton = new QPushButton("create file");
    editButton = new QPushButton("edit file");
    resetButton = new QPushButton ("reset search\nresult");
    removeButton = new QPushButton("delete file");

    hbox->addWidget(list);
    vbox->addWidget(addButton);
    vbox->addWidget(editButton);
    vbox->addWidget(resetButton);
    vbox->addWidget(removeButton);
    hbox->addLayout(vbox);

    dir = new QDir;
    dir->mkdir(currentDirName);
    dir->cd(currentDirName);
    dir->setFilter(QDir::Files);
    dir->setSorting(QDir::Name);

    auto dirList =dir->entryInfoList();

    for(auto &el: dirList){
        auto itemName = el.fileName();
        if (!itemName.isEmpty())
            list->addItem(itemName);
        list->setCurrentRow(list->count()-1);
    }

    textEdit = new QTextEdit;
    textEdit->setDisabled(true);

    layout = new QVBoxLayout(this);
    fileListInfo = new QLabel("\""+currentDirName+"\" directory files:");
    mode = new QLabel("Choose file", this);
    layout->addWidget(fileListInfo);
    layout->addLayout(hbox);
    layout->addWidget(mode);
    layout->addWidget(textEdit);

    insure = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, nullptr);
    insure->setAccessibleDescription("Are you sure?");
    insure->setMinimumSize(200,100);
    insure->setCenterButtons(true);

    connect(addButton, &QPushButton::clicked, this, &FileEditBrowser::createFile);
    connect(editButton, &QPushButton::clicked, this, &FileEditBrowser::editItem);
    connect(removeButton, &QPushButton::clicked, this, &FileEditBrowser::removeItem);
    connect(resetButton, &QPushButton::clicked, this, &FileEditBrowser::resetFileList);

    connect(list, &QListWidget::itemClicked, [this](){
        currentFileName=list->currentItem()->text();
        mode->setText("File info:");
        textEdit->blockSignals(true);
        textEdit->setDisabled(true);
        QFile file(currentDirName+"/"+currentFileName);
        QString fsize;
        fsize.setNum(file.size());
        textEdit->setText("File: "+currentFileName+"\nSize: "+fsize+" bytes");
        textEdit->blockSignals(false);
    });

    connect(list, &QListWidget::itemDoubleClicked, [this](){
        mode->setText("File data:");
        currentFileName = list->currentItem()->text();
        if (currentFile){
            currentFile->close();
            delete currentFile;
        }
        currentFile = new QFile(currentDirName+"/"+currentFileName);
        currentFile->open(QIODevice::ReadWrite);
        QTextStream textFromFile(currentFile);
        QString displayText;
        while (!textFromFile.atEnd()){
            displayText+= textFromFile.readLine();
            displayText+="\n";
        }
        textEdit->setText(displayText);
        textFromFile.reset();
        displayText.clear();
        textEdit->setEnabled(true);
    });

    connect(textEdit, &QTextEdit::textChanged, [this](){
        if (currentFile){
            if (currentFile->isOpen()){
                currentFile->reset();
                QTextStream textToFile(currentFile);
                textToFile.reset();
                textToFile<<textEdit->toPlainText();

            }
        }
    });
}

void FileEditBrowser::addItem(const QString &itemName) {
    if (!itemName.isEmpty()){
        list->addItem(itemName);
        list->setCurrentRow(list->count()-1);
    }
}

void FileEditBrowser::clearList() {
    list->clear();
    textEdit->clear();
}

void FileEditBrowser::createFile(){
    QString itemName = QInputDialog::getText(this, "Create file", "Enter file name:");
    auto nameList = list->findItems(itemName, Qt::MatchExactly);
    if (nameList.isEmpty()){
        if (!itemName.isEmpty()){
            QFile newFile(currentDirName+"/"+itemName);
            if (newFile.open(QIODevice::WriteOnly)){
                addItem(itemName);
                emit fileCreated(itemName);
            }
        }
    }
}

void FileEditBrowser::editItem(){
    auto curItem=list->currentItem();
    if (list->currentRow()!=-1){
       QString currentName = QInputDialog::getText(this, "Edit", "Edit file name:", QLineEdit::Normal, QString(curItem->text()));
       auto nameList = list->findItems(currentName, Qt::MatchExactly);
       if (nameList.isEmpty()){
           if (!currentName.isEmpty()){
               QFile fileToEdit(currentDirName+"/"+curItem->text());
               if (currentFile){
                   if (currentFile->fileName() == fileToEdit.fileName()){
                       currentFile->close();
                       textEdit->clear();
                       textEdit->setDisabled(true);
                       delete currentFile;
                       currentFile = nullptr;
                   }
               }
               curItem->setText(currentName);
               fileToEdit.close();
               fileToEdit.rename(currentDirName+"/"+curItem->text());
           }
       }
    }
}
void FileEditBrowser::removeItem(){
    if (auto curItem = list->currentItem()){
        insure->show();
        connect(insure, &QDialogButtonBox::accepted, [this, curItem](){
            insure->close();
            QFile fileToDelete(currentDirName+"/"+curItem->text());
            if (currentFile){
                if (currentFile->fileName() == fileToDelete.fileName()){
                    currentFile->close();
                    textEdit->clear();
                    textEdit->setDisabled(true);
                    delete currentFile;
                    currentFile = nullptr;
                }
            }
            fileToDelete.close();
            fileToDelete.remove();
            emit fileDeleted(curItem->text());
            delete curItem;
        });

        connect(insure, &QDialogButtonBox::rejected, [this](){});
    }
}

void FileEditBrowser::resetFileList() {
    delete dir;
    dir=new QDir;
    dir->cd(currentDirName);
    fileListInfo->setText("\""+currentDirName+"\" directory files:");
    list->clear();
    auto dirList =dir->entryInfoList();

    for(auto &el: dirList){
        auto itemName = el.fileName();
        if (!itemName.isEmpty() && el.isFile())
            list->addItem(itemName);
        list->setCurrentRow(list->count()-1);
    }
}

void FileEditBrowser::editListInfo(QString text) {
    fileListInfo->setText(text);
}

FileEditBrowser::~FileEditBrowser()
{
    delete currentFile;
    delete dir;
    delete layout;
}

