#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

struct Point
{
	int x;
	int y;
};

class player
{
public:
    char board[10][10]; // board where the players put down their ships.
    char mapboard[10][10]; // strategic table where players see what they have done.
    int hit;
    int end;

    char name[20]; // player name
    player()
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                board[i][j] = '.';
                mapboard[i][j] = '.';
            }
        }
    }
       
    
    void entername()
    {
        cout<<"Enter name"<<endl;
        cin>>name;
    }
    
    void enterdestroyer() // inserting coordinates for size 2 ship
    {
        char c;
        int a,b;
        cout<<"Enter a coordinate for destroyer (size2):";
        cin >> a;
        cin >> b;
        if (a >= 10 || a < 0 || b >= 10 || b < 0 )
            enterdestroyer();
        
        cout << "Would you like to put it vertically(v) or horizontally(h)? (v/h) : ";
        cin >> c;
        

        if (c == 'v')
        {
            if ( a+1 >= 10 )
            {
                cout << "Sorry, the ship goes beyond the board. Please try again."<<endl;
                enterdestroyer();
            }
            
            else if( a+1 < 10 && a + 1 >= 0 )
            {
                for (int i = 0; i<2; i++ )
                board[a+i][b] = '*';
            }
        }
        else if (c == 'h')
        {
            if (b + 1 >= 10)
            {
                cout << "Sorry, the ship goes beyond the board, please try again."<<endl;
                enterdestroyer();
            }
            else if(b+1 < 10 && b+1 >= 0)
            {
                for ( int j = 0; j<2; j++ )
                board[a][b+j] = '*';
            }
        }
        else
        {
            cout<<"Wrong character typed. Try again." << endl;
            enterdestroyer();
        }
        
    }
    
    void entersubmarine() // inserting coordinates for size 3 ship
    {
        int a, b;
        char c;
        cout<<"Enter coordinate for submarine(size3)"<<endl;
        cin>>a;
        cin>>b;
        
        cout<<"Would you like to put it horizontally(h) or vertically(v)?(h/v)"<<endl;
        cin>>c;
        
        if (c == 'v')
        {
            if ( a+1 >= 10 || a+2 >= 10 || a+3 >= 10 )
            {
                cout<<"Sorry. The ship goes beyong the board. Pls try again"<<endl;
                entersubmarine();
            }
            else if( a+1 < 10 && a+2 < 10 && a+3 < 10 && a+1 >= 0 && a+2 >= 0 && a+3 >= 0)
                for( int i = 0; i<3; i++ )
                    board[a+i][b] = '*';
                // 

                //        b
                //           
                //     ..... 
                //a    ...*.
                //a+1  ...*.
                //

        }
        else if (c == 'h')
        {
            if ( b+1 >= 10 || b+2 >= 10 || b+3 >= 10 )
            {
                cout<<"Sorry, th ship is out of the board. Pls try again"<<endl;
                entersubmarine();
            }
            
            else if ( b+1 < 10 && b+2 < 10 && b+3 < 10 && b+1 >= 0 && b+2 >= 0 && b+3 >=0 )
                for ( int j = 0; j<3; j++ )
                    board[a][b+j] = '*';
        }
    }
    
    void enterbattleship() // inserting coordinates for size 4 ship
    {
        int a, b;
        char c;
        cout<<"Enter coordinate for battleship(size4)"<<endl;
        cin>>a;
        cin>>b;
        cout<<"Would you like to put it horizontally or vertically?(h/v)"<<endl;
        cin>>c;
        if ( c == 'v')
        {
            if ( a+1 >= 10 || a+2 >= 10 || a+3 >= 10 || a+4 >= 10 )
            {
                cout<<"Sorry, the ship is out of the board. Pls try again."<<endl;
                enterbattleship();
            }
            else if ( a+1 < 10 && a+2 < 10 && a+3 < 10 && a+4 < 10 && a+1 >= 0 && a+2 >= 0 && a+3 >= 0 && a+4  >= 0 )
                for( int i = 0; i<4; i++ )
                    board[a+i][b] = '*';
        }
        else if ( c == 'h')
        {
            if ( b+1 >= 10 || b+2 >= 10 || b+3 >= 10 || b+4 >= 10 )
            {
                cout<<"Sorry, th ship is out of the board. Pls try again"<<endl;
                entersubmarine();
            }
        
            else if ( b+1 < 10 && b+2 < 10 && b+3 < 10 && b+4 < 10 && b+1 >= 0 && b+2 >= 0 && b+3 >=0 && b+4 >= 0 )
                for ( int j = 0; j<4; j++ )
                    board[a][b+j] = '*';
        
        }
    }


    bool isduplicate(int x, int y) // checks if (x,y) square has been attacked before.
    {
    	if (mapboard[x][y] == 'X' || mapboard[x][y] == 'O')
    	{
    		return true;
    	}
    	else
    		return false;
    }
    
    bool isHit(int x, int y)
    {
        if (board[x][y] == '*')
            return true;
        
        else
            return false;
        
    }
    
    void view()
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                cout << mapboard[i][j];
            }
            cout << endl;
        }
    }
    
    void attack(player p2)
    {
        int x, y;
        view();
        cout << "Enter coordinates to attack:"<<endl;
        cin >> x;
        cin >> y;
        
        if (x < 0 || y < 0 || x >= 10 || y >= 10)
            attack(p2);
        else
        {
            if (!isduplicate(x,y))
            {
            	if (p2.isHit(x,y))
            	{
                	cout << "Hit!"<<endl;
                	mapboard[x][y] = 'O';
                	view();
                	hit++;

                	if (hit < 9)
                	{
                		cout << "Attack once more!" << endl;
                		attack(p2);
                	}

                	else
                	{
                		return;
                	}
                	

            	}
            	else
            	{
                	cout << "Miss!"<<endl;
                	mapboard[x][y] = 'X';
                	view();
                }
            }

            else
            {
            	cout << "You attacked the square before. Attack again." << endl;
            	attack(p2);
            }
            
        }
        
    }
    fstream file;
    fsstream file2;
};

