#short py script to generate testing files

import random

out = "encoded.txt"
num_vals = 100000
minimum = 0
maximum = 10000

with open(out, 'w') as file:
  for _ in range(num_vals):
    file.write(f"{random.randint(minimum, maximum)}\n")
print('done')