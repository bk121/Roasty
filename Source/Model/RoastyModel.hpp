#ifndef ROASTYMODEL_H
#define ROASTYMODEL_H
#include "RoastyModel.hpp"
#include<string>

class Bean {
  std::string name;
public:
  Bean(std::string const& name);
  std::string& getName();
  std::string const& getName() const;
};


class Ingredient{
  Bean bean;
  int amount;
public:
  Ingredient(Bean const& bean, int amount);
  Bean& getBean();
  Bean const& getBean() const;
  int const& getAmount() const;
  void setAmount(int amount);
};

// Struct definition for an ingredient list node in a linked list. This implementation allows
// for the fact that a roast can have 0-n ingredients, and so the ingredients ptr in the class
// Ingredient can be null for 0, and a node can be added/removed for any number of ingredients.
struct IngredientListNode{
  IngredientListNode(Ingredient const& ingredient);
  Ingredient ingredient;
  IngredientListNode* next = nullptr;
};

// Since an event value is optional, it's best implemented as a ptr within the class Event to
// a separate class.
class EventValue{
  long event_value;
public:
  EventValue(long event_value);
  long const& getValue() const;
  void setValue(long new_event_value);
};


class Event{
  std::string event_type;
  EventValue* event_value_ptr;
  long timestamp;
public:
  Event(std::string const& event_type, long timestamp, EventValue* event_value_ptr = nullptr);

  // Event needs a destructor because when an event is removed, a dynamically allocated
  // event value will also need to be removed. 
  Event& operator=(Event const& other);
   Event(Event const& other);
  ~Event();
  
  // Function returns true if an Event has an event value.
  bool hasValue() const;
  long& getTimestamp();
  long const& getTimestamp() const;
  std::string& getType();
  std::string const& getType() const;
  EventValue*& getValue();
  EventValue const* const& getValue() const;
};

// Struct definition for an event list node in a linked list. This implementation allows
// for the fact that a roast can theoretically have 0-n events, and so the events ptr in the class
// Event can be null for 0, and a node can be added/removed for any number of events.
struct EventListNode {
  Event event;
  EventListNode* next = nullptr;
  EventListNode(Event const& event);
};
  
		      


class Roast{
  long timestamp;
  EventListNode* events = nullptr;
  IngredientListNode* ingredients = nullptr;
public:
  Roast(long timestamp);
  // Roast needs a destructor because when a roast is removed, the dynamically allocated
  // linked lists for events and ingredients will also need to be removed.
  Roast& operator=(Roast const& other);
  Roast(Roast const& other);
  ~Roast();

  // Even though a timestamp uniquely identifies a roast and therfore shouldn't be changed,
  // I have included a non-const getter function for timestamp in case a timestamp was
  // incorrectly entered.
  long& getTimestamp();
  long const& getTimestamp() const;
  // function takes in an integer and outputs the number-to-last ingredient added.
  // eg. if number = 5, then the 5th to last ingredient added will be returned.
  Ingredient& getIngredient(int number);
  Ingredient const& getIngredient(int number) const;
  // function takes in an integer and outputs the number-to-last event added.
  // eg. if number = 5, then the 5th to last event added will be returned.
  Event & getEvent(int number);
  Event const& getEvent(int number)const;
  // cycles through linked list of events and returns event with matching timestamp to
  // timestamp parameter.
  Event & getEventByTimestamp(long timestamp);
  Event const& getEventByTimestamp(long timestamp) const;
  // cycles through linked list of ingredients and returns ingredient with matching
  // bean name to name parameter.
  Ingredient& getIngredientByBeanName(std::string const& name);
  Ingredient const& getIngredientByBeanName(std::string const& name) const;
  unsigned int getEventCount() const;
  int getIngredientsCount() const;
  void addIngredient(Ingredient const& ingredient);
  void removeIngredientByBeanName(std::string const& name);
  void addEvent(Event const& event);
  void removeEventByTimestamp(long Timestamp);
};

#endif
