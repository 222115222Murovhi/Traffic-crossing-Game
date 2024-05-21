#ifndef LIBTRAFFIC_H_INCLUDED
#define LIBTRAFFIC_H_INCLUDED
#include<iostream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<assert.h>
#include<functional>
using namespace std;
enum StatusCode{
    ERROR_ARGS=-4,
    ERROR_CONV,
    ERROR_LOST,
    ERROR_WON,
    SUCCESS
};
enum Directions{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const int numBooks=3;
const int lives=3;

enum ENTITY{
    EMPTY_SPACE,
    TRAFFIC_LEFT,
    TRAFFIC_RIGHT,
    BOOK,
    PLAYER
};
enum GameStatus{
    RUNNING,
    LOST_LIFE,
    LOST
};
const char features[5]={'.','<','>','B','P'};
struct Position{
    int row;
    int col;
    int intENTITY;
};
typedef Position* OneDimArray;
typedef OneDimArray* TwoDimArray;
struct GameWorld{
    TwoDimArray arrWorld;
    int intRows;
    int intCols;
    int Prow;
    int Pcol;
    bool isCarryBook=false;
    int Books=numBooks;
    int livesLeft=lives;
    int Status=RUNNING;
};

namespace TrafficSpace{
    int convToInt(string str);
    void dealloc(GameWorld& recWorld);
    TwoDimArray alloc(int rows, int cols);
    GameWorld init(int rows, int cols, int prob);
    void dispaly(GameWorld& recWorld);
    bool isInWorld(GameWorld& recWorld, int r, int c);
    void placePlayer(GameWorld& recWorld);
    void PlaceLeftTraf(GameWorld& recWorld, int prob);
    void placeRightTraf(GameWorld& recWorld, int prob);
    void placeBooks(GameWorld& recWorld);
    auto rangedRandom(int LOWER,int UPPER)->int;
    void movePLayer(GameWorld& recWorld, int Drow, int Dcol);
    void Move(GameWorld& recWorld, Directions d);
    void moveTraffic(GameWorld& recWorld);
    void simul(GameWorld& recWold, int x, int y);
    void simuR(GameWorld& recWold, int x, int y);
    void checkStatus(GameWorld& recWorld);
}

#endif // LIBTRAFFIC_H_INCLUDED
