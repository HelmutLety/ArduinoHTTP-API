// ensure this library description is only included once
#ifndef Message_h
#define Message_h

#include "Dict.h"
#include "Context.h"

// library interface description
class Message
{
  // user-accessible "public" interface
  public:
    Message(arduino::Stream*);
    ~Message();

    Context ctx;
  // library-accessible "private" interface
  private:
    arduino::Stream*  input;
    void readMessage();
    void ReadEntryPoint(String);
};


#endif

