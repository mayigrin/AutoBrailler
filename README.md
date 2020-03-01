# AutoBrailler
This repository contains code and for a device that sits on top of a brailler and allows it to function as a printer.

For more information on this project, go to the following link: [https://devpost.com/software/autobrailler](https://devpost.com/software/autobrailler)

HOW TO RUN BRAILLE PRINTER:

First, move any text file you want to print into this folder.
Then,
   
   If you have Windows:
   
      - Double-click on the '_braillePrinter_WINDOWS_' file 
      
      - If it doesn't work, do the following:
      
           - Using 'dir' to see what files and folders exist and 'cd <folder name>' to go into a folder, 
             navigate your way into this folder
             
           - If this is your first time printing something, run the following command:
                pip install --user pySerial
                
           - Run the following command:
                python code/text_to_serial.py

   If you don't have Windows:
      - Open up Terminal
      
      - Using 'ls' to see what files and folders exist and 'cd <folder name>' to go into a folder, 
        navigate your way into this folder
        
      - If this is your first time printing something, run the following command:
           pip install --user pySerial
           
      - Run the following command:
           python code/text_to_serial.py


Get your braille writer ready to print:

   - Move the carriage all the way to the end
   
   - Insert a sheet of braille paper and rotate the knobs in the direction of insertion until it stops 

Finally, follow the instructions that pop up!


