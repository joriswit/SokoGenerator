#ifndef SOKOGENERATOR_H
#define SOKOGENERATOR_H

#include <QObject>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <queue>
#include <tuple>

using namespace std;

#define WALL '#'
#define FLOOR ' '


class SokoGenerator : public QObject{
    Q_OBJECT
    typedef vector<vector<char>> TwoDVector_char;
    typedef vector<vector<int>> TwoDVector_int;


private:
    int roomWidth;
    int roomHeight;
    int noOfBoxes;
    int noOfLevels;
    int difficulty;
    int percentage;

    struct Level {
        TwoDVector_char grid;
    };

    std::vector<Level> levels;
    std::vector<Level> patterns;

public:
    explicit SokoGenerator(QObject *parent = 0);
    ~SokoGenerator();

    void setRoomWidth(int value){ roomWidth = value; }
    void setRoomHeight(int value){ roomHeight = value; }
    void setBoxes(int value){ noOfBoxes = value; }
    void setLevels(int value){ noOfLevels = value; }
    void setDifficulty(int value){ difficulty = value; }
    void setPercentage(int value){ percentage = value; }

    void updatePercentage(float value);
    void listLevelSet(std::vector<Level>);

    void generateLevel();
    void generateLevel(int roomWidth, int roomHeight, int noOfBoxes, int difficulty, int levelNumber);
    void clearVectors();

    int randomNumber(int min, int max, int divisor = 1);

    void initLevel(Level *level, int roomWidth, int roomHeight);
    void placePatterns(SokoGenerator::Level *level, int roomWidth, int roomHeight);
    void rotatePattern(TwoDVector_char *pattern, int rotation);
    bool checkConnectivity(SokoGenerator::Level *level, int roomWidth, int roomHeight);
    TwoDVector_char getLevel(int level);
    void floodfill(TwoDVector_int &level, int row, int column, int roomWidth, int roomHeigh);

signals:
    void changeProgressBar(float);
    void addToList(int);

};

#endif // SOKOGENERATOR_H
