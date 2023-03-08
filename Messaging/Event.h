//---------------------------------------------------------------------------
#ifndef EventH
#define EventH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Event
{
private:
    String  m_Id;
public:
    Event(const String& id) : m_Id(id) {}

    __property  String Id = { read = m_Id };
};
//---------------------------------------------------------------------------
template <class T>
class OnChange : public Event
{
private:
    T m_Value;
public:
    OnChange(const String& id, const T& value)
    : Event(id)
    , m_Value(value)
    {
    }

    __property  T Value = { read = m_Value };
};
//---------------------------------------------------------------------------
#endif
