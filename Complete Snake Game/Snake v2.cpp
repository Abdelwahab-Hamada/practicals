#include <utility>
#include <vector>
#include <conio.h>
#include <string>
#include <unistd.h>
#include <memory>
#include <thread>
#include <iomanip>
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
    std::shared_ptr<CELL_TYPE> type;
    
public:    
    CELL ()
    {
        row =col =0;
        dir ='R';
        cellName ="CELL ()";
    }
    
    CELL (int x,int y) : CELL()
    {
        row =oX =x;
        col =oY =y;
    }
    
    virtual ~CELL ()
    {
        std::cout<<"~"+ cellName + " ()\n"; 
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
    CELL* c)
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
        type =std::make_shared
        <POISON_TYPE>();
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
        type =std::make_shared
        <FOOD_TYPE>();
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
        type =std::make_shared
        <STONE_TYPE>();
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
        type =std::make_shared
        <HEAD_TYPE>();
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
        type =std::make_shared
        <TAIL_TYPE>();
        cellName ="TAIL";
    }
    
    TAIL (int x,int y) : TAIL ()
    {
        row =oX =x;
        col =oY =y;
    }
    
    void ateFood ()
    {
        type =NULL;
        type =std::make_shared
        <FOOD_TYPE>();
    }
    
    void ateStone ()
    {
        type =NULL;
        type =std::make_shared
        <TAIL_TYPE>();
    }
    
    void poisoned ()
    {
        type =NULL;
        type =std::make_shared
        <POISON_TYPE>();
    }
};

class GENERATOR
{
    char ele;
    int width, height;
    std::shared_ptr<CELL> ptr;
    
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
            case 1 ... 5:
            
            return 'f';
            break;
            
            case 6 ... 7:
            
            return 's';
            break;
            
            case 8 ... 9:
            
            return 'p';
            break;
        }
    }
    
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
    
    inline std::shared_ptr<CELL> generateFood 
    ()
    {
        return std::make_shared<FOOD>
             (XY().first,XY().second);
    }
    
    inline std::shared_ptr<CELL> 
    generateStone ()
    {
        return std::make_shared<STONE> 
             (XY().first,XY().second);
    }
    
    inline std::shared_ptr<CELL> 
    generatePoison ()
    {
        return std::make_shared<POISON> 
             (XY().first,XY().second);
    }
    
    void randomGenerate ()
    {
        ptr =NULL;
        ele =calc(); 
              
        switch (ele)
        {
            case 'f':
            
            ptr =generateFood ();
            break;
            
            case 's':
            
            ptr =generateStone ();
            break;
            
            case 'p':
            
            ptr =generatePoison ();
            break;
            
            default:
            
            ptr =generateFood ();
            break;
            
            throw "ERROR";
        }
    }
    
    std::shared_ptr<CELL> generated ()
    {
        randomGenerate ();
        return ptr;
    }   
};

class SNAKE
{
    int x, y;
    std::shared_ptr<CELL> head;
    std::vector<std::shared_ptr<CELL>> body;  
    
public:    
    SNAKE (int width,int height)
    {
        head =std::make_shared
        <HEAD> (width/2,height/2);
        body.push_back(std::make_shared
        <TAIL> 
        (head->XY().first
        ,head->XY().second));
    }
    
    ~SNAKE ()
    {
        std::cout<<"~SNAKE() \n";
    }
    
    inline void resetBody 
    (std::vector<std::shared_ptr<CELL>> body)
    {
        this->body =body;
    }
    
    inline std::shared_ptr<CELL> getHead ()
    {
        return head;
    }
    
    inline std::vector<std::shared_ptr<CELL>> 
    getBody ()
    {
        return body;
    } 
    
    void shift 
    (std::vector<std::shared_ptr<CELL>> 
    cells,std::shared_ptr<CELL> followed)
    {
        //original old
        int prevX =cells.front().get()
        ->getRow();
        int prevY =cells.front().get()
        ->getCol();
        char dir =cells.front().get()
        ->getDir();
        
        int prevXI,prevYI;
        char dirI;
        
        //new
        cells.front().get()->setRow
        (followed.get()->getRow());
        cells.front().get()->setCol
        (followed.get()->getCol());
        cells.front().get()->setDir
        (followed.get()->getDir());
        
        for (int index =1;index 
        < cells.size();index++)
        {
            //old
            prevXI =cells.at(index).get()
            ->getRow();
            prevYI =cells.at(index).get()
            ->getCol();
            dirI =cells.at(index).get()
            ->getDir();
            
            //new
            cells.at(index).get()
            ->setRow(prevX);
            cells.at(index).get()
            ->setCol(prevY);
            cells.at(index).get()
            ->setDir(dir);
            
            //current
            prevX =prevXI;
            prevY =prevYI;
            dir =dirI;            
        }
    }    
};

