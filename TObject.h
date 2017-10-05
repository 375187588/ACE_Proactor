/*
* �����������
* �ڴ˻�����ʵ�ֶ�̬�¼�����
*/

#ifndef TObjectH
#define TObjectH

/**
* @defgroup �궨��
* @{
*/
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include <windows.h>


#ifdef __BORLANDC__
#ifdef __DLL__
#define __EXPORT__  __declspec(dllexport)
#else
#define __EXPORT__  __declspec(dllimport)
#endif
#else
#ifdef _DLL
#define __EXPORT__  __declspec(dllexport)
#else
#define __EXPORT__  __declspec(dllimport)
#endif
#endif

#ifndef _DEBUG
#define __ALWAYS_INLINE	inline
#else
#define __ALWAYS_INLINE
#endif


/// �ṹ�쳣ָ�룬�˴�ʡ��
#define DECL_EXCEPTION_POINTERS()
#define ASSERT(x)
#define __TRY try
#define __EXCEPT() \
	catch(...) \
	{ }


/**
* @name ���Զ����
* @{
*/
#define INIT_PROPERTY(name, val)    m_##name = (val);

#define INIT_PROP(name, val)    INIT_PROPERTY(name, val)

#define DECL_PROPERTY(type, property)						\
	private:												\
		/**������ */										\
		type	m_##property;								\
	public:													\
		/** ���Ե�set���� */								\
		void set##property(type value)						\
		{													\
			if ( m_##property != value ) m_##property = value;\
		}													\
		/** ���Ե�get���� */								\
		type get##property()								\
		{													\
			return m_##property;								\
		}

#define DECL_PROP(type, property) DECL_PROPERTY(type, property)

#define DECL_PROPERTY_RO(type, property)					\
	private:												\
		/**������ */										\
		type	m_##property;								\
	private:												\
		/** ���Ե�set���� */								\
        void set##property(type value)						\
		{													\
			if ( m_##property != value ) m_##property = value;\
		}													\
    public:													\
		/** ���Ե�get���� */								\
		type get##property()								\
		{													\
			return m_##property;								\
		}

#define DECL_PROP_RO(type, property) DECL_PROPERTY_RO(type, property)

#define DECL_LOCK_PROPERTY(type, property)					\
	private:												\
		/**�����ٽ����������� */							\
		TLockVar<type>	m_##property;						\
	public:													\
		void set##property(type value)						\
		{													\
			if ( m_##property != value ) m_##property = value;\
		}													\
		type get##property()								\
		{													\
			return m_##property;								\
		}

#define DECL_LOCK_PROP(type, property) DECL_LOCK_PROPERTY(type, property)

#define DECL_LOCK_PROPERTY_RO(type, property)				\
	private:												\
		/**��ֻ���Ĵ��ٽ����������� */						\
		TLockVar<type>	m_##property;						\
	private:												\
        void set##property(type value)						\
		{													\
			if ( m_##property != value ) m_##property = value;\
		}													\
    public:													\
		type get##property() const							\
		{													\
			return m_##property;								\
		}

#define DECL_LOCK_PROP_RO(type, property) DECL_LOCK_PROPERTY_RO(type, property)

#define DECL_PROPERTY_INT(type, property)					\
	private:												\
		/**��˽������ */									\
		##type	m_##property;								\
															\
		void set##property(type value)						\
		{													\
			if ( m_##property != value ) m_##property = value;\
		}													\
                                                            \
		##type& get##property()								\
		{													\
			return m_##property;								\
		}

#define DECL_PROP_INT(type, property)   DECL_PROPERTY_INT(type, property)

// property proxy
#define DECL_PROPERTY_PROXY(type, prop, dstobj, prototype)			\
	public:															\
		/**�����Դ����set���� */									\
		void set##prop(type value)									\
		{															\
			ASSERT(get##dstobj());									\
			get##dstobj()->set##prototype(value);					\
		}															\
		/** ���Դ����get����*/										\
		type get##prop()											\
		{															\
			ASSERT(get##dstobj());									\
			return get##dstobj()->get##prototype();					\
		}

#define DECL_PROP_PROXY(type, prop, dstobj, prototype)  DECL_PROPERTY_PROXY(type, prop, dstobj, prototype)

#define DECL_PROPERTY_PROXY_RO(type, prop, dstobj, prototype)		\
	public:															\
		/** ֻ�����Դ����get���� */								\
		type get##prop()											\
		{															\
			ASSERT(get##dstobj());									\
			return get##dstobj()->get##prototype();					\
		}

#define DECL_PROP_PROXY_RO(type, prop, dstobj, prototype)   DECL_PROPERTY_PROXY_RO(type, prop, dstobj, prototype)

#define DECL_PROPERTY_PROXY_WO(type, prop, dstobj, prototype)	\
	public: \
    	/** ֻд���Դ����get���� */							\
        void set##prop(type val) \
        { \
            get##dstobj()->set##prototype(val); \
        }

#define DECL_PROP_PROXY_WO(type, prop, dstobj, prototype) DECL_PROPERTY_PROXY_WO(type, prop, dstobj, prototype)

#define DECL_LOCK_PROPERTY_PROXY(type, prop, dstobj, prototype)	\
	private:													\
		/** �����ٽ����������Դ��� */							\
		TLockVar<type> m_##prop;									\
	public:														\
		/** �����ٽ����������Դ����set����*/					\
		void set##prop(type value)								\
		{														\
			if ( m_##prop != value )								\
			{													\
				ASSERT(get##dstobj());							\
				get##dstobj()->set##prototype(value);			\
				m_##prop = get##dstobj()->get##prototype();		\
			}													\
		}														\
		/** �����ٽ����������Դ����get����*/					\
		type get##prop()										\
		{														\
			return get##dstobj()->get##prototype();				\
		}

#define DECL_LOCK_PROP_PROXY(type, prop, dstobj, prototype) DECL_LOCK_PROPERTY_PROXY(type, prop, dstobj, prototype)


#define DECL_LOCK_PROPERTY_PROXY_CONDITION(type, prop, dstobj, prorotype, condition)	\
	private:																			\
		/** �����ٽ����������жϵ����Դ���*/											\
		TLockVar<type> m_##prop;															\
	public:																				\
		/** �����ٽ����������жϵ����Դ����set����*/									\
		void set##prop(type value)														\
		{																				\
			if ( m_##prop != value )														\
			{																			\
				if ( (condition) )														\
				{																		\
					ASSERT(get##dstobj());												\
					get##dstobj()->set##prorotype(value);								\
					m_##prop = get##dstobj()->get##prorotype();							\
				}																		\
				else																	\
				{																		\
					m_##prop = value;													\
				}																		\
			}																			\
		}																				\
		/** �����ٽ����������жϵ����Դ����get����*/									\
		type get##prop()																\
		{																				\
			return m_##prop;																\
		}

#define DECL_LOCK_PROP_PROXY_CONDITION(type, prop, dstobj, prorotype, condition)    DECL_LOCK_PROPERTY_PROXY_CONDITION(type, prop, dstobj, prorotype, condition)

#define DECL_PROPERTY_PROTECTED(type, property)				\
	protected:												\
		/**������ */										\
		type	m_##property;								\
	public:													\
		/** ���Ե�set���� */								\
		void set##property(type value)						\
		{													\
			if ( m_##property != value ) m_##property = value;\
		}													\
		/** ���Ե�get���� */								\
		type get##property()								\
		{													\
			return m_##property;								\
		}

#define DECL_PROP_PROTECTED(type, property) DECL_PROPERTY_PROTECTED(type, property)

/**
* @}
*/ // name

/**
* @}
*/ // defgroup
namespace igame
{
    /**
	* @class TObject
	* @brief ���ж���Ļ���
	*/
	class TObject
	{
	public:
		/// ctor
		TObject() { }

		/// dtor
		virtual ~TObject() { }
	};
};

#endif