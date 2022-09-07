#include <utility>
#include <vector>
#include <conio.h>
#include <string>
#include <iostream>

class CELL
{
protected:
    int row, col, oX, oY;//original XY    
    std::string cellType;
    char dir;
    
public:    
    CELL ()
    {
        row =col =0;
        dir ='U';
        
    }
    
    CELL (int x,int y) : CELL()
    {
        row =oX =x;
        col =oY =y;
    }
    
    void locationReset ()
    {
        row =oX;
        col =oY;
    }
    
    inline std::string getCellType ()
    {
        return cellType;
    }
    
    inline int getRow ()
    {
        return this->row;
    }
    
    inline int getCol ()
    {
        return this->col;
    }
    
    inline void setRow (int row)
    {
        this->row =row;
    }
    
    inline void setCol (int col)
    {
        this->col =col;
    }
    
    inline void moveUp ()
    {
        col--;
        dir ='U';
    }
    
    inline void moveDown ()
    {
        col++;
        dir ='D';
    }
    
    inline void moveRight ()
    {
        row++;
        dir ='R';
    }
    
    inline void moveLeft ()
    {
        row--;
        dir ='L';
    }
    
    std::pair<int,int> XY ()
    {
        int changed;
        switch (dir)
        {
            case 'U':
                    changed =col;
                    changed++;
                    return 
                    std::make_pair(row
                    ,changed);
                    break;
            case 'D':
                    changed =col;
                    changed--;
                    return 
                    std::make_pair(row
                    ,changed);
                    break;
            case 'R':
                    changed =row;
                    changed--;
                    return 
                    std::make_pair(changed
                    ,col);
                    break;
            case 'L':
                    changed =row;
                    changed++;
                    return 
                    std::make_pair(changed
                    ,col);
                    break;       
        }
    }
    
    friend std::ostream &
    operator<<(std::ostream & o, 
    CELL *c)
	{
		o <<"CELL [" <<c->row <<"," 
		<<c->col <<"]" <<c->getCellType() 
		<<"\n";
		return o;
	}

};

class POISON : public CELL
{
    
public:    
    POISON ()
    {
        cellType ="\x1B[31m×\033[0m";
    }
    
    POISON (int x,int y) : POISON ()
    {
        row =oX =x;
        col =oY =y;
    }
};

class FOOD : public CELL
{
    
public:    
    FOOD ()
    {
        cellType ="\x1B[32m•\033[0m";
    }
    
    FOOD (int x,int y) : FOOD ()
    {
        row =oX =x;
        col =oY =y;
    } 
};

class STONE : public CELL
{
    
public:    
    STONE ()
    {
        cellType ="\x1B[90mo\033[0m";
    }
    
    STONE (int x,int y) : STONE ()
    {
        row =oX =x;
        col =oY =y;
    }
};

class HEAD : public CELL
{
    
public:    
    HEAD ()
    {
        cellType ="\x1B[94mO\033[0m";
    }
    
    HEAD (int x,int y) : HEAD ()
    {
        row =oX =x;
        col =oY =y;
    }
};

class TAIL : public CELL
{
    
public:    
    TAIL ()
    {
        cellType ="\x1B[32m•\033[0m";
    }
    
    TAIL (int x,int y) : TAIL ()
    {
        row =oX =x;
        col =oY =y;
    }
};

class SNAKE
{
    int x, y;
    CELL* head;
    std::vector<CELL*> body;    
    
public:    
    SNAKE (int width,int height)
    {
        head =new HEAD (width/2,height/2);
        body.push_back(new TAIL 
        (head->XY().first,head->XY().second));
    }
    
    void grow ()
    {
        body.push_back(new TAIL
        (body.back()->XY().first
        ,body.back()->XY().second));
    }
    
    void loseWeight ()
    {
        body.pop_back();
    }    
    
    CELL* getHead ()
    {
        return head;
    }
    
    std::vector<CELL*> getBody ()
    {
        return body;
    }
};

class GAME_ENGINE
{
    enum eDir {stop=0,Up,Down,Right,Left};
    eDir dir;
    int width, height;
    bool quit;
    SNAKE* snake;
    CELL* snakeHead;
    std::vector<CELL*> snakeBody;
    
public:    
    GAME_ENGINE (int w,int h)
    {
        dir =stop;
        width =w;
        height =h;
        quit =false;
        snake =new SNAKE (w,h);
        snakeHead =snake->getHead();
        snakeBody =snake->getBody();        
    }
    
    void grow ()
    {
        snakeBody.push_back(new TAIL
        (snakeBody.back()->XY().first
        ,snakeBody.back()->XY().second));
        snake->grow();
    }
    
    void loseWeight ()
    {
        snakeBody.pop_back();
        snake->loseWeight();
    }
    
    void draw ()
    {
        system ("cls");
        for (int w = 0; w < width; w++)
			std::cout<< "-";
		std::cout<<std::endl;
		
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
			    if (snakeHead->getRow() == w 
			     && snakeHead->getCol() == h )
			        std::cout
		   	     <<snakeHead
		   	     ->getCellType();
			    else
			    {
			        bool space =true;
			        for (auto cl : snakeBody)
			        {
			            if 
			            (cl->getRow() 
			             == w 
			          && cl->getCol()
			             == h)
			             {
			                 std::cout
			                 <<cl->
			                 getCellType();
			                 space =false;
			             }
			        }
			        if (space)
			            std::cout<<" ";
			    }			        	    
			}
		}
		
		for (int w = 0; w < width; w++)
			std::cout<< "-";
		std::cout<<std::endl;
    }
    
    void input ()
    {
        if (_kbhit())
            switch (_getch())
            {
                case 'w':case 'W':
                snakeHead->moveUp();
                for (auto tail : snakeBody)   
                     tail->moveUp();
                break;
                case 's':case 'S':
                break;
                case 'd':case 'D':
                break;
                case 'a':case 'A':
                break;
                case 'q':case 'Q':
                break;
            }
    }
    
};

int main()
{
    GAME_ENGINE ge(83,20);
    ge;
}