# Flyweight Pattern

it is a pattern about space optimization. It aims to reduce memory usage when dealing with a large number of almost
similar objects, like player name dictionaries in Genshin Impact. This pattern shares common parts between objects,
thereby reducing memory footprint.

The name "Flyweight" is derived from boxing, where a "flyweight" is one of the lightest weight classes. 

## What I Learnt
- Using static map to store common data externally
- Idea of Range on Homogeneous collections to store data related to those ranges