class BOARD
{
    int width, height, score, seconds;
    std::shared_ptr<CELL> snakeHead;    
    std::vector<std::shared_ptr<CELL>> 
    snakeBody;
    std::shared_ptr<CELL> ele;
    
public:    
    BOARD (int width,int height,int score
          ,std::shared_ptr<CELL> snakeHead
          ,std::vector<std::shared_ptr<CELL>> 
          snakeBody
          ,std::shared_ptr<CELL> ele)
    {
        this->width =width;
        this->height =height;
        this->score =0;
        this->seconds =0; 
        this->snakeHead =snakeHead;
        this->snakeBody =snakeBody;
        this->ele =ele;        
    }
    
    ~BOARD ()
    {
        std::cout<<"~BOARD()\n";
    }
    
    inline void setSnakeHead 
    (std::shared_ptr<CELL> snakeHead)
    {
        this->snakeHead =snakeHead;
    }
    
    inline void setSnakeBody 
    (std::vector<std::shared_ptr<CELL>> 
    snakeBody)
    {
        this->snakeBody =snakeBody;
    }
    
    inline void setEle (std::shared_ptr<CELL> 
    ele)
    {
        this->ele =ele;
    }
    
    inline void setScore (int score)
    {
        this->score =score;
    }
    
    inline void setSeconds (int seconds)
    {
        this->seconds =seconds;
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
			    if (snakeHead.get()->getRow() 
			    == w 
			    && snakeHead.get()->getCol() 
			    == h )
			        std::cout
		   	     <<snakeHead.get()
		   	     ->getCellType();
		   	     
		   	 else if (ele.get()->getRow() 
		   	 == w
		   	  && ele.get()->getCol() == h)
		   	     std::cout<<ele.get()
		   	     ->getCellType();
		   	     
			    else
			    {
			        bool space =true;
			        for (auto &cl : snakeBody)
			        {
			            if 
			            (cl.get()->getRow() 
			             == w 
			          && cl.get()->getCol()
			             == h)
			             {
			                 std::cout
			                 <<cl.get()->
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
		std::cout<<"Score :"<<score;
		
		for (int count =0;count < width-10; 
		count++)
		     std::cout<<" ";
		std::cout<<std::setfill('0')
		<<std::setw(2)
		<<seconds<<"\n";
    }
};

class GAME_ENGINE
{
    enum eDir {stop=0,Up,Down,Right,Left};
    enum eSpeed {fast =10000,slow =100000};
    eDir dir;
    eSpeed speed;
    int width, height, score, seconds, 
    count;
    bool stoned,poisoned,healed,boost,quit;
    std::shared_ptr<SNAKE> snake;
    std::shared_ptr<CELL> snakeHead;    
    std::vector<std::shared_ptr<CELL>> 
    snakeBody;
    std::shared_ptr<CELL> element;
    std::shared_ptr<BOARD> board;
    std::shared_ptr<GENERATOR> generator;
    
public:    
    GAME_ENGINE (int w,int h)
    {
        dir =Right;
        width =w;
        height =h;
        score =0;
        seconds =0;
        count =5;
        speed =slow;
        quit =false;
        boost =false;
        poisoned =false;
        healed =false;
        stoned =false;
        snake =std::make_shared
        <SNAKE> (w,h);
        snakeHead =snake.get()->getHead();
        snakeBody =snake.get()->getBody();
        generator =std::make_shared
        <GENERATOR> (w,h);
        element =
        generator.get()->generated();
        board =std::make_shared
        <BOARD> 
        (w,h,score,snakeHead,snakeBody
        ,element);         
    }
    
    ~GAME_ENGINE ()
    {        
        std::cout<<"~GAME_ENGINE()\n";
    }
            
    void draw ()
    {
        board.get()->draw();
    }
    
    void countSeconds()
    {
        while (!Quit())
        {
            sleep(1);
            
            ++seconds;
            
            board->setSeconds(seconds);
            
            if (count <= seconds)
            {
                seconds =0;
                reGenerate ();
            }
        }
    }
    
    void reGenerate ()
    {
        element =NULL;
        element =generator.get()
        ->generated();
        board.get()->setEle(element);       
    }
    
    void loseWeight ()
    {           
        if (poisoned)
            for (auto &cell : snakeBody)
                 ((TAIL*)cell.get())
                 ->poisoned();
                     
        if (score > 0)
        {        
            snakeBody.pop_back();
            
            if (stoned)
            ((TAIL*)snakeBody.back().get())
            ->ateStone();   
        
            snake->resetBody(snakeBody);
        
            board->setSnakeBody(snakeBody);
        
            board->setScore(--score);
        }        
        reGenerate ();
    }    
    
    void grow ()
    {        
       if (poisoned)
       {
           for (auto &cell : snakeBody)
                ((TAIL*)cell.get())
                ->ateStone();                
           
           poisoned =false;
           healed =true;
       }
       else if (stoned)
       {
           ((TAIL*)snakeBody.back().get())
            ->ateFood();
           stoned =false;
       }       
       else if (healed)
       {           
           for (auto &cell : snakeBody)
                ((TAIL*)cell.get())
                ->ateFood();
                
           board->setScore(++score);
           
           healed =false;          
       }
       else
       {
       ((TAIL*)snakeBody.back().get())
       ->ateFood();
                
       snakeBody.push_back
       (std::make_shared<TAIL>
       (snakeBody.back()->XY().first
       ,snakeBody.back()->XY().second));
       
       ((TAIL*)snakeBody.back().get())
        ->ateFood();           
                                
       snake->resetBody(snakeBody);
        
       board->setSnakeBody(snakeBody);
        
       board->setScore(++score);
       }
        
       reGenerate ();
    }    
    
    void DoThis (char arrows)
    {
        snake.get()->shift(snakeBody
                    ,snakeHead);
        
        switch (arrows)
        {
            case 'w':
            snakeHead.get()->moveUp();
            break;
            
            case 's':
            snakeHead.get()->moveDown();
            break;
            
            case 'd':
            snakeHead.get()->moveRight();
            break;
            
            case 'a':
            snakeHead.get()->moveLeft();
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
                
                if (boost)
                    speed =fast;
                boost =true;
                break;
                
                case 'p':case 'P':
                
                if (speed == fast)
                    speed =slow;
                else
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
        usleep(speed);       
    }
    
    void logic ()
    {
        if (snakeHead.get()->getRow() 
        >= width)
            snakeHead.get()->setRow(0);           
        else if (snakeHead.get()->getRow() 
        < 0)                 
        snakeHead.get()->setRow(width-1);
                 
        else if (snakeHead.get()->getCol() 
         < 0 
         || snakeHead.get()->getCol() 
         >= height)
        {
            quit =true;
            std::cout<<"Game Over\n";
        }
        else if (snakeHead.get()->getRow()
        == element.get()->getRow() 
        && snakeHead.get()->getCol() 
        == element.get()->getCol())
        {
            seconds =0;
            
            if (element.get()->getCellName() 
            == "FOOD")
            grow ();
            else if 
            (element.get()->getCellName()
            == "POISON")
            {
                poisoned =true;
                healed =!poisoned;
                loseWeight ();
            }
            else
            {
                stoned =true;
                loseWeight ();
            }            
        }
        else
        {
          for (auto &tail : snakeBody)
          {
             if (snakeHead.get()->getRow() 
             == tail.get()->getRow() 
             && snakeHead.get()->getCol() 
             == tail.get()->getCol())
             {
                 std::cout<<"Game Over\n";
                 quit =true;
             }
             
             if (tail.get()->getRow() 
             == element.get()->getRow() 
             && tail.get()->getCol() 
             == element.get()->getCol())
             reGenerate ();             
          }
          if (score >= 5)
          {
              std::cout<<"You win\n";
              
              if (snakeBody.size()-1 == score)
              {
                  std::cout<<
                  "Score +1 Bounus\n";
                  score++;
              }
                  
              quit =true;
          } 
        }
          
    }
    
    bool Quit ()
    {
        return quit;
    }
    
    void debug ()
    {
        //std::cout<<element;
        //std::cout<<snakeBody.back();
        //std::cout<<snakeHead;
        //std::cout<<"\t\t"<<seconds<<"\n";
    }
    
    void run ()
    {
        do
        {
            draw();
            input();
            move();
            logic();
            //debug();            
        }while (!Quit());
    }                    
};

int main()
{
    std::shared_ptr<GAME_ENGINE> 
    ge(std::make_shared<GAME_ENGINE>(83,20));
    
    std::thread 
    task(&GAME_ENGINE::countSeconds,ge);
    
    ge->run();
    
    if (ge->Quit())    
        task.join();    
}