#include "config.h"
#include <cstring>

#include "esp_log.h"

#include "roles/roleBehaviourVine.h"

static const char* TAG = "config";
#define MAX_LINE_LENGTH 80
char line[MAX_LINE_LENGTH] = {0};

Config::Config()
{}

/*
Config::Config( int _creature, uint8_t  _mac[], int _roles )
{
  creatureNumber = _creature;
  //std::memcpy(mac, _mac, 6);

  roles = _roles;
}

Config::Config( int _creature, uint8_t _mac[], int _neighbourL, int _neighbourR, int _neighbourF, int _neighbourB, int _roles )
{
  creatureNumber = _creature;
  //std::memcpy(mac, _mac, 6);
  neighbours[0] = _neighbourL;
  neighbours[1] = _neighbourR;
  neighbours[2] = _neighbourF;
  neighbours[3] = _neighbourB;
  
  roles = _roles;
}
*/

/*
Sample file for a behaviour node

    3  #node number
    BEHAVIOUR AIRBOX_PRESSURE  #list of behaviours this node will perform
    0 1 2 3 4 #other nodes, in order: 3 chambers, airbox, atmosphere (only required for BEHAVIOUR)
    17  #creature number (only required for BEHAVIOUR)
    16 18 10 20 #neighbour creatures


Sample file for a simple pressure-feedback node

    1
    PRESSURE_FEEDBACK


*/

void Config::read()
{
    char *path = (char*) "/storage/config.cfg";

    FILE *f = fopen(path, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open config %s", path);
        return;
    }

    
    if( ! fgets(line, MAX_LINE_LENGTH, f))
    {
        ESP_LOGE(TAG, "config has no node number");
        return;
    }

    nodeNumber = atoi(line);

    if( ! fgets(line, MAX_LINE_LENGTH, f))
    {
        ESP_LOGE(TAG, "config has no roles");
        return;
    }

    // read the line of roles

    numRoles = 0;
	char delim[] = " ";

    

	char *ptr = strtok(line, delim);

	while(ptr != NULL)
	{
        addRole(ptr);
		//printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}

    if( roles && ROLE_BEHAVIOUR)
    {
        // read node numbers of other nodes in this creature
        if(  ! readNumbers(f, otherNodes, NUM_OTHER_NODES))
            return;

        // read our creature number
        if( ! fgets(line, MAX_LINE_LENGTH, f))
        {
            ESP_LOGE(TAG, "config has no creature number");
            return;
        }

        creatureNumber = atoi(line);

        // read neighbour creature numbers
        
        if(  ! readNumbers(f, neighbours, NUM_NEIGHBOURS))
            return;
    }

    fclose( f );
}

bool Config::readNumbers(FILE *f,int* target, int num)
{
    if( ! fgets(line, MAX_LINE_LENGTH, f))
    {
        ESP_LOGE(TAG, "readNumbers has no line");
        return false;
    }

    

	char delim[] = " ";

    int i = 0;

	char *ptr = strtok(line, delim);

	while(ptr != NULL)
	{
        if( i >= num )
        {
            ESP_LOGE(TAG, "readNumbers has too many numbers");
            return false;
        }

        int n = atoi(ptr);
        target[i++] = n;
		//pr intf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}

    return true;
}
void Config::addRole(char*ptr)
{
    

    int role = 0;

    for( int i = 0; strlen(roleNames[i]) > 0; i ++ )
    {
        if( 0 == strcmp(ptr,roleNames[i]))
        {
            //role = 1 << i;

            Role * r;

            switch(i)
            {
                case 0:
                    r = new RoleBehaviourVine();
                    break;
            }
            roles[numRoles++] = r;
        }
    }

    if( role == 0 )
        ESP_LOGE(TAG, "Bad role name %s", ptr);
    else
        roles |= role;
}