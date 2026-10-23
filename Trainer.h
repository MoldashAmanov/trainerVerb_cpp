#pragma once

#include "Verb.h"
#include <vector>
#include <random>
#include <string>
#include <chrono>

using namespace std;

class Trainer
{
    private:
        vector<Verb> verbs;
        int score;
        int totalQuestions;
        mt19937 gen;

        chrono::steady_clock::time_point quizStartTime;
        chrono::steady_clock::time_point quizEndTime;
        
        void initRandom();
        void loadVerbsFromFile(const string& filename);
        void loadDefaultVerbs();
        void showResults() const;
        void saveStats() const;

        string formatDuration(chrono::seconds duration) const;
    public:
        Trainer();
        void startQuiz(int qCount);
};