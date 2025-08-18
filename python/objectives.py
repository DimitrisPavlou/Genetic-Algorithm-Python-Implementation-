# objective functions

def ones(x) : 
	return len(x)-sum(x)

def banana(x):
	return 100*(x[1] - x[0]**2)**2 + (1 - x[0])**2

def powel(x) : 
	return (x[0] + 10*x[1])**2 + 5*(x[2] - x[3])**2 + (x[1] - 2*x[2])**2 + 10*(x[0] - x[3])**2
