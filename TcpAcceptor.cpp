#include "TCPAcceptor.h"

namespace igame
{
	int TTcpAcceptor::validate_connection (const ACE_Asynch_Accept::Result& result,
									   const ACE_INET_Addr &remote,
									   const ACE_INET_Addr& local)
	{
		if (m_OnClientValidate.valid())
			// ���Ｄ��TOnClientValidate�¼�
			return m_OnClientValidate(remote.get_ip_address(), remote.get_port_number()) ? 0 : -1;
		else
			return 0; // Ĭ����������
	}

	TTcpHandler* TTcpAcceptor::make_handler(void)
	{
		TTcpHandler* handler = 0;

		ACE_NEW_RETURN (handler, TTcpHandler(), 0);

		// �����¼����
		handler->setOnClientConnect(m_OnClientConnect);
		handler->setOnClientDisconnect(m_OnClientDisconnect);
		handler->setOnDataReceive(m_OnDataReceive);
		handler->setOnDataSendSucceeded(m_OnDataSendSucceeded);
		handler->setOnDataSendFailed(m_OnDataSendFailed);

		return handler;
	}
} // namespace igame