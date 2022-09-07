#include <vector>
#include <iostream> // std::cout
#include <memory> // std::auto_ptr
#include <algorithm> // std::for_each
#include <string>
using namespace std;
 
class Graphic//component
{
public:
  virtual void print()  = 0;
  virtual ~Graphic() {}
};
//leaf 
class Ellipse : public Graphic
{
    std::string name_;
    static int counter;
    int num;
public:
  Ellipse (std::string name) : name_(name) 
  {
      this->num =++counter;
      }
  std::string  getName ()
  {
      return name_;
  }
  void print()  {
   cout << std::to_string(num) + getName () + 
   " Ellipse \n" ;
  }
};
int Ellipse ::counter =0;
//composite 
class CompositeGraphic : public Graphic
{
public:
  void print()  {
    for(Graphic * a: graphicList_) {
      a->print();
    }
  }
 
  void add(Graphic *aGraphic) {
    graphicList_.push_back(aGraphic);
  }
 
private:
  vector<Graphic*>  graphicList_;
};
 
int main()
{
  // Initialize four ellipses
  const auto_ptr<Ellipse> ellipse1(new Ellipse("st"));
  const auto_ptr<Ellipse> ellipse2(new Ellipse("nd"));
  const auto_ptr<Ellipse> ellipse3(new Ellipse("rd"));
  const auto_ptr<Ellipse> ellipse4(new Ellipse("th"));
 
  // Initialize three composite graphics
  const auto_ptr<CompositeGraphic> graphic(new CompositeGraphic());
  const auto_ptr<CompositeGraphic> graphic1(new CompositeGraphic());
  const auto_ptr<CompositeGraphic> graphic2(new CompositeGraphic());
 
  // Composes the graphics
  graphic1->add(ellipse1.get());
  graphic1->add(ellipse2.get());
  graphic1->add(ellipse3.get());
 
  graphic2->add(ellipse4.get());
 
  graphic->add(graphic1.get());
  graphic->add(graphic2.get());
 
  // Prints the complete graphic (four times the string "Ellipse")
  graphic->print();
  return 0;
}