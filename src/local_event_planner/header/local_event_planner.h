/**
 * @file local_event_planner.h
 *
 * @brief Provides functions for math. utilities
 */

#ifndef LOCAL_EVENT_PLANNER_H
#define LOCAL_EVENT_PLANNER_H

#include "../../utility/header/commonTypes.h"

namespace Coruh {
namespace local_event_planner {
/**
    @class local_event_planner
    @brief Provides Basic functions for various operations.
*/
class local_event_planner {
 public:
  /**
   * Adds two numbers.
   * @param a First operand.
   * @param b Second operand.
   * @return The sum of a and b.
   */
  static double add(double a, double b);

  /**
   * Subtracts the second number from the first.
   * @param a Minuend.
   * @param b Subtrahend.
   * @return The result of a - b.
   */
  static double subtract(double a, double b);

  /**
   * Multiplies two numbers.
   * @param a First operand.
   * @param b Second operand.
   * @return The product of a and b.
   */
  static double multiply(double a, double b);

  /**
   * Divides the first number by the second.
   * Throws std::invalid_argument if the second number is zero.
   * @param a Dividend.
   * @param b Divisor.
   * @return The result of a / b.
   * @throws std::invalid_argument If b is zero.
   */
  static double divide(double a, double b);


};
}
}

#endif // LOCAL_EVENT_PLANNER_H