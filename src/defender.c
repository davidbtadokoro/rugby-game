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
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

  // we don't spy on the attacker's position.
  UNUSED(attacker_spy);

  static position_t previous_position = INVALID_POSITION;
  static direction_t best_direction = DIR_UP;
  static bool dir_up = true;

  // the strategy revolves around simply moving up and down, so
  // the defender can cover more ground.
  if (equal_positions(defender_position, previous_position)) {
    if (dir_up) {
      best_direction = (direction_t) DIR_DOWN;
      dir_up = false;
    }
    else {
      best_direction = (direction_t) DIR_UP;
      dir_up = true;
    }
  }

  previous_position = defender_position;

  return best_direction;
}

/*----------------------------------------------------------------------------*/
