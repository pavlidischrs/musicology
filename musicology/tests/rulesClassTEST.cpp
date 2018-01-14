#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <vector>

#include "rulesClass.h"


TEST(rulesClass, answerCheck){

    RulesClass obj;

    rulesSource source = USE_ALGORITHM;

    std::vector<int> givenAnswer1 = {2,4,3,4,5,6,7};
    std::vector<int> givenExercise1 = {2,4,5,6,7,8,9};


    std::vector<int> givenAnswer2;
    std::vector<int> givenExercise2 = {2,4,5,6,7,8,9};

    std::vector<int> givenAnswer3 = {2,4,5,6,7,8,9};
    std::vector<int> givenExercise3 = {2,4,5,6,7,8,9};

    EXPECT_EQ(1, obj.checkAnswer( &givenAnswer1, &givenExercise1, source));
    EXPECT_EQ(0, obj.checkAnswer( &givenAnswer2, &givenExercise2, source));
    EXPECT_EQ(-1, obj.checkAnswer( &givenAnswer3, &givenExercise3, source));

}





