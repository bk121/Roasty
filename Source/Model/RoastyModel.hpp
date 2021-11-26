#ifndef ROASTYMODEL_H
#define ROASTYMODEL_H
#include "RoastyModel.hpp"
#include<string>

class Bean {
  std::string name;
public:
  Bean(std::string name);
  std::string& getName();
  std::string const& getName() const;
};


class Ingredient{
  Bean bean;
  int amount;
public:
  Ingredient(Bean bean, int amount);
  Bean& getBean();
  Bean const& getBean() const;
  int& getAmount();
  int const& getAmount() const;
  void setAmount(int amount);
};


struct IngredientListNode{
  IngredientListNode(Ingredient const& ingredient);
  Ingredient ingredient;
  IngredientListNode* next = nullptr;
};


class EventValue{
  long event_value;
public:
  EventValue(long event_value);
  long& getValue();
  long const& getValue() const;
  void setValue(long new_event_value);
};


class Event{
  std::string event_type;
  EventValue* event_value_ptr;
  long timestamp;
public:
  Event(std::string event_type, long timestamp, EventValue* event_value_ptr = nullptr);


  Event& operator=(Event const& other);
   Event(Event const& other);
  ~Event();
  

  bool hasValue() const;
  long& getTimestamp();
  long const& getTimestamp() const;
  std::string& getType();
  std::string const& getType() const;
  EventValue*& getValue();
  EventValue* const& getValue() const;
};

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

  Roast& operator=(Roast const& other);
  Roast(Roast const& other);
  ~Roast();

  long& getTimestamp();
  long const& getTimestamp() const;
  Ingredient& getIngredient(int number);
  Ingredient const& getIngredient(int number) const;
  Event & getEvent(int number);
  Event const& getEvent(int number)const;
  Event & getEventByTimestamp(long timestamp);
  Event const& getEventByTimestamp(long timestamp) const;
  Ingredient& getIngredientByBeanName(std::string name);
  Ingredient const& getIngredientByBeanName(std::string name) const;
  unsigned int getEventCount() const;
  int getIngredientsCount() const;
  void addIngredient(Ingredient ingredient);
  void removeIngredientByBeanName(std::string name);
  void addEvent(Event event);
  void removeEventByTimestamp(long Timestamp);
};

#endif
