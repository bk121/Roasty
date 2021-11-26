#include <string>
#include "RoastyModel.hpp"

using namespace std;

// Bean 

Bean::Bean(string const& name) : name(name){}
string& Bean::getName() {return name;}
string const& Bean::getName() const {return name;}

// Ingredient

Ingredient::Ingredient(Bean const& bean, int amount) : bean(bean), amount(amount){}
Bean& Ingredient::getBean() {return bean;}
Bean const& Ingredient::getBean() const {return bean;}
int const& Ingredient::getAmount() const {return amount;}
void Ingredient::setAmount(int new_amount){amount=new_amount;}

// IngredientListNode

IngredientListNode::IngredientListNode(Ingredient const& ingredient) : ingredient(ingredient){}

// EventValue

EventValue::EventValue(long event_value) : event_value(event_value){}
long const& EventValue::getValue() const {return event_value;}
void EventValue::setValue(long new_event_value){event_value=new_event_value;}



// Event

Event::Event(string const& event_type, long timestamp, EventValue* event_value_ptr)
  : event_type(event_type), timestamp(timestamp), event_value_ptr(event_value_ptr){}


Event& Event::operator=(Event const& other){
  this->event_type = other.event_type;
  this->timestamp = other.timestamp;
  // if the Event being copied has an event value, it is (deep)copied
  if (other.event_value_ptr!=nullptr){
    this->event_value_ptr = new EventValue(other.event_value_ptr->getValue());
  }
  else {
    this->event_value_ptr = nullptr;
  }
  return *this;
} 

Event::Event(Event const& other){
  *this = other;
}

Event::~Event(){
  if (event_value_ptr!=nullptr)
  delete event_value_ptr;
}


bool Event::hasValue() const {
  if (event_value_ptr==NULL){
    return false;
  }
  return true;
}
long& Event::getTimestamp() {return timestamp;}
long const& Event::getTimestamp() const {return timestamp;}
string& Event::getType() {return event_type;}
string const& Event::getType() const {return event_type;}
EventValue* & Event::getValue() {return event_value_ptr;}
EventValue const* const& Event::getValue() const {return event_value_ptr;}


// EventListNode


EventListNode::EventListNode(Event const& event) : event(event){}


// Roast

Roast::Roast(long timestamp) : timestamp(timestamp) {}


Roast&Roast::operator=(Roast const& other){
  this->timestamp = other.timestamp;

  // any existing events are deleted prior to deep copying other's events.
  while (this->events!=nullptr){
    EventListNode* nxt = this->events->next;
    delete this->events;
    this->events = nxt;
  }
  // deep copying other's events.
  EventListNode* nxt = other.events;
  while (nxt!=nullptr){
    this->addEvent(nxt->event);
    nxt = nxt->next;
  }

  // any existing ingredients are deleted prior to deep copying other's ingredients.
  while (this->ingredients!=nullptr){
   IngredientListNode* nxt = this->ingredients->next;
   delete this->ingredients;
   this->ingredients = nxt;
  }
  // deep copying other's ingredients.
  IngredientListNode* nxtIn = other.ingredients;
  while (nxt!=nullptr){
    this->addIngredient(nxtIn->ingredient);
    nxtIn = nxtIn->next;
  }
  
  return *this;
}

Roast::Roast(Roast const& other){
 *this = other;
}

Roast::~Roast(){
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


long& Roast::getTimestamp() {return timestamp;}
long const& Roast::getTimestamp() const {return timestamp;}


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


Event & Roast::getEvent(int number) {
  EventListNode* event_node_ptr = events;
  for (int i=0; i<number && event_node_ptr!=nullptr; i++){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

Event const& Roast::getEvent(int number)const {
  EventListNode* event_node_ptr = events;
  for (int i=0; i<number && event_node_ptr!=nullptr; i++){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

Event & Roast::getEventByTimestamp(long timestamp) {
  EventListNode* event_node_ptr = events;
  while (event_node_ptr->event.getTimestamp()!=timestamp && event_node_ptr!=nullptr){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

Event const& Roast::getEventByTimestamp(long timestamp) const {
  EventListNode* event_node_ptr = events;
  while (event_node_ptr->event.getTimestamp()!=timestamp && event_node_ptr!=nullptr){
      event_node_ptr = event_node_ptr->next;
    }
  return event_node_ptr->event;
}

Ingredient& Roast::getIngredientByBeanName(string const& name) {
    IngredientListNode* ingredient_node_ptr = ingredients;
    while (ingredient_node_ptr->ingredient.getBean().getName()!=name){
    if (ingredient_node_ptr!=nullptr){

    }
  }
  return ingredient_node_ptr->ingredient;
}

Ingredient const& Roast::getIngredientByBeanName(string const& name) const {
    IngredientListNode* ingredient_node_ptr = ingredients;
    while (ingredient_node_ptr->ingredient.getBean().getName()!=name){
    if (ingredient_node_ptr!=nullptr){

    }
  }
  return ingredient_node_ptr->ingredient;
}

unsigned int Roast::getEventCount() const{
  EventListNode* event_node_ptr = events;
  unsigned int count=0;
  while (event_node_ptr!=nullptr){
    event_node_ptr = event_node_ptr->next;
    count++;
  }
  return count;
}


int Roast::getIngredientsCount() const{
  IngredientListNode* ingredient_node_ptr = ingredients;
  int count=0;
  while (ingredient_node_ptr!=nullptr){
    ingredient_node_ptr = ingredient_node_ptr->next;
    count++;
  }
  return count;
}

void Roast::addIngredient(Ingredient const& ingredient){
  auto* nxt = ingredients;
  ingredients = new IngredientListNode(ingredient);
  ingredients->next = nxt;
}

void Roast::removeIngredientByBeanName(string const& name){
  IngredientListNode* node_before_ptr = ingredients;
  IngredientListNode* discardable_node = ingredients;
  // condition makes sure loop doesn't exceed bounds of linked list if ingredient with
  // bean name passed in is not in list.
  while (discardable_node!=nullptr){
    if (discardable_node->ingredient.getBean().getName()==name){
      // special case of first item in list being removed sets data member ingredients to
      // point to second item in list.
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

void Roast::addEvent(Event const& event){
  auto* nxt = events;
  events = new EventListNode(event);
  events->next = nxt;
}

void Roast::removeEventByTimestamp(long Timestamp) {
  EventListNode* node_before_ptr = events;
  EventListNode* discardable_node = events;
  // condition makes sure loop doesn't exceed bounds of linked list if event with
  // timestamp passed in is not in list.
  while (discardable_node!=nullptr){
    if (discardable_node->event.getTimestamp()==Timestamp){
      // special case of first item in list being removed sets data member events to
      // point to second item in list.
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



