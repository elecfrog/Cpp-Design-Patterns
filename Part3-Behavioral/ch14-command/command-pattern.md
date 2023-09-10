## Command Design Pattern

command pattern is a method to process a sequence of commands should be executed by sequences.

For example,

- copy text -- `ctrl + c`

- paste text -- `ctrl + v`

- withdraw text -- `ctrl + z`

they all follow a pattern to execute a sequence of pressing and releasing keys.

Vulkan also has the concept of command buffers. It describes the sequence of rendering process.

In the example, it defines what is a command,

```cpp
struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;
};
```

Then it creates concrete class to explain what the commands executed.

```cpp
struct BankAccountCommand : Command {
    BankAccount &account;
    enum Action { deposit, withdraw } action;
    void call() override {
        switch (action) { /* ... */ }
    }
    void undo() override {
        switch (action) { /* ... */ }
    }
};
```

Finally, combines them into a sequence(vector), that is done!

```cpp
struct CompositeBankAccountCommands : Command {
    std::vector<BankAccountCommand> commands;
    void call() override { /* ... */ }
    void undo() override { /* ... */ }
};
```

So, the main idea is to bundle an array of actions by a particle sequences!