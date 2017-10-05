#ifndef TcpUnitTestH
#define TcpUnitTestH

/**
* @defgroup ����
* @author igame
* @date 2009-1-5
* @version 1.0
* revision
* -
* @{
*/

#include <ace/OS.h>
#include <ace/Task.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>
#include "TObject.h"
#include "Tcp.h"

namespace igame
{
	const int CLIENT_THREAD_NUM = 1; //< ģ��ͻ����߳���

	/**
	* @class TTcpUnitTest
	* @brief �򵥵ĵ�Ԫ����
	*/
	class TTcpUnitTest : public TObject // Ҫʹ���¼����͵ô�TObject�̳�
	{
		/**
		* @name �¼�������
		* @{
		*/
		void OnClientConnect(ACE_UINT32 ip, ACE_UINT16 port, TTcpHandler* handler);

		void OnClientDisconnect(ACE_UINT32 ip, ACE_UINT16 port);

		bool OnClientValidate(ACE_UINT32 ip, ACE_UINT16 port);

		void OnDataReceive(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size);

		void OnDataSendSucceeded(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size);

		void OnDataSendFailed(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size);
		/**
		* @}
		*/
	private:
		TTcp* m_Tcp; //< TCP����
		
		
	public:
		/// ctor
		TTcpUnitTest();

		/// ���Է���
		int test();
	};
} // namespace igame

/**
* @}
*/

#endif // TcpUnitTestH