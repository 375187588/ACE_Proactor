#ifndef TcpEmuClientThreadH
#define TcpEmuClientThreadH

#include <ace/OS.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>
#include <ace/Task.h>

namespace igame
{
	#define TCP_CLIENT_THREAD_SEND	0x777

	const int CLIENT_CONNECTION_NUM_OF_PER_THREAD = 1; //< �ͻ���ÿ���̵߳�������
	/**
	* @class TTcpClientThread
	* @brief TCP�ͻ��˲����߳�
	*/
	class TTcpClientThread : public ACE_Task<ACE_MT_SYNCH>
	{
		ACE_SOCK_Connector connector[CLIENT_CONNECTION_NUM_OF_PER_THREAD]; //< ������
		ACE_SOCK_Stream peerStream[CLIENT_CONNECTION_NUM_OF_PER_THREAD]; //< ������

	public:
		/// ctor
		~TTcpClientThread();
		
		/// ����
		int open();

		/// ֹͣ����
		int close();
	private:
		/// �̺߳���
		virtual int svc();
	};

} // namespace

#endif // TcpEmuClientThreadH