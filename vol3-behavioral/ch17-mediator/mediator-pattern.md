# Mediator Pattern

components may go in and out of a system at any time

- Chat Room
- Players in Genshin Impact
- [UE `UWorld` Class](https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Engine/UWorld/)

Issues:
Those references may go dead

Solution:
**have then all refer to some cent ral component that facilitates communication**

### Chat Room

In the example of Chat Room, objects communicate with each other by ChatRoom object, which is the mediator in this
situation.

```cpp
struct ChatRoom;
struct Person { ChatRoom *room{nullptr}; };
```

one person object may has many chat functions, speaking, personal messages, receiving...

But one person holds a `ChatRoom` pointer, person itself never modify this pointer unless initialized it.

Its change happens in

```cpp
void ChatRoom::join(Person *p) {
    string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);
    p->room = this;
    people.push_back(p);
}
```

while the person was added into the chat room.

In the case, person the instance may go in or quit, but ChatRoom is the mediator to hold and act as a channel to
communicate.

### Event Broker and Messages
Mediator could be a communication service center, it could support:
- Broadcast: it receives messages from one instance and broadcast other instances registered
- Multicast: it could cast messages to a group of objects by filtering them
- Single Point: it also could transmit messages from one instance to another instance

This example also implemented by using Qt signals-slots, it sends a message from player to coach by an intermediate object,
`Game`. It could also be seen as a global object. It was similar to the UWorld class in the unreal Engine.

