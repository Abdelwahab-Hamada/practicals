#include <utility>
#include <vector>
#include <conio.h>
#include <string>
#include <unistd.h>
#include <thread>
#include <iostream>

class CELL_TYPE
{
protected:    
    std::string typeName;
    
public:    
    CELL_TYPE ()
    {
        typeName ="CELL";
    }
    
    CELL_TYPE (std::string typeName) : 
    CELL_TYPE () 
    {
        this->typeName =typeName;
    }
    
    std::string virtual cellType () =0;
    
    virtual ~CELL_TYPE ()
    {
        std::cout<<"~" + typeName +
        "_TYPE ()\n";
    }
};

class POISON_TYPE : public CELL_TYPE
{
    std::string cellType ()
    {
        return "\x1B[31m×\033[0m";
    }
    
public:    
    POISON_TYPE (std::string typeName 
    ="POISON")
    {
        this->typeName =typeName;
    }       
};

class FOOD_TYPE : public CELL_TYPE
{
    std::string cellType ()
    {
        return "\x1B[32m•\033[0m";
    }
    
public:    
    FOOD_TYPE (std::string typeName ="FOOD")
    {
        this->typeName =typeName;
    }    
};

class STONE_TYPE : public CELL_TYPE
{
    std::string cellType ()
    {
        return "\x1B[90mo\033[0m";
    }
    
public:    
    STONE_TYPE (std::string typeName 
    ="STONE")
    {
        this->typeName =typeName;
    }        
};

class HEAD_TYPE : public CELL_TYPE
{
    std::string cellType ()
    {
        return "\x1B[94mO\033[0m";
    }
    
public:    
    HEAD_TYPE (std::string typeName 
    ="HEAD")
    {
        this->typeName =typeName;
    }         
};

class TAIL_TYPE : public CELL_TYPE
{
    std::string cellType ()
    {
        return "\x1B[90m•\033[0m";
    }
    
public:    
    TAIL_TYPE (std::string typeName 
    ="TAIL")
    {
        this->typeName =typeName;
    }        
};

class DEFAULT_TYPE : public CELL_TYPE
{
    std::string cellType ()
    {
        return "•";
    }
    
public:    
    DEFAULT_TYPE (std::string typeName 
    ="DEFAULT")
    {
        this->typeName =typeName;
    }
};

class CELL
{
protected:
    int row, col, oX, oY;//original XY    
    std::string cellName;
    char dir;
    CELL_TYPE* type;
    
public:    
    CELL ()
    {
        row =col =0;
        dir ='R';
        cellName ="CELL ()";
        type =new DEFAULT_TYPE ();
    }
    
    CELL (int x,int y) : CELL()
    {
        row =oX =x;
        col =oY =y;
    }
    
    virtual ~CELL ()
    {
        std::cout<<"~"+ cellName + " ()\n";
        if (type != NULL)
            delete type;
    }
    
    void locationReset ()
    {
        row =oX;
        col =oY;
    }
    
    inline void setDir (char dir)
    {
        this->dir =dir;
    }
    
    inline char getDir ()
    {
        return dir;
    }
    
    inline std::string getCellType ()
    {
        return type->cellType();
    }
    
    inline std::string getCellName ()
    {
        return cellName;
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
    
    std::pair<int,int> XY ()//to calc XY based on it's direction
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
		<<c->dir<<"\n";
		return o;
	}

};

class POISON : public CELL
{
    
public:    
    POISON ()
    {
        delete type;
        type =new POISON_TYPE();
        cellName ="POISON";
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
        delete type;
        type =new FOOD_TYPE();
        cellName ="FOOD";
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
        delete type;
        type =new STONE_TYPE();
        cellName ="STONE";
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
        delete type;
        type =new HEAD_TYPE();
        cellName ="HEAD";
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
        delete type;
        type =new TAIL_TYPE();
        cellName ="TAIL";
    }
    
    TAIL (int x,int y) : TAIL ()
    {
        row =oX =x;
        col =oY =y;
    }
};

class GENERATOR
{
    char ele;
    int width, height;
    CELL*ptr;
    
public:    
    GENERATOR (int width,int height)
    {
        ele ='f';
        this->width =width;
        this->height =height;
        ptr =NULL;      
    }
    
    ~GENERATOR ()
    {
        std::cout<<"~GENERATOR ()\n";
    }
    
