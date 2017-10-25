#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>
#include <QGraphicsView>
#include <QDebug>

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>

#include "musicalNoteItem.h"
#include "rulesClass.h"

namespace Ui {
class MainWindow;
}

using namespace Music;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


////     The mousePressEvent from MyNoteItem will be grapped from MainWindow to handle it
////     I.e. if a Note was selected to put it on the pentagram
//    static void mousePressEvent(QGraphicsSceneMouseEvent *event, int itemID);



private slots:

    // When the newExercisButton is clicked create a new exercise
    void on_newExerciseButton_clicked();

    /**
     * @brief updateUpperPentagram: This function is called every time the user clicks a Mysical Note (from the choices box)
     *                              to add it in the system-upper pentagram. (We make it a SLOT so as to connect it with the update() signal)
     * @param noteItemID
     *
     */
    void updateUpperPentagramSLOT(int noteItemID);

    void on_checkAnswerButton_clicked();

private:

    /**
     * @brief displaySequence   : display the exercise in the counterpointSystem (QGraphicsView)
     * @param sizeOfExercise    : length of the exercise
     * @param upper             : wether to fill the upper or the lower pentagram of the system
     */
    void displaySequence(int sizeOfExercise, int upper);

    /**
     * @brief displayChoices    : display the Notes choices in the choicesBox (QGraphicsView)
     * @param sizeOfExercise
     * @param upper
     */
    void displayChoices();

    /**
     * @brief addElementToScene : this functions adds a NoteItem to a scene
     * @param scene             : the scene where the item will be added
     * @param noteItemID        : the ID of the Musical Note
     * @param x                 : position in x axes
     * @param y                 : position in y axes
     */
    void addNoteToScene(QGraphicsScene* scene, int noteItemID, int x, int y );


    /**
     * @brief checkAnswer: In this method we examine the given answer according to the Rules
     */
    void checkAnswer();

    /**
     * @brief clearPreviousExercise: clear variables and scene of previous exercise
     */
    void clearPreviousExercise();

    // the next empty position of the upper pentagram. When the user adds a Note it is increased by 1
    int nextPosition_;


    // We will display the System (lower and upper pentagram) on this scene
    QGraphicsScene* systemScene_ ;

    // We will display the Note choices on this scene
    QGraphicsScene* choicesScene_ ;

    // Width and height of the Items inside the scenes
    int widthOfItems_;
    int heightOfItems_;

    // Size of the exercise (for the demo is 10)
    int sizeOfExercise_=10;

    int flag_=0;


    // We will keep the user's answer in this vector
    std::vector<int> *givenAnswer_;

    // We will keep the created exercise (lower pentagram) in this variable
    std::vector<int> *givenExercise_;


    // We will store the rules on this var
    map<int, vector<int>> rules_;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
