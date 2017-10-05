#ifndef TEventH
#define TEventH

#include <utility>
using namespace std;

namespace igame
{
	#define __TEVENT_TEMPLATE_IMPL(numOfArg)	\
	public: \
		typedef TEvent type; \
		typedef pair<TObject*, eventPrototype> eventType; \
		enum { argNum = numOfArg }; \
	private: \
		eventType _event; \
	public: \
		TEvent() { _event = make_pair<TObject*, eventPrototype>(0, 0); } \
		TEvent(TObject* obj, eventPrototype e) { _event = make_pair<TObject*, eventPrototype>(obj, e); } \
		TEvent(eventType& val):_event(val) { } \
		TEvent(TEvent& ref) { _event = (eventType)ref; } \
		void assign(TObject* obj, eventPrototype e) { _event = make_pair<TObject*, eventPrototype>(obj, e); } \
		bool valid() { return _event.first && _event.second; } \
		TEvent& operator = (eventType& e) { _event = e; return *this; } \
		operator eventType() { return _event; } \
        operator bool() { return valid(); } \
		bool operator == (TEvent& ref) { return this == &ref ? true : _event == (eventType)ref; } \
		bool operator == (eventType& e) { return _event == e; } \
		bool operator != (TEvent& ref) { return this == &ref ? false : _event != (eventType)ref; } \
		bool operator != (eventType& e) { return _event != e; }

	// TEvent with 10 arguments
	template <typename RT = void, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void, typename T6 = void, typename T7 = void, typename T8 = void, typename T9 = void, typename T10 = void>
	class TEvent
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);

		__TEVENT_TEMPLATE_IMPL(10)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7, T8 _8, T9 _9, T10 _10)
		{
            if (_event.first && _event.second)
                return (_event.first->*_event.second)(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10);
            else
                return RT();
		}
	};

	// TEvent with 9 arguments
	template <typename RT, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	class TEvent<RT, T1, T2, T3, T4, T5, T6, T7, T8, T9, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4, T5, T6, T7, T8, T9);

		__TEVENT_TEMPLATE_IMPL(9)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7, T8 _8, T9 _9)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3, _4, _5, _6, _7, _8, _9);
			else
				return RT();
		}
	};

	// TEvent with 8 arguments
	template <typename RT, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	class TEvent<RT, T1, T2, T3, T4, T5, T6, T7, T8, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4, T5, T6, T7, T8);
		
		__TEVENT_TEMPLATE_IMPL(8)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7, T8 _8)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3, _4, _5, _6, _7, _8);
			else
				return RT();
		}
	};

	// TEvent with 7 arguments
	template <typename RT, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	class TEvent<RT, T1, T2, T3, T4, T5, T6, T7, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4, T5, T6, T7);

		__TEVENT_TEMPLATE_IMPL(7)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3, _4, _5, _6, _7);
			else
				return RT();
		}
	};

	// TEvent with 6 arguments
	template <typename RT, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class TEvent<RT, T1, T2, T3, T4, T5, T6, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4, T5, T6);

		__TEVENT_TEMPLATE_IMPL(6)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3, _4, _5, _6);
			else
				return RT();
		}
	};

	// TEvent with 5 arguments
	template <typename RT, typename T1, typename T2, typename T3, typename T4, typename T5>
	class TEvent<RT, T1, T2, T3, T4, T5, void, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4, T5);

		__TEVENT_TEMPLATE_IMPL(5)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4, T5 _5)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3, _4, _5);
			else
				return RT();
		}
	};

	// TEvent with 4 arguments
	template <typename RT, typename T1, typename T2, typename T3, typename T4>
	class TEvent<RT, T1, T2, T3, T4, void, void, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3, T4);

		__TEVENT_TEMPLATE_IMPL(4)

		RT operator () (T1 _1, T2 _2, T3 _3, T4 _4)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3, _4);
			else
				return RT();
		}
	};

	// TEvent with 3 arguments
	template <typename RT, typename T1, typename T2, typename T3>
	class TEvent<RT, T1, T2, T3, void, void, void, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2, T3);

		__TEVENT_TEMPLATE_IMPL(3)

		RT operator () (T1 _1, T2 _2, T3 _3)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2, _3);
			else
				return RT();
		}
	};

	// TEvent with 2 arguments
	template <typename RT, typename T1, typename T2>
	class TEvent<RT, T1, T2, void, void, void, void, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1, T2);

		__TEVENT_TEMPLATE_IMPL(2)

		RT operator () (T1 _1, T2 _2)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1, _2);
			else
				return RT();
		}
	};

	// TEvent with 1 arguments
	template <typename RT, typename T1>
	class TEvent<RT, T1, void, void, void, void, void, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)(T1);

		__TEVENT_TEMPLATE_IMPL(1)

		RT operator () (T1 _1)
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)(_1);
			else
				return RT();
		}
	};

	// TEvent with 1 arguments
	template <typename RT>
	class TEvent<RT, void, void, void, void, void, void, void, void, void, void>
	{
	public:
		typedef RT (TObject::*eventPrototype)();

		__TEVENT_TEMPLATE_IMPL(0)

		RT operator () ()
		{
			if (_event.first && _event.second)
				return (_event.first->*_event.second)();
			else
				return RT();
		}
	};
} // namespace

/*
* @defgroup �¼������ĺ궨��
* @{
*/
/*
* @name �¼�������ǰ׺
* @{
* @code
	// ������ΪTMyEvent(void, int)���¼�
	typedef void (__EVENT_DECL TMyEvent)(void, int);
* @endcode
*/
#ifndef __EVENT_DECL
#define __EVENT_DECL	TObject::*
#endif

/**
* @}
*/ // TODO: end here

/*
* @name
* @{
*/

/**
* �¼�ӳ�䣬����ķ���ӳ�䵽�¼�ԭ��
* ˵��
* - eventType �¼����壬���¼��ɶ�TEvent<>��ģ������ػ�����
* - eventType::eventPrototype �¼�ԭ�ͣ���TEvent<>::eventPrototype����
* - _class Ҫӳ�䵽���¼��ķ����������࣬�������̳���(ֱ�ӻ���)TObject
* - funcptr ӳ�䵽���¼��ķ���
* @code
	// �¼�����
  	TEvent<void, int, int> TMyEvent;
    // ��Ӧ���¼�����
  	class TMyClass : public TMyObject
    {
    public:
    	// �¼�������
    	void myFunc(int a, int b)
        {
        	// empty
        }
    };
    // �¼�ԭ�ͣ���ͬ��typedef void (__EVENT_DECL eventPrototype)(int, int)
    TMyEvent::eventPrototype proto;
    // �¼�ӳ��
  	proto = EVENT_CAST(TMyEvent, TMyClass, myFunc);
* @endcode
* @see TEvent
*/
#define EVENT_CAST(eventType, _class, funcptr) static_cast<eventType::eventPrototype>(&_class::funcptr)
/**
* ���¼�������и�ֵ����������ǰ��(this)��ָ�������ҽӵ��¼����
* ˵��
* - _eventType �¼�����
* - _class ��ǰ�������
* - _obj ���ʵ��
* - funcptr �¼�������������
* @code
	// ��this->eventProcFunc���ӵ�BClass->OnMyEvent�¼���
    BClass->OnMyEvent = EVENT(TOnMyEvent, AClass, eventProcFunc);
* @endcode
* @see TEvent
*/
#define EVENT(_eventType, _class, _obj, funcptr) _eventType(_obj, EVENT_CAST(_eventType, _class, funcptr))

/**
* @}
*/ // TODO: end here
/**
* @}
*/ // TODO: end here
 
#endif