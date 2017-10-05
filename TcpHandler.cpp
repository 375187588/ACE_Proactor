#include "TcpHandler.h"

namespace igame
{
	TTcpHandler::TTcpHandler()
		:m_CurDataMB(0) // ��ʼ��
	{ }

	TTcpHandler::~TTcpHandler()
	{
		if (handle() != ACE_INVALID_HANDLE)
		{
			ACE_OS::closesocket(handle()); // �رվ��

#ifdef _DEBUG
			// ��ӡ������Ϣ
			ACE_TCHAR remoteAddrStr[128];
			
			m_ClientAddr.addr_to_string(remoteAddrStr, sizeof(remoteAddrStr) / sizeof(ACE_TCHAR));

			ACE_DEBUG((LM_INFO, ACE_TEXT("Disconnect from %s\n"), remoteAddrStr));
#endif
			// �ͻ��˶Ͽ�
			m_OnClientDisconnect(m_ClientAddr.get_ip_address(), m_ClientAddr.get_port_number());

			if (m_CurDataMB)
				m_CurDataMB->release();
		}
	}

	int TTcpHandler::send(unsigned int seq, const char* data, unsigned short dataSize)
	{
		ACE_Message_Block* dataMB = 0;
		
		ACE_NEW_NORETURN(dataMB, ACE_Message_Block(sizeof(unsigned int) + sizeof(unsigned short) + dataSize));
		
		short len = dataSize;

		dataMB->copy((const char *)&seq, sizeof(unsigned int)); // ����û�д���seq
		dataMB->copy((const char *)&len, sizeof(unsigned short));
		dataMB->copy((const char *)data, dataSize);
			
		int ret = m_Writer.write(*dataMB, dataMB->length()); // ����

		if (ret == -1)
			m_OnDataSendFailed(m_ClientAddr.get_ip_address(), m_ClientAddr.get_port_number(), seq, data, dataSize);
		else
			m_OnDataSendSucceeded(m_ClientAddr.get_ip_address(), m_ClientAddr.get_port_number(), seq, data, dataSize);

		return ret;
	}

	void TTcpHandler::addresses (const ACE_INET_Addr &remote_address,
						  const ACE_INET_Addr &local_address)
	{
		m_ClientAddr = remote_address; // ȡ�ÿͻ��˵�ַ
	}

	void TTcpHandler::open(ACE_HANDLE h, ACE_Message_Block& mb)
	{
		handle(h); // set handle
		
		if (m_Reader.open(*this) == -1) // �����
		{
			ACE_ERROR((LM_ERROR, ACE_TEXT("failed to open read handle %i\n"), errno));

			delete this;

			return;
		}

		if (m_Writer.open(*this) == -1) // ����д
		{
			ACE_ERROR((LM_ERROR, ACE_TEXT("failed to open write handle %i\n"), errno));

			delete this;

			return;
		}
		
		// �����ͻ��������¼�
		m_OnClientConnect(m_ClientAddr.get_ip_address(), m_ClientAddr.get_port_number(), this);

		initCurDataMB();
		
		m_Reader.read(*m_CurDataMB, m_CurDataMB->space()); // ������
	}

	void TTcpHandler::handle_read_stream(const ACE_Asynch_Read_Stream::Result& result)
	{
		ACE_Message_Block& mb = result.message_block();

		if (!result.success() || result.bytes_transferred() == 0) // no data or failed?
		{
			mb.release();

			delete this;
		}
		else
		{
			if (this->m_CurDataMB->length() < TCP_PACK_HEADER_SIZE) // try to read header info
			{
				this->m_Reader.read(*m_CurDataMB, m_CurDataMB->space());

				return ;
			}

			TTcpPackHeader* header = reinterpret_cast<TTcpPackHeader *>(this->m_CurDataMB->rd_ptr());
			ACE_Message_Block* dataMB = this->m_CurDataMB->cont();

			if (!dataMB)
			{
				ACE_NEW_NORETURN(dataMB, ACE_Message_Block(header->len));

				if (dataMB)
					this->m_CurDataMB->cont(dataMB);
				else
				{
					this->m_CurDataMB->release();

					ACE_DEBUG((LM_ERROR, ACE_TEXT("Failed to allocated: %i\n"), errno));

					delete this;

					return ;
				}
			}
			
			if (dataMB->length() == header->len)
			{
				// �ɹ���ȡ�����ݣ�
				m_OnDataReceive(m_ClientAddr.get_ip_address(), m_ClientAddr.get_port_number(), header->seq, dataMB->rd_ptr(), header->len);
				
				m_CurDataMB->release();

				initCurDataMB(); // ��һ������
				
				this->m_Reader.read(*m_CurDataMB, m_CurDataMB->space()); // next, try to get header

				return ;
			}
			
			this->m_Reader.read(*dataMB, dataMB->space()); // try to get data left
		}
	}

	void TTcpHandler::handle_write_stream(const ACE_Asynch_Write_Stream::Result& result)
	{
		if (result.success() && result.bytes_transferred() > 0) // ���ͳɹ�
		{
			ACE_Message_Block& mb = result.message_block();

#ifdef _DEBUG
			ACE_TCHAR addrStr[128];
			
			m_ClientAddr.addr_to_string(addrStr, sizeof(addrStr) / sizeof(ACE_TCHAR));
			
			ACE_DEBUG((LM_INFO, ACE_TEXT("Send to client: %s len:%i\n"), addrStr, result.bytes_transferred()));
			
			char* ptr = mb.rd_ptr();
			
#endif
			
			mb.release();
		}
	}

	void TTcpHandler::initCurDataMB()
	{
		ACE_NEW_NORETURN(m_CurDataMB, ACE_Message_Block(TCP_PACK_HEADER_SIZE, TCP_DATA_RECEIVE));
	}

} // namespace igame