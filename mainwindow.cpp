#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

using namespace std;

vector<int> numbers;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generate_clicked()
{
    ui->listWidget->clear();
    numbers.clear();

    int size=(ui->size->text()).toInt();
    int number;

    QListWidget listwidget;
    QString widgetItem;

   // Generate a list of integers
   for (int i = 0; i < size; ++i)
   {
       number = rand()%11;
       numbers.push_back(number);
       widgetItem = QString::number(number);
       listwidget.addItem(widgetItem);
        ui->listWidget->insertItem(i+1, widgetItem);

   }
}


void merge(vector<int> array, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp lists
    QList<int> leftArray, rightArray;

    // Copy data to temp lists leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray.append(array[left + i]);
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray.append(array[mid + 1 + j]);

    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp lists back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(vector<int>& array, int begin, int end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}
void MainWindow::on_MergeSort_clicked()
{
    ui->listWidget->clear();

    mergeSort(numbers,0,numbers.size()-1);
    QListWidget listwidget;
    QString widgetItem;

    for (int i = 0; i < int(numbers.size()); ++i)
    {
        widgetItem = QString::number(numbers.at(i));
        listwidget.addItem(widgetItem);
        ui->listWidget->insertItem(i+1, widgetItem);

    }

}

