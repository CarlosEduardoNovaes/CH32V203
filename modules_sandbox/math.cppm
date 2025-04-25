// math.cppm - Module implementation file 
  
// module declaration for math module 
  
export module math; 
  
// function to add two integers
export template<class T>
T add(T a, T b) { return a + b; } 

export template<class T, int gain = 2>
T scale(T a) { return a * gain; } 
  
// function to multiply two integers 
export template<class T>
T multiply(T a, T b) { return a * b; }