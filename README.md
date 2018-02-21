# Simple-Messaging
**A lightweight synchronous messaging/event system for Rad Studio C++ Builder using C++11**

##Overview
This is a simple messaging system designed for use with MVVM, MVC, MVP applications.
The goal was to make it easy to define new messages/events and to deliver them to 
multiple subscribers.

Messages/events are subscribed/published by templated types. This allows for subscribing to
only the messages you are interested in handling. It also means that there is no way to 
peek on all of the messages sent. A feature I had no use for.

Note: This implementation is not thread safe

##Usage

### Create a Custom Message
Simply define a new ```class``` with the data you would like to capture.
```c++
class MyMessage : public Event
{
private:
    int m_Value;
	bool m_Flag;
public:
    __fastcall MyMessage(const String& id, int value, bool flag)
    : Event(id)
    , m_Value(value)
	, m_Flag(flag)
    {
    }

    __property  int 	Value = { read = m_Value };
    __property  bool 	Flag  = { read = m_Flag  };
};
```

### Publish a message
Simply call ```Publish<T>() with an instantiation of your message type and data items set.
```c++
void Button1::OnClick()
{
	::Messaging::Bus::Publish(MyMessage("NumberBox1.Value.Changed", NumberBox1->Value, NumberBox1->Value > 10));
}

```
### Subscribe to handling a custom message
Simply call ```Subscribe<T>()``` with your custom message class and the function used to handle the message.
```c++
void Init()
{
	::Messaging::Bus::Subscribe<MyMessage>(HandleMyMessage);
}

void HandleMyMessage(const TMyMessage& message)
{
	// TODO: process the message
}
```
