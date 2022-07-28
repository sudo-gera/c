from h import *
nums=[]
b=1
while ((c:=stdin.read(1))):
	if (c.isdigit()):
		if (b):
			nums.append('')
		nums[len(nums)-1]+=c;
		b=0;
	else:
		b=1;
nums=[''.join(w) for w in permutations(nums)]
print(max(nums))
