# Observer Pattern

Getting notification when things happen.

Terminology:

- events and subscriptions
- signals and slots(Qt)

- observable => who wants to be notified (generating events)
- observer => who notify others 

## Events and subscriptions
Assume I am a youtuber, I uploaded video and other people subscribed me.

That is what happens in reality.

But in the Observer Pattern, the thing is I should hold a vector of observers.
And I should register the subscription for each observer.

The youtuber is observable. And subscribers are observers.

This is not instinctive with real world, but it does what Observer pattern does.

### Thread Safety
Considering that observers and observables may are in different threads.

Without any safe code, the data send to observers might have be changed while sending or inner looping.  

One solution is to directly using a lock.

## Signals & Slots
The lecturer does not foucsd on signals and slots pattern and he implement it in Boost.

I prefer to use Qt signals-slots