int main()
{
    player p1, p2;
    p1.hit = 0;
    p2.hit = 0;
    p1.end = 0;
    p2.end = 0;

    int n;
    cout<<"Press 1 to start new game"<<endl;
    cout<<"Press 2 to show previous game"<<endl;
    cout<<"Press 3 to quit"<<endl;
    cin>>n;
    if ( n == 1 )
    {
        p1.entername();
        p1.enterdestroyer();
        p1.entersubmarine();
        p1.enterbattleship();
        system("clear");
    
        p2.entername();
        p2.enterdestroyer();
        p2.entersubmarine();
        p2.enterbattleship();
        system("clear");
        while(p1.hit < 9 && p2.hit < 9)
        {
            cout << "Player 1's turn!"<< endl;
            p1.attack(p2);
            //system("clear");

            if (p1.hit == 9)
            	break;
            cout << "Player 2's turn!"<< endl;
            p2.attack(p1);

            if(p2.hit == 9)
            	break;
            //system("clear");
            cout << p1.hit;
            cout << endl;
            cout << p2.hit;
            cout << endl;
        }
        if ( p1.hit == 9 )
        {
        	cout << "Player 1 wins!";
        }
        else
        {
        	cout << "Player 2 wins!";
        }
        return 0;
    }

    else if( n == 2 )
    {
        while(file.read((char*)&p3,sizeof(p3)))
        {
            cout<<p3.name<<":"<<p3.c<<endl;
        }
        while(file2.read((char*)&p4,sizeof(p4)))
        {
            cout<<p4.name<<":"<<p4.c1<<endl;
        }

    }

    else if (n == 3)
    {
    	exit(0);
    }

    else
    {
    	cout << "Entered wrong character"<<endl;
        main();
    }
   
}
