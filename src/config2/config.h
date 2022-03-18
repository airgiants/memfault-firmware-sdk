
#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdio.h>

#include "roles/role.h"

#define ROLE_BEHAVIOUR 1
#define ROLE_AIRBOX_PRESSURE 2
#define ROLE_ATM_PRESSURE 4
#define ROLE_PRESSURE_FEEDBACK 8
#define ROLE_LIDAR 16

#define MAX_ROLES 5

static const char* roleNames[] = {"BEHAVIOUR","AIRBOX_PRESSURE","ATM_PRESSURE","PRESSURE_FEEDBACK","LIDAR",""};


#define NUM_NEIGHBOURS 4
#define NUM_OTHER_NODES 10

class Config
{
  
  public:
  int nodeNumber = -1;
  int creatureNumber;    // id number of this creature, used ot manage neighbour relations
  //uint8_t mac[6]={0};
  int neighbours[NUM_NEIGHBOURS] = {-1}; // creature numbers of neighbours in order LRFB (Left Right Front Back)
  int otherNodes[NUM_OTHER_NODES] = {-1}; // node numbers of other nodes in this creature, with implicit role requirements
  int numRoles = 0;
  Role*roles[MAX_ROLES]={NULL};

  float receivedActivation = 0.0; // workspace used in neighbour comms

  public:
  //Config( int _creature, uint8_t _mac[], int _neighbourL, int _neighbourR, int _neighbourF, int _neighbourB, int roles );
  Config();
  void read();
  void addRole(char*ptr);
  bool readNumbers(FILE *f,int* target, int num);
  
};

#endif