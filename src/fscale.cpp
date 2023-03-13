/* fscale
  Floating Point Autoscale Function V0.1
  Paul Badger 2007
  Modified from code by Greg Shakar

  This function will scale one set of floating point numbers (range) to another set of floating point numbers (range)
  It has a "curve" parameter so that it can be made to favor either the end of the output. (Logarithmic mapping)

  It takes 6 parameters

  originalMin - the minimum value of the original range - this MUST be less than origninalMax
  originalMax - the maximum value of the original range - this MUST be greater than orginalMin

  newBegin - the end of the new range which maps to orginalMin - it can be smaller, or larger, than newEnd, to facilitate inverting the ranges
  newEnd - the end of the new range which maps to originalMax  - it can be larger, or smaller, than newBegin, to facilitate inverting the ranges

  inputValue - the variable for input that will mapped to the given ranges, this variable is constrained to originaMin <= inputValue <= originalMax
  curve - curve is the curve which can be made to favor either end of the output scale in the mapping. Parameters are from -10 to 10 with 0 being
          a linear mapping (which basically takes curve out of the equation)

  To understand the curve parameter do something like this:

  void loop(){
  for ( j=0; j < 200; j++){
    scaledResult = fscale( 0, 200, 0, 200, j, -1.5);

    Serial.print(j, DEC);
    Serial.print("    ");
    Serial.println(scaledResult, DEC);
  }
  }

  And try some different values for the curve function - remember 0 is a neutral, linear mapping

  To understand the inverting ranges, do something like this:

  void loop(){
  for ( j=0; j < 200; j++){
    scaledResult = fscale( 0, 200, 200, 0, j, 0);

    //  Serial.print lines as above

  }
  }

*/

#include <cmath>

const float fscale(const float original_min, 
                   const float original_max,
                   const float new_begin,
                   const float new_end,
                   const float input_value,
                   const float curve) {
    float original_range = 0;
    float new_range = 0;
    float zero_ref_cur_val = 0;
    float normalized_cur_val = 0;
    float ranged_value = 0;
    float clipped_input_value = input_value;
    float clipped_curve = curve;
    bool inv_flag = 0;

    // condition curve parameter
    // limit range

    if (clipped_curve > 10) {
        clipped_curve = 10;
    }

    if (clipped_curve < -10) {
        clipped_curve = -10;
    }

    clipped_curve = (clipped_curve * -.1);  // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
    clipped_curve = pow(10, clipped_curve); // convert linear scale into lograthimic exponent for other pow function

    // Check for out of range inputValues
    if (clipped_input_value < original_min) {
        clipped_input_value = original_min;
    }

    if (clipped_input_value > original_max) {
        clipped_input_value = original_max;
    }

    // Zero Refference the values
    original_range = original_max - original_min;

    if (new_end > new_begin) {
        new_range = new_end - new_begin;
    } else {
        new_range = new_begin - new_end;
        inv_flag = 1;
    }

    zero_ref_cur_val = clipped_input_value - original_min;
    normalized_cur_val = zero_ref_cur_val / original_range; // normalize to 0 - 1 float

    // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
    if (original_min > original_max) {
        return 0;
    }

    if (inv_flag == 0) {
        ranged_value = (pow(normalized_cur_val, clipped_curve) * new_range) + new_begin;

    } else { // invert the ranges
        ranged_value = new_begin - (pow(normalized_cur_val, clipped_curve) * new_range);
    }

    return ranged_value;
}
