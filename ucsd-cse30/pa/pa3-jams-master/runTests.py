#!/usr/bin/env python

# ******************************* PLEASE DO NOT MODIFY *******************************

import os

with open('testCases.txt') as fp:
    for line in fp:
        if not line.isspace():
            if line.startswith("TEST CASES FOR"):
                parsedLine = line.split()
                currFunction = parsedLine[-1]
                print("<----------------------------------------------------------------->")
                print("TESTING " + currFunction)
            else:
                parsedLine = line.split(",")
                if currFunction == "STRLEN:":
                    if len(parsedLine) != 1:
                        print("Error: strlen takes a single argument")
                    else:
                        res = os.system("./pa3-runner strlen " + parsedLine[0])
                elif currFunction == "STRCMP:":
                    if len(parsedLine) != 2:
                        print("Error: strcmp takes two arguments")
                    else:
                        os.system("./pa3-runner strcmp " + parsedLine[0] + " " + parsedLine[1])
                elif currFunction == "STRTRUNC:":
                    if len(parsedLine) != 2:
                        print("Error: strtrunc takes two arguments")
                    else:
                        os.system("./pa3-runner strtrunc " + parsedLine[0] + " " + parsedLine[1])
                elif currFunction == "STRREV:":
                    if len(parsedLine) != 3:
                        print("Error: strrev takes three arguments")
                    else:
                        os.system("./pa3-runner strrev " + parsedLine[0] + " " + 
                        (parsedLine[1] + " " + parsedLine[2]))
                elif currFunction == "PALINDROME:":
                    if len(parsedLine) != 1:
                        print("Error: palindrome takes a single argument")  
                    else:
                        os.system("./pa3-runner palindrome " + parsedLine[0])
                elif currFunction == "STRFIND:":
                    if len(parsedLine) != 2:
                        print("Error: strfind takes two arguments")
                    else:
                        os.system("./pa3-runner strfind " + parsedLine[0] + " " + parsedLine[1])
                else:
                    print("Error: unrecognized function")
print("<----------------------------------------------------------------->")
