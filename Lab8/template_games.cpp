// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <algorithm>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 5; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

// Chess - another game implementing
// primitive operations
class Dice: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numDice_; ++i) 
	     compRoll_[i] = 0; 

      for(int i=0; i < numDice_; ++i) 
	     humRoll_[i] = 0;

       compDecision_ = true;
       humDecision_ = true;
       compScore_ = 0;
       humScore_ = 0;
       roundNum_ = 1;
   }

   

   void makeMove(int player){
      if (roundNum_ < 3) {                                                                      //if the round number is 1 or two, we are going to ask the computer and human for decisions,
        if (compDecision_ == true) {                                                            //in round 3 no decisions are asked
            fillArray(compRoll_);                                                               // if the computer chooses to roll again, we are going to refill the array with new numbers
            compScore_ = sumUpArray(compRoll_);                                                 // and then add them upp and save them to the computers score
        }        
        
        if (humDecision_ == true) {                                                             // same idea for the human's decision
            fillArray(humRoll_);
            humScore_ = sumUpArray(humRoll_);
        }

        printRound();                                                                           // print the computers and humans results from the rounf
        computerDecision();                                                                     // asks the computer if they would like to pass, or roll again
        humanDecision();                                                                        // same idea for human

        

        if (humDecision_ == true && compDecision_ == false) {                                   // if the human wants to roll again and the computer does not, we are going to set all integers 
            humScore_ = 0;                                                                      // back to 0 so we can fill them up in the next round
            std::for_each(humRoll_, humRoll_ + 5, [](int& x) { x = 0; });
        }
        else if (humDecision_ == false && compDecision_ == true) {                              // same idea for if only the computer wants to roll again
             compScore_ = 0;
             std::for_each(compRoll_, compRoll_ + 5, [](int& x) { x = 0; });
        }
        else if (humDecision_ == true && compDecision_ == true) {                               // uif both the human and computer watns to roll again, we will set everything for both entities to 0
            compScore_ = 0;
            humScore_ = 0;
            std::for_each(humRoll_, humRoll_ + 5, [](int& x) { x = 0; });
            std::for_each(compRoll_, compRoll_ + 5, [](int& x) { x = 0; });
        }
        else {
            compareScores();                                                                    // if both the human and computer pass, then the game is over
            playerWon_ = 1;                                                                     // the scores are compared and the winner is output of the terminal, assigning playerWon_ to a non -1 integer will end the game
        }
      }

      else {                                                                                    // WHEN IT IS THE 3RD ROUND
        if (compDecision_ == true) {                                                            // since there are no rounds past this point, we do not need to worry about asking for decsions or assigning integers to 0
            fillArray(compRoll_);                                                                       
            compScore_ = sumUpArray(compRoll_);                                                 // fill up both arrays and get the scores
        }        

        if (humDecision_ == true) {
            fillArray(humRoll_);
            humScore_ = sumUpArray(humRoll_);
        }

        printRound();                                                                           // print the round
        compareScores();                                                                        // compare the scores and declare a winner
        playerWon_ = 1;                                                                         // end the game since we cannot pass round 3
      }
      ++roundNum_;                                                                              // increment round number
   }

   void printWinner(){
      cout << "game over" << endl;
   }
//===============================================================================================
//                                  Helper functions
   void fillArray(int arr[]) {
    for (int i = 0; i < numDice_; ++i) {
        arr[i] = rand() % 6 + 1;
    }
   }

   int sumUpArray(int arr[]) {
    int sum = std::accumulate(arr, arr + 5, 0);
    return sum;
   }

   void computerDecision() {                                                                    // randomly assigns the compDecision to a bool
    int num = rand() % 2;
    switch (num) {
        case 0:
            compDecision_ = false;
            break;
        case 1: 
            compDecision_ = true;
            break;
        default:
            break;
    }
   }

    void humanDecision() {                                                                      // asks user to make a decision through the command line and assigns a bool based on it
        char choice;
        std::cout << "Roll again? [y/n]" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 'y':
                humDecision_ = true;
                break;
            case 'n':
                humDecision_ = false;
                break;
            default:
                std::cout << "Invalid choice. Please enter y/n" << std::endl;
                break;
        }
    }

    void printRound() {                                                                                                             // has to print different prompts based on it user/comp passed in the previous round
        if (compDecision_ == 0) {
            std::cout << "Round " << roundNum_ << ": Computer rolled: passed, computer's score = " << compScore_ << std::endl;      // will just display "passed" instead of the values of the array if user/comp selected pass last round
        }
        else if (compDecision_ == 1) {
            std::cout << "Round " << roundNum_ << ": Computer rolled: ";
            for (int i = 0; i < numDice_; ++i) {
                std::cout << compRoll_[i] << " ";
            }
            std::cout << ", computer's score = " << compScore_ << std::endl;
        }
        if (humDecision_ == 0) {
            std::cout << "You rolled: passed, your score = " << humScore_ << std::endl;
        }
        else if (humDecision_ == 1) {
            std::cout << "You rolled: ";
            for (int i = 0; i < numDice_; ++i) {
                std::cout << humRoll_[i] << " ";
            }
            std::cout << ", your score = " << humScore_ << std::endl;
        }
}

    void printArray(int x) {
        std::cout << x << " ";
    }

    void wipeArray(int& x) {
        x = 0;
    }

    void compareScores() {
        if (humScore_ < compScore_) {
            std::cout << "You lose!" << std::endl;
        }
        else if (humScore_ > compScore_){
            std::cout << "You win!" << std::endl;
        }
    }
   

private:
   static const int numDice_ = 5;
   static const int numPlayers_ = 2;
   static const int minMoves_ = 1; // nobody wins before minMoves_
   static const int maxMoves_ = 3; // somebody wins before maxMoves_
   static int roundNum_; // round number
   static  bool compDecision_; // computers decision to roll again Y = true, N = false
   static  bool humDecision_; // humans decision to roll again Y = true, N = false
   static int compScore_;
   static int humScore_;
   int compRoll_[numDice_]; 
   int humRoll_[numDice_];
};

bool Dice::compDecision_ = true;
bool Dice::humDecision_ = true;
int Dice::compScore_ = 0;
int Dice::humScore_ = 0;
int Dice::roundNum_ = 1;

int main() {
   srand(time(nullptr));

   Game* gp = nullptr;

   // play chess 7 times
   /*for (int i = 0; i < 7; ++i){ 
      gp = new Chess;
      gp -> playGame(); 
      delete gp;
   }
      

   // play monopoly 7 times
   for (int i = 0; i < 7; ++i){
      gp = new Monopoly;
      gp -> playGame(); 
      delete gp;
   }*/
   gp = new Dice;
   gp -> playGame();
   delete gp;
}