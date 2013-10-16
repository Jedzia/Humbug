//include guards
#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

namespace gui {

//message id
typedef unsigned int MSGID;

//message parameters
typedef void* MSGPARM;

/*
	==CMessageHandler==
	Message notification class.
	Base class of all other core components.
	Provides a parent child relationship to derived objects.
	Hungarian: mhX, *pmhX
*/
class CMessageHandler
{
private:
	//parent message handler
	CMessageHandler* m_pmhParent;

	//next message id(static)
	static MSGID s_NextMSGID;
public:
	//constructor
	CMessageHandler(CMessageHandler* pmhParent);

	//destructor
	virtual ~CMessageHandler();

	//set parent
	void SetParent(CMessageHandler* pmhNewParent);

	//get parent
	CMessageHandler* GetParent();

	//has parent?
	bool HasParent();

	//send message
	bool SendMessageQ(MSGID MsgID,MSGPARM Parm1=NULL,MSGPARM Parm2=NULL,MSGPARM Parm3=NULL,MSGPARM Parm4=NULL);

	//process message(virtual)
	virtual bool OnMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4);

	//get next message id(static)
	static MSGID GetNextMSGID();

	//msgid: add child(static): Parm1=Parent, Parm2=Child
	static MSGID MSGID_AddChild;

	//msgid: remove child(static): Parm1=Parent, Parm2=Child
	static MSGID MSGID_RemoveChild;

	//add child handler
	virtual void OnAddChild(CMessageHandler* pmhChild);

	//remove child handler
	virtual void OnRemoveChild(CMessageHandler* pmhChild);
};

} // namespace gui

#endif //#ifndef __MESSAGEHANDLER_H__
