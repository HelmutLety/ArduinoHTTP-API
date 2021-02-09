// include core Wiring API
#include "Arduino.h"
// #include "Stream.h"
// include this library's description file
#include "Message.h"
#include "Dict.h"
// #include "Context.h"


// include description files for other libraries used (if any)
#include "HardwareSerial.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Message::Message(arduino::Stream* s)
{
  ctx = Context(); 
  input = s;
  readMessage();

}
Message::~Message()
{
}

void Message::readMessage()
{
  String currentLine = ""; 
  bool stop= false;
  int lines = 0;

  ctx.headers = Dict<String>();
  while(!stop)
  {
    char c = input->read();

     if (c == '\n') 
        {                            
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) 
          {
            break;
          }
          else 
          {      
            // if you got a newline, then clear currentLine:

            if (lines == 0) 
            {
              ReadEntryPoint(currentLine);
            } else {
              ctx.headers.add(currentLine.substring(0,currentLine.indexOf(":")),currentLine.substring(currentLine.indexOf(":")+2));
            }

            lines++;
            currentLine = "";
          }
        }
    else if (c != '\r') 
       {    
         // if you got anything else but a carriage return character,
         currentLine += c;      // add it to the end of the currentLine
       }

  }
}

void Message::ReadEntryPoint(String line)
{
  String argsline = "";
  String newArgs = "";
  ctx.method = line.substring(0, line.indexOf(" "));
  ctx.endpoint = line.substring(line.indexOf(" ")+2,line.lastIndexOf(" "));
  ctx.args = Dict<String>();

  if (ctx.endpoint.indexOf("?") != -1)
  {
    argsline = ctx.endpoint.substring(ctx.endpoint.indexOf("?")+1);
    ctx.endpoint = ctx.endpoint.substring(0, ctx.endpoint.indexOf("?"));
  }
  while (!argsline.equals(""))
  {
    newArgs = argsline.substring(0, argsline.indexOf("&"));
    if (newArgs.indexOf("=") != -1)
    {
      ctx.args.add(newArgs.substring(0,newArgs.indexOf("=")),newArgs.substring(newArgs.indexOf("=")+1));
    } else {
      ctx.args.add(newArgs, "");
    }
    if (argsline.indexOf("&") != -1)
    {
      argsline = argsline.substring(argsline.indexOf("&")+1);

      
    } else {
      argsline = "";
    }
  }


}
