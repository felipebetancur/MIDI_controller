#ifndef MIDI_CONTROL_ELEMENT_h
#define MIDI_CONTROL_ELEMENT_h

#include "MIDI_Element.h"

class MIDI_Control_Element : public MIDI_Element
{
public:
  MIDI_Control_Element() // Constructor
  {
    if (first == nullptr)
      first = this;
    previous = last;
    if (previous != nullptr)
      previous->next = this;
    last = this;
    next = nullptr;
  }
  ~MIDI_Control_Element()
  {
    if (previous != nullptr)
      previous->next = next;
    if (this == last)
      last = previous;
    if (next != nullptr)
      next->previous = previous;
    if (this == first)
      first = next;
  }
  virtual void refresh() {}              // Check if the state or value of the control has changed since last refresh, if so, send MIDI event
  virtual void average(size_t length) {} // Use the average of multiple samples of analog readings
  virtual void map(int (*fn)(int)) {}    // Change the function pointer for analogMap to a new function. It will be applied to the raw analog input value in Analog::refresh()

  MIDI_Control_Element *getNext()
  {
    return next;
  }
  static MIDI_Control_Element *getFirst()
  {
    return first;
  }

protected:
  MIDI_Control_Element *next = nullptr, *previous = nullptr;

  static MIDI_Control_Element *last;
  static MIDI_Control_Element *first;
};

#endif // MIDI_CONTROL_ELEMENT_h