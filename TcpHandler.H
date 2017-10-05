#ifndef TcpHandlerH
#define TcpHandlerH

/**
* @defgroup TcpHandler
* @author igame
* @date 2009-2-5
* @version 1.0
* revision
* -
* @{
*/
#include <ace/OS.h>
#include <ace/SOCK_Stream.h>
#include <ace/INET_Addr.h>
#include <ace/Asynch_IO.h>
#include <ace/Message_Block.h>
#include <ace/Recursive_Thread_Mutex.h>
#include "TCPDef.h"
#include "TObject.h"
#include "TEvent.h"

namespace igame
{
	/**
	* @class TTcpHandler
	* @brief Tcp���Ӿ��
	*/
	class TTcpHandler : public ACE_Service_Handler
	{
	public:
		/**
		* @brief �ͻ��������¼����Ͷ���
		* @param [in] ACE_UINT32 �ͻ��˵�ַ
		* @param [in] ACE_UINT16 �ͻ��˶˿�
		* @param [in] TTcpHandler* ���Ӿ��
		*/
		typedef TEvent<void, ACE_UINT32, ACE_UINT16, TTcpHandler *> TOnClientConnect;

		/**
		* @brief �ͻ��˶Ͽ������¼����Ͷ���
		* @param [in] ACE_UINT32 �ͻ��˵�ַ
		* @param [in] ACE_UINT16 �ͻ��˶˿�
		*/
		typedef TEvent<void, ACE_UINT32, ACE_UINT16> TOnClientDisconnect;

		/**
		* @brief �ͻ���������֤�¼�
		* @param [in] ACE_UINT32 �ͻ��˵�ַ
		* @param [in] ACE_UINT16 �ͻ��˶˿�
		* @return bool
		* - true ��֤ͨ��
		* - false ��֤ʧ��
		*/
		typedef TEvent<bool, ACE_UINT32, ACE_UINT16> TOnClientValidate;

		/**
		* @brief ���յ��ͻ��������¼����Ͷ���
		* @param [in] ACE_UINT32 �ͻ��˵�ַ
		* @param [in] ACE_UINT16 �ͻ��˶˿�
		* @param [in] unsigned int ���ݰ����к�
		* @param [in] const char* ��������ָ��
		* @param [in] size_t ���ݳ���
		*/
		typedef TEvent<void, ACE_UINT32, ACE_UINT16, unsigned int, const char*, unsigned short> TOnDataReceive;
		
		/**
		* @brief �ɹ����Ϳͻ��������¼����Ͷ���
		* @param [in] ACE_UINT32 �ͻ��˵�ַ
		* @param [in] ACE_UINT16 �ͻ��˶˿�
		* @param [in] unsigned int ���ݰ����к�
		* @param [in] const char* ��������ָ��
		* @param [in] size_t ���ݳ���
		*/
		typedef TEvent<void, ACE_UINT32, ACE_UINT16, unsigned int, const char*, unsigned short> TOnDataSendSucceeded;
		
		/**
		* @brief ʧ�ܷ��Ϳͻ��������¼����Ͷ���
		* @param [in] ACE_UINT32 �ͻ��˵�ַ
		* @param [in] ACE_UINT16 �ͻ��˶˿�
		* @param [in] unsigned int ���ݰ����к�
		* @param [in] const char* ��������ָ��
		* @param [in] size_t ���ݳ���
		*/
		typedef TEvent<void, ACE_UINT32, ACE_UINT16, unsigned int, const char*, unsigned short> TOnDataSendFailed;


	private:
		ACE_Asynch_Read_Stream m_Reader; //< �첽��������
		ACE_Asynch_Write_Stream m_Writer; //< �첽д������
		ACE_Message_Block* m_CurDataMB; //< ��ǰ��ȡ����
		ACE_INET_Addr m_ClientAddr; //< �ͻ��˵�ַ

	public:
		/**
		* @name �¼����
		* @{
		*/
		DECL_PROP(TOnClientConnect, OnClientConnect) //< �ͻ��������¼����
		DECL_PROP(TOnClientDisconnect, OnClientDisconnect) //< �ͻ��˶Ͽ��¼����
		DECL_PROP(TOnDataReceive, OnDataReceive) //< ���յ����ݵ��¼����
		DECL_PROP(TOnDataSendSucceeded, OnDataSendSucceeded) //< �ɹ��������ݵ��¼����
		DECL_PROP(TOnDataSendFailed, OnDataSendFailed) //< ��������ʧ�ܵ��¼����
		/**
		* @}
		*/
	public:
		/// ctor
		TTcpHandler();
		
		/// dtor
		~TTcpHandler();
		
		/**
		* @brief ��������
		* @param [in] unsigned int ���ݰ����к�
		* @param [in] const char* Ҫ���͵���������ָ��
		* @param [in] size_t Ҫ���͵����ݳ���
		* @return int
		* - 0 �ɹ�
		* - 1 ʧ��
		*/
		int send(unsigned int seq, const char* data, unsigned short size);
		
		/**
		* @brief �򿪾��
		* @see ACE_Service_Handler
		*/
		virtual void open(ACE_HANDLE h, ACE_Message_Block& mb);
	
		/**
		* @brief ��ȡ��ַ
		* @see ACE_Service_Handler
		*/
		virtual void addresses (const ACE_INET_Addr &remote_address,
							  const ACE_INET_Addr &local_address);
		
		/**
		* @brief ��ȡ�������¼�
		* @see ACE_Service_Handler
		*/
		virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result& result);

		/**
		* @brief д���������¼�
		* @see ACE_Service_Handler
		*/
		virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result& result);

		/**
		* @brief ��ʼ����ǰ���ݽ��ջ����¼�
		*/
		void initCurDataMB();
	}; // class TTcpHandler

} // namespace

/**
* @}
*/
#endif // TcpHandlerH