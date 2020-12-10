for p1 in range(100):
	for k1 in range(100):
		for p2 in range(100):
			for k2 in range(100):
				if k1*17==p1*20:
					if p2*4==k2*5:
						if (p1+p2)*0.07==(p1+p2-k1-k2):
							print(p1+p2+k1+k2)