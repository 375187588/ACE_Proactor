#include <ace/INET_Addr.h>
#include <ace/Proactor.h>

#include <iostream>
using namespace std;

#include <conio.h>
#include "TcpUnitTest.h"
#include "TcpEmuClientThread.h"

namespace igame
{
	TTcpUnitTest::TTcpUnitTest()
	{
		ACE_NEW_NORETURN(m_Tcp, TTcp()); // ����TCP����
	}

	int TTcpUnitTest::test()
	{
		if (!m_Tcp)
			return -1;

		// �����¼����
		m_Tcp->setOnClientConnect(EVENT(TTcpHandler::TOnClientConnect, TTcpUnitTest, this, OnClientConnect));
		m_Tcp->setOnClientDisconnect(EVENT(TTcpHandler::TOnClientDisconnect, TTcpUnitTest, this, OnClientDisconnect));
		m_Tcp->setOnClientValidate(EVENT(TTcpHandler::TOnClientValidate, TTcpUnitTest, this, OnClientValidate));
		m_Tcp->setOnDataReceive(EVENT(TTcpHandler::TOnDataReceive, TTcpUnitTest, this, OnDataReceive));
		m_Tcp->setOnDataSendSucceeded(EVENT(TTcpHandler::TOnDataSendSucceeded, TTcpUnitTest, this, OnDataSendSucceeded));
		m_Tcp->setOnDataSendFailed(EVENT(TTcpHandler::TOnDataSendFailed, TTcpUnitTest, this, OnDataSendFailed));

		m_Tcp->open();
		
		// ��ʱ5�룬�ȴ�Proactor�߳�����
		ACE_DEBUG((LM_INFO, ACE_TEXT("Waiting...\n")));

		Sleep(1000);

		ACE_DEBUG((LM_INFO, ACE_TEXT("."))); // ����ʱ��

		Sleep(1000);

		ACE_DEBUG((LM_INFO, ACE_TEXT(".")));

		Sleep(1000);

		ACE_DEBUG((LM_INFO, ACE_TEXT(".")));

		Sleep(1000);

		ACE_DEBUG((LM_INFO, ACE_TEXT(".\n")));

		// �ͻ��˿�ʼ����
		
		TTcpClientThread clientThd[CLIENT_THREAD_NUM];

		// ���пͻ����߳�
		for(int i = 0; i < CLIENT_THREAD_NUM; i++)
		{
			clientThd[i].open();
		}

		
		// �ȴ�����
		while(!_kbhit())
		{
			for(int i = 0; i < CLIENT_THREAD_NUM; i++)
			{
				ACE_Message_Block* clientDataMb = 0;

				ACE_NEW_RETURN(clientDataMb, ACE_Message_Block(0, TCP_CLIENT_THREAD_SEND), 0);

				clientThd[i].putq(clientDataMb);
			}

			::Sleep(1000);
		}

		m_Tcp->close();
		
		delete m_Tcp;

		// ����
		for(int i = 0; i < CLIENT_THREAD_NUM; i++)
		{
			clientThd[i].close();
			
		}

		return 0;
	}

	void TTcpUnitTest::OnClientConnect(ACE_UINT32 ip, ACE_UINT16 port, TTcpHandler* handler)
	{
		ACE_TCHAR addrStr[128];

		ACE_INET_Addr(port, ip).addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));

		ACE_DEBUG((LM_INFO, ACE_TEXT("Client connected from %s\n"), addrStr));
	}

	void TTcpUnitTest::OnClientDisconnect(ACE_UINT32 ip, ACE_UINT16 port)
	{
		ACE_TCHAR addrStr[128];

		ACE_INET_Addr(port, ip).addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));


		ACE_DEBUG((LM_INFO, ACE_TEXT("Client disconnected from %s\n"), addrStr));
	}

	bool TTcpUnitTest::OnClientValidate(ACE_UINT32 ip, ACE_UINT16 port)
	{
		ACE_TCHAR addrStr[128];

		ACE_INET_Addr(port, ip).addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));

		ACE_DEBUG((LM_INFO, ACE_TEXT("Client validate: %s\n"), addrStr));

		return true;
	}

	void TTcpUnitTest::OnDataReceive(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size)
	{
		ACE_TCHAR addrStr[128];

		ACE_INET_Addr(port, ip).addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));

		ACE_DEBUG((LM_INFO, ACE_TEXT("Receive from:%s seq=%i len=%i data=%s\n"), addrStr, seq, size, data));

		m_Tcp->send(ip, port, seq, data, size);
	}

	void TTcpUnitTest::OnDataSendSucceeded(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size)
	{
		ACE_TCHAR addrStr[128];

		ACE_INET_Addr(port, ip).addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));

		ACE_DEBUG((LM_INFO, ACE_TEXT("Succeeded to send to :%s seq=%i len=%i data=%s\n"), addrStr, seq, size, data));
	}

	void TTcpUnitTest::OnDataSendFailed(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size)
	{
		ACE_TCHAR addrStr[128];

		ACE_INET_Addr(port, ip).addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));

		ACE_DEBUG((LM_INFO, ACE_TEXT("Failed to send to :%s seq=%i len=%i data=%s\n"), addrStr, seq, size, data));
	}
} // namespace igame