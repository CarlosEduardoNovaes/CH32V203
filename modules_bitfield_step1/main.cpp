// main.cpp 
#include <iostream>
#include <cstdint>

// importing the math module 
  

import reg;

static uint32_t fake_reg = 1024;

Register<&fake_reg> myreg;

int main() 
{ 
    // calling the add function from the math module 
    //int result = add(3, 5); 
  
    // calling the multiply function from the math module 
    //result = multiply(2, 4);
    //result = scale<int, 4>(result);
    //myreg.field0 = 1;
    //myreg.field0.set(1);
    //myreg.field1.set(2);
    //myreg.status.set(false);
    (
        myreg.field0.prepare(1) | myreg.field1.prepare(2) | myreg.status.prepare(false)
    ).apply();



    // std::cout << "result is :" << fake_reg << std::endl;
    // std::cout << "field0 :" << myreg.field0.get() << std::endl;
    // std::cout << "field1 :" << myreg.field1.get() << std::endl;
    // std::cout << "field2 :" << myreg.field2.get() << std::endl;
    // std::cout << "status :" << myreg.status.get() << std::endl;
    return 0; 
}