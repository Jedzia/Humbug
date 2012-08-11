
#include "../stdafx.h"
//
#include "Command.h"

//
#include <build/cmake/include/debug.h>
namespace templates {

namespace designpatterns {

DocumentCommand::~DocumentCommand() {
}

ToolbarButton::ToolbarButton(DocumentCommand * clickedCommand) 
: m_clickedCommand( clickedCommand ) {
}

//! Is executed, when the ToolbarButton is pressed.
void ToolbarButton::clicked() {
  m_clickedCommand->execute();
}

void OpenCommand::execute() {
  doc.open();
}

OpenCommand::OpenCommand(Document & document)
:doc(document) {
}

void CloseAllCommand::execute() {
  client->closeAll();
}

CloseAllCommand::CloseAllCommand(Client * theClient) 
: client(theClient) {
}

void SaveCommand::execute() {
  // open a file browser window to specify a save-file.
  std::string filename("example.txt");
  doc.save(filename);
}

SaveCommand::SaveCommand(Document & document) 
  : doc(document) {
}

//! An Action
void Document::open() {
  std::cout << "Opening Document" << std::endl;
}

//! An Action
void Document::close() {
  std::cout << "Closing Document" << std::endl;
}

//! An Action
void Document::save(const std::string & filename) {
  std::cout << "Saving Document" << std::endl;
}

//! Main execution method.
/// Set up the commands and invoker.
int Client::main(int argc, char ** argv) {
  
  // Create all the instances.
  Document *doc = new Document();
  
  // Hmmm... use pointer or reference?!?
  DocumentCommand *cmdOpen = new OpenCommand(*doc);
  DocumentCommand *cmdCloseAll = new CloseAllCommand(this);
  DocumentCommand *cmdSave = new SaveCommand(*doc);
  
  ToolbarButton *bnOpen = new ToolbarButton(cmdOpen);
  ToolbarButton *bnCloseAll = new ToolbarButton(cmdCloseAll);
  ToolbarButton *bnSave = new ToolbarButton(cmdSave);
  
  // Simulate action
  bnOpen->clicked();
  bnSave->clicked();
  bnCloseAll->clicked();
  
  // Tidy up.
  delete bnSave;
  delete bnCloseAll;
  delete bnOpen;
  delete cmdSave;
  delete cmdCloseAll;
  delete cmdOpen;
  
  return 0;
}

void Client::closeAll() {
  // close_all_documents_here();
}


} // namespace templates::designpatterns

} // namespace templates
