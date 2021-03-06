#include "IqRouter.h"
#include "MsgTypeIqProcessHandler.h"
#include  "JID.h"
#include  <string>
#include  <sstream>
#include <proxy/ProxyRegister.h>
#include <proxy/MucServiceProxy.h>
#include <proxy/RouterProxy.h>
//#include <proxy/FaceBookServiceProxy.h>
#include  <iostream>
#include "talk/TalkServer.h"
#include "constant/MessageType.h"

using namespace mtalk::talk;
using namespace mtalk::constant;
using namespace std;
using namespace mtalk::proxy;

namespace mtalk{
	namespace xmpp{
		IqRouter::IqRouter():
			msgTypeHandlerPtr_(new MsgTypeIqProcessHandler()){
			}
		ProcessResult IqRouter::route(mtalk::talk::SessionPtr sessionPtr, const pugi::xml_node& node){
			std::string toStr = node.attribute("to").value();
			std::string fromStr = node.attribute("from").value();
			JID to(toStr);
			JID from(fromStr);
			if(to.getEndpoint() == "muc.m.renren.com"){
				long fromid = from.getUserId();
				string sessionid = sessionPtr->getSessionId();								
				stringstream ss;
				node.print(ss,"\t",pugi::format_raw);
				string message=ss.str();
													 
				bool forward = MY_INSTANCE(ProxyRegister).getProxy<MucServiceProxy>("mucProxy")->forwardIq(fromid,sessionid,message);	//推给muc服务器
				// 如果forward成功，返回ok，否则返回error
				if(forward){
					ProcessResult result(ProcessResult::OK, "<success/>");
					return result;
				}else {
					ProcessResult result(ProcessResult::ERROR, "forward muc fail");
					return result;
				}

			}

			//单聊信息
			if(to.getEndpoint() == "talk.sixin.com" || to.getEndpoint() == "renren.sixin.com" || to.getEndpoint() == "talk.m.renren.com" ||to.getEndpoint() ==""){
					if(node.child("msgType")){
							return msgTypeHandlerPtr_->handler(sessionPtr, node);
					}

					stringstream os;
					node.print(os,"\t",pugi::format_raw);
					MY_INSTANCE(TalkServer).remotePush(from.getUserId(), to.getUserId(), os.str(), MessageType::ENTITY);

					ProcessResult result;
					return result;

			} else {
				long fromid = from.getUserId();
				long toid = to.getUserId();
				//string sessionid = sessionPtr->getSessionId();											
				stringstream ss;
				node.print(ss,"\t",pugi::format_raw);
				string message=ss.str();
				string router=to.getRouter();
				LOG_DEBUG("IqRoute::route  forward "<< router<<"iq msg = "<<message);	

				router.append("ServiceProxy");
				ProcessResult result;									 

				bool forward = 0;

				if(MY_INSTANCE(ProxyRegister).getProxy<RouterServiceProxy>(router).get()!=0){

					LOG_DEBUG("IqRoute::get RouterServiceProxy and  forward"<<router<<" iq msg = "<<message);	

					forward = MY_INSTANCE(ProxyRegister).getProxy<RouterServiceProxy>(router)->forwardIq(fromid,toid,message);

				}
			 
				// 如果forward成功，返回ok，否则返回error
					string id = node.attribute("id").value();
					string type=node.attribute("type").value();
				if(forward){
					result.setCode(ProcessResult::OK);
					stringstream ss;
					ss<<"<success id='";
					ss<<id;
					ss << "' from='";
					ss << from.toString();
					ss << "' to='";
					ss << to.toString();
					ss<<"'  type='";
					ss<<type;
					ss<<"'/>";
					result.setMsg(ss.str());
					return result;
				}else {
					ProcessResult result(ProcessResult::ERROR);
					stringstream s;
					s<<"<error id='";
					s<<id;
					s<<"'>fail to ";
					s<<to.getEndpoint();
					s<<" error</error>";
					result.setMsg(s.str());
					result.setMsg("<error>talk internal error</error>");
					return result;
				}

			}

	}
};
};
