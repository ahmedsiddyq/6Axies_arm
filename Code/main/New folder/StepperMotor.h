#include <AccelStepper.h>

class StepperMotor
{
  private:
    AccelStepper stepper;

    int stepPin;
    int dirPin;

    int microstep = 1;

    float maxSpeed = 1000;
    float acceleration = 500;

  public:

    StepperMotor(int step_pin, int dir_pin)
      : stepper(AccelStepper::DRIVER, step_pin, dir_pin)
    {
      stepPin = step_pin;
      dirPin = dir_pin;
    }

    void begin()
    {
      stepper.setMaxSpeed(maxSpeed);
      stepper.setAcceleration(acceleration);
    }

 
    void setMaxSpeed(float speed)
    {
      maxSpeed = speed;
      stepper.setMaxSpeed(speed);
    }

    void setAcceleration(float accel)
    {
      acceleration = accel;
      stepper.setAcceleration(accel);
    }

    void setMicrostep(int ms)
    {
      microstep = ms;
    }

    int getMicrostep()
    {
      return microstep;
    }

    void moveSteps(long steps)
    {
      stepper.move(steps * microstep);
    }

    void moveTo(long position)
    {
      stepper.moveTo(position * microstep);
    }

    void setSpeed(float speed)
    {
      stepper.setSpeed(speed * microstep);
    }

    void run()
    {
      stepper.run();
    }

    void runSpeed()
    {
      stepper.runSpeed();
    }

    void stop()
    {
      stepper.stop();
    }

    long getPosition()
    {
      return stepper.currentPosition() / microstep;
    }

    void setPosition(long pos)
    {
      stepper.setCurrentPosition(pos * microstep);
    }

    bool isRunning()
    {
      return stepper.distanceToGo() != 0;
    }

    long distanceToGo()
    {
      return stepper.distanceToGo() / microstep;
    }

    void home(bool switchState, int homingSpeed = -400)
    {
      stepper.setSpeed(homingSpeed);

      while (!switchState)
      {
        stepper.runSpeed();
      }

      stepper.setCurrentPosition(0);
    }
};