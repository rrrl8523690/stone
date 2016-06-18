from os import listdir
from os import walk
import os


def count_file_lines(file):
	cnt = 0
	with open(file, 'r') as f:
		for line in f:
			cnt += 1
	return cnt


nowdir = os.path.dirname(os.path.abspath(__file__))

res = 0
for (dirpath, dirnames, filenames) in walk(nowdir):
	for filename in filenames:
		if (filename.endswith((".h", ".hpp", ".cpp"))):
			res += count_file_lines(os.path.join(dirpath, filename))
print res