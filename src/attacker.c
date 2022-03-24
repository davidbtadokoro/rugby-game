// Standard headers
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  static position_t defender_position;
  static position_t previous_position = INVALID_POSITION;
  static direction_t best_direction = DIR_RIGHT;
  static size_t round = 1;

  // after 2 rounds, we spy the defender to decide the direction
  // that moves the attacker farther from the defender, while also
  // moving forward.
  if (round == 3) {
    defender_position = get_spy_position(defender_spy);
    if (defender_position.i >= attacker_position.i)
      best_direction = (direction_t) DIR_UP_RIGHT;
    else if (defender_position.i < attacker_position.i)
      best_direction = (direction_t) DIR_DOWN_RIGHT;
  }

  // if we hit an obstacle, we choose a random direction (without
  // moving backwards) to overcome it.
  if (equal_positions(attacker_position, previous_position)) {
    srand(clock());
    switch (rand() % 5) {
      case 0: {
        best_direction = (direction_t) DIR_UP;
        break;
      }
      case 1: {
        best_direction = (direction_t) DIR_UP_RIGHT;
        break;
      }
      case 2: {
        best_direction = (direction_t) DIR_RIGHT;
        break;
      }
      case 3: {
        best_direction = (direction_t) DIR_DOWN_RIGHT;
        break;
      }
      case 4: {
        best_direction = (direction_t) DIR_DOWN;
        break;
      }
      default:
        assert(false);
    }
  }

  previous_position = attacker_position;
  round++;

  return best_direction;
}

/*----------------------------------------------------------------------------*/
