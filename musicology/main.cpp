#include "mainwindow.h"
#include <QApplication>

#include "gtest/gtest.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Run tests.
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return a.exec();
}
