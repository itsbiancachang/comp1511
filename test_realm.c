// Assignment 2 19T2 COMP1511: Castle Defense
// test_realm.c
//
// This file allows you to automatically test the functions you
// implement in realm.c.
//
// This program was written by CHUNG CHI CHANG (z5224457)
// on 08/01/2019
//
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

#include "realm.h"

static void test_new_realm();
static void test_print_realm();
static void test_add_location();
static void test_new_tower();
static void test_new_enemy();
static void test_advance_enemies();
static void test_apply_damage();
static void test_apply_buff();

int main(void) {
    printf("\n================== Castle Defense Tests ==================\n");
    test_new_realm();
    test_print_realm();
    test_add_location();
    test_new_tower();
    test_new_enemy();
    test_advance_enemies();
    test_apply_damage();
    test_apply_buff();
}

////////////////////////////////////////////////////////////////////////
//                  Castle Defense Test Functions                     //
////////////////////////////////////////////////////////////////////////


// This function checks that a realm is actually being created.
static void test_new_realm() {
    printf(">> Testing new_realm\n");

    printf("... Creating new realm.\n");
    Realm realm = new_realm();

    printf("... Checking it is not null.\n");
    assert(realm != NULL);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will print out an empty realm - it should not crash.
static void test_print_realm() {
    printf(">> Testing print_realm\n");
    Realm realm = new_realm();

    printf("... This should show an empty realm - it should not crash.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations and try to print them.
static void test_add_location() {
    printf(">> Testing add_location.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "First_Location");
    add_location(realm, "Second_Location");
    add_location(realm, "Third_Location");

    printf("... This should show an realm with three extra locations.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}


// This function will add new towers and try to print them.
static void test_new_tower() {

    printf(">> Testing new_tower.\n");
    Realm realm = new_realm();

    printf("... Adding tower.\n");
    new_tower(realm, "Lair", "Tower_1", 10, 10);
    new_tower(realm, "Lair", "Tower_2", 20, 20);


    printf("... Adding Tower_1 after the lair with 10 power and 10 uses.\n");
    printf("... Adding Tower_2 after the lair with 20 power and 20 uses.\n");


    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);



}

// int new_enemy(Realm realm, char *location_name, char *name, int hp)
// This function will add new enemies and try to print them.
static void test_new_enemy() {

    printf(">> Testing new_enemy.\n");
    Realm realm = new_realm();

    printf("... Adding enemies.\n");
    new_enemy(realm, "Lair", "Enemy_1", 10);
    new_enemy(realm, "Lair", "Enemy_2", 20);
    new_enemy(realm, "Castle", "Enemy_3", 30);

    printf("... Adding Enemy_1 with 10hp and Enemy_2 with 20 hp at the lair.\n");
    printf("... Adding Enemy_3 with 30hp at the castle.\n");


    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);

}

// This function will advance enemies towards the castl and try to print them 
static void test_advance_enemies() {
    printf(">> Testing advance_enemies.\n");
    Realm realm = new_realm();

    
    printf("... Let's add some enemies first so we can test the advance_enemies function.\n");


    new_enemy(realm, "Lair", "Enemy_1", 10);
    new_enemy(realm, "Lair", "Enemy_2", 20);
    new_enemy(realm, "Castle", "Enemy_3", 30);
    print_realm(realm);
    printf("... all the enemies will move one location foward toward the castle.\n");
    printf("... but if moving beyond the castle, that enemy will be freed.\n");

    advance_enemies(realm); 
    print_realm(realm);

    printf("... Advance the enemies one location foward toward the castle.\n");
    


    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);

}

//This functuon will test apply_damage function
static void test_apply_damage() {
    //
    printf(">> Testing apply_damage.\n");
    Realm realm = new_realm();



    printf("...Adding tower.");
    new_tower(realm, "Lair", "Tower_1", 7, 2);
    printf("... Adding Tower_1 after the lair with 7 power and 2 uses.\n");


    printf("... Adding enemies under Tower_1.\n");
    new_enemy(realm, "Tower_1", "Enemy_1", 3);
    new_enemy(realm, "Tower_1", "Enemy_2", 8);
    

    printf("... Add Enemy_1 with 3hp and Enemy_2 with 8 hp at the Tower_1.\n");
    print_realm(realm);
    

    printf("...Let's do the damage now.\n");
    apply_damage(realm);
    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);


}

//int apply_buff(Realm realm, char *search_term, Buff buff, int amount){
static void test_apply_buff() {
    printf(">> Testing apply_buff.\n");
    Realm realm = new_realm();

    printf("... Let's add some enemies and towers first so we can test apply_buff()\n");

    printf("... Adding enemies.\n");
    new_enemy(realm, "Lair", "Enemy_1", 10);
    new_enemy(realm, "Lair", "Enemy_2", 10);
    new_enemy(realm, "Lair", "Enemy_3", 10);
    new_enemy(realm, "Castle", "Enemy_4", 20);
    printf("... Adding Enemy_1, Enemy_2, and Enemy_3 under the lair all with 10 hp.\n");
    printf("... Adding Enemy_4 under the caslte with 20 hp.\n");


    printf("... Adding towers.\n");
    new_tower(realm, "Lair", "Tower_1", 7, 2);
    new_tower(realm, "Lair", "SHOT_2", 5, 1);
    printf("... Adding Tower_1 after the lair with 7 power and 2 uses.\n");
    printf("... Adding SHOT_2 after the lair with 5 power and 1 use.\n");


    print_realm(realm);

    printf("... Start testing apply_buff() - BUFF_ENEMY_HP.\n");
    apply_buff(realm, "E?e*", BUFF_ENEMY_HP, 5);
    printf("... BUFF_ENEMY_HP, with the amount of 5, with the search term Ene*.\n");

    print_realm(realm);

    printf("... Tesing apply_buff() - BUFF_TOWER_POWER.\n");
    apply_buff(realm, "T*1", BUFF_TOWER_POWER, 2);
    printf("... BUFF_TOWER_POWER, with the amount of 2, with the searh term T*1.\n");

    print_realm(realm);

    printf("... Testing apply_buff() - BUFF_TOWER_USES.\n");
    apply_buff(realm, "S*", BUFF_TOWER_USES, 1);
    printf("... BUFF_TOWER_USES, with the amount of 1, with the searh term S*.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);

}
