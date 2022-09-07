#include <vector>
#include <iostream> // std::cout
#include <memory> // std::auto_ptr
#include <algorithm> // std::for_each
using namespace std;
 
class Graphic//component
{
public:
  virtual void add(Graphic* )
  {}
  virtual void print() const = 0;
  virtual ~Graphic() {}
};
//leaf 
class Ellipse : public Graphic
{
public:
  void print() const {
    cout << "Ellipse \n";
  }
};
//composite 
class CompositeGraphic : public Graphic
{
public:
  void print() const {
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
  const auto_ptr<Graphic> ellipse1(new Ellipse());
  const auto_ptr<Graphic> ellipse2(new Ellipse());
  const auto_ptr<Graphic> ellipse3(new Ellipse());
  const auto_ptr<Graphic> ellipse4(new Ellipse());
 
  // Initialize three composite graphics
  const auto_ptr<Graphic> graphic(new CompositeGraphic());
  const auto_ptr<Graphic> graphic1(new CompositeGraphic());
  const auto_ptr<Graphic> graphic2(new CompositeGraphic());
 
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