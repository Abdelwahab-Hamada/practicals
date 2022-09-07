#include <utility>
#include <vector>
#include <list>
#include <conio.h>
#include <string>
#include <unistd.h>
#include <memory>
#include <thread>
#include <iomanip>
#include <time.h>
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
public:    
    int row, col;
    char dir;
    
protected:    
    std::string cellName;    
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
        row =x;
        col =y;
    }
    
    virtual ~CELL ()
    {
        std::cout<<"~"+ cellName + " ()\n"; 
    }    
    
    inline std::string getCellType ()
    {
        return type->cellType();
    }
    
    inline std::string getCellName ()
    {
        return cellName;
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
        row =x;
        col =y;
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
        row =x;
        col =y;
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
        row =x;
        col =y;
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
        row =x;
        col =y;
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
        row =x;
        col =y;
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
        srand(time(0));        
        int X =rand() %width;
        int Y =rand() %height;
        return std::make_pair(X,Y);
    }
    
    char calc ()
    {
        srand(time(0));
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
    int x, y,oX,oY;
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
        oX =head->row;
        oY =head->col;
    }
    
    ~SNAKE ()
    {
        std::cout<<"~SNAKE() \n";
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
    
    void reset ()
    {
        head->row =oX;
        head->col =oY;
        body.front()->row =head->XY().first;
        body.front()->col =head->XY().second;
    } 
    
    void shift 
    (std::vector<std::shared_ptr<CELL>> 
    cells,std::shared_ptr<CELL> followed)
    {
        //original old
        int prevX =cells.front().get()
        ->row;
        int prevY =cells.front().get()
        ->col;
        char dirI =cells.front().get()
        ->dir;
        
        int prevXI,prevYI;
        char dirII;
        
        //new
        cells.front().get()->row =
        (followed.get()->row);
        cells.front().get()->col =
        (followed.get()->col);
        cells.front().get()->dir =
        (followed.get()->dir);
        
        for (int index =1;index 
        < cells.size();index++)
        {
            //old
            prevXI =cells.at(index).get()
            ->row;
            prevYI =cells.at(index).get()
            ->col;
            dirII =cells.at(index).get()
            ->dir;
            
            //new
            cells.at(index).get()
            ->row =prevX;
            cells.at(index).get()
            ->col =prevY;
            cells.at(index).get()
            ->dir =dirI;
            
            //current
            prevX =prevXI;
            prevY =prevYI;
            dirI =dirII;            
        }
    }    
};

class BOARD_IF
{
public:    
    virtual void 
    update(int score,int seconds
    ,std::shared_ptr<CELL> snakeHead
    ,std::vector<std::shared_ptr<CELL>> 
    snakeBody,std::shared_ptr<CELL> ele) =0;
};

class DISPLAYBOARD_IF
{
public:    
    virtual void draw () =0;
};

class GAME_ENGINE_IF
{
protected:    
    enum eDir {stop=0,Up,Down,Right,Left};
    enum eSpeed {fast =10000,slow =100000};
    eDir dir;
    eSpeed speed;
    int width, height, score, seconds, 
    count;
    bool stoned,poisoned,healed,boost,quit
    ,chase,autoMove;
    std::shared_ptr<SNAKE> snake;
    std::shared_ptr<CELL> snakeHead;    
    std::vector<std::shared_ptr<CELL>> 
    snakeBody;
    std::shared_ptr<CELL> element;
    std::shared_ptr<GENERATOR> generator;
    std::list<std::shared_ptr<BOARD_IF>> 
    boards;

protected:        
    void reGenerate ()
    {
        element =NULL;
        element =generator.get()
        ->generated();       
    }
    
