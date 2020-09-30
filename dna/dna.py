import re
from sys import argv
from sys import exit
import csv

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

def main(database, sequence):
    with open(database, 'r') as data_file:
        data_reader = csv.reader(data_file)

        seque = next(data_reader)

        with open(sequence, 'r') as seq_file:
            seq_reader = csv.reader(seq_file)
            for line in seq_reader:
                seq = line[0]

            res = list()

            for code in seque:
                sub = code
                longest = max(re.findall('((?:' + re.escape(sub) + ')*)', seq), key = len)
                res.append(str(int(len(longest)/len(code))))

            for row in data_reader:
                if (row[1:]) == (res[1:]):
                    print(row[0])
                    return 0
            else:
                print("No match")
                return 0

main(argv[1], argv[2])