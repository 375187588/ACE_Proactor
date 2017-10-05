#include <ace/Proactor.h>
#include "TCPNetThread.h"

namespace igame
{
	int TTcpNetThread::open() { return this->activate(); }

	int TTcpNetThread::close()
	{
		ACE_Proactor::instance()->proactor_end_event_loop(); // ��ֹACE_Proactorѭ��

		this->wait(); // �ȴ������ֳ�

		return 0;
	}
	
	int TTcpNetThread::svc()
	{
		ACE_INET_Addr listenAddr(DEF_LISTENING_PORT); // Ĭ�ϼ�����ַ
		TTcpAcceptor tcpAcceptor; // ������

		// �����¼�
		tcpAcceptor.setOnClientConnect(m_OnClientConnect);
		tcpAcceptor.setOnClientDisconnect(m_OnClientDisconnect);
		tcpAcceptor.setOnClientValidate(m_OnClientValidate);
		tcpAcceptor.setOnDataReceive(m_OnDataReceive);
		tcpAcceptor.setOnDataSendFailed(m_OnDataSendFailed);
		tcpAcceptor.setOnDataSendSucceeded(m_OnDataSendSucceeded);
		
		// �ݳ���ʼ
		if (tcpAcceptor.open(listenAddr, 0, 1, 5, 1, 0, 0) != 0)
			ACE_ERROR_RETURN((LM_ERROR, ACE_TEXT("%p\n"), ACE_TEXT("failed to open TcpAcceptor errno=%i\n"), errno), -1);

		// Proactor���¼�ѭ����ʼ
		ACE_Proactor::instance()->proactor_run_event_loop();

		ACE_DEBUG((LM_DEBUG, ACE_TEXT("Network fin\n")));

		return 0;
	}
} // namespace igame