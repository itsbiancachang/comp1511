// Assignment 2 19T2 COMP1511: Castle Defense
//
// This program was written by CHUNG CHI CHANG (z5224457)
// on 08/08/2019
//
// Version 1.0.0 (2019-07-22): Assignment released.
// Version 1.0.1 (2019-07-22): Fix minor style issue with print_tower.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "realm.h"


////////////////////////////////////////////////////////////////////////

// `struct realm` represents a realm, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// locations, though you may want to add other fields to it.
//
// You may need to add fields to struct realm.
struct realm {
    struct location *castle;
    struct location *lair;
};

// `struct location` represents a location, which could be a land,
// a tower, or a castle. Each of those places has a different type
// of information that this struct will need to store.
//
// You will need to add fields to struct location.
struct location {
    
    char name[MAX_NAME_LENGTH];
    int type; 
    int power;
    int uses; 
    //only for castle
    int hp;  
    Effect effect; 
    struct enemy *enemies;
    struct location *next;
    struct location *prev; 



};

// `struct enemy` represents an enemy, which will move through the
// realm (to each location). Towers can deal damage to it, and
// it can deal damage to the Castle.
//
// You will need to add fields to struct enemy.
struct enemy {

    char name[MAX_NAME_LENGTH];
    int max_hp;
    int current_hp;
    struct enemy *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Function prototypes for helper functions
static Location new_location(char *name);
static void print_tower(char *name, int power, int uses, Effect effect);
static void print_land(char *name);
static void print_castle(char *name, int defense);
static void print_enemy(char *name, int cur_hp, int max_hp);


// Add prototypes for any extra functions you create here.
static int match(char* search_term, char* name);

////////////////////////////////////////////////////////////////////////

// You need to implement the following 9 functions.
// In other words, write code to make the function work as described 
// in realm.h.

// Create a new realm, and return a pointer to it.
Realm new_realm(void) {
    
    struct realm *realm = malloc(sizeof(struct realm));
    realm->lair = new_location("Lair");
    realm->lair->type = TYPE_LAND; 
    realm->castle = new_location("Castle");
    realm->castle->type = TYPE_CASTLE; 
    realm->castle->hp = STARTING_CASTLE_HP; 

    if (realm->lair != NULL && realm->castle != NULL) {
        realm->lair->next = realm->castle;
    }

    return realm;
}

static Location new_location(char *name) {

    // TODO: Make this create a location and return a pointer to it.
    struct location *location = malloc(sizeof(struct location));
    strcpy(location->name, name);
    //defualt type 
    location->type = TYPE_LAND; 
    //default new for now 
    location->next = NULL;
    location->prev = NULL; 
    location->enemies = NULL;
    location->power = 0;
    location->uses = 0;
    location->hp = 0; 

    return location;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new location to the realm.
void add_location(Realm realm, char *name) {

    struct location *a_l = new_location(name);
    struct location *temp = realm->lair; 
    struct location *tail = realm->castle;

    struct location *current_node = temp; 
    while (temp->next != NULL) {
        current_node = temp; 
        temp = temp->next; 
    }

    current_node->next = a_l; 
    a_l->next = tail; 
    

}

// Print out the realm.
void print_realm(Realm realm) {


    struct location *temp = realm->lair;
    int there_are_enemies = 0; 
    struct enemy *enemy_temp = NULL;

    // Note: you should use the provided print functions here.
    while (temp != NULL) {
        there_are_enemies = 0;
        //find the head of the enemies by looping thru the location 
        if (temp->enemies != NULL) {
            there_are_enemies = 1; 
            enemy_temp = temp->enemies; //get the head of enemies 
        }
        
        //static void print_enemy(char *name, int cur_hp, int max_hp);
        if (temp->type == TYPE_LAND) {
            print_land(temp->name);
            
            if (there_are_enemies == 1) {
                while (enemy_temp != NULL) {
                    print_enemy(enemy_temp->name, enemy_temp->current_hp, enemy_temp->max_hp);
                    enemy_temp = enemy_temp->next; 
                }
        
            }
            
        } else if (temp->type == TYPE_TOWER) {
            
            print_tower(temp->name, temp->power, temp->uses, temp->effect);
            if (there_are_enemies == 1) {
                while (enemy_temp != NULL) {
                    print_enemy(enemy_temp->name, enemy_temp->current_hp, enemy_temp->max_hp);
                    enemy_temp = enemy_temp->next; 
                }
             
            }
        } else if (temp->type == TYPE_CASTLE) {
            print_castle(temp->name, temp->hp);
            if (there_are_enemies == 1) {
                while (enemy_temp != NULL) {
                    print_enemy(enemy_temp->name, enemy_temp->current_hp, enemy_temp->max_hp);
                    enemy_temp = enemy_temp->next; 
                }
               
            }
        }

        temp = temp->next;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new tower to the realm.
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses) {
    
    struct location *n_t = new_location(name);
    n_t->type = TYPE_TOWER;

    struct location *temp = realm->lair;
    struct location *ptr1 = NULL;  
    struct location *ptr2 = NULL; 
    
    int exist = 0; 
    while (temp != NULL) {
        
        if (strcmp(temp->name, prev_name) == 0) {
            exist = 1;
            ptr1 = temp; 
            ptr2 = temp->next; 
            break;
        }

        temp = temp->next; 
    }

    if (exist != 1) {
        return ERROR_NO_LOCATION; 
    } else if ((power < 1) || (uses < 1)) {
        return ERROR_INVALID_STAT; 
    } else {
        
        n_t->power = power; 
        n_t->uses = uses; 
        n_t->effect = 0;
        ptr1->next = n_t;
        n_t->next= ptr2; 

        return SUCCESS;
    }
}

// Add an enemy to the realm.
int new_enemy(Realm realm, char *location_name, char *name, int hp) {
    
    struct enemy *n_e = malloc(sizeof(struct enemy));
    struct location *temp = realm->lair; 
    //struct enemy *p_enemy = NULL; 
    //struct enemy *temp_enemy = NULL; 
    
    int exist = 0; 
    
    while (temp != NULL) {
        
        if (strcmp(temp->name, location_name) == 0) {
            exist = 1;
            break; 
        }
        temp = temp->next; 
    }

    //still store the value if invalid? 
    if (exist != 1) {
        return ERROR_NO_LOCATION; 
    } else if(hp < 1) {
        return ERROR_INVALID_STAT; 
    } else {

        //put the value in 
        
        strcpy(n_e->name, name);
        n_e->max_hp = hp; 
        n_e->current_hp = hp;
        n_e->next = NULL;


        //pointing to the head of the enemy first 
        //the first enemy
        if (temp->enemies == NULL) {

            temp->enemies = n_e; 
        } else {                          //head of the enemy node
            struct enemy *ptr_e = temp->enemies; 
            while (ptr_e->next != NULL) {
                ptr_e = ptr_e->next; 
            }

            //link the new enemy node after the last node
            ptr_e->next = n_e;
            n_e->next = NULL;
        }
        return SUCCESS;
    }
    
}

// Advance enemies towards the castle.
int advance_enemies(Realm realm) {

    struct location *forward_temp = realm->lair; //start of the realm
    struct location *current = NULL; //just a temp var to store the location of the previous location node
    struct location *backward_temp = NULL;

    //struct enemy *temp_e = NULL; //the head of the enemy in that particular location
    struct location *location_of_final_e = NULL; //the final location which has enemy 

    //create a doubly linked list (location)
    while (forward_temp != NULL) {
        forward_temp->prev = current;
        current = forward_temp; 
        backward_temp = forward_temp;
        forward_temp = forward_temp->next;
    }

    //find where the enemies are located in the final location which is the closest to the castle
    while (backward_temp != NULL) {
    
        if (backward_temp->enemies != NULL) {
            //getting the final location who enemy exists
            location_of_final_e = backward_temp;
            break;
        }
         
        backward_temp = backward_temp->prev; //move on to the next location
    }

    //let's move all the enemy one location forward 
    //in backward direction 
    int count_removed_enemies = 0;
    //struct enemy *head_of_enemy_castle = realm->castle->enemies;
    struct enemy *free_enemy = NULL;
    while (location_of_final_e != NULL) {
        //it's already at the castle, move forward, destroy them
        if (location_of_final_e->type == TYPE_CASTLE) {
            struct enemy *temp_enemy_at_castle = location_of_final_e->enemies;

            //count the enemy that is going to be removed 
            while (temp_enemy_at_castle != NULL) {
                count_removed_enemies++;
                temp_enemy_at_castle = temp_enemy_at_castle->next;
            }

            //let's free the enemy one by one
            temp_enemy_at_castle = location_of_final_e->enemies;
            while (temp_enemy_at_castle != NULL) {
                free_enemy = temp_enemy_at_castle;
                temp_enemy_at_castle = temp_enemy_at_castle->next;
                free(free_enemy);
            }

        } else {
            location_of_final_e->next->enemies = location_of_final_e->enemies; 
            location_of_final_e->enemies = NULL;
        }

        location_of_final_e = location_of_final_e->prev;
        
    }

    return count_removed_enemies;    
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply damage from the enemies at each tower to that tower.
int apply_damage(Realm realm) {

    struct location *temp = realm->lair; 
    struct enemy *temp_e = NULL; //head of the enemy in that location
     
    //struct enemy *prev_e = temp->enemies;
    struct enemy *enemy_to_free = NULL;

    int damaged_enemy = 0; 

    int count_enemy_total_hp = 0;

    //looping thru each location 
    while (temp != NULL) {
        //see if this location is a tower 
        //if there is a tower and there exists a list of enemy in that particular location 
        
            if ((temp->type == TYPE_TOWER) && (temp->enemies != NULL)) {
                //loop through the enemy list while tower is have uses 
                //and enemy still exisits 
                //damage it
                temp_e = temp->enemies;
            
                while ((temp->uses > 0) && (temp_e != NULL)) {
                    //damage it 
                    temp_e->current_hp -= temp->power;
                    //reudce that tower's num of uses by 1, if it did damage to an enemy
                    temp->uses -= 1; 

                    //if an enemy's current_hp is below zero, remove it from the list of enemies at that location 
                    if (temp_e->current_hp <= 0) {

                        //if affecting the first enemy (that is directly linked to the tower)
                        if (temp->enemies == temp_e) {
                            
                            enemy_to_free = temp_e; 
                            temp->enemies = temp_e->next;
                            temp_e = temp_e->next;
                            free(enemy_to_free);
                        }
                    } 
                    damaged_enemy++; 
               }


            //check if the tower uses all its power
            //if yes, turn it into a land
            if(temp->uses == 0)
            {
                temp->type = TYPE_LAND;
                temp->power = 0; 
            }
        } else if ((temp->type == TYPE_CASTLE) && (temp->enemies != NULL)) {
            //check if the location is a castle and has enemy 
            //if yes, add up all the enemy hp 
            //reduce castle's hp by enemy list's total hp in this castle location
            temp_e = temp->enemies;
            while (temp_e != NULL) {
                count_enemy_total_hp += temp_e->current_hp;

                temp_e = temp_e->next; 
            }

            realm->castle->hp -= count_enemy_total_hp;
        }
        
        temp = temp->next; 
    }
    
    
    return damaged_enemy;
    
}

// Destroy the realm, and free any associated memory.
void destroy_realm(Realm realm) {

    struct location *l = realm->lair;
    struct enemy *l_e = realm->lair->enemies;  

    struct enemy *free_e = NULL;
    struct location *free_l = NULL; 
    struct realm *free_r = NULL;

    //find the location of the ememy and free it first
    while (l != NULL) {
        //enemy list to free
        if (l_e != NULL) {
            free_e = l_e; 
            l_e = l_e->next; 
            free(free_e);
        }
        
        l = l->next;  
    }

    //default: pointing back to the head
    l = realm->lair;

    //free the location one by one
    while (l != NULL) {
        free_l = l;
        l = l->next; 
        free(free_l);
    }

    //free the realm struct: lair and castle
    free_r = realm; 
    free(free_r);

}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified buff to the relevant towers or enemies.
int apply_buff(Realm realm, char *search_term, Buff buff, int amount) {


    struct location *temp = realm->lair;
    struct enemy *temp_e = NULL; 

    struct enemy *enemy_to_free = NULL; 
    struct enemy *prev_e = temp->enemies;
    int count_match = 0;


    if ((buff == BUFF_TOWER_USES) || (buff == BUFF_TOWER_POWER)) {
        while (temp != NULL) {
            //we've reached the tower 
            if (temp->type == TYPE_TOWER) {
                if (match(search_term, temp->name) == 0) {
                    count_match += 1; 
                    
                    if (buff == BUFF_TOWER_POWER) {
                        temp->power += amount;

                        //convert into land if power < 0 
                        if (temp->power < 1) {
                            temp->type = TYPE_LAND;
                            temp->power = 0;
                            temp->uses = 0;
                        }

                    } else {
                        
                        temp->uses += amount;
                        //convert into land if uses < 0
                        if (temp->uses < 1) {
                            temp->type = TYPE_LAND;
                            temp->power = 0;
                            temp->uses = 0;
                        }
                    }
                }
            }

            temp = temp->next; 
        }

    } else if (buff == BUFF_ENEMY_HP) {
        
        //loop thru each location and see if there's enemy 
        while (temp != NULL) {
            //if there's enemy at this location, let's get in 
            if (temp->enemies != NULL) {
                //get the head of the enemy list in this location
                temp_e = temp->enemies; 
                
                //start looking at enemy's name and see if it matches
                while (temp_e != NULL) {
                    
                    if (match(search_term, temp_e->name) == 0) {
                        count_match += 1; 
                        temp_e->current_hp = (temp_e->current_hp + amount);
                    }
                    temp_e = temp_e->next; 
                }

                temp_e = temp->enemies;

                //if an enemy's current_hp is below zero, remove it from the list of enemies at that location 
                while (temp_e != NULL) {
                    
                    if (temp_e->current_hp <= 0) {
                     

                        //if affecting the first enemy that is directly linked to the tower 
                        if (temp->enemies == temp_e) {
                            
                            //cut this head of the enemy with the next enemy node
                            enemy_to_free = temp_e; 
                            temp->enemies = temp_e->next;
                            temp_e->next = NULL;
                        } else {
                          
                            enemy_to_free = temp_e;
                            prev_e->next = temp_e->next;  
                        } 
                    }

                    prev_e = temp_e;
                    temp_e = temp_e->next;

                    free(enemy_to_free);
                }     
            }

            temp = temp->next;
        }
    }
    return count_match;
}



////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified effect to each tower whose name matches the
// specified search term.
int apply_effect(Realm realm, char *search_term, Effect effect) {
    return 0;
}

////////////////////////////////////////////////////////////////////////

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.

static int match(char* search_term, char* name) {
    int i = 0;
    int j = 0;

    int search_term_char_remained = 0;
    int name_char_remained = 0;
    int star_amount;
    int special_search = 0;

    int pass = 0;

    //check if the search term contains special char
    for (int k = 0; k < strlen(search_term); k++) {
        if (search_term[k] == '?') {
            special_search = 1;
            break; 
        }

        if (search_term[k] == '*') {
            special_search = 2;
            break; 
        }
    }

    //no special_search char is contained 
    if (special_search == 0) {
        //see if it's of the same length 
        if (strlen(search_term) == strlen(name)) {
            int cmp_length = strlen(search_term);

            for (int k = 0; k < cmp_length; k++) {
                
                if (search_term[k] == name[k]) {
                    pass += 0;
                } else  {
                    pass += 1;
                }
            }  
        } else {
            pass += 1; 
        }

    } else if (special_search == 1 || special_search == 2) {

    //with ? and *
        while (i < strlen(search_term)) {
            
            if (search_term[i] == name[j]) {
                pass += 0;
                j++;
            } else if (search_term[i] == '?') {
             
                pass += 0;
                j++;
            } else if (search_term[i] == '*') {
              
                pass += 0;
                search_term_char_remained = strlen(search_term) - (i+1);
                name_char_remained = strlen(name) -  (i+1); 
                star_amount = name_char_remained - search_term_char_remained;
                j += (star_amount + 1);
            } else {
                pass += 1;
                break; 
            }
            
            i++;  
        }
    }

    return pass; 
}


////////////////////////////////////////////////////////////////////////
//                    Provided print functions                        //
//         NOTE: YOU SHOULD NOT MODIFY THE FOLLOWING FUNCTIONS        //
////////////////////////////////////////////////////////////////////////

static void print_tower(char *name, int power, int uses, int effect) {
    printf("%32s [pow: %3d | uses: %3d]", name, power, uses);
    if (effect == EFFECT_NONE) {
        printf(" {%c}", EFFECT_NONE_CHAR);
    } else if (effect == EFFECT_ICE) {
        printf(" {%c}", EFFECT_ICE_CHAR);
    } else if (effect == EFFECT_BOUNCE) {
        printf(" {%c}", EFFECT_BOUNCE_CHAR);
    }
    printf("\n");
}

static void print_land(char *name) {
    printf("%32s [____________________]\n", name);
}

static void print_castle(char *name, int defense) {
    printf("%32s [Castle Defenses: %3d]\n", name, defense);
}

static void print_enemy(char *name, int cur_hp, int max_hp) {
    printf("%40s [hp: %d/%d]\n", name, cur_hp, max_hp);
}

////////////////////////////////////////////////////////////////////////
//              End of provided print functions                        //
////////////////////////////////////////////////////////////////////////
