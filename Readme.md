# Handle debouncing buttons

# Methods:

NoBounceButtons(); 	// default constructor
    
char create(unsigned char pin);  // create a new button and return id
 
unsigned char action(unsigned char id);	// check if button has been pressed

void reset(unsigned char id);	// reset button action

void check();	// call in main loop; contains all the important code
