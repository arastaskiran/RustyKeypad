

<pre>
  ....        ...   
 :::::........:::.  
   .:.        .:.    Welcome to the Rusty KeyPad Project
   .:          :.    ##################################################
  ..:          :.    
.::::..........:...  With this library, you can easily
   .:::........::..  use your custom-designed keypads in your project. 
   .:.:.       :.    With T9 keyboard support, you will be able to  
   .:. .::           write text on numeric keypads. You can use it as
   .:.   .::.        you wish in your Arduino projects,
   .:.      ::.      We can also contribute to the project
   .:         .:.    and make it more advanced.
    :           .:  
                  . 


+----------------+          +-----------------+
|     Arduino    |          |      Keypad     |
|  +----------+  |          |  +---+---+---+  |
|  |          |  |          |  | 1 | 2 | 3 |  |
|  |  USB     |  |          |  +---+---+---+  |
|  |  Port    |  |          |  | 4 | 5 | 6 |  |
|  |          |  |   ------>|  +---+---+---+  |
|  +----------+  |   |      |  | 7 | 8 | 9 |  |
+--------|-------+   |      |  +---+---+---+  |
         |           |      |  | * | 0 | # |  |
         |           |      |  +---+---+---+  |
         +-----------+      +-----------------+
</pre>

## Some theoretical information before starting the documentation.

### Basic Structure of a Numeric Keypad:
Numeric keypads typically consist of a matrix of buttons arranged in a 3x4 or 4x4 grid. Each button is located at the intersection of a row and a column. This arrangement is used to identify which button is pressed.

### Matrix Layout:
Rows: These are the horizontal lines of connections in the keypad.
Columns: These are the vertical lines of connections in the keypad.
Each button is positioned at the intersection of a row and a column. This setup allows for efficient button reading.

### Basic Operating Principle:

#### Connections:

The rows and columns of the keypad are connected to the digital pins of the Arduino. Typically, each row and column has its own pin.

#### Button Reading:

The Arduino reads the row and column connections. When a button is pressed, it creates a short circuit between the row and column where the button is located. The Arduino detects this short circuit to determine which button was pressed.

#### Row and Column Scanning:

The Arduino activates one row at a time while keeping all other rows inactive. It then reads which columns are active in that row. This process is repeated for all rows to determine which button is pressed.

## Below is an example of the internal structure of a 3x4 keypad.
The 'C' letters represent the columns, while the 'R' letters represent the rows. Generally, these keypads do not come with documentation, so you may need to use a measurement tool to identify the correct pins.
<pre>

           _I_        _I_          _I_
           o o---+    o o---+      o o--+
(R1)   ____|_____+____|_____+______|    +  
                 +          +           +
                 +          +           +  
                 +          +           +                                       
                 +          +           +   
           _I_   +    _I_   +      _I_  +   
           o o---+    o o---+      o o--+  
(R2)   ____|_____+____|_____+______|    +                                       
                 +          +           +   
                 +          +           +   
                 +          +           +  
                 +          +           +                                       
           _I_   +    _I_   +      _I_  +   
           o o---+    o o---+      o o--+   
(R3)   ____|_____+____|_____+______|    +  
                 +          +           +                                       
                 +          +           +   
                 +          +           +   
                 +          +           +  
           _I_   +    _I_   +      _I_  +                                       
           o o---+    o o---+      o o--+   
(R4)   ____|_____+____|_____+______|    +   
                 +          +           +  
                 +          +           +                                       
                 +          +           +   
                (C1)       (C2)        (C3)        
                                      
</pre>