#!/usr/bin/env python3
import glob
import re

pattern = re.compile(r'^Temperature:\s*([0-9]+(?:\.[0-9]+)?)\s+deg\s+at\s+time:?\s*([0-9]+(?:\.[0-9]+)?)\s+sec')

out_file = "out.txt"
temps = []
lines_out = []

for fname in sorted(glob.glob('measured/measurements*.txt')):
    with open(fname, 'r') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                temp = float(match.group(1))
                time = match.group(2)
                temps.append(temp)
                lines_out.append(f"{temp}\t{time}")

with open(out_file, 'w') as f:
    f.write("TEMPERATURE\tTIME\n")
    for row in lines_out:
        f.write(row + "\n")

if temps:
    avg = sum(temps) / len(temps)
    print(f"Average temperature: {avg:.2f} ({len(temps)} samples

