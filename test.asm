%include "macro.inc"


begin


def fact
	_uif _ax,>,0
		_sub _bx,_ax,1
		call1 _bx,fact,_bx
		_mul _ax,_bx
	else
		_mov _ax,1
	end
end



call1 _ax,fact,20
_uprint _ax


end
