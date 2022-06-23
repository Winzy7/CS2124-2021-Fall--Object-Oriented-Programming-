/*
  rec11.cpp
  Jiezhi Winston Zuo-yu
 */

#include <iostream>
#include <vector>
using namespace std;
class Instrument {
public:
    virtual void play() const = 0;
    virtual void makeSound() const {
        cout << "To make a sound... ";
    }
private:
};

class Brass: public Instrument{
public:
    Brass(const int size) : mouthpiece(size) {};
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
private:
    int mouthpiece;
};
class Trombone: public Brass{
public:
    Trombone (const int size) : Brass(size) {};
    void play() const {
        cout << "Blat";
    }
};
class Trumpet: public Brass{
public:
    Trumpet (const int size) : Brass(size) {};
    void play() const {
        cout << "Toot";
    }
};

class String: public Instrument{
public:
    String(const unsigned pitch) : pitch(pitch) {};
    void makeSound() const {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Cello: public String {
public:
    Cello(const unsigned pitch) : String(pitch) {};
    void play() const {
        cout << "Squawk";
    }
};

class Violin: public String {
public:
    Violin(const unsigned pitch) : String(pitch) {};
    void play() const {
        cout << "Screech";
    }
};

class Percussion: public Instrument{
public:
    void makeSound() const{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};
class Drum : public Percussion {
    void play() const {
        cout << "Boom";
    }
};
class Cymbal: public Percussion {
    void play() const {
        cout << "Crash";
    }
};

class MILL {
public:
    Instrument* loanOut() {
        for (size_t i = 0; i < instPtrs.size(); ++i) {
            if (instPtrs[i] != nullptr) {
                Instrument *tempPtr = instPtrs[i];
                instPtrs[i] = nullptr;
                return tempPtr;
            }
        }
        return nullptr;
    }
    bool receiveInstr(Instrument& inst) {
        for (Instrument* instPtr : instPtrs) {
            if (instPtr == &inst) {
                return false;
            }
        }
        for (size_t i = 0; i < instPtrs.size(); ++i) {
            if (instPtrs[i] == nullptr) {
                instPtrs[i] = &inst;
                inst.makeSound();
                return true;
            }
        }
        inst.makeSound();
        instPtrs.push_back(&inst);
        return true;
    }
    void dailyTestPlay() const {
        for (Instrument* instPtr : instPtrs) {
            if (instPtr != nullptr) {
                instPtr->makeSound();
            }
        }
    }
private:
    vector<Instrument*> instPtrs;
};
class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }
    void play() const {
        if (instr != nullptr) {
            instr->play();
        }
    }
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};

class Orch{
public:
    bool addPlayer(Musician& player) {
        for (Musician* musPtr : playerPtrs) {
            if (musPtr == &player) {
                return false;
            }
        }
        for (size_t i = 0; i < playerPtrs.size(); ++i) {
            if (playerPtrs[i] == nullptr) {
                playerPtrs[i] = &player;
                return true;
            }
        }
        playerPtrs.push_back(&player);
        return false;
    }
    void play() const {
        for (Musician* musPtr : playerPtrs) {
            if (musPtr != nullptr) {
                musPtr->play();
            }
        }
        cout << endl;
    }
private:
    vector<Musician*> playerPtrs;
};


int main() {

    //
    // PART ONE
    //
//    cout << "P A R T  O N E\n";
//
//    cout << "Define some instruments ----------------------------------------\n";
//     Drum drum;
//     Cello cello(673);
//     Cymbal cymbal;
//     Trombone tbone(4);
//     Trumpet trpt(12) ;
//     Violin violin(567) ;
//
//    // use the debugger to look at the mill
//    cout << "Define the MILL ------------------------------------------------\n";
//    MILL mill;
//
//    cout << "Put the instruments into the MILL ------------------------------\n";
//     mill.receiveInstr(trpt);
//     mill.receiveInstr(violin);
//     mill.receiveInstr(tbone);
//     mill.receiveInstr(drum);
//     mill.receiveInstr(cello);
//     mill.receiveInstr(cymbal);
//
//    cout << "Daily test -----------------------------------------------------\n"
//         << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//
//    cout << "Define some Musicians-------------------------------------------\n";
//     Musician harpo;
//     Musician groucho;
//
//     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
//     groucho.testPlay();
//     cout << endl;
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//
//     cout << endl << endl;
//
//     groucho.testPlay();
//     cout << endl;
//     mill.receiveInstr(*groucho.giveBackInstr());
//     harpo.acceptInstr(mill.loanOut());
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     harpo.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//
//     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
//
//     // fifth
//     mill.receiveInstr(*groucho.giveBackInstr());
//     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
//     mill.receiveInstr(*harpo.giveBackInstr());
//
//
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//
//     cout << endl;


    //
    // PART TWO
    //


    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

}
