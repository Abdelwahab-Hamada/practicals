class RECEIVER
{
    //somecodes done by someone includes 
    //commands guide
};

class COMMAND
{
public:    
    virtual void Do() =0;
    virtual void unDo() =0;
};

class NONCOMMAND
{
public:    
    void Do()
    {}
    void unDo()
    {}
};

class COMMAND1 : public COMMAND
{
public:    
    void Do()
    {
    }
    void unDo()
    {
    }
};

class COMMAND2 : public COMMAND
{
public:    
    void Do()
    {
    }
    void unDo()
    {
    }
};

class INVOKER
{
private:    
    COMMAND* c1;
    COMMAND* c2;
    
public:    
    INVOKER() 
    { this->c1 =new NONCOMMAND (); }
    
    void setCommands(reciver index, 
    command1,command2)
    {
        c1[index] =command1;
        c2[index] =command2;
    }
    
    void press command()
    {
        c1[index]->Do();
    }
    void unpress command()
    {
        c2[index]->Do();
    }
};


main()
{
    RECIVER* R =new RECEIVER();
    
    COMMAND* C1 =new COMMAND1(R);
    COMMAND* C2 =new COMMAND2(R);
    
    INVOKER* I =new INVOKER();
    I->setCommands(R,C1,C2);
    
    I->press command ();
    I->unpress command ();
}

