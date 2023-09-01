# Prototype Pattern

Prototype Pattern, it is all about object copy. 

Instead of creating a totally new instance of an object, the main idea of prototyping is to create a "default" object previously. Then clone(deep copy) it, customized it.

## What I Learnt

### Why Use Prototype?

**Performance**: 

When an object requires a **time-consuming compilation** or database access during its creation.


**Unique instances with shared data**: 

Sometimes, you need objects that **share some common data** but also have individual differences.

### How to Implement Prototype?

In the example, it could combine builder method and factory method only if necessary. 

### Combines with Serialization/Deserialization

Using serialization / deserialization combines with prototype pattern. 

It will have both cloning and serialization / deserialization functionalities.


## Inspiration Future Work
- [ ] Prototypes(Primitive Objects) in the Sparrow Renderer