q='01 12 23 30 04 15 26 37 45 56 67 74'
q=q.split()
q=[[int(w[0]),int(w[1])] for w in q]
q=[sorted(w) for w in q]
A='ABCDEFGH'
for w in q:
	print('Луч {0}{1} продлим до пересечения с окружностью в точке {0}_{1}. Покрасим отрезок {1}{0}_{1} в красный цвет.'.format(A[w[0]],A[w[1]]))
	print('Луч {0}{1} продлим до пересечения с окружностью в точке {0}_{1}. Покрасим отрезок {1}{0}_{1} в синий цвет.'.format(A[w[1]],A[w[0]]))
for w in q:
	for e in q:
		o=set(w)&set(e)
		if o:
			o=list(o)[0]
			print('Прямые {0}_{1}{1}_{0} и {2}_{3}{3}_{2} пересекаются в точке {4}, и однозначно задают плоскость. В этой плоскости точки {0}_{1}, {1}_{0}, {2}_{3}, {3}_{2} лежат на одной окружности. Её хорды пересекаются в точке {4}, следовательно {0}_{1}{4} * {4}{1}_{0} = {2}_{3}{4} * {4}{3}_{2} ')