// main.cpp 
#include <iostream>
#include <cstdint>

// importing the math module 
  
import math; 
import reg;


  


volatile uint32_t fake_reg = 1024;

Register<&fake_reg> myreg;

int main() 
{ 
    // calling the add function from the math module 
    int result = add(3, 5); 
  
    // calling the multiply function from the math module 
    result = multiply(2, 4);
    result = scale<int, 4>(result);
    myreg.field1.set(1);

    std::cout << "result is :" << fake_reg << std::endl;
    return 0; 
}