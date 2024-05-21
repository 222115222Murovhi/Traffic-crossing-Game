#include "libTraffic.h"

using namespace TrafficSpace;

int main(int argc, char* argv[])
{
    if(argc!=4){
        cerr<<"Usage: "<<argv[0]<<" <rows><cols><traffic Prob>"<<endl;
        exit(ERROR_ARGS);
    }
    int rows=convToInt(argv[1]);
    int cols=convToInt(argv[2]);
    srand(time(0));
    int trafProb=convToInt(argv[3]);
    GameWorld recWorld=init(rows,cols,trafProb);
    bool blnContinue=true;
    char op;
    do{
        system("cls");
        dispaly(recWorld);
        switch(cin>>op ; tolower(op)){
        case 'w':
            {
                Move(recWorld,UP);
                break;
            }
        case 's':
            {
                Move(recWorld,DOWN);
                break;
            }
        case 'a':
            {
                Move(recWorld,LEFT);
                break;
            }
        case 'd':
            {
                Move(recWorld,RIGHT);
                break;
            }
        case 'q':
            {
                cout<<"quiting............."<<endl;
                blnContinue=false;
                break;
            }
        }
    }while(blnContinue);

    dealloc(recWorld);
    return SUCCESS;
}