    CELL* generate ()
    {
        ptr =NULL; 
        ele =calc(); 
              
        switch (ele)
        {
            case 'f':
            
            ptr =new FOOD 
            (XY().first,XY().second);
            break;
            
            case 's':
            
            ptr =new STONE 
            (XY().first,XY().second);
            break;
            
            case 'p':
            
            ptr =new POISON 
            (XY().first,XY().second);
            break;
            
            default:
            
            ptr =new FOOD 
            (XY().first,XY().second);
            break;
        }
        return ptr;
    }
    
    CELL* reGenerate ()
    {
        delete ptr;
        return generate ();
    }
    
    std::pair<int,int> XY ()
    {
        int X =rand() %width;
        int Y =rand() %height;
        return std::make_pair(X,Y);
    }
    
    char calc ()
    {
        int num =rand() %9;
        switch (num)
        {
            case 1 ... 3:
            
            return 'f';
            break;
            
            case 4 ... 6:
            
            return 's';
            break;
            
            case 7 ... 9:
            
            return 'p';
            break;
        }
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
    
    ~SNAKE ()
    {
        delete head;
        std::cout<<"~SNAKE() \n";
    }
    
    inline void grow (std::vector<CELL*> body)
    {
        this->body =body;
    }
    
    inline void loseWeight 
    (std::vector<CELL*> body)
    {
        this->body =body;
    } 
    
    void shift (std::vector<CELL*> 
    cells,CELL* followed)
    {
        //original old
        int prevX =cells.front()->getRow();
        int prevY =cells.front()->getCol();
        char dir =cells.front()->getDir();
        
        int prevXI,prevYI;
        char dirI;
        
        //new
        cells.front()->setRow
        (followed->getRow());
        cells.front()->setCol
        (followed->getCol());
        cells.front()->setDir
        (followed->getDir());
        
        for (int index =1;index 
        < cells.size();index++)
        {
            //old
            prevXI =cells.at(index)->getRow();
            prevYI =cells.at(index)->getCol();
            dirI =cells.at(index)->getDir();
            
            //new
            cells.at(index)->setRow(prevX);
            cells.at(index)->setCol(prevY);
            cells.at(index)->setDir(dir);
            
            //current
            prevX =prevXI;
            prevY =prevYI;
            dir =dirI;            
        }
    }    
    
    inline CELL* getHead ()
    {
        return head;
    }
    
    inline std::vector<CELL*> getBody ()
    {
        return body;
    }
};

class BOARD
{
    int width, height, score;
    CELL* snakeHead;
    CELL* ele;
    std::vector<CELL*> snakeBody;
    
public:    
    BOARD (int width,int height,int score
          ,CELL* snakeHead
          ,std::vector<CELL*> snakeBody
          ,CELL* ele)
    {
        this->width =width;
        this->height =height;
        this->score =score;
        this->snakeHead =snakeHead;
        this->snakeBody =snakeBody;
        this->ele =ele;
    }
    
    ~BOARD ()
    {
        std::cout<<"~BOARD()\n";
    }
    
    inline void setSnakeBody 
    (std::vector<CELL*> snakeBody)
    {
        this->snakeBody =snakeBody;
    }
    
    inline void setScore (int score)
    {
        this->score =score;
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
		   	     
		   	 else if (ele->getRow() == w
		   	  && ele->getCol() == h)
		   	     std::cout<<ele
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
		std::cout<<"Score :"<<score<<"\n";
    }
};

class GAME_ENGINE
{
    enum eDir {stop=0,Up,Down,Right,Left};
    eDir dir;
    int width, height, score;
    bool boost,quit;
    SNAKE* snake;
    CELL* snakeHead;
    CELL* element;
    std::vector<CELL*> snakeBody;
    BOARD* board;
    GENERATOR* generator;
    
public:    
    GAME_ENGINE (int w,int h)
    {
        dir =Right;
        width =w;
        height =h;
        score =0;
        quit =false;
        boost =false;
        snake =new SNAKE (w,h);
        snakeHead =snake->getHead();
        snakeBody =snake->getBody();
        generator =new GENERATOR (w,h);
        element =generator->generate(); 
        board =new BOARD 
        (w,h,score,snakeHead,snakeBody
        ,element);         
    }
    
    ~GAME_ENGINE ()
    {        
        for (auto cell : snakeBody)
             delete cell;
        delete snake;
        delete board;
        delete element;
        delete generator;
        std::cout<<"~GAME_ENGINE()\n";
    }
    
    void grow ()
    {        
        if (score >= 0)
        snakeBody.push_back(new TAIL
        (snakeBody.back()->XY().first
        ,snakeBody.back()->XY().second));
        else
        snakeBody.push_back(new TAIL 
        (snakeHead->XY().first
        ,snakeHead->XY().second));  
                    
        snake->grow(snakeBody);
        
        board->setSnakeBody(snakeBody);
        
        board->setScore(++score);
        
        reGenerate ();
    }
    