    void DoThis (char arrows)//Side task
    {
        snake.get()->shift(snakeBody
                    ,snakeHead);
        
        switch (arrows)
        {
            case 'w':
            
            ((HEAD*)snakeHead.get())
            ->moveUp();
            dir =Up;
            break;
            
            case 's':
            
            ((HEAD*)snakeHead.get())
            ->moveDown();
            dir =Down;
            break;
            
            case 'd':
            
            ((HEAD*)snakeHead.get())
            ->moveRight();
            dir =Right;
            break;
            
            case 'a':
            
            ((HEAD*)snakeHead.get())
            ->moveLeft();
            dir =Left;
            break;
        }        
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
            --score;   
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
                
           ++score;     
           
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
        
       ++score;                       
       }
        
       reGenerate ();
    }                
    
    void debug ()
    {
        //std::cout<<element;
        //std::cout<<snakeBody.back();
        //std::cout<<snakeHead;
        //std::cout<<"\t\t"<<seconds<<"\n";
    }
    
public:    
    void countSeconds()
    {
        while (!quit)
        {
            sleep(1);
            
            ++seconds;
            
            if (count <= seconds)
            {
                seconds =0;
                reGenerate ();
            }
        }
    }
    
    bool Quit ()
    {
        return quit;
    }                
    
public:    
    virtual void attach 
    (std::shared_ptr<BOARD_IF>) =0;
    
    virtual void dettach 
    (std::shared_ptr<BOARD_IF>) =0;
    
    virtual void notify () =0;
};

class GAME_ENGINE : public GAME_ENGINE_IF
{        
protected:    
    void notify ()
    {
        for (auto &board : boards)
             board.get()->update(score
             ,seconds,snakeHead,snakeBody
             ,element);
    }
        
public:    
    GAME_ENGINE (int w,int h)
    {
        dir =Right;
        width =w;
        height =h;
        score =0;
        seconds =0;
        count =10;
        speed =slow;
        quit =false;
        boost =false;
        poisoned =false;
        healed =false;
        stoned =false;
        chase =false;
        autoMove =false;
        snake =std::make_shared
        <SNAKE> (w,h);
        snakeHead =snake.get()->getHead();
        snakeBody =snake.get()->getBody();
        generator =std::make_shared
        <GENERATOR> (w,h);
        element =
        generator.get()->generated();        
    }
    
    ~GAME_ENGINE ()
    {        
        std::cout<<"~GAME_ENGINE()\n";
    }
    
    void attach (std::shared_ptr<BOARD_IF> 
    board)
    {
        boards.push_back(board);
    }
    
    void dettach (std::shared_ptr<BOARD_IF> 
    board)
    {
        boards.remove(board);
    }
    
    void changeable (int score,int seconds
    ,std::shared_ptr<CELL> snakeHead
    ,std::vector<std::shared_ptr<CELL>> 
    snakeBody,std::shared_ptr<CELL> element)
    {
        this->score =score;
        this->seconds =seconds;
        this->snakeHead =snakeHead;
        this->snakeBody =snakeBody;
        this->element =element;
        notify ();
    }                
            
    void setChangeable ()
    {
        changeable (score,seconds,snakeHead
        ,snakeBody,element);
    }              
    
    void input ()
    {
        if (_kbhit())
            switch (_getch())
            {
                case 'w':case 'W':
                
                if (dir != Down)      
                    DoThis('w');
                else
                    sleep(2);      
                break;
                
                case 's':case 'S':
                
                if (dir != Up)               
                    DoThis('s'); 
                else
                    sleep(2);  
                break;
                
                case 'd':case 'D':
                
                if (dir != Left)
                    DoThis('d');
                else
                    sleep(2);   
                break;
                
                case 'a':case 'A':
                
                if (dir != Right)
                    DoThis('a');
                else
                    sleep(2);  
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
                
                case 'c':case 'C':
                
                if (!chase)
                    chase =true;
                else
                    chase =false;
                autoMove =false;
                break;
                
                case 'm':case 'M':
                
                if (!autoMove)
                    autoMove =true;
                else
                    autoMove =false;
                chase =false;
                break;
            }
    }
    
