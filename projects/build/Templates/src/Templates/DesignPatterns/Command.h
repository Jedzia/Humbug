#ifndef TEMPLATES_DESIGNPATTERNS_COMMAND_H
#define TEMPLATES_DESIGNPATTERNS_COMMAND_H


#include "../global.h"
//
#include <string>

namespace templates {

namespace designpatterns {

class DocumentCommand;
class ToolbarButton;
class SaveCommand;
class OpenCommand;
class Document;
class Client;

//! The Abstract Command.
/// Or interface to the execute command.
class PLATFORM_DECL DocumentCommand {
  public:
    virtual void execute() = 0;

    virtual ~DocumentCommand();

};
//! The Invoker.
class PLATFORM_DECL ToolbarButton {
  private:
    DocumentCommand * m_clickedCommand;


  public:
    ToolbarButton(DocumentCommand * clickedCommand);

    //! Is executed, when the ToolbarButton is pressed.
    void clicked();

};
//! A Concrete Command.
class PLATFORM_DECL OpenCommand : public DocumentCommand {
  public:
    virtual void execute();


  private:
    int state;

    Document& doc;


  public:
    OpenCommand(Document & document);

};
//! This one closes all documents,
/// Therefore it needs a reference to the client.
class PLATFORM_DECL CloseAllCommand : public DocumentCommand {
  public:
    virtual void execute();


  private:
    unsigned char state;


  public:
    CloseAllCommand(Client * theClient);


  private:
    Client * client;

};
class PLATFORM_DECL SaveCommand : public DocumentCommand {
  public:
    virtual void execute();


  private:
    bool state;


  public:
    SaveCommand(Document & document);


  private:
    Document& doc;

};
//! The Receiver.
class PLATFORM_DECL Document {
  public:
    //! An Action
    void open();

    //! An Action
    void close();

    //! An Action
    void save(const std::string & filename);

};
class PLATFORM_DECL Client {
  private:
    Document * doc;


  public:
    //! Main execution method.
    /// Set up the commands and invoker.
    int main(int argc, char ** argv);

    void closeAll();

};

} // namespace templates::designpatterns

} // namespace templates
#endif
