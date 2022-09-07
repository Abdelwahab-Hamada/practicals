#include <iostream>

class REQUEST
{
public:    
    double a,b;    
    char op;
   
    REQUEST (double a, double b, char op)
    {
        this->a =a;
        this->b =b;
        this->op =op;
    }
};

class MATHHANDLER
{
public:    
    virtual void setNext (MATHHANDLER* ) =0;
    virtual void calc (REQUEST* ) =0;    
};

class SUMHANDLER : public MATHHANDLER
{
    MATHHANDLER* next;
public:    
    void setNext (MATHHANDLER* hdr)
    {
        this->next =hdr;
    }
    
    void calc (REQUEST* req)
    {
        if (req->op == '+')
            std::cout<<"Sum of: "<<req->a<<
                       req->op<<req->b<<" ="
                       <<req->a+req->b<<"\n";
        else 
        this->next->calc(req);
    }
    
};

class SUBHANDLER : public MATHHANDLER
{
    MATHHANDLER* next;
public:    
    void setNext (MATHHANDLER* hdr)
    {
        this->next =hdr;
    }
    
    void calc (REQUEST* req)
    {
        if (req->op == '-')
            std::cout<<"Sub of: "<<req->a<<
                       req->op<<req->b<<" ="
                       <<req->a-req->b<<"\n";
        else 
        this->next->calc(req);
    }
    
};

class MULHANDLER : public MATHHANDLER
{
    MATHHANDLER* next;
public:    
    void setNext (MATHHANDLER* hdr)
    {
        this->next =hdr;
    }
    
    void calc (REQUEST* req)
    {
        if (req->op == '*')
            std::cout<<"Mul of: "<<req->a<<
                       req->op<<req->b<<" ="
                       <<req->a*req->b<<"\n";
        else 
        this->next->calc(req);
    }
    
};

class DIVHANDLER : public MATHHANDLER
{
    MATHHANDLER* next;
public:    
    void setNext (MATHHANDLER* hdr)
    {
        this->next =hdr;
    }
    
    void calc (REQUEST* req)
    {
        if (req->op == '/')
            std::cout<<"Div of: "<<req->a<<
                       req->op<<req->b<<" ="
                       <<req->a/req->b<<"\n";
        else 
        std::cout<<"Sorry , MATHHANDLER Support +,-,× and ÷ only for now\n";
    }
    
};

class RECEIVER
{
    MATHHANDLER* sum =new SUMHANDLER();
    MATHHANDLER* sub =new SUBHANDLER();
    MATHHANDLER* mul =new MULHANDLER();
    MATHHANDLER* div =new DIVHANDLER();
    
public:    
    RECEIVER ()
    {
        sum->setNext(sub);
        sub->setNext(mul);
        mul->setNext(div);
    }
    
    void sendReq (REQUEST* req)
    {
        sum->calc(req);
    }
};

int main()
{
    REQUEST* r =new REQUEST (10,5,'-');
    RECEIVER* rec =new RECEIVER ();
    rec->sendReq(r);
}