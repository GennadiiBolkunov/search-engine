#include "search_line.h"
#include "./ui_search_line.h"

SearchLine::SearchLine(QWidget *parent): QWidget(parent), ui(new Ui::SearchLine) {
    ui->setupUi(this);

    connect(ui->searchButton, &QPushButton::clicked, [this](){
        emit searchStarted(ui->lineEdit->text());
    });

    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this](int value){
        emit responsesNumChanged(value);
    });
}

SearchLine::~SearchLine() noexcept {

}