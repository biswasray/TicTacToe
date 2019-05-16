#include<random>
#include<iostream>
#include<cstdlib>
#include<string>
#include<string.h>
using namespace std;
int avail[9];
bool found;
class tictactoe
{
	public:
    int X=1,O=-1, EM=0;
    int player=X,look=1;
    int board[3][3];
    int virtualb[3][3];
    int fboard[3][3];
    bool isEm=false;
    string warn;
	tictactoe() {
		for(int i=0;i<3;i++)
         {
             for(int j=0;j<3;j++)
             {
				 board[i][j]=0;
				 virtualb[i][j]=0;
				 fboard[i][j]=0;
			 }
		 }
	}
    void putSign(int z)
    {
	int x,y;
        if(z<0||z>8)
        {
            warn="Invalid board position";
            return;
             }
	x=z/3;
	y=z%3;
       if(virtualb[x][y]!=0) {
		   string st1(to_string(z+1));
		   string st2(" place already asigned");
		   warn=st1+st2;
		//strcat(warn,(char)(z+1));
	//warn=(char*)((char*)(z+1)+" place already asigned");
	//strcat(warn," place already asigned");
	return;
	}
        board[x][y]=player;
        fboard[x][y]=player;
        virtualb[x][y]=1;
        player=-player;
    }
    bool check(int z,int pl,int c) {
	int x,y;
	x=z/3;
	y=z%3;
	fboard[x][y]=pl;
	if(isFWin(pl,c)) {
	fboard[x][y]=0;
	return true ;
	}
	fboard[x][y]=0;
	return false ;
    }
    bool isWin(int player)
    {
        return ((board[0][0]+board[0][1]+board[0][2]==player*3)||(board[1][0]+board[1][1]+board[1][2]==player*3)||
                (board[2][0]+board[2][1]+board[2][2]==player*3)||(board[0][0]+board[1][0]+board[2][0]==player*3)||
                (board[0][1]+board[1][1]+board[2][1]==player*3)||(board[0][2]+board[1][2]+board[2][2]==player*3)||
                (board[2][0]+board[1][1]+board[0][2]==player*3)||(board[0][0]+board[1][1]+board[2][2]==player*3));
    }
    bool isFWin(int player,int c)
    {
        return ((fboard[0][0]+fboard[0][1]+fboard[0][2]==player*c)||(fboard[1][0]+fboard[1][1]+fboard[1][2]==player*c)||
                (fboard[2][0]+fboard[2][1]+fboard[2][2]==player*c)||(fboard[0][0]+fboard[1][0]+fboard[2][0]==player*c)||
                (fboard[0][1]+fboard[1][1]+fboard[2][1]==player*c)||(fboard[0][2]+fboard[1][2]+fboard[2][2]==player*c)||
                (fboard[2][0]+fboard[1][1]+fboard[0][2]==player*c)||(fboard[0][0]+fboard[1][1]+fboard[2][2]==player*c));
    }
    void displayWinner()
    {
        if(isWin(X))
        {
          cout<<"\n X wins....!\n\n"<<endl;
          isEm=false;
        }
        else if(isWin(O))
        {
              cout<<"\n O wins....!\n\n"<<endl;
          isEm=false;
        }
        else
        {
            if(!isEm)
            {
                 cout<<"it's tie\n\n"<<endl;

            }
        }
    }
    void toString()
    {
         char *s;
         isEm=false;
         for(int i=0;i<3;i++)
         {
             for(int j=0;j<3;j++)
             {
                 switch(board[i][j])
                 {
                     case 1:
                         cout<<"X";
                         break;
                     case -1:
                         cout<<"O";
                         break;
                     case 0:
		if(look<10) {
						 cout<<look;
		look++;
		}
		else {
		 cout<<" ";
		}
                         isEm=true;
                         break;
                          }
                 if(j<2)
                 {
                    cout<<"|";
                 }
             }
             if(i<2)
             {
                cout<<"\n------\n";
             }

         }
         cout<<endl;
    }

};
int getPoint() {
	int teb;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type>dist6(0,8);
	while(true) {
		teb=dist6(rng);
		if(avail[teb]!=0)
			break;
	}
	return avail[teb];
}
void singlePlayer(int dr) {
	tictactoe *tc=new tictactoe();
         int x=0,y=0,teb;
	int z=0;
	//system("clear");
	for(int i=0;i<9;i++)
        avail[i]=i+1;
	tc->toString();
    cout<<"____________"<<endl;
	tc->player=dr;
         do
         {
	found=false;
             cout<<(tc->player==tc->X ? "player X turn" : "player O turn")<<endl;
             if(tc->player==tc->X) {
				 cin>>teb;
             z=teb-1;
	}
	else {
	for(int i=0;i<9;i++) {
		if(avail[i]!=0) {
		if(tc->check(avail[i]-1,-1,3)) {
			z=avail[i]-1;
			found=true;
		}
		}
	}
	if(!found) {
	for(int i=0;i<9;i++) {
		if(avail[i]!=0) {
		if(tc->check(avail[i]-1,1,3)) {
			z=avail[i]-1;
			found=true;
		}
		}
	}
	}
	if(!found) {
	for(int i=0;i<9;i++) {
		if(avail[i]!=0) {
		if(tc->check(avail[i]-1,-1,2)) {
			z=avail[i]-1;
			found=true;
		}
		}
	}
	}
	if(!found) {
	z=getPoint()-1;
	}
	}
	tc->putSign(z);
	for(int i=0;i<9;i++) {
		if(avail[i]==(z+1)) {
			avail[i]=0;
		}
	}
	system("clear");
	if(tc->warn.c_str()!=NULL) {
	cout<<tc->warn<<endl;
	tc->warn="\0";
	}
             tc->toString();
			 cout<<"____________"<<endl;
             tc->displayWinner();
   } while (tc->isEm);
   delete tc;
}
void dualPlayer() {
	tictactoe *tc=new tictactoe();
         int x=0,y=0,teb;
	int z=0;
	//system("clear");
	for(int i=0;i<9;i++)
        avail[i]=i+1;
	tc->toString();
    cout<<"____________"<<endl;
		do
         {
			 cout<<(tc->player==tc->X ? "player X turn" : "player O turn")<<endl;
			 cin>>teb;
             z=teb-1;
			tc->putSign(z);
	for(int i=0;i<9;i++) {
		if(avail[i]==(z+1)) {
			avail[i]=0;
		}
	}
	system("clear");
	if(tc->warn.c_str()!=NULL) {
	cout<<tc->warn<<endl;
	tc->warn="\0";
	}
             tc->toString();
			 cout<<"____________"<<endl;
             tc->displayWinner();
   } while (tc->isEm);
   delete tc;
}
int main() {
	system("clear");
	while(true) {
	cout<<"1:Player vs Computer\n2:Computer vs Player\n3:Player vs Player\n4:Exit"<<endl;
	cout<<"\tPress 1 or 2 or 3 or 4\n"<<endl;
	int choice;
	cin>>choice;
	switch(choice) {
	case 1:
	cout<<"\n"<<endl;
	    singlePlayer(1);
	break;
	case 2:
	cout<<"\n"<<endl;
	    singlePlayer(-1);
	break;
	case 3:
	cout<<"\n"<<endl;
	    dualPlayer();
	break;
	case 4:
	system("clear");
	exit(0);
	break;
	default :
	    cout<<"Wrong Input,Try Again\n"<<endl;
	}
    }
}
