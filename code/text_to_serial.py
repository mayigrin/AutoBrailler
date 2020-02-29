# -*- coding: utf-8 -*-
"""
Created on Mon Feb 24 14:29:20 2020

@author: mayan
"""
import serial
import time
import os.path

def remove_nonvalid(text):
    #Get set of valid chars
    valid = set()
    for i in range(65, 91):
        valid.add(chr(i))
    for i in range(97, 123):
        valid.add(chr(i))
    for i in range(48, 60):
        valid.add(chr(i))
    valid.add(" ")
    valid.add(",")
    valid.add(";")
    valid.add(":")
    valid.add(".")
    valid.add("!")
    valid.add("?")
    valid.add("'")
    valid.add(".")
    valid.add("-")
    valid.add("\n")

    nonvalid = set(text) - valid
    
    for char in nonvalid:
        text = text.replace(char, "")
    
    return text
    

def split_into_lines(text):
    new_text = ""
    lines = text.split("\n")
    counter = 0
    for line in lines:
        words = line.split()
        for word in words:
            if len(word) + counter > 30:
                new_text += "\n"
                counter = 0
                
            if len(word) + counter == 30:
                new_text += word + "\n"
                counter = 0
            else:
                new_text += word + " "
                counter += len(word) + 1
    return new_text+"\n"

def process_file(f):
    text = f.read()
    f.close()
    
    text = remove_nonvalid(text)
    text = split_into_lines(text)
    
    for char in text:
        yield char

print("")        

COMport='COM7'

print("Opening COM port...")
try:
    ser=serial.Serial(COMport,baudrate=9600,timeout=30)
except:
    ser.close()
    ser=serial.Serial(COMport,baudrate=9600,timeout=30)
print("Opened.")

print("")

time.sleep(2) #Needed because opening the port takes some time

ser.write(bytes([5])) #Make sure the arduino is doing what it should be

print("Checking Arduino Communication...")
if int(ser.read().hex(),16)!=None:
    print("Good")
else:
    print("BAD")

print("")

running=True
while(running):
    fileSet=False
    while not fileSet:
        try:
            filename=input("Enter filename (including extension), or EXIT: ")
            if filename=="EXIT":
                break
            else:
                f = open(os.path.join(os.path.dirname(__file__), os.pardir, filename))
                fileSet=True
                
                print("")
                print("Processing file...")
                time.sleep(1)
                print("Done processing!")
        except:
            print("Try again...")
            
    if not fileSet:
        print("Program ended by user.")
        break
    
    print("")
    
    try:
        print("Sending to printer...")
        for char in process_file(f):
            converted = str.encode(char)
            ser.write(converted)
            
        print("Sending complete!")
        
        print("")
        input("Press Enter to exit.")
        
        running = False
        
    except KeyboardInterrupt: #Try to gracefully turn off all the notes before stopping
        ser.read()
        print("Sending Terminated")
        
        
ser.close()




