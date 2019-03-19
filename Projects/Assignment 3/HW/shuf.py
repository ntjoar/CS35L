#!/usr/bin/python

import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, intRange, count, repeat, filename, args):
        if((filename == '-' or len(args) == 0) and intRange == None):
            self.lines = sys.stdin.readlines()
        elif(filename != None):
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()
        sys.tracebacklimit = 0

    def chooseline(self):
        return random.choice(self.lines)

def main():
    version_msg = '%prog 1.0'
    usage_msg = """%prog [OPTION]... FILE                                       
       or:  %prog -e [OPTION]... [ARG]...                                       
Write a random permutation of the input lines to standard output.               
                                                                                
Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-i", "--input-range",
                     action="store", dest="intRange", 
                     help="shuffles INTEGERS")
    parser.add_option("-n", "--head-count",
                      action="store", dest="count",
                      help="output at most COUNT lines")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat", default=False,
                      help="output lines can be REPEATED")
    options, args = parser.parse_args(sys.argv[1:])
    
    if options.intRange is not None:
        array = options.intRange.split("-")
        try:
            sys.tracebacklimit = 0
            for i in range(len(array)):
                array[i] = int(array[i])
        except:
            sys.tracebacklimit = 0
            parser.error("invalid input-range: {0}".
                        format(options.intRange))
        if len(array) != 2:
            sys.tracebacklimit = 0
            parser.error("invalid input-range: {0}".
                    format(options.intRange))
        if array[0] > array[1]:
            sys.tracebacklimit = 0
            parser.error("invalid input-range: {0}".
                    format(options.intRange))
    else:
        intRange = None
    if options.count is not None:
        try:
            sys.tracebacklimit = 0
            if options.count.isdigit() :
                count = int(options.count)
            else:
                count = int(options.count[0])
        except:
            sys.tracebacklimit = 0
            parser.error("invalid head-count: {0}".
                        format(options.count))
        if count < 0:
            sys.tracebacklimit = 0
            parser.error("negative count: {0}".
                        format(count))
    else:
        sys.tracebacklimit = 0
        count = None
    try:
        sys.tracebacklimit = 0
        repeat = bool(options.repeat)
    except:
        sys.tracebacklimit = 0
        parser.error("invalid option -- '{0}'".format(options.repeat))

    filename = None   
    if((len(args) == 1 and options.intRange is not None) or
        len(args) > 1):
        sys.tracebacklimit = 0
        parser.error("wrong number of operands")
    elif(len(args) != 0):
        sys.tracebacklimit = 0
        filename = args[0] 
    
    try:
        sys.tracebacklimit = 0
        shuffle = shuf(options.intRange, count, repeat, filename, args)
        #For the -i option
        if options.intRange is not None:
            array = options.intRange.split("-")
            array[0]=int(array[0])
            array[1]=int(array[1])
            printArray = []
            for x in range(array[0], array[1] + 1):
                printArray.append(x)
            random.shuffle(printArray)
            #Count exists
            if count is not None:
                if repeat:
                    for i in range(0, count):
                        random.shuffle(printArray)
                        print(printArray[0])
                else:
                    index = 0
                    for i in range(0, count):
                        print(printArray[index])
                        index += 1
                        if(index == (array[1] - array[0] + 1)):
                            index = 0
            # No count
            else:
                if repeat:
                    while True:
                        random.shuffle(printArray)
                        print(printArray[i])
                else:
                    print('\n'.join(map(str, printArray)))
        else:
            #Count exists
            if count is not None:
                #Repeat
                if repeat:
                    for i in range(0, count):
                        sys.stdout.write(shuffle.chooseline())
                else:
                    randLine = shuffle.lines
                    random.shuffle(randLine)
                    for i in range(0, count):
                        if i >= len(randLine):
                            break
                        sys.stdout.write(randLine[i])
            #No count
            else:
                #Repeat
                if repeat:
                    while True:
                        sys.stdout.write(shuffle.chooseline())
                else:
                    randLine = shuffle.lines
                    random.shuffle(randLine)
                    print(randLine)
                    for i in range(len(randLine)):
                        sys.stdout.write(randLine[i])
    except IOError as e:
        sys.tracebacklimit = 0
        errno = e.errno
        strerror = e.strerror
        parser.error('I/O error({0}): {1}'.format(errno, strerror))
        
if __name__ == '__main__':
    main()