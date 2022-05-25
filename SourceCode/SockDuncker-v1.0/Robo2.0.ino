#include <Braccio.h>
class _State {
  public: byte baseAngle;
  public: byte shoulderAngle;
  public: byte elbowAngle;
  public: byte wristVerAngle;
  public: byte wristRotAngle;
  public: byte gripAngle;
  public: byte velocity;

  public: _State() {
    this->baseAngle = 90;
    this->elbowAngle = 90;
    this->wristVerAngle = 90;
    this->wristRotAngle = 90;
    this->shoulderAngle = 90;
    this->gripAngle = 73;
    this->velocity = 20;
  }

  public: _State(byte _baseAngle, byte _shoulderAngle, byte _elbowAngle, byte _wristVerAngle, byte _wristRotAngle, byte _gripAngle, byte _velocity) {
    this->baseAngle = _baseAngle;
    this->shoulderAngle = _shoulderAngle;
    this->elbowAngle = _elbowAngle;
    this->wristVerAngle = _wristVerAngle;
    this->gripAngle = _gripAngle;
    this->velocity = _velocity;
  }

  void Run(){
    Braccio.ServoMovement(velocity, baseAngle, shoulderAngle, elbowAngle, wristVerAngle, wristRotAngle, gripAngle);
  }
  
  public:void Save(byte _baseAngle, byte _shoulderAngle, byte _elbowAngle, byte _wristVerAngle, byte _wristRotAngle, byte _gripAngle, byte _velocity ) {
    baseAngle = _baseAngle;
    shoulderAngle = _shoulderAngle;
    elbowAngle = _elbowAngle;
    wristVerAngle = _wristVerAngle;
    gripAngle = _gripAngle;
    velocity = _velocity;
  }

  public: void Reset() {
    this->baseAngle = 90;
    this->elbowAngle = 90;
    this->wristVerAngle = 90;
    this->wristRotAngle = 90;
    this->shoulderAngle = 90;
    this->gripAngle = 73;
    this->velocity = 20;
  }
 /* ~State() {
    //Wow, useless 
  }*/
};
