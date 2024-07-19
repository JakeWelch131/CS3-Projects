// State transitions
// Jacob Welch
// 4/10/2024

#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process {
    public:
        Process();
        
        // behaviors
        void create();
        void exit();
        void dispatch();
        void suspend();
        void block();
        void unblock();
        string report();
        int getCounter() {return processCounter_;};

        void changeState(State* state) {state_=state;};

    private:
        State* state_;
        static int processCounter_;
        
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
        virtual int getCounter(Process* c) {return c->getCounter();};
        virtual string report() = 0;

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

// process member functions
Process::Process() {
            ++processCounter_;
            state_ = NewState::instance();
        }

int Process::processCounter_ = 0;
int main() {
    Process p1;
    cout << "process " << p1.getCounter() << " is " << p1.report() << endl;

    p1.create();
    cout << "process " << p1.getCounter() << " is " << p1.report() << endl;

    p1.dispatch();
    cout << "process " << p1.getCounter() << " is " << p1.report() << endl;

    p1.exit();
    cout << "process " << p1.getCounter() << " is " << p1.report() << endl;

    p1.dispatch();
    cout << "process " << p1.getCounter() << " is " << p1.report() << endl;

    Process p2;
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;

    p2.create();
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;

    p2.dispatch();
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;

    p2.block();
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;

    p2.unblock();
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;

    p2.dispatch();
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;

    p2.suspend();
    cout << "process " << p2.getCounter() << " is " << p2.report() << endl;
}