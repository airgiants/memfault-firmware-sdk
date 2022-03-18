#ifndef ROLE_BEHAVIOUR_H
#define ROLE_BEHAVIOUR_H

#include "role.h"

class RoleBehaviour:Role
{
    public:
    RoleBehaviour();

    virtual void loop();
};

#endif