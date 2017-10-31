#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtWidgets>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    systemScene_ = new QGraphicsScene();
    choicesScene_ = new QGraphicsScene();

    // Code for adding QGraphicsItems in a QGraphicsScene and the visualise with QGraphicsView
    ui->counterpointSystem->setScene(systemScene_);
    ui->counterpointSystem->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Code for adding QGraphicsItems in a QGraphicsScene and the visualise with QGraphicsView
    ui->choicesSystem->setScene(choicesScene_);
    ui->choicesSystem->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    widthOfItems_ =80;
    heightOfItems_ =80;

    qDebug() << ui->counterpointSystem->dragMode();

    givenAnswer_ = new std::vector<int>;
    givenExercise_ = new std::vector<int>;

    nextPosition_=0;


    // Rules Class
    rulesObject_ = new RulesClass("../musicology/rsc/rules");

    rules_ = rulesObject_->getRulesMap();

    rulesObject_->printRules(rules_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUpperPentagramSLOT(int noteItemID)
{

    // Zero flag means the user has filled all the pentagram.
    // So do not add any more symbols that happens to choose
    if(!flag_)
        return;

    // Keep user's answer
    givenAnswer_->push_back(noteItemID);

    // Add the chose item (passes as parameter from the updateUpperPentagram caller)
    addNoteToScene(systemScene_, noteItemID, nextPosition_*widthOfItems_, 0);

    // Go to next position
    nextPosition_++;

    // The user has filled all the pentagram
    // Check her answer and zero the flag_
    if(nextPosition_==sizeOfExercise_){
        on_checkAnswerButton_clicked();
        flag_=0;
    }

}





void MainWindow::displayChoices() {


    // Add all the the Notes
    for(int i=0; i<10; i++){
        addNoteToScene(choicesScene_, i, i*widthOfItems_, 0);
    }

}

void MainWindow::addNoteToScene(QGraphicsScene *scene, int noteItemID, int x, int y)
{

    // create a Musical Note item so as to add it in the QGraphicScene
    MusicalNoteItem *noteItem = new MusicalNoteItem(noteItemID);

    connect(noteItem, SIGNAL(updatePentagramSignal(int)), this, SLOT(updateUpperPentagramSLOT(int)));

    // Open the image
    QImage image("../musicology/rsc/" + QString::number(noteItemID) + ".png");

//    image = image.scaled(widthOfItems_,heightOfItems_,Qt::IgnoreAspectRatio);

    // Take pixmap from image
    noteItem->setPixmap(QPixmap::fromImage(image));

    // Place the item in the appropriate position
    noteItem->setPos(x, y);

    // Add it to the scene
    scene->addItem(noteItem);
}

// class generator:
struct c_unique {
  int current;
  c_unique() {current=0;}
  int operator()() {return current++;}
} UniqueNumber;

void MainWindow::on_newExerciseButton_clicked()
{

// Step 1: Clear previous exercise (if any)
    clearPreviousExercise();


// Step 2: Create the upper empty pentagram and display it
    for(int i=0; i<sizeOfExercise_; i++){
            addNoteToScene(systemScene_, 100, i*widthOfItems_, 0);
    }


// Step 3: Create the lower pentagram and display it
    // !!!Note we now create the exercise like this so as to be
    // random on each new exercise.
    // When we will have the rules the below procedure will be
    // substituted to create exercise according to rules

    givenExercise_->resize(sizeOfExercise_);

    // Generte a sequence from 0-sizeOfExercise_
    std::generate (givenExercise_->begin(), givenExercise_->end(), UniqueNumber);

    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Shuffle them
    shuffle (givenExercise_->begin(), givenExercise_->end(), std::default_random_engine(seed));

    int pos=0;
    std::for_each (givenExercise_->begin(), givenExercise_->end(),
                   [&](int num){
        addNoteToScene(systemScene_,  num, pos++*widthOfItems_, heightOfItems_);
    });

// Step 4: Display the Musical Notes choises
    displayChoices();

}


void MainWindow::clearPreviousExercise(){
    // Empty the text
    ui->answerResult->setText("");

    // Reset flag
    flag_=1;

    // Reset exercise
    nextPosition_=0;

    // Clear the scenes
    choicesScene_->clear();
    systemScene_->clear();

    // Empty the give answer vector
    givenAnswer_->clear();

    // Empty previous exercise vector
    givenExercise_->clear();
}


void MainWindow::on_checkAnswerButton_clicked()
{
    int answer = rulesObject_->checkAnswer(givenAnswer_, givenExercise_);

    if(answer == 1){
        ui->answerResult->setText("Congrats! You are Mozarts's descendant");
    }
    else if(answer == -1){
        ui->answerResult->setText("I'm sorry.. Your answer is incorrect :( ");
    }
    else{
        ui->answerResult->setText("Don't be hurry! Put something first");;
    }
}

void MainWindow::on_eraseSymbol_clicked()
{
    if(nextPosition_>0){
        nextPosition_--;
        addNoteToScene(systemScene_,  100, nextPosition_*widthOfItems_, 0);
        givenAnswer_->pop_back();
    }
}
