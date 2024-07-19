// State transitions
// Jacob Welch
// 4/10/2024

#include <iostream>
#include <string>
#include <queue>

using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process {
    public:
        Process();
        Process(int id) {currentID_ = id;}
        
        // behaviors
        void create();
        void exit();
        void dispatch();
        void suspend();
        void block();
        void unblock();
        string report();
        int getCounter() {return currentID_;};
        int decrementCounter() {return --processCounter_;};

        Process* clone();
        void changeState(State* state) {state_=state;};

    private:
        State* state_;
        static int processCounter_;
        int currentID_;
        
};

// abstract state
class State{
    public:
        virtual void create(Process*){}
        virtual void exit(Process*){}
        virtual void dispatch(Process*){}
        virtual void suspend(Process*){}
        virtual void block(Process*){}
        virtual void unblock(Process*){}
        //virtual int getCounter(Process* c) {return c->getCounter();};
        virtual string report() = 0;
        virtual State* clone() = 0;

        void changeState(Process* c, State* state) {
            c->changeState(state);
        };

};

class Ready: public State {
    public:
        static State* instance(){
            static State* onlyInstance = new Ready;
            return onlyInstance;
        }
        virtual void dispatch(Process*) override;
        string report() override {
            return "ready";
        }
        State *clone() override {return new Ready();}
    private:
        Ready(const Ready&) = delete;
        Ready& operator=(const Ready&) = delete;
        Ready(){}
};

class Running: public State {
    public:
        static State* instance(){
            static State* onlyInstance = new Running;
            return onlyInstance;
        }
        virtual void exit(Process*) override;
        virtual void suspend(Process*) override;
        virtual void block(Process*) override;
        State *clone() override {return new Running();}
        string report() override {
            return "running";
        }
    private:
        Running(const Running&) = delete;
        Running& operator=(const Running&) = delete;
        Running(){}
};

class Blocked: public State {
    public:
        static Blocked* instance(){
            static Blocked* onlyInstance = new Blocked;
            return onlyInstance;
        }
        virtual void unblock(Process*) override;
        string report() override {
            return "blocked";
        }
        State *clone() override {return new Blocked();}
    private:
        Blocked(const Blocked&) = delete;
        Blocked& operator=(const Blocked&) = delete;
        Blocked(){}
};

class NewState: public State {
    public:
    static NewState* instance() {
        static NewState* onlyInstance = new NewState;
        return onlyInstance;
    }
    virtual void create(Process*) override;
    string report() override {
        return "new";
    }
    State *clone() override {return new NewState();}

    private:
        NewState(const NewState&) = delete;
        NewState& operator=(const NewState&) = delete;
        NewState(){}
};

class Terminated: public State {
    public:
    static Terminated* instance() {
        static Terminated* onlyInstance = new Terminated;
        return onlyInstance;
    }

    string report() override {
        return "terminated";
    }
    State *clone() override {return new Terminated();}
    private:
        Terminated(const Terminated&) = delete;
        Terminated& operator=(const Terminated&) = delete;
        Terminated(){}
};

void Ready::dispatch(Process* p){
    changeState(p, Running::instance());
}

void Running::suspend(Process* p){
    changeState(p, Ready::instance());
}

void Running::exit(Process* p) {
    changeState(p, Terminated::instance());
}

void Running::block(Process* p) {
    changeState(p, Blocked::instance());
}

void Blocked::unblock(Process* p) {
    changeState(p, Ready::instance());
}

void NewState::create(Process* p) {
    changeState(p, Ready::instance());
}

// behaviors
void Process::create(){state_->create(this);}
void Process::exit(){state_->exit(this);}
void Process::unblock(){state_->unblock(this);}
void Process::dispatch(){state_->dispatch(this);}
void Process::suspend(){state_->suspend(this);}
void Process::block(){state_->block(this);}
string Process::report(){return state_->report();}
Process* Process::clone(){return new Process();}

// process member functions
Process::Process() {
            state_ = Ready::instance();
            processCounter_++;
            currentID_ = processCounter_;
        }

int Process::processCounter_ = -1;
int main() {
    srand(time(nullptr));
    std::queue<Process*> readyQueue;
    std::queue<Process*> blockedQueue;

    const int processNum = 4;
    Process p;

    for(int i = 0; i < processNum; ++i) {
        readyQueue.push(p.clone());
    }

    cout << "--------------scheduler running-----------------" << endl;
    while (!readyQueue.empty()) {
        cout << endl << "=====ready queue is beginning====" << endl;
        while(!readyQueue.empty()) {
            
            cout << "ready queue size " << readyQueue.size() << endl;
            Process* process = readyQueue.front();
        
            process->dispatch();
            cout << "Dispatching.." << endl;
            cout << "PID" << process->getCounter() << " state: " << process->report() << endl;
            switch (rand() % 3) {
                case 0:
                    cout << "Exiting... " << endl;
                    process->exit();
                    readyQueue.pop();
                    break;
                case 1:
                    cout << "Suspending... " << endl;
                    process->suspend();
                    cout << "PID" << process->getCounter() << " state: " << process->report() << endl;
                    readyQueue.pop();
                    readyQueue.push(process);
                    break;
                case 2:
                    cout << "Blocking... " << endl;
                    process->block();
                    cout << "PID" << process->getCounter() << " state: " << process->report() << endl;
                    readyQueue.pop();
                    blockedQueue.push(process);
                    break;
            }        
        }
        cout << endl << "the ready queue is empty" << endl;
        cout << endl << "the blocked queue has " << blockedQueue.size() << " processes in it" << endl;
        
        while (!blockedQueue.empty()) {
            Process* process;
            switch (rand() % 2) {
                case 0:
                    cout << "Unblocking..." << endl;
                    process = blockedQueue.front();
                    process->unblock();
                    cout << "PID" << process->getCounter() << " state: " << process->report() << endl;

                    readyQueue.push(process);
                    blockedQueue.pop();
                    break;
                case 1:
                    cout << "didn't unblock for randomization reason" << endl;
                    break;
            }
        }
        cout << endl << "the blocked queue is empty" << endl;
    }
    cout << "all processes exited" << endl;
    cout << "-------------- scheduler done --------------" << endl;
}