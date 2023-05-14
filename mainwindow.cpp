#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>

using namespace std;

vector<int> numbersNotSorted;
vector<int> numbersSorted;
int sortTime;


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
    numbersNotSorted.clear();

    int size=(ui->size->text()).toInt();
    ui->outSize->setText(QString::number(size));
    int number;

    QListWidget listwidget;
    QString widgetItem;

   // Generate a list of integers
   for (int i = 0; i < size; ++i)
   {
       number = rand()%1001;
       numbersNotSorted.push_back(number);
       widgetItem = QString::number(number);
       listwidget.addItem(widgetItem);
        ui->listWidget->insertItem(i+1, widgetItem);

   }
   numbersSorted = numbersNotSorted;
}


int binarySearch(std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // return the index if target found
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // return -1 if target not found
}


int linearSearch(std::vector<int>& arr, int target) {
    for (int i = 0; i < int(arr.size()); i++) {
        if (arr[i] == target) {
            return i; // return the index if target found
        }
    }
    return -1; // return -1 if target not found
}


void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp vectors back into arr[l..r]
    int i = 0; // Initial index of first subvector
    int j = 0; // Initial index of second subvector
    int k = l; // Initial index of merged subvector

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l >= r) {
        return; // Returns recursively
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}


void MainWindow::on_MergeSort_clicked()
{
    ui->sortingAlgo->setText("Merge Sort");
    auto start = std::chrono::steady_clock::now();
    ui->listWidget->clear();
    ui->message->setText("Array Sorted");

    mergeSort(numbersSorted,0,numbersSorted.size()-1);

    QListWidget listwidget;
    QString widgetItem;

    for (int i = 0; i < int(numbersSorted.size()); ++i)
    {
        widgetItem = QString::number(numbersSorted.at(i));
        listwidget.addItem(widgetItem);
        ui->listWidget->insertItem(i+1, widgetItem);

    }
    auto end = std::chrono::steady_clock::now();
    sortTime = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

}


void MainWindow::on_STLsort_clicked()
{

    ui->sortingAlgo->setText("STL Sort");

    auto start = std::chrono::steady_clock::now();
    numbersSorted = numbersNotSorted;
    ui->listWidget->clear();
    ui->message->setText("Array Sorted");
    sort(numbersSorted.begin(), numbersSorted.end());

    QListWidget listwidget;
    QString widgetItem;

    for (int i = 0; i < int(numbersSorted.size()); ++i)
    {
        widgetItem = QString::number(numbersSorted.at(i));
        listwidget.addItem(widgetItem);
        ui->listWidget->insertItem(i+1, widgetItem);

    }
    auto end = std::chrono::steady_clock::now();
    sortTime = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}





void MainWindow::on_searchBTN_clicked()
{
    long searchtime = 55;
    int result = -1;
    int target = ui->numberSearch->text().toInt();


    if(ui->normalbtn->isChecked()){
        ui->searchingAlgo->setText("Normal Search");
        auto start = std::chrono::steady_clock::now();
        result = linearSearch(numbersSorted,target);
        auto end = std::chrono::steady_clock::now();
        searchtime = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    }else if(ui->binarybtn->isChecked()){
        ui->searchingAlgo->setText("Binary Search");
        auto start = std::chrono::steady_clock::now();
        result = binarySearch(numbersSorted,target);
        auto end = std::chrono::steady_clock::now();
        searchtime = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    };


    QMessageBox Qmessage;

    if(result == -1){
        QMessageBox::information(this,"Number not found","The number was not found in the array\n the searching took time "+QString::number(searchtime)+" nanoseconds \n the sorting took time "+ QString::number(sortTime)+" nanoseconds");

    }else{
        QMessageBox::information(this,"Number was found","The number was found in the array\n the searching took time "+QString::number(searchtime)+" nanoseconds \n the sorting took time "+ QString::number(sortTime)+" nanoseconds");

    };
}



