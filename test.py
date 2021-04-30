bin_opers_names={'.':'getattr','**':'pow','*':'mul','@':'matmul','/':'truediv','//':'floordiv','%':'mod','+':'add','-':'sub','<<':'lshift','>>':'rshift',
	'&':'band','^':'bxor','|':'bor','in':'contains','not_in':'not_in','is':'is','is_not':'is_not','<':'lt','<=':'le','>':'gt','>=':'ge','!=':'ne','==':'eq','and':'and','or':'or'}
un_opers_names={'await':'await','-':'neg','+':'pos','~':'inv','not':'not'}
sign_operators={}
for w in bin_opers_names:
	sign_operators[bin_opers_names[w]]={'sign':w,'name':bin_opers_names[w],'type':'binary'}
for w in un_opers_names:
	sign_operators[un_opers_names[w]]={'sign':w,'name':un_opers_names[w],'type':'unary'}
#print(sign_operators)