    void loseWeight ()
    {
        if (score > 0)
        {
        delete snakeBody.back();
        
        snakeBody.pop_back();
        
        snake->loseWeight(snakeBody);
        
        board->setSnakeBody(snakeBody);
        
        board->setScore(--score);
        }
        
        reGenerate ();
    }
    
    void draw ()
    {
        board->draw();
    }
    
    void reGenerate ()
    {
        while (1)
        {
        element =NULL;
        element =generator->reGenerate();
        sleep(10);
        }
    }
    
    void DoThis (char arrows)
    {
        snake->shift(snakeBody
                    ,snakeHead);
        
        switch (arrows)
        {
            case 'w':
            snakeHead->moveUp();
            break;
            
            case 's':
            snakeHead->moveDown();
            break;
            
            case 'd':
            snakeHead->moveRight();
            break;
            
            case 'a':
            snakeHead->moveLeft();
            break;
        }        
    }
    
    void input ()
    {
        if (_kbhit())
            switch (_getch())
            {
                case 'w':case 'W':
                
                if (dir != Down)
                {                    
                    DoThis('w');
                    
                    dir =Up;
                }
                else
                {
                    quit =true;
                    
                    std::cout<<"Frozen❄️\n";
                }                        
                break;
                
                case 's':case 'S':
                
                if (dir != Up)
                {                
                    DoThis('s');
                    
                    dir =Down;
                }               
                else
                {
                    quit =true;
                    
                    std::cout<<"Frozen❄️\n";
                }                   
                break;
                
                case 'd':case 'D':
                
                if (dir != Left)
                {                    
                    DoThis('d');
                    
                    dir =Right;
                }
                else
                {
                    quit =true;
                    
                    std::cout<<"Frozen❄️\n";
                }                    
                break;
                
                case 'a':case 'A':
                
                if (dir != Right)
                {
                    DoThis('a');
                    
                    dir =Left;
                }
                else
                {
                    quit =true;
                
                    std::cout<<"Frozen❄️\n";
                }                   
                break;
                
                case 'q':case 'Q':
                
                quit =true;
                break;
                
                case 'b':case 'B':
                boost =true;
                break;
                
                case 'p':case 'P':
                boost =false;
                break;
            }
    }
    
    void move ()
    {
        if (boost)            
            switch (dir)
            {
                case Up:
            
                DoThis('w');
                break;
            
                case Down:
            
                DoThis('s');
                break;
            
                case Right:
            
                DoThis('d');
                break;
            
                case Left:
            
                DoThis('a');
                break;            
            }
        usleep(100000);       
    }
    
    void logic ()
    {
        if (snakeHead->getRow() >= width)
            snakeHead->setRow(0);           
        else if (snakeHead->getRow() < 0)
                 snakeHead->setRow(width-1);
                 
        if (snakeHead->getCol() < 0 
         || snakeHead->getCol() >= height)
        {
            quit =true;
            std::cout<<"Game Over";
        }
        else if (snakeHead->getRow()
        == element->getRow() 
        && snakeHead->getCol() 
        == element->getCol())
        {
            if (element->getCellName() 
            == "FOOD")
            grow ();
            else if (element->getCellName() 
            == "STONE")
            loseWeight ();
            else
            loseWeight ();
        }
        
        for (auto tail : snakeBody)
        {
             if (snakeHead->getRow() 
             == tail->getRow() 
             && snakeHead->getCol() 
             == tail->getCol())
             {
                 std::cout<<"Game Over\n";
                 quit =true;
             }
             
             if (tail->getRow() 
             == element->getRow() 
             && tail->getCol() 
             == element->getCol())
             reGenerate ();             
        }
        
        /*while (element->getCellName() 
             == "STONE" 
             || element->getCellName()
             == "POISON" && quit != true)
             {
                 reGenerate ();
                 draw();
                                     
                 usleep (1000000);
             }*/
             
        if (score == 5)
            std::cout<<"You win\n";                            
    }
    
    bool Quit ()
    {
        return quit;
    }    
};

int main()
{
    GAME_ENGINE* ge =new GAME_ENGINE(83,20);
    std::thread 
    task(&GAME_ENGINE::reGenerate,ge);
    do
      {
            ge->draw();
            ge->input();
            ge->move();
            ge->logic();
            //std::cout<<element;
            //std::cout<<snakeBody.back();
            //std::cout<<snakeHead;
      }while (!ge->Quit());
      task.join();
}