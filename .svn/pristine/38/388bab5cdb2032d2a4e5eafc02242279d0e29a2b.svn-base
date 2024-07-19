// implements command history (multiple undos)
// demonstrates command pattern
// Mikhail Nesterenko
// 04/13/2023

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

   Document(const vector <string> & lines={}): lines_(lines){}

   // actions
   void insert(int line, const string &str) {
      const int index = line-1;
      if (index <= lines_.size())
	 lines_.insert(lines_.begin()+index, str); 
      else
	 cout << "line out of range" << endl; 
   }

   const string remove(int line) {
      const int index = line-1;
      string deletedLine="";
      if(index < lines_.size()){
	 // deletedLine = lines_[index];
	 deletedLine = *(lines_.begin()+index); 
	 lines_.erase(lines_.begin() + index); 
      }else
	 cout << "line out of range" << endl; 
      return deletedLine;
   } 

   void show() {
      for(int i = 0; i < lines_.size(); ++i)
	 cout << i + 1 << ". " << lines_[i] << endl; 
   }

private:
   vector<string> lines_; 
}; 

// abstract command
class Command{
public:
   Command(Document *doc) : doc_(doc){}
   virtual void execute() = 0; 
   virtual void unexecute() = 0;
   virtual void show() = 0;
   virtual string getString() = 0;
   virtual int getLine() = 0;
   virtual string getType()= 0;
   virtual ~Command(){}
protected:
   Document *doc_; 
}; 

// two concrete commands
class InsertCommand : public Command {
public:
   InsertCommand(Document *doc, int line, const string &str): 
      Command(doc), line_(line),  str_(str), type_("insert") {}
   void execute() override { doc_->insert(line_, str_);}
   void unexecute() override {doc_->remove(line_);}
   void show() override {cout << "insert " << "\"" << str_ << "\""<< "at line "<< line_ << endl;}
   int getLine() override { return line_; }
   string getString() override { return str_; }
   string getType() override { return type_; }
private:
   int line_; 
   string str_; 
   string type_;
}; 


class EraseCommand : public Command {
public:
   EraseCommand(Document *doc, int line): 
      Command(doc), line_(line), str_(""), type_("erase") {}
   void execute() override {str_ = doc_->remove(line_);}
   void unexecute() override {doc_->insert(line_, str_);}
   void show() override {cout << "erase line " << line_ << endl;}
   int getLine() override { return line_; }
   string getString() override { return str_; }
   string getType() override { return type_; }
private:
   int line_;
   string str_;
   string type_;
};

// client ?
class DocumentWithHistory{
public:
   DocumentWithHistory(const vector<string> & doc={}) : doc_(doc){}

   void insert(int line, string str) {
      Command *com = new InsertCommand(&doc_, line, str); 
      com->execute(); 
      doneCommands_.push_back(com); 
   }

   void erase(int line){
      Command *com = new EraseCommand(&doc_, line);
      com->execute();
      doneCommands_.push_back(com);
   }

   void undo() {
      if(doneCommands_.size() != 0) {
	 Command *com = doneCommands_.back(); 
     com->unexecute();
	 doneCommands_.pop_back(); 
	 
	 delete com; // don't forget to delete command
      }else
	 cout << "no commands to undo" << endl; 
   }

   void history() {
    int counter = 0;
    for(auto command : doneCommands_) {
        ++counter;
        cout << counter << ".";
        command->show();
    }
   }

   void redo(int lineNumber) {
      auto command = doneCommands_[lineNumber - 1];
      string str = command->getString();
      int line = command->getLine();
      string type = command->getType();
      if (type == "erase") {
         Command *com = new EraseCommand(&doc_, line);
         com->execute();
      }
      if (type == "insert") {
         Command *com = new InsertCommand(&doc_, line, str);
         com->execute();
      }
   }

    vector<Command*> getCommands() {
        return doneCommands_;
    }

    void setCommands(vector<Command*> vector) {
      doneCommands_ = vector;
    }

   void show() {cout << endl; doc_.show();}

   class Memento *checkpoint() const;  
   void rollback(class Memento *); 

private:
   Document doc_;
   vector<Command*> doneCommands_; 
}; 

class Memento {
public:
   Memento(DocumentWithHistory doc): doc_(doc) {
    doneCommands_ = doc.getCommands();
   }
   const DocumentWithHistory& getState() const {return doc_;}  
private:
   const DocumentWithHistory doc_;
    std::vector<Command*> doneCommands_;
};

Memento *DocumentWithHistory::checkpoint() const{
   return new Memento(*this); // copying the Document itself
}

void DocumentWithHistory::rollback(Memento *mem){
   *this = mem->getState();  // copying back
}

// invoker
int main() {
   DocumentWithHistory his({
	 "Lorem Ipsum is simply dummy text of the printing and typesetting",
	 "industry. Lorem Ipsum has been the industry's standard dummy text",
	 "ever since the 1500s, when an unknown printer took a galley of",
	 "type and scrambled it to make a type specimen book. It has",
	 "survived five centuries."}); 

   char option; int lineChoice;
   do{
      static Memento *safeState = nullptr;
      his.show(); 
      cout << endl;

      cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command, (c)heckpoint, roll(b)ack, (h)istory, (r)edo: ";
      cin >> option; 

      int line; string str; vector<Command*> vector;
      switch(option) {

      case 'i':
	    cout << "line number to insert: "; 
        cin >> line; 
        cout << "line to insert: "; 
        cin.get(); // removes end-of-line character so getline() works correctly
        getline(cin, str); 
        his.insert(line, str); 
        break;
 
      case 'e':
        cout << "line number to remove: ";
        cin >> line;
        his.erase(line);
        break;

      case 'u':
        his.undo(); 
        break; 
      
      case 'c':
         vector = his.getCommands();
         vector.clear();
         his.setCommands(vector);

        safeState = his.checkpoint();
        break;
      case 'b':
        if (safeState != nullptr){
            his.rollback(safeState);
            delete safeState;
            safeState = nullptr;
        }else
            cout << "No checkpoint created" << endl;
            break;

        case 'h':
            his.history();
            cout << endl;
            break;

         case 'r':
            cout << "Select the command history number you want to redo: " << endl;
            cin >> lineChoice;
            his.redo(lineChoice);

            break;
      }

   }while(option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}