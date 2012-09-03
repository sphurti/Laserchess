#ifndef GAMEMOVE_H
#define GAMEMOVE_H

class GameMove {
  public:
    GameMove() {}
    // Base class destructor needs to be virtual. This prevents the 
    // base class pointer pointing to derived class object from calling
    // base class destructor. Also pure virtual class prevents instanstiation 
    // of the object of the class.
    virtual ~GameMove() {}
    virtual GameMove* clone() const = 0;
    virtual void printMove() const = 0;
};

#endif // GAMEMOVE_H
