// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body 
class Fill{
public:
   Fill(char border, char internal): borderChar_(border), internalChar_(internal) {}
   virtual char getBorder() {return borderChar_;}
   virtual char getInternal() {return internalChar_;}
   virtual ~Fill() {}
protected:
   char borderChar_;
   char internalChar_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char border):Fill(border, ' '){}
   //char getBorder() override {return fillChar_;}
   //char getInternal() override {return ' ';}
   ~Hollow() override {}
};


// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar, fillChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~Filled() override {}
};

class FullyFilled: public Filled {
   public:
      FullyFilled(char borderChar, char innerChar): Filled(borderChar), internalChar_(innerChar){}
      char getInternal() override { return internalChar_; }
   private:
      char internalChar_;
};

class RandomFilled : public Fill {
public:
    RandomFilled(char char1, char char2) : Fill(char1, char2) {}
    char getBorder() override { return getRandomChar(); }
    char getInternal() override { return getRandomChar(); }
private:
    char getRandomChar() {
        return (rand() % 2 == 0) ? borderChar_ : internalChar_;
    }
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){
   srand(time(NULL));
   
   Figure* hollowSquare = new Square(7, new Hollow('&'));
    Figure* filledSquare = new Square(7, new Filled('@'));
    Figure* fullyFilledSquare = new Square(7, new FullyFilled('#', '*'));
    Figure* randomFilledSquare = new Square(7, new RandomFilled('X', 'O'));

    cout << "Hollow Square:" << endl;
    hollowSquare->draw();
    cout << endl;

    cout << "Filled Square:" << endl;
    filledSquare->draw();
    cout << endl;

    cout << "Fully Filled Square:" << endl;
    fullyFilledSquare->draw();
    cout << endl;

    cout << "Random Filled Square:" << endl;
    randomFilledSquare->draw();
    cout << endl;

    // Cleanup
    delete hollowSquare;
    delete filledSquare;
    delete fullyFilledSquare;
    delete randomFilledSquare;

    return 0;
   
}