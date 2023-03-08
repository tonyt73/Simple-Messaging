//---------------------------------------------------------------------------
#ifndef MessagingH
#define MessagingH
//---------------------------------------------------------------------------
#include <assert.h>
#include <list>
#include <memory>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
//---------------------------------------------------------------------------
namespace Messaging
{
using namespace std;

class Bus
{
friend class Registrar;
private:
    static unsigned int s_NextId;
    // Non-templated base class
    // Makes storing the templated objects easier
    class Subscription_
    {
    private:
        unsigned int            m_SubscriptionId;

    public:
                                Subscription_(unsigned int id) : m_SubscriptionId(id) {}
        virtual                ~Subscription_() {}

        __property unsigned int SubscriptionId = { read = m_SubscriptionId };
    };

    // Template specialization of a message subscription
    template <class T>
    class Subscription : public Subscription_
    {
    private:
        std::function<void (const T&)>  m_Handler;
    public:
        Subscription(const std::function<void (const T&)>& handler, unsigned int subscriptionId)
        : Subscription_(subscriptionId)
        , m_Handler(handler)
        {
        }

        void Execute(const T& message)
        {
            m_Handler(message);
        }
    };

    // the map of message subscription handlers
    typedef std::list<std::unique_ptr<Subscription_>> Subscriptions;
    typedef std::unordered_map<std::type_index, std::unique_ptr<Subscriptions>> SubscriptionsMap;
    static SubscriptionsMap* s_Handlers;

protected:
    // subscribe a handler to a templated message type
    template <class T>
    static unsigned int Subscribe(const std::function<void (const T&)>& handler)
    {
        if (s_Handlers == nullptr) {
            s_Handlers = new SubscriptionsMap();
        }

        auto& subscriptions = (*s_Handlers)[typeid(T)];
        if (subscriptions == nullptr) {
            // add a new subscriptions list to the type handlers list
            subscriptions = make_unique<Subscriptions>();
            (*s_Handlers)[typeid(T)] = std::move(subscriptions);
        }

        // add the handler to the subscriptions list for the type and assign a new id
        auto subscription = make_unique<Subscription<T>>(handler, ++s_NextId);
        subscriptions->push_back(std::move(subscription));
        return s_NextId;
    }

    static void Unsubscribe(unsigned int subscriptionId);

public:
    // publish a message to all subscribers of the type
    template <class T>
    static void Publish(const T& message)
    {
        if (s_Handlers) {
            auto& subscriptions = (*s_Handlers)[typeid(T)];
            if (subscriptions != nullptr) {
                for (const auto& subscription : *subscriptions) {
                    (reinterpret_cast<Subscription<T>*>(subscription.get()))->Execute(message);
                }
            }
        }
    }
};
//---------------------------------------------------------------------------
class Registrar
{
private:
    std::list<unsigned int> m_SubscriptionIds;

public:
                            Registrar();
                           ~Registrar();

    template <class T>
    void Subscribe(std::function<void (const T&)> handler) {
        m_SubscriptionIds.push_back(::Messaging::Bus::Subscribe(handler));
    }
    void Unsubscribe();
};
//---------------------------------------------------------------------------
} // namespace Messaging
//---------------------------------------------------------------------------
#endif

