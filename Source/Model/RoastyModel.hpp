#ifndef ROASTYMODEL_H
#define ROASTYMODEL_H
#include "RoastyModel.hpp"
#include<string>

class Bean {
public:
  std::string const name;
  //friend
public:
  Bean(std::string name);
  Bean();
  std::string getName() const;
};


class Ingredient{
public:
  Bean bean;
  //friend
  int amount;
public:
  Ingredient(Bean bean, int amount);
  Ingredient();
  Bean getBean() const;
  int getAmount() const;
  void setAmount(int amount);
};

struct IngredientListNode{
  Ingredient ingredient;
  IngredientListNode* next = nullptr;
  IngredientListNode(Ingredient const& ingredient);
};


class EventValue{
  long event_value;
public:
  EventValue(long event_value);
  EventValue();
  EventValue(EventValue const&);
  long getValue() const;
  void setValue(long new_event_value);
};


class Event{
public:
  std::string event_type;
  EventValue* event_value_ptr;
  long timestamp;
  //friend Event& Roast::getEventByTimestamp(long timestamp) const;
public:
  Event(std::string event_type, long timestamp, EventValue* event_value_ptr = nullptr);


  Event& operator=(Event const& other);
  Event(Event const& other);
  //  ~Event();
  

  bool hasValue() const;
  long getTimestamp() const;
  std::string getType() const;
  EventValue* getValue() const;  
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
  Roast();

  Roast& operator=(Roast const& other);
  Roast(Roast const& other);
  //~Roast();

  long getTimestamp() const;
  Ingredient const& getIngredient(int number) const;
  Ingredient& getIngredient(int number);
  Event const& getEvent(int number)const;
  Event & getEvent(int number);
  Event const& getEventByTimestamp(long timestamp) const;
  Event & getEventByTimestamp(long timestamp);
  unsigned int getEventCount() const;
  int getIngredientsCount() const;
  Ingredient getIngredientByBeanName(std::string name) const;
  
  void addIngredient(Ingredient ingredient);
  void removeIngredientByBeanName(std::string name);
  void addEvent(Event event);
  void removeEventByTimestamp(long Timestamp);
};



#endif
