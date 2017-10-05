#ifndef TTcpH
#define TTcpH

/**
* @defgroup TTcp TCP��װ
* @author igame
* @date 2009-2-5
* @version 1.0
* revision
* -
* @{
*/

#include <ace/Thread_Mutex.h>
#include "TcpHandler.h"
#include "TcpNetThread.h"

#include <utility>
#include <hash_map>
using namespace std;
using namespace stdext;

namespace igame
{
	/**
	* @class TTcp
	* @brief TCP���պ��¼���������߳�
	*/
	class TTcp : public TObject, public ACE_Task<ACE_MT_SYNCH>
	{
	public:
		/**
		* @name �ض����¼�����
		* @see TTcpHandler
		* @{
		*/
		typedef TTcpHandler::TOnClientConnect TOnClientConnect;
		typedef TTcpHandler::TOnClientDisconnect TOnClientDisconnect;
		typedef TTcpHandler::TOnClientValidate TOnClientValidate;
		typedef TTcpHandler::TOnDataReceive TOnDataReceive;
		typedef TTcpHandler::TOnDataSendSucceeded TOnDataSendSucceeded;
		typedef TTcpHandler::TOnDataSendFailed TOnDataSendFailed;
		/**
		* @}
		*/
	private:
		/**
		* @name ��Ա����
		* @{
		*/
		ACE_Recursive_Thread_Mutex m_Lock; //< �߳���
		hash_map<unsigned __int64, TTcpHandler *> m_AddrMap; //< ��ַ/���ӳ��
		TTcpNetThread* m_TcpNetThd;
		/**
		* @}
		*/
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

	public:
		/// ctor
		TTcp();

		/// dtor
		~TTcp();

		/// ����
		void open();

		/// ֹͣ
		void close();
		
		/// ��������
		int send(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* buf, unsigned short len);

	private:
		/// �̺߳���
		virtual int svc();

	private:
		/**
		* @name TTcpNetThread �¼�������
		* �����¼�ԭ�͵Ķ��壬��ο� @see TTcpHandler
		* @{
		*/
		void tcpNetThread_OnClientConnect(ACE_UINT32 ip, ACE_UINT16 port, TTcpHandler* handler);

		void tcpNetThread_OnClientDisconnect(ACE_UINT32 ip, ACE_UINT16 port);

		void tcpNetThread_OnDataReceive(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size);

		void tcpNetThread_OnDataSendSucceeded(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size);

		void tcpNetThread_OnDataSendFailed(ACE_UINT32 ip, ACE_UINT16 port, unsigned int seq, const char* data, unsigned short size);
		/**
		* @}
		*/
	}; // class TTcp


} // namespace

/**
* @}
*/
#endif // TTcpH