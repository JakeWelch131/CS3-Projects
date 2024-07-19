// figures: class adapter pattern
// Jacob Welch
// 4/5/2024

#include <iostream>

using std::cout; using std::endl; using std::cin;

// target interface
class Square {
public:
   virtual void draw() const =0;
   virtual ~Square(){}
};

// adaptee/implementer
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

   void oldDraw() const {
      for(int i=0; i < bottomRightY_; ++i){
	 for(int j=0; j < bottomRightX_; ++j)
	    if(i >= topLeftY_  && j >= topLeftX_ )
	       cout << '*';
	    else
	       cout << ' ';
	 cout << endl;
      }
   }

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
      topLeftX_ = topLeftX;
      topLeftY_ = topLeftY;
      bottomRightX_ = bottomRightX;
      bottomRightY_ = bottomRightY;
   }

   int getTopLeftX() {
      return topLeftX_;
   }

   int getTopLeftY() {
      return topLeftY_;
   }

   int getBottomRightX() {
      return bottomRightX_;
   }

   int getBottomRightY() {
      return bottomRightY_;
   }
// defining top/left and bottom/right coordinates 
private: 
    int topLeftX_;
    int topLeftY_;
    int bottomRightX_;
    int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Square, 
		     private LegacyRectangle {
public:
   SquareAdapter(int size): LegacyRectangle(0,0,size,size){};

   void draw() const override {
      oldDraw();
   }

   int size() {
      return getBottomRightX();
   }

   void resize(int newSize) {
      move(getTopLeftX(), getTopLeftY(), newSize, newSize);
   }
};


int main(){
   //LegacyRectangle* adaptee = new LegacyRectangle(2, 2, 4, 4);

   int response;
   cout << "Enter a size for the square ";
   cin >> response;
   SquareAdapter* adapter = new SquareAdapter(response);
   adapter->draw();

   cout << "Enter a new size for the square ";
   cin >> response;

   adapter->resize(response);
   adapter->draw();
}