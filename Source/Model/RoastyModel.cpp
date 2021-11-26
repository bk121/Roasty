#include <string>
#include "RoastyModel.hpp"

using namespace std;

// Bean 

Bean::Bean(string name) : name(name){}
Bean::Bean(){}
string Bean::getName() const {return name;}

// Ingredient

Ingredient::Ingredient(Bean bean, int amount) : bean(bean), amount(amount){}
Ingredient::Ingredient(){}

Bean Ingredient::getBean() const {return bean;}
int Ingredient::getAmount() const {return amount;}
void Ingredient::setAmount(int new_amount){amount=new_amount;}

// IngredientListNode

IngredientListNode::IngredientListNode(Ingredient const& ingredient) : ingredient(ingredient){}



// EventValue

EventValue::EventValue(long event_value) : event_value(event_value){}
EventValue::EventValue(){}
EventValue::EventValue(EventValue const&){}
long EventValue::getValue() const {return event_value;}
void EventValue::setValue(long new_event_value){event_value=new_event_value;}



// Event

Event::Event(string event_type, long timestamp, EventValue* event_value_ptr)
  : event_type(event_type), timestamp(timestamp), event_value_ptr(event_value_ptr){}


Event& Event::operator=(Event const& other){
  this->event_type = other.event_type;
  this->event_value_ptr = other.event_value_ptr;
  this->timestamp = other.timestamp;
  return *this;
} 
Event::Event(Event const& other){
  *this = other;
}
/*Event::~Event(){
  if (event_value_ptr!=nullptr)
  delete event_value_ptr;
}
*/


bool Event::hasValue() const {
  if (event_value_ptr==NULL){
    return false;
  }
  return true;
}
string Event::getType() const {return event_type;}
EventValue* Event::getValue() const {return event_value_ptr;}
long Event::getTimestamp() const {return timestamp;}

// EventListNode


EventListNode::EventListNode(Event const& event) : event(event){}


// Roast

Roast::Roast(long timestamp) : timestamp(timestamp) {}


Roast&Roast::operator=(Roast const& other){
  this->timestamp = other.timestamp;
  this->events = other.events;
  this->ingredients = other.ingredients;
  return *this;
}
Roast::Roast(Roast const& other){
  *this = other;
}
/*Roast::~Roast(){
  while (ingredients!=nullptr){
    IngredientListNode* ptr = ingredients->next;
    delete ingredients;
    ingredients=ptr;
  }

  while (events!=NULL){
    EventListNode* ptr = events->next;
    delete events;
    events=ptr;
  }
}
*/
long Roast::getTimestamp() const {return timestamp;}

Ingredient& Roast::getIngredient(int number) {
  IngredientListNode* ingredient_node_ptr = ingredients;
  for (int i=0; i<number && ingredient_node_ptr!=nullptr; i++){
      ingredient_node_ptr = ingredient_node_ptr->next;
  }
  return ingredient_node_ptr->ingredient;
}


Ingredient const& Roast::getIngredient(int number) const {
  IngredientListNode* ingredient_node_ptr = ingredients;
  for (int i=0; i<number && ingredient_node_ptr!=nullptr; i++){
      ingredient_node_ptr = ingredient_node_ptr->next;
  }
  return ingredient_node_ptr->ingredient;
}


int Roast::getIngredientsCount() const {
  IngredientListNode* ingredient_node_ptr = ingredients;
  int count=0;
  while (ingredient_node_ptr!=nullptr){
    ingredient_node_ptr = ingredient_node_ptr->next;
    count++;
  }
  return count;
}

Event const& Roast::getEvent(int number)const {
  EventListNode* event_node_ptr = events;
  for (int i=0; i<number && event_node_ptr!=nullptr; i++){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

Event & Roast::getEvent(int number) {
  EventListNode* event_node_ptr = events;
  for (int i=0; i<number && event_node_ptr!=nullptr; i++){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}


Event const& Roast::getEventByTimestamp(long timestamp) const {
  EventListNode* event_node_ptr = events;
  while (event_node_ptr->event.timestamp!=timestamp && event_node_ptr!=nullptr){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

Event & Roast::getEventByTimestamp(long timestamp) {
  EventListNode* event_node_ptr = events;
  while (event_node_ptr->event.timestamp!=timestamp && event_node_ptr!=nullptr){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

unsigned int Roast::getEventCount() const {
  EventListNode* event_node_ptr = events;
  int count=0;
  while (event_node_ptr!=nullptr){
    event_node_ptr = event_node_ptr->next;
    count++;
  }
  return count;
}
Ingredient Roast::getIngredientByBeanName(string name) const {
    IngredientListNode* ingredient_node_ptr = ingredients;
  while (ingredient_node_ptr->ingredient.bean.name!=name){
    if (ingredient_node_ptr!=nullptr){

    }
  }
  return ingredient_node_ptr->ingredient;
}

void Roast::addIngredient(Ingredient ingredient){
  auto* nxt = ingredients;
  ingredients = new IngredientListNode(ingredient);
  ingredients->next = nxt;
}

void Roast::removeIngredientByBeanName(string name){
  IngredientListNode* node_before_ptr = ingredients;
  IngredientListNode* discardable_node = ingredients;
    while (discardable_node!=nullptr){
    if (discardable_node->ingredient.bean.name==name){
      if (discardable_node==ingredients){
        ingredients=discardable_node->next;
      }
      else{
	node_before_ptr->next = discardable_node->next;
      }
      delete discardable_node;
      return;
    }
    node_before_ptr = discardable_node;
    discardable_node = discardable_node->next;
  }
  return; 
    
}

void Roast::addEvent(Event event){
  auto* nxt = events;
  events = new EventListNode(event);
  events->next = nxt;
}

void Roast::removeEventByTimestamp(long Timestamp) {
  EventListNode* node_before_ptr = events;
  EventListNode* discardable_node = events;
  while (discardable_node!=nullptr){
    if (discardable_node->event.timestamp==Timestamp){
      if (discardable_node==events){
	events=discardable_node->next;
      }
      else{
	node_before_ptr->next = discardable_node->next;
      }
      delete discardable_node;
      return;
    }
    node_before_ptr = discardable_node;
    discardable_node = discardable_node->next;
  }
  return;  
  
}



