#include "file_browser.h"
#include "./ui_file_browser.h"
#include <QTextStream>
#include <QFile>

//изменение директория


FileBrowser::FileBrowser(const QString &dir_name, QWidget *parent)
    : QWidget(parent), ui(new Ui::FileBrowser), dir(dir_name)
{
    ui->setupUi(this);

    ui->lineEdit->setText(dir.absolutePath());

    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    auto dirList =dir.entryInfoList();

    for(auto &el: dirList){
        auto itemName = el.fileName();
        if (!itemName.isEmpty())
            ui->listWidget->addItem(itemName);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }

    connect(ui->browseButton, &QPushButton::clicked, [this](){
        
    });

    connect(ui->listWidget, &QListWidget::itemClicked, [this](){
        ui->fileBrowsingMode->setText("File info:");
        QFile file(dir.filePath(ui->listWidget->currentItem()->text()));
        QString fsize;
        fsize.setNum(file.size());
        ui->textBrowser->setText("File: "+ui->listWidget->currentItem()->text()+"\nSize: "+fsize+" bytes");
    });

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, [this](){
        ui->fileBrowsingMode->setText("File data:");
        QFile currentFile(dir.filePath(ui->listWidget->currentItem()->text()));
        currentFile.open(QIODevice::ReadWrite);
        QTextStream textFromFile(&currentFile);
        QString displayText;
        while (!textFromFile.atEnd()){
            displayText+= textFromFile.readLine();
            displayText+="\n";
        }
        ui->textBrowser->setText(displayText);
        textFromFile.reset();
        displayText.clear();
    });
}

void FileBrowser::addItem(const QString &itemName) {
    if (!itemName.isEmpty()){
        ui->listWidget->addItem(itemName);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
}

void FileBrowser::clearList() {
    ui->listWidget->clear();
    ui->textBrowser->clear();
}

void FileBrowser::resetFileList() {
    ui->fileListInfo->setText("\""+dir.dirName()+"\" directory files:");
    ui->listWidget->clear();
    auto dirList =dir.entryInfoList();

    for(auto &el: dirList){
        auto itemName = el.fileName();
        if (!itemName.isEmpty() && el.isFile())
            ui->listWidget->addItem(itemName);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
}

void FileBrowser::editListInfo(QString text) {
    ui->fileListInfo->setText(text);
}

FileBrowser::~FileBrowser()
{

}
