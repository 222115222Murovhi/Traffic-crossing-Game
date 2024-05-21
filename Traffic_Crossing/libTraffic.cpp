#include "libTraffic.h"

namespace TrafficSpace{
    int convToInt(string str){
        int num=0;
        stringstream ss {str};
        ss>>num;
        if(ss.fail()){
            cerr<<"could not convert "<<str<<" to integer"<<endl;
            exit(ERROR_CONV);
        }
        return num;
    }
    void dealloc(GameWorld& recWorld){
        for(int i=0;i<recWorld.intRows;i++){
            delete[] recWorld.arrWorld[i];
        }
        delete[] recWorld.arrWorld;
        recWorld.arrWorld=nullptr;
    }
    TwoDimArray alloc(int rows, int cols){
        TwoDimArray arr =new OneDimArray[rows];
        for(int i=0;i<rows;i++){
            arr[i]=new Position[cols];
            for(int j=0;j<cols;j++){
                arr[i][j].row=i;
                arr[i][j].col=j;
                arr[i][j].intENTITY=EMPTY_SPACE;
            }
        }
        return arr;
    }
    void dispaly(GameWorld& recWorld){
        for(int i=0;i<recWorld.intRows;i++){
            for(int j=0;j<recWorld.intCols;j++){
                cout<<features[recWorld.arrWorld[i][j].intENTITY]<<" ";
            }
            cout<<endl;
        }
        cout<<"lives: "<<recWorld.livesLeft<<endl;
        if(recWorld.isCarryBook){
            cout<<"carried Books: 1"<<endl;
        }
        else{
            cout<<"carried Books: 0"<<endl;
        }

        cout<<endl;
        cout<<"w. UP\n ";
        cout<<"s. DOWN\n";
        cout<<"a. LEFT\n";
        cout<<"d. RIGHT\n";
        cout<<"q. QUIT\n";
    }
    bool isInWorld(GameWorld& recWorld, int r, int c){
        if(r<0 || r>=recWorld.intRows){
            return false;
        }
        if(c<0 || c>=recWorld.intCols){
            return false;
        }
        return true;
    }
      auto rangedRandom(int LOWER, int UPPER)->int {
        return rand()%(UPPER-LOWER+1)+LOWER;
    }
    void placePlayer(GameWorld& recWorld){
        int x,y;
        y=rangedRandom(0,recWorld.intCols-1);
        x=recWorld.intRows-1;
        recWorld.arrWorld[x][y].intENTITY=PLAYER;
        recWorld.Prow=x;
        recWorld.Pcol=y;
    }
    void PlaceLeftTraf(GameWorld& recWorld, int prob){
        for(int i=recWorld.intRows-2;i>0;i-=2){
            for(int j=0;j<recWorld.intCols;j++){
                //int temp=rangedRandom(1,100);
                if(int temp=rangedRandom(1,100)<=prob){
                    recWorld.arrWorld[i][j].intENTITY=TRAFFIC_LEFT;
                }
            }
        }
    }
    void placeRightTraf(GameWorld& recWorld, int prob){
        for(int i=recWorld.intRows-3;i>0;i-=2){
            for(int j=0;j<recWorld.intCols;j++){
                int temp=rangedRandom(1,100);
                if(temp<=prob){
                    recWorld.arrWorld[i][j].intENTITY=TRAFFIC_RIGHT;
                }
            }
        }
    }
    void placeBooks(GameWorld& recWorld){
        int y;
        for(int i=0;i<numBooks;i++){
            do{
                y=rangedRandom(0,recWorld.intCols-1);
            }while(recWorld.arrWorld[0][y].intENTITY!=EMPTY_SPACE);
            recWorld.arrWorld[0][y].intENTITY=BOOK;
        }
    }
    GameWorld init(int rows, int cols, int prob){
        GameWorld recWorld;
        recWorld.arrWorld=alloc(rows,cols);
        recWorld.intRows=rows;
        recWorld.intCols=cols;
        placePlayer(recWorld);
        placeBooks(recWorld);
        PlaceLeftTraf(recWorld,prob);
        placeRightTraf(recWorld,prob);
        return recWorld;
    }
    void simul(GameWorld& recWold, int x, int y){
        if(isInWorld(recWold,x,y-1)){
            if(recWold.arrWorld[x][y-1].intENTITY==PLAYER){
                recWold.Status=LOST_LIFE;
            }
            recWold.arrWorld[x][y-1].intENTITY=TRAFFIC_LEFT;
            recWold.arrWorld[x][y].intENTITY=EMPTY_SPACE;
        }
        else{
            recWold.arrWorld[x][y].intENTITY=EMPTY_SPACE;
            if(recWold.arrWorld[x][recWold.intCols-1].intENTITY==PLAYER){
                recWold.Status=LOST_LIFE;
            }
            recWold.arrWorld[x][recWold.intCols-1].intENTITY=TRAFFIC_LEFT;
        }
    }
    void simuR(GameWorld& recWold, int x, int y){
        if(isInWorld(recWold,x,y+1)){
            if(recWold.arrWorld[x][y+1].intENTITY==PLAYER){
                recWold.Status=LOST_LIFE;
            }
            recWold.arrWorld[x][y+1].intENTITY=TRAFFIC_RIGHT;
            recWold.arrWorld[x][y].intENTITY=EMPTY_SPACE;
        }
        else{
            recWold.arrWorld[x][y].intENTITY=EMPTY_SPACE;
            if(recWold.arrWorld[x][0].intENTITY==PLAYER){
                recWold.Status=LOST_LIFE;
            }
            recWold.arrWorld[x][0].intENTITY=TRAFFIC_RIGHT;
        }
    }
    void moveTraffic(GameWorld& recWorld){
        for(int i=0;i<recWorld.intRows;i++){
            for(int j=0;j<recWorld.intCols;j++){
                if(recWorld.arrWorld[i][j].intENTITY==TRAFFIC_LEFT){
                    simul(recWorld,i,j);
                }
            }
        }
        for(int i=recWorld.intRows-2;i>0;i--){
            for(int j=recWorld.intCols-1;j>=0;j--){
                if(recWorld.arrWorld[i][j].intENTITY==TRAFFIC_RIGHT){
                    simuR(recWorld,i,j);
                }
            }
        }
    }
    void movePLayer(GameWorld& recWorld, int Drow, int Dcol){
        if(recWorld.arrWorld[Drow][Dcol].intENTITY==BOOK){
            if(recWorld.isCarryBook){
                return;
            }
            recWorld.isCarryBook=true;
        }
        if(recWorld.arrWorld[Drow][Dcol].intENTITY==TRAFFIC_LEFT || recWorld.arrWorld[Drow][Dcol].intENTITY==TRAFFIC_RIGHT){
            recWorld.Status=LOST_LIFE;
        }
        if(Drow==recWorld.intRows-1){
            if(recWorld.isCarryBook){
                if(--recWorld.Books==0){
                    system("cls");
                    cerr<<"YOU WON!"<<endl;
                    exit(ERROR_WON);
                }
                recWorld.isCarryBook=false;
            }
        }
        recWorld.arrWorld[Drow][Dcol].intENTITY=PLAYER;
        recWorld.arrWorld[recWorld.Prow][recWorld.Pcol].intENTITY=EMPTY_SPACE;
        recWorld.Prow=Drow;
        recWorld.Pcol=Dcol;
    }
    void Move(GameWorld& recWorld, Directions d){
        int Drow=recWorld.Prow;
        int Dcol=recWorld.Pcol;
        switch(d){
        case UP:
            {
                Drow--;
                break;
            }
        case DOWN:
            {
                Drow++;
                break;
            }
        case LEFT:
            {
                Dcol--;
                break;
            }
        case RIGHT:
            {
                Dcol++;
                break;
            }
        }
        if(isInWorld(recWorld,Drow,Dcol)){
            movePLayer(recWorld,Drow,Dcol);
        }
        moveTraffic(recWorld);
        checkStatus(recWorld);
    }
    void checkStatus(GameWorld& recWorld){
        if(recWorld.Status==LOST_LIFE){
            int y=rangedRandom(0,recWorld.intCols-1);
            recWorld.arrWorld[recWorld.intRows-1][y].intENTITY=PLAYER;
            recWorld.Prow=recWorld.intRows-1;
            recWorld.Pcol=y;
            if(--recWorld.livesLeft==0){
                system("cls");
                cerr<<"YOU LOST, OUT OF LIVES!"<<endl;
                exit(ERROR_LOST);
            }
            recWorld.Status=RUNNING;
        }
    }
}
