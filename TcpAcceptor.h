#ifndef TTCPAcceptorH
#define TTCPAcceptorH

/**
* @defgroup TcpAcceptor
* @author igame
* @date 2009-2-5
* @version 1.0
* revision
* -
* @{
*/

#include <ace/Asynch_Acceptor.h>
#include "TcpHandler.h"

namespace igame
{
	/**
	* @class TTcpAcceptor
	* @brief TCP������
	* @see ACE_Asynch_Acceptor
	* @see TTcpHandler
	*/
	class TTcpAcceptor : public ACE_Asynch_Acceptor<TTcpHandler>
	{
	public:
		/**
		* @name TCP�¼����
		* @see TTcpHandler
		* @{
		*/
		DECL_PROP(TTcpHandler::TOnClientConnect, OnClientConnect)
		DECL_PROP(TTcpHandler::TOnClientDisconnect, OnClientDisconnect)
		DECL_PROP(TTcpHandler::TOnClientValidate, OnClientValidate)
		DECL_PROP(TTcpHandler::TOnDataReceive, OnDataReceive)
		DECL_PROP(TTcpHandler::TOnDataSendSucceeded, OnDataSendSucceeded)
		DECL_PROP(TTcpHandler::TOnDataSendFailed, OnDataSendFailed)
		/**
		* @}
		*/
	protected:
		/**
		* @brief ������֤
		* @note ���� OnClientValidate �¼� @see TOnClientValidate
		* @see ACE_Asynch_Acceptor
		*/
		virtual int validate_connection (const ACE_Asynch_Accept::Result& result,
								   const ACE_INET_Addr &remote,
								   const ACE_INET_Addr& local);
		/**
		* @brief �������Ӿ���¼�
		* @see ACE_Asynch_Acceptor
		*/
		virtual TTcpHandler* make_handler(void);
	}; // class TTcpAcceptor
} // namespace igame

/**
* @}
*/
#endif // TTCPAcceptorH