    void move ()
    {
        if (autoMove && !chase)            
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
    
    void chaseMode ()
    {
        if (element.get()->getCellName() 
            == "FOOD" && chase && !autoMove)
            if (snakeHead.get()->row
            != element.get()->row 
            || snakeHead.get()->col
            != element.get()->col)
            {
                if (snakeHead.get()->col 
                > element->col)
                    DoThis('w');
                else
                if (snakeHead.get()->col 
                < element->col)
                    DoThis('s');
                else
                if (snakeHead.get()->row 
                < element->row)
                    DoThis('d');
                else
                if (snakeHead.get()->row 
                > element->row)
                    DoThis('a');    
            }                
    }
    
    void logic ()
    {
        if (snakeHead.get()->row >= width)
            snakeHead.get()->row =0;           
        else if (snakeHead.get()->row < 0)                 
        snakeHead.get()->row =(width-1);
                 
        else if (snakeHead.get()->col < 0 
         || snakeHead.get()->col >= height)
        {
            quit =true;
            std::cout<<"Game Over\n";
        }
        else if (snakeHead.get()->row
        == element.get()->row 
        && snakeHead.get()->col
        == element.get()->col)
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
          int tails =0;
              
          for (auto &tail : snakeBody)
          {                          
             if (tail.get()->row 
             == element.get()->row 
             && tail.get()->col 
             == element.get()->col)
             reGenerate ();
             
             if (snakeHead.get()->row 
             == tail.get()->row 
             && snakeHead.get()->col 
             == tail.get()->col)
             {                 
                 int oldSize 
                 =snakeBody.size();
                 
                 snakeBody.erase
                 (snakeBody.begin()+tails
                 ,snakeBody.end());
                 
                 for(int c=0;c<
                 (oldSize-snakeBody.size())
                 ;c++)
                 score--;                 
                 
                 sleep(1);
             }
             else
             tails++; 
          }
          
          if (score >= 10)
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
        
    void run ()
    {
        do
        {
            input();
            move();
            chaseMode ();
            setChangeable();            
            logic();
            //debug();            
        }while (!Quit());
    }                    
};

class BOARD : public BOARD_IF, public DISPLAYBOARD_IF
{
    int width, height, score, seconds;
    std::shared_ptr<CELL> snakeHead;    
    std::vector<std::shared_ptr<CELL>> 
    snakeBody;
    std::shared_ptr<CELL> ele;
    
protected:    
    std::shared_ptr<GAME_ENGINE> gameEngine_;
    
public:    
    BOARD (std::shared_ptr<GAME_ENGINE>
    gameEngine,int w,int h) 
    : gameEngine_(gameEngine)
    {
        this->width =w;
        this->height =h;
        gameEngine_->attach
        (std::shared_ptr<BOARD_IF>(this ));
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
			    if (snakeHead.get()->row == w 
			    && snakeHead.get()->col == h )
			        std::cout
		   	     <<snakeHead.get()
		   	     ->getCellType();
		   	     
		   	 else if (ele.get()->row 
		   	 == w
		   	  && ele.get()->col == h)
		   	     std::cout<<ele.get()
		   	     ->getCellType();
		   	     
			    else
			    {
			        bool space =true;
			        for (auto &cl : snakeBody)
			        {
			            if 
			            (cl.get()->row 
			             == w 
			          && cl.get()->col
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
    
    void update (int score,int seconds
    ,std::shared_ptr<CELL> snakeHead
    ,std::vector<std::shared_ptr<CELL>> 
    snakeBody,std::shared_ptr<CELL> element)
    {
        this->score =score;
        this->seconds =seconds;
        this->snakeHead =snakeHead;
        this->snakeBody =snakeBody;
        this->ele =element;
        draw ();
    }                
    
};

int main()
{
    int width, height;
    width =83;
    height =20;
    std::shared_ptr<GAME_ENGINE> 
    gameEngine    
(std::make_shared<GAME_ENGINE>(width
    ,height));
    
    std::thread 
    task
    (&GAME_ENGINE::countSeconds,gameEngine);
    
    std::shared_ptr<BOARD> 
    board    (std::make_shared<BOARD>(gameEngine,width
    ,height));
    
    gameEngine->run();
    
    if (gameEngine->Quit())    
        task.join();    
}