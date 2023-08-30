#include "PersonBuilder.h"

PersonAddressBuilder PersonBuilder::lives() {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilder::works()
{
  return PersonJobBuilder{ person };
}

