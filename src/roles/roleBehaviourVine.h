
#ifndef ROLE_BEHAVIOUR_VINE_H
#define ROLE_BEHAVIOUR_VINE_H

#include "roleBehaviour.h"

class RoleBehaviourVine:public RoleBehaviour
{
    public:
    RoleBehaviourVine();

    void loop(); // handle neighbour relations in here
};

#endif