## Overview

This document is mainly for my own use, so I do not have to spam comments inside my code to remember stuff.
It covers my reasoning behind writing code the way I have.

## IComponentList and ComponentList

So the class IComponentList exists to allow polymorphism for the lists in ComponentManager. It lets us store shared
pointers to objects of IComponentList, which will then be ComponentList<T>. This lets us store different underlying T's,
since just having the one ComponentList<T> definition would allow for only one underlying type, or we would have to
specify T, U, V, W.... for each type.

ComponentList maintains a vector of the Component it holds. Functions are provided to insert, remove Components, as well
as other utility functions.

## Managers

### EntityManager

This class is used for managing entity ID creation, as well as managing the entity bit masks. A queue is used to reuse
any IDs of deleted Entities.

### ComponentManager

